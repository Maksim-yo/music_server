#include <map>
#include "metadata/TagLib.h"

#include <taglib/apetag.h>
#include <taglib/asffile.h>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/mp4file.h>
#include <taglib/mpcfile.h>
#include <taglib/mpegfile.h>
#include <taglib/opusfile.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <taglib/vorbisfile.h>
#include <taglib/wavpackfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2tag.h>



namespace Metadata {
using namespace TagLib;

    using TagMap = std::map<std::string, std::vector<std::string>>;

    TagMap
    constructTagMap(const TagLib::PropertyMap& properties)
    {
        TagMap tagMap;

        for (const auto& [propertyName, propertyValues] : properties)
        {
            std::vector<std::string>& values {tagMap[propertyName.upper().to8Bit(true)]};
            for (const TagLib::String& propertyValue : propertyValues)
            {
                std::string trimedValue {(propertyValue.to8Bit(true))};
                values.emplace_back(std::move(trimedValue));
            }
        }

        return tagMap;
    }

    static QString getMimyType(const std::string& str){

        auto _start = std::find(str.cbegin(),str.cend(), '/');
        return QString(std::string(_start + 1, str.cend()).c_str());
    }

    static void mergeTagMaps(TagMap& dst, TagMap&& src)
    {
        for (auto&& [tag, values] : src)
        {
            if (dst.find(tag) == std::cend(dst))
                dst[tag] = std::move(values);
        }
    }


    std::vector<std::string> getFirstMatch(const TagMap& tags, std::initializer_list<std::string> keys){

        std::vector<std::string> res;
        for (std::string key : keys){

            const auto it{tags.find(key)};
            if (it == std::cend(tags))
                continue;

            if (it->second.empty())
                continue;

            for (auto& elm : it->second){


                res.emplace_back(std::move(elm));
            }

        }

        return res;

    }

    std::vector<Artist> getArtists(const TagMap& map, std::initializer_list<std::string> artistTagNames){

        std::vector<Artist> res;

        const auto artistNames{getFirstMatch(map, artistTagNames)};

          std::transform(artistNames.cbegin(), artistNames.cend(), std::back_inserter(res), [&](std::string name) { return Artist{QString(name.c_str())};});


        return res;

    }

    void getImage(TagLib::ID3v2::FrameList frameLists, Track& track){

        auto frame_img = frameLists.front();
        auto temp = frame_img->toString();
        auto img = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frame_img);
        Image track_img;
        track_img.mimeType = getMimyType(img->mimeType().to8Bit());
        track_img.data = img->picture().data();
        track.image = track_img;

    }

    std::optional<Track> TaglibParser::parse(std::filesystem::path path)
    {

        TagLib::FileRef file  = TagLib::FileRef(path.c_str(), true, parsingSpeed);
        if(file.isNull())
            return std::nullopt;

        const auto audio_properties = file.audioProperties();
        if(!audio_properties)
            return std::nullopt;

        Track track;
        track.bitrate = audio_properties->bitrate();
        track.sampleRate = audio_properties->sampleRate();
        track.channels = audio_properties->channels();
        audio_properties->lengthInMilliseconds();

        auto properties = constructTagMap(file.file()->properties());

        track.artists = getArtists(properties, {"ARTISTS", "ARTIST"});

        for (auto[tag, values] : properties){

            if (!values.empty())
                processTag(track, tag, values);
        }


        auto getAPETags = [&](const TagLib::APE::Tag* apeTag)
        {
            if (!apeTag)
                return;

            mergeTagMaps(properties, constructTagMap(apeTag->properties()));
        };

        if (TagLib::MPEG::File* mp3File {dynamic_cast<TagLib::MPEG::File*>(file.file())}){

            if (mp3File->ID3v2Tag())
            {
                const auto& frameListMap {mp3File->ID3v2Tag()->frameListMap()};

                if (!frameListMap["APIC"].isEmpty()){
                    getImage(frameListMap["APIC"], track);
                }
            }
            getAPETags(mp3File->APETag());
        }

        return track;
    }


    void TaglibParser::processTag(Track& track, std::string tag, std::vector<std::string> values)
    {

        QString value{values.front().c_str()};

        if (tag == "TITLE")
            track.title = value;
        else if (tag == "DATE")
            track.date = QDateTime::fromString(value);
        else if (tag == "YEAR" && !track.date.isValid())
            track.date = QDateTime::fromString(value);
        else if (tag == "ORIGINALDATE")
            track.date = QDateTime::fromString(value);
        else if (tag == "ORIGINALYEAR" && !track.date.isValid())
            track.date = QDateTime::fromString(value);

    }


    static
    TagLib::AudioProperties::ReadStyle
    ParserSpeedToTagLibReadStyle(ParserSpeed readStyle)
    {
        switch (readStyle)
        {
            case ParserSpeed::Fast: return TagLib::AudioProperties::ReadStyle::Fast;
            case ParserSpeed::Average: return TagLib::AudioProperties::ReadStyle::Average;
            case ParserSpeed::Low: return TagLib::AudioProperties::ReadStyle::Accurate;
        }
    }

    TaglibParser::TaglibParser(ParserSpeed speed)
    {
        parsingSpeed = ParserSpeedToTagLibReadStyle(speed);
    }


}
