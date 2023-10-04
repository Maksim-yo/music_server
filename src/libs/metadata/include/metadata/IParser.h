#ifndef IPARSER_H
#define IPARSER_H


#include <filesystem>
#include <QString>
#include <QDateTime>
#include <optional>
#include <vector>

namespace Metadata {

    struct Artist {

      QString name;

    };



    struct Image {

        QString data;
        QString mimeType;
    };

    struct Album {

        QString title;
    };

    struct Track{

        qint64 duration;
        QString title;
        qint64 bitrate;
        qint64 sampleRate;
        qint64 channels;
        QDateTime date;
        Album album;
        std::vector<Artist> artists;
        std::optional<Image> image;
    };

    enum ParserSpeed{

        Fast,
        Average,
        Low
    };

    enum ParserType{

        Taglib
    };

    class IParser {

    public:
        virtual ~IParser() {}
        virtual std::optional<Track> parse(std::filesystem::path file) = 0;
        virtual void processTag(Track& track, std::string tag, std::vector<std::string> values) = 0;

    };


    std::unique_ptr<IParser> createParser(ParserType type, ParserSpeed speed);
}

#endif
