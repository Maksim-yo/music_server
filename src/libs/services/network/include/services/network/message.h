#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QBuffer>
#include <QDateTime>
#include <QList>
#include "services/network/Constants.h"
namespace Network {

//    #pragma pack(push, 1)

//    using


    struct MessageItem{
        QString key;
        QVariant value;
    };

    struct header{


        friend QDataStream &operator>>(QDataStream &data_stream,  quint32 &head);

        friend QDataStream& operator<<(QDataStream &data_stream,  header *&head){


            data_stream << head->header_size;
            data_stream << head->type;

            return data_stream;

        }

        friend QDataStream& operator<<(QDataStream &data_stream,  header &head){


            data_stream << head.header_size;
            data_stream << head.type;

            return data_stream;

        }


        friend QDataStream &operator>>(QDataStream &data_stream,  header &head){

            data_stream >> head.header_size;
            data_stream >> head.type;
            return data_stream;
        }


        friend QDataStream &operator>>(QDataStream &data_stream,  header *&head){

            data_stream >> head->header_size;
            data_stream >> head->type;
            return data_stream;
        }

        header(Constants::MessageType _type);

        header();

        static qint64 getInitialSize() {

            return sizeof(Constants::MessageType) + sizeof(header_size);
        }

        virtual ~header() {}

        Constants::MessageType get_type() {return type; }
        quint64 get_size() {return header_size; }


    private:

        Constants::MessageType type;
        quint64 header_size = 0;


    };


    struct message
    {
    public:
        message(Constants::MessageType type);
        message(message*&& msg);
        message();
        virtual ~message(){}

        QByteArray* _serialize();
        void _deserialize(QByteArray* deseriliazed_data );

        virtual QByteArray* serialize() {return _serialize();}
        virtual void deserialize(QByteArray* data) {return _deserialize(data);}

        virtual QVector<MessageItem> map() { return{}; }

        friend struct header;
        friend QDataStream &operator<<(QDataStream &data_stream, message& msg)  // serailize
        {

            data_stream << msg.head;
            data_stream << msg.msg_size;
            return data_stream;
        }

        friend QDataStream &operator<<(QDataStream &data_stream, message*& msg)  // serailize
        {

            data_stream << msg->head;
            data_stream << msg->msg_size;
            return data_stream;
        }

        friend QDataStream &operator>>(QDataStream &data_stream, message& msg)  // deserailize
        {

            data_stream >> msg.head;
            data_stream >> msg.msg_size;
            return data_stream;

        }


        friend QDataStream &operator>>(QDataStream &data_stream, message*& msg)  // deserailize
        {

            msg->head = header();
            data_stream >> msg->head;
            data_stream >> msg->msg_size;
            return data_stream;

        }

         auto get_type(){
            return head.get_type();
        }

        header& get_head(){
            return head;
        }

        static qint64 getInitialSize() {

            return sizeof(msg_size) + header::getInitialSize();
        }

        qint64 get_size(){
            return msg_size;
        }
    protected:

        header head ;
        qint64 msg_size{0};

    };
//    #pragma pack(pop)

    struct ping_message : message{


        ping_message() : message(Constants::MessageType::Ping){}


    };


    struct pong_message :  message{


        pong_message() : message(Constants::MessageType::Pong){}

    };

//struct mainRecomednationMessage:  message {


//    mainRecomednationMessage() : message(TrackMetadata) {}
//    std::vector<struct TrackMetadata> tracks;


//};




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



////     serialize(){


////        QByteArray* data = new QByteArray();
////        QDataStream data_stream(data, QIODevice::WriteOnly);
////        data_stream << music_name;
////        data_stream << date_of_creation;
////        data_stream << music_duration;
////        data_stream << authors.size();
////        for (QString author : authors){
////            data_stream << author;
////        }
//////        if (image)
//////          data_stream << image;
////        output.setBuffer(data);




//    void deserialize(QByteArray* input){

////        QByteArray data = input.buffer();
////        QDataStream data_stream(&data, QIODevice::ReadOnly);
////        data_stream >> music_name;
////        data_stream >> date_of_creation;
////        data_stream >> music_duration;
////        quint32 counts;
////        QString author;
////        data_stream >> counts;
////        for (int i = 0; i < counts; ++i){
////              data_stream >> author;
////              authors.push_back(author);

////        }
////        data_stream >> image;
//    }



