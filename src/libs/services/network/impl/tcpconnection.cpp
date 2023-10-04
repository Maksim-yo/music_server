#include <memory>
#include <QTcpSocket>
#include <QTimer>
#include <QMetaEnum>
#include <QTimerEvent>
#include <QThread>

#include "services/network/tcpconnection.h"
#include "services/network/message.h"

static const int SECONDS_IN_MILLISECONDS = 1000;
static const int TIME_DROP_CONN = SECONDS_IN_MILLISECONDS * 30000;
static const int CONNECTION_ESTABLISHING_TIME = SECONDS_IN_MILLISECONDS * 3;

namespace Network {


// replace with move if is valid

TCPConnection::TCPConnection(QTcpSocket*& socket) : _socket(socket)
{

    setDropConnectionTimer();

    connect(_socket, &QTcpSocket::stateChanged, &_signals, &IConnectionSignals::socketStateChanged);

    connect(&_signals, &IConnectionSignals::dropConnection, this, &TCPConnection::deleteConnection, Qt::DirectConnection);
    connect(&_signals, &IConnectionSignals::socketStateChanged, this, &TCPConnection::checkConnectonEstablishing);
    connect(_socket, &QTcpSocket::bytesWritten, &_signals, &IConnectionSignals::bytesWritten);

    start = QDateTime::currentMSecsSinceEpoch();


#ifdef VERBOSE_STATES
    connect( &_signals, &IConnectionSignals::socketStateChanged, this, &TCPConnection::connectionStateChanged);
#endif


}

void TCPConnection::setQueue(SendQueue*& queue){

    _sendQueue = queue;
    connect(_sendQueue, &SendQueue::readyToSend, &_signals, &IConnectionSignals::readyToSend);

}

void TCPConnection::isConnected(){

    if (get_state() == QAbstractSocket::ConnectedState){
        if (connectionEstablishingTimer)
            killTimer(connectionEstablishingTimer);
        qDebug() << "Connection established";
    }

}


void TCPConnection::setDropConnectionTimer(){

    dropConnectionTimer = startTimer(TIME_DROP_CONN);

}

void TCPConnection::checkConnectonEstablishing(QAbstractSocket::SocketState socketState){


    switch(socketState){

    case QAbstractSocket::ConnectedState:

        startConnected = QDateTime::currentMSecsSinceEpoch();
        if (connectionEstablishingTimer)
            killTimer(connectionEstablishingTimer);

        emit _signals.connectionEstablished();
        qInfo("Connection successful established");
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


void TCPConnection::setConnectionEstablishingTimer(){

    connectionEstablishingTimer = startTimer(CONNECTION_ESTABLISHING_TIME);

}
#ifdef VERBOSE_STATES

void TCPConnection::connectionStateChanged(){


    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << "Connection state: " <<  metaEnum.valueToKey(get_state());

}
#endif

void TCPConnection::timerEvent(QTimerEvent *event)
{

    qDebug() << "Connection timers works";

    qDebug()<<"Thread::cleint : "<<QThread::currentThreadId();

    if (event->timerId() == dropConnectionTimer){

        qDebug() << "Connection: " << _socket->socketDescriptor() << "is disconnected by expired time (" << TIME_DROP_CONN/SECONDS_IN_MILLISECONDS << ")";

        emit _signals.dropConnection();
    }
    if (event->timerId() == connectionEstablishingTimer){
        QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
        qDebug() << "Connection couldn't started, last state: " << metaEnum.valueToKey(get_state());

        emit _signals.dropConnection();
    }
    QTcpSocket::timerEvent(event);

}

QTcpSocket* TCPConnection::get_socket(){
    return _socket;
}

bool TCPConnection::canTransferMore() {

    return _socket->bytesAvailable() > 0
        || !_sendQueue->isEmpty();

}

//reimplement without qbytearray 'cause is too memoery expensive
qint64 TCPConnection::send(qint64 bytes){


    if (_socket->state() != QAbstractSocket::ConnectedState){

        qDebug() << "Connection is not established, abort send";
        return -1;
    }

    auto msgs = _sendQueue->getMessages(bytes);
    if (!msgs.value())
        return -1;

    qint64 totalWritten = 0;

    do {

        qint64 written = _socket->write(msgs.value()->constData(),
                                        qMin<qint64>(bytes - totalWritten, msgs.value()->size()));

        if (written <= 0)
            break;

        totalWritten += written;
        msgs.value()->remove(0, written);
    } while (totalWritten < bytes && !msgs.value()->isEmpty());

    return totalWritten;
//    if (owner == Owner::Client){

//         qDebug() << "Sending message size: " << to_write
//                  << "\nsuccessful send: " << written;

//     }
//    else {

//        qDebug() << _socket->socketDescriptor() << "Sending message size: " << to_write
//                 << "\nsuccessful send: " << written;


//    }

}

qint64 TCPConnection::recieve(qint64 bytes){

    if (dropConnectionTimer)
        killTimer(dropConnectionTimer);

   dropConnectionTimer = startTimer(TIME_DROP_CONN);

   char buffer[1024];
   qint64 totalRead = 0;

   do {


       qint64 bytesRead = _socket->read(buffer, qMin<qint64>(bytes - totalRead, sizeof(buffer)));
       if (bytesRead <= 0)
               break;

       totalRead += bytesRead;
       qint64 oldSize = recieveMessages.size();
       recieveMessages.resize(oldSize + bytesRead);
       memcpy(recieveMessages.data() + oldSize, buffer, bytesRead);

   }

    while (totalRead < bytes);


//   if (owner == Owner::Client){

//        qDebug() << "Incoming message size: " << total_size
//                 << "\nsuccessful read: " << read;
//    }
//   else {

//       qDebug() << _socket->socketDescriptor() <<": Incoming message size: " << total_size
//                << "\nsuccessful read: " << read;
//   }

   emit _signals.newRecieveMessages();
   return totalRead;
}

void TCPConnection::deleteConnection(){

    if (dropConnectionTimer)
        killTimer(dropConnectionTimer);
    if (connectionEstablishingTimer)
        killTimer(connectionEstablishingTimer);
    _socket->abort();
    deleteLater();

}
}

