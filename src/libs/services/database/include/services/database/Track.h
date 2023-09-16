#ifndef TRACKS_HPP
#define TRACKS_HPP
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/pivot.hpp>

#include "services/database/Url.h"
#include "services/database/Artist.h"
#include "services/database/Year.h"
#include "services/database/Lyric.h"
#include "services/database/Utils.h"
#include "services/database/Album.h"

namespace Database {

    using TableItem = Orm::Tiny::AttributeItem;

}


namespace Database::Model {
    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsTo;
    using Orm::Tiny::Relations::BelongsToMany;
    using Orm::Tiny::Relations::Pivot;
    using Orm::Tiny::Relations::HasOne;

    class Url;
    class Artist;
    class Year;
    class Lyric;
    class Album;

    class Track final: public Model<Track, Lyric, Year, Artist, Album, Url, Pivot>{

        friend Model;
        using Model::Model;

    public:
//        Track() = default;
//        Track(QString title, qint64 bitrate, qint64 sampleRate);
        struct FindParams {

            std::optional<qint64> id;
            std::optional<QString> title;
            std::optional<qint64> bitrate;
            std::optional<qint64>  sampleRate;
            std::optional<qint64> discNumber;
            std::optional<qint64> trackNumber;
            std::optional<QDateTime> releaseDate;
            std::optional<Lyric> lyrics;
            std::optional<std::vector<Artist>>        artists;

            void                        setId(qint64 _id)                        {id = _id;}
            void                        setTitle(QString name)                   {title = name;}
            void                        setDisckNumber(qint64 num)               {discNumber = num;}
            void                        setTrackNumber(qint64 num)               {trackNumber = num;}
            void                        setBitrate(qint64 rate)                  {bitrate = rate;}
            void                        setSamplerate(qint64 rate)               {sampleRate = rate;}
            void                        setReleaseDate(QDateTime date)           {releaseDate = date;}
//            void                        setLyrics(Lyric lyric)                   {lyrics = std::make_optional<Lyric>(lyric);}
            void                        setArtists(std::vector<Artist> artist)   {artists = artist;}

        };

        FindParams                  getParams();

        void                        setTitle(QString name)          {setAttribute("Title", name);}
        void                        setDisckNumber(qint64 num)      {setAttribute("DisckNUmber", num);}
        void                        setTrackNumber(qint64 num)      {setAttribute("TrackNumber", num);}
        void                        setBitrate(qint64 bitrate)      {setAttribute("Bitrate",bitrate);}
        void                        setSamplerate(qint64 rate)      {setAttribute("SampleRate", rate);}
        void                        setReleaseDate(QDateTime date)  {setAttribute("ReleaseDate", date);}
        void                        setLyrics(Lyric lyric)         {lyrics()->save(lyric);}
        void                        setArtist(Artist artist)       {artists()->save(artist);}
//        void                        setUrl(Url* _url)                {url()->save(*_url);}
//        void                        setUrl(Url* url)                {getRelationValue<Url, Orm::One>("url")->save(*url);}
//        void                        save()                          {push();}

        qint64                              getId()             const    {return getAttribute<qint64>("TrackId");}
        QString                             getTitle()          const    {return getAttribute<QString>("Title");}
        std::optional<qint64>               getBitrate()        const    {return getAttribute<qint64>("Bitrate");}
        std::optional<qint64>               getSampleRate()     const    {return getAttribute<qint64>("SamplRate");}
        std::optional<qint64>               getDiscNumber()     const    {return getAttribute("DiscNumber").isNull() ? std::nullopt : std::make_optional(getAttribute("DiscNumber").toInt());}
        std::optional<qint64>               getTrackNumber()    const    {return getAttribute("TrackNumber").isNull() ? std::nullopt : std::make_optional(getAttribute("TrackNumber").toInt());}
        std::optional<QDateTime>            getReleaseDate()    const    {return getAttribute("ReleaseDate").isNull() ? std::nullopt : std::make_optional(getAttribute("ReleaseDate").toDateTime());}
        Url*                                 getUrl()            {return getRelationValue<Url, Orm::One>("url");}
        QList<Album*>                        getAlbums();
        QList<Artist*>                       getArtists();
        std::optional<Lyric>                getLyrics();

        static std::optional<Track> findById(qint64 id);
        static QList<Track>         findByName(QString name);
//        static std::optional<QList<Track>> findByParams(FindParams params);
//        static std::optional<Artist> findByArtists(Artist);

        std::unique_ptr<BelongsTo<Track, Year>>         year();
        std::unique_ptr<HasOne<Track, Lyric>>           lyrics();
        std::unique_ptr<BelongsToMany<Track, Artist>>   artists();
        std::unique_ptr<BelongsToMany<Track, Album>>    albums();
        std::unique_ptr<HasOne<Track, Url>>          /* */  url();

        static Track                                     createTrack(FindParams findParams);

    private:
        QString u_table {"Tracks"};
        bool u_timestamps = false;
        QString u_primaryKey {"TrackId"};

        QHash<QString, RelationVisitor> u_relations {
            {"year", [](auto &v) { v(&Track::year); }},
            {"lyrics", [](auto &v) { v(&Track::lyrics); }},
            {"artists", [](auto &v) { v(&Track::artists); }},
            {"url", [](auto &v) { v(&Track::url); }},
            {"albums", [](auto &v) { v(&Track::albums); }},

        };

        inline static QStringList u_fillable {
            "Title",
            "Bitrate",
            "SampleRate",
            "Url",
        };
    };


}

#endif
