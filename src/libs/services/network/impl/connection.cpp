#include "services/network/connection.h"
#include <memory>
#include <QTcpSocket>
#include "services/network/Constants.h"
#include "services/network/message.h"
#include <QTimer>
#include <QMetaEnum>
#include <QTimerEvent>
#include <QThread>


// replace with move if is valid
static const int SECONDS_IN_MILLISECONDS = 1000;
static const int TIME_DROP_CONN = SECONDS_IN_MILLISECONDS * 30000;
static const int CONNECTION_ESTABLISHING_TIME = SECONDS_IN_MILLISECONDS * 3;

Connection::Connection(QTcpSocket*& socket, Owner owner) : _socket(socket), owner(owner)
{

    start = QDateTime::currentMSecsSinceEpoch();
    connect(this, &Connection::new_message_outgoing, this, &Connection::send);
    connect(this, &Connection::dropConnection, this, &Connection::deleteConnection, Qt::DirectConnection);
    connect(_socket, &QTcpSocket::stateChanged, this, &Connection::checkConnectonEstablishing);
    connect(_socket, &QTcpSocket::readyRead, this, &Connection::recieve);
    connect(this, &Connection::s_connectionEstablished, this, &Connection::send);
    dropConnectionTimer = 0;
    connectionEstablishingTimer = 0;

    isConnected();

#ifdef VERBOSE_STATES
    connect(_socket, &QTcpSocket::stateChanged, this, &Connection::connectionStateChanged);
#endif


}


void Connection::isConnected(){

    if (get_state() == QAbstractSocket::ConnectedState){
        if (connectionEstablishingTimer)
            killTimer(connectionEstablishingTimer);
        qDebug() << "Connection established";
    }

}


void Connection::setDropConnectionTimer(){

    dropConnectionTimer = startTimer(TIME_DROP_CONN);

}

void Connection::checkConnectonEstablishing(QAbstractSocket::SocketState socketState){


    switch(socketState){

    case QAbstractSocket::ConnectedState:

        startConnected = QDateTime::currentMSecsSinceEpoch();
        if (connectionEstablishingTimer)
            killTimer(connectionEstablishingTimer);

        qInfo("Connection successful established");
        emit s_connectionEstablished();
        break;


    case QAbstractSocket::ClosingState:

        end = QDateTime::currentMSecsSinceEpoch();
        if (!dropConnectionTimer){
           if ( (end - start) >= TIME_DROP_CONN && (end - start) <= (TIME_DROP_CONN + SECONDS_IN_MILLISECONDS))
                qDebug() << "connection was disconnect by server by " << TIME_DROP_CONN/ SECONDS_IN_MILLISECONDS << "s of afk";
}
        break;


    }


}


void Connection::setConnectionEstablishingTimer(){

    connectionEstablishingTimer = startTimer(CONNECTION_ESTABLISHING_TIME);

}
#ifdef VERBOSE_STATES

void Connection::connectionStateChanged(){


    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << "Connection state: " <<  metaEnum.valueToKey(get_state());

}
#endif

void Connection::timerEvent(QTimerEvent *event)
{

    qDebug() << "Connection timers works";

    qDebug()<<"Thread::cleint : "<<QThread::currentThreadId();

    if (event->timerId() == dropConnectionTimer){

        qDebug() << "Connection: " << _socket->socketDescriptor() << "is disconnected by expired time (" << TIME_DROP_CONN/SECONDS_IN_MILLISECONDS << ")";

        dropConnection();
    }
    if (event->timerId() == connectionEstablishingTimer){
        QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
        qDebug() << "Connection couldn't started, last state: " << metaEnum.valueToKey(get_state());
        emit dropConnection();
    }
    QTcpSocket::timerEvent(event);



}


QTcpSocket* Connection::get_socket(){
    return _socket;
}


//to make priorety for sending message: make a slot with connected readyRead signal and
//checking for outgoing message, if not zero, than call send, else recieve
//drawbacks:: some calls of send func will be empty, depending on recieve message

//post send message to an invent system
void Connection::send(){


    if (_socket->state() != QAbstractSocket::ConnectedState){

        qDebug() << "Connection is not established, abort send";
        return;
    }

    if (outgoing.size() == 0)
        return;
    message msg;
    QByteArray* data = outgoing.first();
    QDataStream in(data, QIODevice::ReadWrite);
    in >> msg;
    msg.set_send_time();
    data = msg.serialize();
    quint64 to_write = msg.get_size();
    quint64 written = 0;

    do {
    written = _socket->write(data->constData(), to_write);
//    Q_ASSERT(written == to_write);

    data->remove(0, written);
    } while (written < to_write);
    if (owner == Owner::Client){

         qDebug() << "Sending message size: " << to_write
                  << "\nsuccessful send: " << written;

     }
    else {

        qDebug() << _socket->socketDescriptor() << "Sending message size: " << to_write
                 << "\nsuccessful send: " << written;


    }

}


QByteArray* Connection::_get_last_msg(QList<QByteArray*>& list) {

    QByteArray* data = list.last();
    list.removeLast();
    return data;

}

QByteArray* Connection::_get_first_msg(QList<QByteArray*>& list) {

    QByteArray* data = list.first();
    list.removeFirst();
    return data;

}



//needed to add pragma pack for struct to disable optimizing for correct size
void Connection::recieve(){

    if (dropConnectionTimer)
        killTimer(dropConnectionTimer);

   dropConnectionTimer = startTimer(TIME_DROP_CONN);
   QByteArray* msg = new QByteArray();
   quint64 min_to_read = sizeof(message);
   char buffer[1024];
   quint64 read = _socket->read(buffer, min_to_read);
//   Q_ASSERT(read == min_to_read);
   quint64 old_size = msg->size();
   msg->resize(old_size + read);

   memcpy(msg->data() /*+ old_size*/, buffer, read);

   QDataStream out(*msg);
   Q_ASSERT(out.byteOrder() == QDataStream::BigEndian);
   message data;
   out >> data;
   quint64 total_size = data.get_size();

   quint64 temp = total_size - read;

   do {
   old_size = msg->size();
   read = _socket->read(buffer, total_size - read);
   msg->resize(old_size + read);
   memcpy(msg->data() + old_size, buffer, read);

   } while (read != temp);


   incoming.append(msg);


   if (owner == Owner::Client){

        qDebug() << "Incoming message size: " << total_size
                 << "\nsuccessful read: " << read;

    }
   else {

       qDebug() << _socket->socketDescriptor() <<": Incoming message size: " << total_size
                << "\nsuccessful read: " << read;


   }
    emit new_message_income();
}



void Connection::deleteConnection(){

    if (dropConnectionTimer)
        killTimer(dropConnectionTimer);
    if (connectionEstablishingTimer)
        killTimer(connectionEstablishingTimer);
    _socket->abort();
    deleteLater();


}


QAbstractSocket::SocketState Connection::get_state(){


    return _socket->state();
}

QString Connection::peer_address(){
    return _socket->peerAddress().toString();
}

QString Connection::local_address(){
    return _socket->localAddress().toString();
}


void Connection::add_first_msg_in(message* msg) {

    incoming.append(msg->serialize());
}

void Connection::add_first_msg_out(message* msg) {

    outgoing.append(msg->serialize());
}

void Connection::add_last_msg_in(message* msg) {

    incoming.append(msg->serialize());
}

void Connection::add_last_msg_out(message* msg) {

    outgoing.append(msg->serialize());
}


