#include "services/database/Track.h"


namespace Database::Model {


    std::unique_ptr<BelongsTo<Track, Year>>
    Track::year()
    {
        return belongsTo<Year>("ReleaseDate", "Id");
    }

    std::unique_ptr<HasOne<Track, Lyric>>
    Track::lyrics(){

        auto relation = hasOne<Lyric>("Lyrics", "Id");
        relation->withDefault();
        return relation;

    }

    std::unique_ptr<BelongsToMany<Track, Artist>>
    Track::artists(){

        return belongsToMany<Artist>("Track_artist", "Track", "Artist", "TrackId", "ArtistId", QString::fromUtf8(__func__) );
    }

    std::unique_ptr<BelongsToMany<Track, Album>>
    Track::albums()
    {
        return belongsToMany<Album>("Track_album","Album", "Track","TrackId", "Id", QString::fromUtf8(__func__));
    }

    std::unique_ptr<HasOne<Track, Url>>
    Track::url(){

        return hasOne<Url>("Url", "Urlid");
    }

    Track Track::createTrack(FindParams findParams)
    {
        QVector<AttributeItem> data;
//        data.push_back{"Title", findParams.title};
        data.emplace_back("Title", findParams.title.value());
        data.emplace_back("Bitrate", findParams.bitrate.value());
        data.emplace_back("SampleRate", findParams.sampleRate.value());
        if(findParams.discNumber)
            data.emplace_back("DiscNumber", findParams.discNumber.value());
        if(findParams.releaseDate)
            data.emplace_back("ReleaseDate", findParams.releaseDate.value());

        return Track::create(data);

        }



//    Track::Track(QString title, qint64 bitrate, qint64 sampleRate) : Model()
//    {
//        create({{"Title", title}, {"Bitrate", bitrate}, {"SampleRate", sampleRate}});
//    }

    Track::FindParams Track::getParams()
    {
//        return {getKey().toInt(), getTitle(), getBitrate(), getSampleRate(), getDiscNumber(), getTrackNumber(), getReleaseDate(), getLyrics(), getArtists()};
        return {};
    }

    QList<Album*> Track::getAlbums()
    {
        auto it = getRelationValue<Album>("albums");
        QList<Album*> models;
        std::transform(it.begin(), it.end(), std::back_inserter(models), [&](Album* album){ return album;});
        return models;
    }

    QList<Artist*> Track::getArtists()
    {
       auto it = getRelationValue<Artist>("artists");
       QList<Artist*> models;
       std::transform(it.begin(), it.end(),  std::back_inserter(models), [&](Artist* artist){ return artist;});
       return models;

    }


    std::optional<Lyric> Track::getLyrics()  {


        auto lyric = getRelationValue<Lyric, Orm::One>("lyrics");
        using res = std::optional<Lyric>;
        if (lyric->doesntExist())
            return res{};
        return res{*lyric};

    }

    std::optional<Track> Track::findById(qint64 id)
    {
        return Track::find(id);
    }

    QList<Track> Track::findByName(QString name)
    {
        auto tracks = Track::whereEq("Name", name)->get();
        return {Track()};

    }

//    std::optional<Artist> Track::findByArtists(Artist)
//    {

//    }

//    std::optional<QList<Track>> Track::findByParams(FindParams params)
//    {
//        QList<Track> tracks;
//        if (params.title.has_value())
//            tracks = findByName(params.title.value());



//        if (params.artists.has_value())
//        {

//            for
//        }

//    }





}

