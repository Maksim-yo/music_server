#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>
#include <optional>
#include <QDataStream>
#include <QString>
#include <QBuffer>
#include <QDateTime>

#include "Constants.h"

#pragma pack (1)
struct header{


    friend QDataStream &operator>>(QDataStream &data_stream,  quint32 &head);

    friend QDataStream& operator<<(QDataStream &data_stream,  header *&head){


        data_stream << head->header_size;
        data_stream << head->send_time;
        data_stream << head->type;

        return data_stream;

    }

    friend QDataStream& operator<<(QDataStream &data_stream,  header &head){


        data_stream << head.header_size;
        data_stream << head.send_time;
        data_stream << head.type;

        return data_stream;

    }


    friend QDataStream &operator>>(QDataStream &data_stream,  header &head){

        data_stream >> head.header_size;
        data_stream >> head.send_time;
        data_stream >> head.type;
        return data_stream;
    }


    friend QDataStream &operator>>(QDataStream &data_stream,  header *&head){

        data_stream >> head->header_size;
        data_stream >> head->send_time;
        data_stream >> head->type;
        return data_stream;
    }

    header(MessageType _type){

        type = _type;
        header_size += sizeof(type);
        header_size += sizeof(send_time);
        header_size += sizeof(header_size);
    }

    header(){}

    void set_send_time(){

        send_time = QDateTime::currentSecsSinceEpoch();

    }

    MessageType get_type() {return type; }
    quint64 get_time_send() {return send_time; }
    quint64 get_size() {return header_size; }


private:

    quint64 send_time = 0;
    quint64 header_size = 0;
    MessageType type;


};

#pragma pack (1)
struct message
{
public:
    message(MessageType type) : head(type) {

        msg_size += sizeof(msg_size);
        msg_size += head.get_size();

    }

    message() {}
    QByteArray* _serialize(){

        QByteArray* serialized_data = new QByteArray();
        QDataStream data_stream(serialized_data, QIODevice::WriteOnly);
        header& head = this->head;
//        header* head = reinterpret_cast<header*>(this);
        data_stream << head;
        data_stream << msg_size;
        return serialized_data;

    }
    void _deserialize(QByteArray* deseriliazed_data ){

        QDataStream data_stream(deseriliazed_data, QIODevice::ReadOnly );
        header* head = reinterpret_cast<header*>(this);
        data_stream >> *head;
        data_stream >> msg_size;

    }

    virtual QByteArray* serialize() {return _serialize();}
    virtual void deserialize(QByteArray* data) {return _deserialize(data);}

    void set_send_time(){
        head.set_send_time();
    }

    friend struct header;
    friend QDataStream &operator<<(QDataStream &data_stream, message& msg)  // serailize
    {

        data_stream << msg.head;
        data_stream << msg.msg_size;
        return data_stream;
    }

//    friend QDataStream &operator<<(QDataStream &data_stream, message*& msg)  // serailize
//    {

//        data_stream << msg->head;
//        data_stream << msg->msg_size;
//        return data_stream;
//    }

    friend QDataStream &operator>>(QDataStream &data_stream, message& msg)  // deserailize
    {

        data_stream >> msg.head;
        data_stream >> msg.msg_size;
        return data_stream;

    }


//    friend QDataStream &operator>>(QDataStream &data_stream, message*& msg)  // deserailize
//    {

//        msg->head = header();
//        data_stream >> msg->head;
//        data_stream >> msg->msg_size;
//        return data_stream;

//    }

    virtual ~message() = default;
     auto get_type(){
        return head.get_type();
    }

     quint64 get_send_time(){
         return head.get_time_send();
     }

    header& get_head(){
        return head;
    }

    qint64 get_size(){
        return msg_size;
    }
protected:

    header head ;
    qint64 msg_size = 0;

};


struct  ping_message : public message{


    ping_message() : message(PingMessage){}


};


struct pong_message : public message{


    pong_message() : message(PongMessage){}   

};


//    QByteArray* serialize() override {

//        QDataStream data_stream(*data);
//        _serialize();
//        data_stream << count;
//        return data;
//    }
//    QByteArray* deserialize() override {

//        QDataStream data_stream(*data);
//        _deserialize();
//        header head = this->get_head();
//        data_stream >> head;
//        return data;

//    }





//};



struct registration_message : message{


    registration_message(QString login, QString password, QString name, QString nickname) : message(RegistrationMessage),
    password(password), login(login), name(name), nickname(nickname) {}
    QString get_login() { return login;}
    QString get_password() { return password; }


private:
    QString password;
    QString login;
    QString name;
    QString nickname;
};


struct  authorization_message : message {

    authorization_message(QString login, QString password): message(AuthorizationMessage), login(login), password(password) {


    }

    QString get_login(){ return login;}
    QString get_password() { return password;}

private:
    QString login;
    QString password;
};

enum SERVER_STATUS_CODE{

    Deny,
    Accept
};

/*struct server_response : message{


    server_response(): message(){


    }
private:

    SERVER_STATUS_CODE code;

}*/;
struct track_message_header : message{

//    track_message_header(QString name, std::vector<QString> authors,  QDateTime date_of_creation,
//    quint32 music_duration /*std::optional<QImage> image*/):
//        music_name(music_name), authors(authors), date_of_creation(date_of_creation),
//        music_duration(music_duration)/*, image(image)*/
//    {};



//     serialize(){


//        QByteArray* data = new QByteArray();
//        QDataStream data_stream(data, QIODevice::WriteOnly);
//        data_stream << music_name;
//        data_stream << date_of_creation;
//        data_stream << music_duration;
//        data_stream << authors.size();
//        for (QString author : authors){
//            data_stream << author;
//        }
////        if (image)
////          data_stream << image;
//        output.setBuffer(data);




    void deserialize(QByteArray* input){

//        QByteArray data = input.buffer();
//        QDataStream data_stream(&data, QIODevice::ReadOnly);
//        data_stream >> music_name;
//        data_stream >> date_of_creation;
//        data_stream >> music_duration;
//        quint32 counts;
//        QString author;
//        data_stream >> counts;
//        for (int i = 0; i < counts; ++i){
//              data_stream >> author;
//              authors.push_back(author);

//        }
//        data_stream >> image;
    }

private:
  QString music_name;
  std::vector<QString> authors;
  QDateTime date_of_creation;
  quint32 music_duration; // in seconds
//  std::optional<QImage> image; // track image




};


#endif // MESSAGE_H
