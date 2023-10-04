#include <QTimer>
#include <QTcpSocket>

#include "services/network/session.h"
#include "services/network/tcpconnection.h"
#include "services/network/message.h"
#include "services/network/Constants.h"
#include "services/network/sendqueue.h"
#include "services/network/proccessmessage.h"
#include "services/network/IConnection.h"
#include "impl/IConnection.cpp"


namespace Network {

Session::Session(std::unique_ptr<IConnection> _conn, std::unique_ptr<IProccessMessage> _prc_msg, Constants::Owner owner, QObject* parent): conn(std::move(_conn)), owner(owner), QObject(parent) {


    _prc_msg->set_session(this);
//    proccess_msg = _prc_msg;
    connect(&_conn->_signals, &IConnectionSignals::dropConnection, this, &QObject::deleteLater);
    connect(&conn->_signals, &IConnectionSignals::newRecieveMessages, this, &Session::readMessage);

}


void Session::write(messageParams msg){

    conn->getQueue()->sendData(std::move(msg));

}


void Session::handleMessage(){

//    proccess_msg->proccess(conn->getRecieveMessages());

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




        // IS BIG ENDIAN OR LITTLE ENDIAN
        QByteArray msgs = conn->getRecieveMessages();
        int initSize = message::getInitialSize();

        if (!partialMessage.isEmpty()) {

            msgs.push_front(partialMessage);

        }
        while (true){

            QByteArray msg;
            message _message;
            {
                    QDataStream in(&msgs, QIODevice::ReadWrite);
//                    in.setByteOrder(QDataStream::LittleEndian);
                    in >> _message;
            }

            msg = msgs.remove(0,_message.get_size());
            if (msg.size() < _message.get_size()){

                partialMessage = msg;
                return;
            }

            proccess_msg->proccess(msg, _message.get_type());

        }
}


IConnection* Session::get_connection(){

    return conn.get();

}

Session* createSession(QTcpSocket*& socket, Constants::Owner owner, QObject *parent, ConnType type)
{
    std::unique_ptr<IConnection> conn = createConnection(socket, ConnType::TCP);
    conn->setConnectionEstablishingTimer();
    SendQueue* _sendQueue = new SendQueue();
    conn->setQueue(_sendQueue);
    std::unique_ptr<IProccessMessage> proc_msg = createProcMsg();
    Session* session = new Session(std::move(conn), std::move(proc_msg), owner);
    proc_msg->set_session(session);
    return session;

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
}
