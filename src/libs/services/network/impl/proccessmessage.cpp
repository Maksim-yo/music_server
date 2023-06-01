#include "services/network/proccessmessage.h"
#include "services/network/messagehandles.h"
#include "services/network/message.h"
#include "services/network/session.h"




class RegistrationHandle{

    void proccess(registration_message& msg){

        QString login = msg.get_login();
//        bool res = validate_login(login);
//        if (res){

//            DB::ADD(//new structutr)   //user like informationx
//        }


    }

};


class AuthorizationHandle{

    AuthorizationHandle(authorization_message msg){

        QString login = msg.get_login();
        QString password = msg.get_password();

    }
};

ProccessMessage::ProccessMessage(Owner owner) : owner(owner)
{

}

void ProccessMessage::set_session(Session* session){

    std::string str = "ProccessMessage already has a queue";


    _session = session;


}

void ProccessMessage::proccess(QByteArray*& msg){

//    if (outgoing == QList<message*>())
//        throw std::runtime_error("ProccessMessage is not set a queue");
    QDataStream in(*msg);
    message message;
    in >> message;
    MessageType msg_type = message.get_type();
    switch(msg_type){

    case TrackMessage:
//        auto n_msg = reinterpret_cast<TrackMessage>(msg);
        break;
    case ServerDeny:
        break;
    case ServerAccept:
        break;
    case ArtistMessage:
        break;
    case PlayListMessage:
        break;
    case SettingsMessage:
        break;
    case RegistrationMessage:
        break;
    case AuthorizationMessage:
        break;
    case PingMessage:
    {
        pong_message* _msg = new pong_message();
        _session->write(_msg);
        break;
    }
    case PongMessage:
        qDebug() << "Reply from "<<_session->peer_address() << " " << "response_time=";

        break;
//        _session->add_last_msg_out(new ping_message());
//        quint64 response_time = QDateTime::currentDateTime().msecsTo(message->get_send_time());
}
}
