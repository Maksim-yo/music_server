#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QByteArray>
namespace Network {

    namespace Constants {
        Q_NAMESPACE

        inline constexpr qint8 BYTE = 8;
        inline constexpr qint16 KB = 1024 * BYTE;
        inline constexpr qint64 MB = 1024 * KB;


        enum class Owner{

            Client,
            Server
        };

        enum  MessageHttpType {

            Get = 0,
            Post,
            Response,

        };


        enum MessageType{

            Artist,
            Album,
            TrackMetadata,
            InitialPage,
            TrackData,
            PlayList,
            Settings,
            Registration,
            Authorization,
            ServerDeny,
            ServerAccept,
            Ping,
            Pong

    };

    Q_ENUM_NS(MessageType)
    }
}
#endif // CONSTANTS_H