    struct Lyric: message {

        QVector<MessageItem> map() override;
        QString getData(){return data;}
        qint64 getId(){return id;}
    private:
        QString data;
        qint64 id;
    };

    struct Artist: message {

        qint64                 getId() const {return id;}
        QString                getName() const {return name;}
        bool                   getIsImageNeeded() const {return isImageNeeded;}
        std::optional<QString> getImage() const {return img;}

        QVector<MessageItem> map() override;

    private:
        qint64 id;
        QString name;
        bool isImageNeeded;
        std::optional<QString> img;
    };

    struct offset {

        qint64 _start;
        qint64 _end;
    };
    struct TrackData {

        offset _offset;
        QString data;
    };

    struct TrackMetadata: message {

        qint64                      getId() const {return id;}
        QString                     getTitle() const {return title;}
        std::optional<qint64>       getBitrate() const {return bitrate;}
        std::optional<qint64>       getSampleRate() const {return sampleRate;}
        std::optional<qint64>       getDiscNumber() const {return discNumber;}
        std::optional<qint64>       getTrackNumber() const {return trackNumber;}
        std::optional<QDateTime>    getReleaseDate() const {return releaseDate;}
        std::optional<QString>      getImage() const {return image;}
        std::optional<Lyric>        getLyric() const{return lyrics;}
        std::optional<TrackData>    getData() const {return data;}
        std::vector<Artist>         getArtists() const {return artists;}
        bool                        getIsImageNeed() const {return isImageNeed;}
        bool                        getIsDataNeed() const {return isDataNeed;}

        void            setId(qint64 _id){ id = _id;}
        void            setTitle(QString _title){title = _title ;}
        void            setBitrate(qint64 _bitrate){bitrate = _bitrate;}
        void            setSampleRate(qint64 _samplerate){sampleRate = _samplerate;}
        void            setDiscNumber(qint64 _discNumber){discNumber = _discNumber;}
        void            setTrackNumber(qint64 _trackNumber){trackNumber = _trackNumber;}
        void            setReleaseDate(QDateTime _releaseDate){releaseDate = _releaseDate;}
        void            setArtists(std::vector<Artist> _artists){artists = _artists;}
        void            setImage(QString _img){image = _img;}
        void            setLyric(Lyric _lyric){lyrics = _lyric;}
        void            setData(TrackData _data){data = _data;}
        void            setIsImageNeed(bool res){isImageNeed = res;}
        void            setIsDataNeed(bool res){isDataNeed = res;}


    private:
        qint64 id;
        QString title;
        bool isDataNeed;
        bool isImageNeed;
        std::optional<qint64> listCount;            // the lack of protocol leads to keep the count of data in message
        std::optional<qint64> bitrate;
        std::optional<qint64> sampleRate;
        std::optional<qint64> discNumber;
        std::optional<qint64> trackNumber;
        std::optional<QDateTime> releaseDate;
        std::optional<QString> image;
        std::optional<Lyric>  lyrics;
        std::optional<TrackData> data;
        std::vector<Artist> artists;

    };


    struct messageParams{

    //    messageParams(Priorety pri, )
    ;
      enum Priorety{

            High,
            Normal,
            Low
      };
      Priorety getPiorety(){

          return priorety;
      }

      message* getMessage(){
          return msg.get();
      }

      message* release(){
          return msg.release();
      }

      Priorety priorety{Priorety::Normal};
      std::unique_ptr<message> msg;

    };

}
#endif // MESSAGE_H
