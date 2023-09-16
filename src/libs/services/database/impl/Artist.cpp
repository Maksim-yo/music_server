#include "services/database/Track.h"



namespace Database::Model {


    QList<Track *> Artist::getTracks()
    {
        QList<Track*> data;
        auto tracks = getRelationValue<Track>("tracks");
        for(Track* track : tracks){
            data.emplace_back(track);
        }
        return data;
    }
    std::optional<QList<Album> > Artist::getAlbums()
    {
        auto data = getRelationValue<Album>("albums");
        QList<Album> albums;
        return albums;
    }

    std::unique_ptr<BelongsToMany<Artist, Track>>
        Artist::tracks(){
        return belongsToMany<Track>("Track_artist", "Artist", "Track", "ArtistId", "TrackId");
    }

    std::unique_ptr<BelongsToMany<Artist, Album> >
        Artist::albums()
    {
        return belongsToMany<Album>("Album_artist", "Artist", "Album", "ArtistId", "Id");
    }

    std::optional<Artist::FindParams> Artist::findByParams(FindParams params)
    {
//        return Artist::findById(params.getId());
        return std::nullopt;
    }

    std::optional<Artist> Artist::findById(qint64 id)
    {
        return Artist::find(id);
    }

    std::optional<Artist> Artist::findByName(QString name)
    {
        return Artist::whereEq("Name", name)->first();
    }

    Artist Artist::createArtist(QString name)
    {
        QVector<AttributeItem> items{{"Name", name.toStdString().c_str()}};
        return Artist::create(items);
    }


}
