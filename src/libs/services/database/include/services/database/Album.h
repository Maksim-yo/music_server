#ifndef ALBUMS_HPP
#define ALBUMS_HPP
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/pivot.hpp>

#include "services/database/Image.h"
#include "services/database/Track.h"

namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsToMany;
    using Orm::Tiny::Relations::Pivot;
    using Orm::Tiny::Relations::HasOne;
    using Orm::Tiny::Relations::BelongsTo;

    class Artist;
    class Track;

    class Album final: public Model<Album, Artist, Track, Image, Pivot>{

        friend Model;
        using Model::Model;

    public:
        struct FindParams {

            std::optional<qint64> id;
            std::optional<QString> title;
            std::optional<QDateTime> releaseDate;
            std::optional<QList<Track>> tracks;
            std::optional<QList<Artist>> artists;
        };

        void                setName(QString name)       {setAttribute("Name",name);}
        void                setTrack(Track* track)       {tracks()->save(*track);}
        void                setArtist(Artist* _artist)   {artist()->save(*_artist);}

        QString             getName()    {return getAttribute<QString>("Name");}
        QList<Artist>       getArtist();
        QList<Image>        getImage();
        QList<Track*>        getTracks();

        std::unique_ptr<BelongsToMany<Album, Artist>>          artist();
        std::unique_ptr<BelongsToMany<Album, Track>>           tracks();
        std::unique_ptr<BelongsToMany<Album, Image>>           image();


        static std::optional<Album>             findById(qint64 id) {return Album::find(id);}
        static std::optional<QList<Album>>      findByTitle(QString);
        static std::optional<QList<Album>>      findByParams();

        static Album                            createAlbum(QString title);
    private:
        QString u_table {"Albums"};
        bool u_timestamps = false;
        QString u_primaryKey {"Id"};

        QHash<QString, RelationVisitor> u_relations {
            {"tracks", [](auto &v) { v(&Album::tracks); }},
            {"artist", [](auto &v) { v(&Album::artist); }},
            {"image",  [](auto &v) { v(&Album::image); }},

    };

  };
}
#endif
