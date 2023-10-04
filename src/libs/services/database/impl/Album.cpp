#include "services/database/Image.h"
#include "services/database/Track.h"

namespace Database::Model {

    QList<Artist> Album::getArtist()
    {
        auto it = getRelationValue<Artist>("artist");
        QList<Artist> models;
        std::transform(it.begin(), it.end(), std::back_inserter(models), [&](Artist* artist){ return *artist;});
        return models;

    }

    QList<Image> Album::getImage()
    {
        auto it = getRelationValue<Image>("image");
        QList<Image> models;
        std::transform(it.begin(), it.end(), std::back_inserter(models), [&](Image* image){ return *image;});
        return models;
    }

    QList<Track*> Album::getTracks()
    {
        auto it = getRelationValue<Track>("tracks");
        QList<Track*> models;
        std::transform(it.begin(), it.end(), std::back_inserter(models), [&](Track* track){ return track;});
        return models;

    }

    std::unique_ptr<BelongsToMany<Album, Artist> > Album::artist()
    {

     return belongsToMany<Artist>("Album_artist", "Album", "Artist", "Id", "ArtistId");
    }

    std::unique_ptr<BelongsToMany<Album,Track>>
    Album::tracks()
    {
        return belongsToMany<Track>("Track_album","Album", "Track","Id", "TrackId", QString::fromUtf8(__func__));
    }

    std::unique_ptr<BelongsToMany<Album, Image>> Album::image()
    {
        return belongsToMany<Image>("Album_image","Album", "Image", "Id", "Id", QString::fromUtf8(__func__));
    }

    std::optional<QList<Album> > Album::findByTitle(QString title)
    {

        return Album::whereEq("Title", title)->get();

    }

    Album Album::createAlbum(QString title)
    {
        QVector<AttributeItem> items{{"Title", title.toStdString().c_str()}};

        return Album::create(std::move(items));
    }





}
