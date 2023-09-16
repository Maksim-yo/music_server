#include "services/network/message.h"
#include "services/database/Utils.h"

namespace {

    void addStructToVec(QVector<Network::MessageItem>& vec, auto var){

        vec.emplace_back(VARIABLE_NAME(var), var);
    }

}

namespace Network {

    message::message(Constants::MessageType type) : head(type) {

        msg_size += sizeof(msg_size);
        msg_size += head.get_size();

    }

    message::message() {

        msg_size += sizeof(msg_size);
        msg_size += head.get_size();
    }

    message::message(message *&&msg) {

        head = msg->head;
        msg_size = msg->msg_size;
    }

    QByteArray *message::_serialize(){

        QByteArray* serialized_data = new QByteArray();
        QDataStream data_stream(serialized_data, QIODevice::WriteOnly);
        header& head = this->head;
        //        header* head = reinterpret_cast<header*>(this);
        data_stream << head;
        data_stream << msg_size;
        return serialized_data;

    }

    void message::_deserialize(QByteArray *deseriliazed_data){

        QDataStream data_stream(deseriliazed_data, QIODevice::ReadOnly );
        header* head = reinterpret_cast<header*>(this);
        data_stream >> *head;
        data_stream >> msg_size;

    }

    header::header(Constants::MessageType _type){

        type = _type;
        header_size += sizeof(type);
        header_size += sizeof(header_size);
    }

    header::header(){

        header_size += sizeof(type);
        header_size += sizeof(header_size);
    }

    QVector<MessageItem> Lyric::map()
    {
        return QVector<MessageItem>{{VARIABLE_NAME(data), data}};
    }

    QVector<MessageItem> Artist::map()
    {
        return QVector<MessageItem>{{VARIABLE_NAME(id), id}, {VARIABLE_NAME(name), name}};

    }




}
