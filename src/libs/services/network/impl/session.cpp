#include "services/network/session.h"
#include "services/network/connection.h"
#include <QTimer>
#include <QTcpSocket>
#include "services/network/message.h"
#include "services/network/Constants.h"
#include "services/network/iproccessmessage.h"
class QDateTime ;
Session::Session(QTcpSocket*& socket,IProccessMessage* _prc_msg, Owner owner, QObject* parent) : conn(std::move(new Connection(socket, owner))), QObject(parent)    //why conn(socket) not working?
{

        _prc_msg->set_session(this);
        connect(conn, &Connection::new_message_income, this, &Session::readMessage);
        connect(conn, &Connection::dropConnection, this, &QObject::deleteLater);
        proccess_msg = _prc_msg;

}


void Session::write(message *msg){


    add_last_msg_out(msg);
    emit conn->new_message_outgoing();

}


QByteArray* Session::get_first_msg_out(){return conn->get_first_msg_out();}
QByteArray* Session::get_last_msg_out(){return conn->get_last_msg_out();}
QByteArray* Session::get_last_msg_in(){return conn->get_last_msg_in();}
QByteArray* Session::get_first_msg_in(){return conn->get_last_msg_in();}


void Session::add_last_msg_in(message* msg){


    conn->add_last_msg_in(msg);
}


void Session::add_last_msg_out(message* msg) {

    conn->add_last_msg_out(msg);
}

void Session::read(message *&msg){

//    incoming.append(msg);


}
Session::Session(Connection*& _conn, IProccessMessage* _prc_msg, QObject* parent): conn(_conn),  QObject(parent) {


//    conn = _conn;
    _prc_msg->set_session(this);
    connect(_conn->get_socket(), SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(_conn, &Connection::dropConnection, this, &QObject::deleteLater);
    proccess_msg = _prc_msg;
}



void Session::ping(qint64 count){


    for(int i = 0; i < count; ++i){
        message* msg = new ping_message();
        write(msg);
    }
}

void Session::get_state()
{
    qDebug() << conn->get_state();
}

//void Session::dbgRecieve(message*& msg){

////    header head = msg->get_head();
////    qDebug() << "----------Message_info----------"
////             << "\n-----------[RECIEVED]-----------"
////             << "\nsend_time:    " << head.get_time_send()
//////             << "\nrecieve_time: " << head.get_time_recieve()
////             << "\nmessage_type: " << head.get_type()
////             << "\nmessage_size: " << head.get_size() << "\n";


//}


//void Session::dbgSend(message*& msg){

////    header head = msg->get_head();
////    qDebug() << "----------Message_info----------"
////             << "\n-------------[SEND]-------------"
////             << "\nsend_time:    " << head.get_time_send()
//////             << "\nrecieve_time: " << head.get_time_recieve()
////             << "\nmessage_type: " << head.get_type()
////             << "\nmessage_size: " << head.get_size() << "\n";

//}

void Session::readMessage(){


        QByteArray* msg;
        msg = get_first_msg_in();
        proccess_msg->proccess(msg);

}


QString Session::local_address() {

    return conn->local_address();
}
QString Session::peer_address() {

    return conn->peer_address();
}


Connection* Session::get_connection(){

    return conn;

}

//template<typename SocketType>
//void Session<SocketType>::processM(QNetworkDatagram datagram){

////sql invoking
//    QByteArray data = datagram.data();
//    QBuffer buffer = QBuffer(&data);
//    message<MessageType> _message = message<MessageType>();
//    _message.serialize(buffer);
//    process_message(_message);

//}


