#include "services/network/proccessmessage.h"
#include "services/network/messagehandles.h"
#include "services/network/message.h"
#include "services/network/session.h"
#include <QMetaEnum>


namespace Network {

    using namespace Constants;

std::unique_ptr<IProccessMessage> createProcMsg() {


    return std::make_unique<ProccessMessage>();
}


class RegistrationHandle{

//    void proccess(registration_message& msg){

//        QString login = msg.get_login();
////        bool res = validate_login(login);
////        if (res){

////            DB::ADD(//new structutr)   //user like informationx
////        }


//    }

};

class AuthorizationHandle{

//    AuthorizationHandle(authorization_message msg){

//        QString login = msg.get_login();
//        QString password = msg.get_password();

//    }
};

ProccessMessage::ProccessMessage()
{

}

void ProccessMessage::set_session(Session* session){

    std::string str = "ProccessMessage already has a queue";


    _session = session;


}

void ProccessMessage::proccess(QByteArray& msg, MessageType type){

//    if (outgoing == QList<message*>())
//        throw std::runtime_error("ProccessMessage is not set a queue");

//    message _message;
//    {
//        QDataStream in(msg, QIODevice::ReadWrite);
//        in >> _message;
//    }
//    MessageType msg_type = _message.get_type();
//    qDebug() << "Proccessing message : " << QString((QMetaEnum::fromType<MessageType>().valueToKey(type)));

    switch(type){

    case MessageType::TrackMetadata:
//        auto n_msg = reinterpret_cast<TrackMessage>(msg);
        break;
    case MessageType::ServerDeny:
        break;
    case MessageType::ServerAccept:
        break;
    case MessageType::Artist:
        break;
    case MessageType::PlayList:
        break;
    case MessageType::Settings:
        break;
    case MessageType::Registration:
        break;
    case MessageType::Authorization:
        break;
    case MessageType::Ping:
    {
        pong_message* _msg = new pong_message();
        {
            QDataStream in(&msg, QIODevice::ReadWrite);
            in >> *_msg;
        }
        std::unique_ptr<message> msg = std::make_unique<message>(std::move(static_cast<message*>(_msg)));
//
        messageParams msgParam = {messageParams::Priorety::High, std::move(msg)};
        _session->write(std::move(msgParam));
        break;
    }
//    case MessageType::Pong:

        break;
//        _session->add_last_msg_out(new ping_message());
//        quint64 response_time = QDateTime::currentDateTime().msecsTo(message->get_send_time());

    }
}
}
