#ifndef ARTISTS_HPP
#define ARTISTS_HPP
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/pivot.hpp>
#include "services/database/Track.h"

namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsToMany;
    using Orm::Tiny::Relations::Pivot;

    class Track;
    class Album;

    class Artist final: public Model<Artist, Album, Track, Pivot>{

        friend Model;
        using Model::Model;

    public:

        struct FindParams{

            qint64 id;
            QString artistName;

            void setName(QString name) {artistName = name; }
            void setId(qint64 _id) {id = _id;}

            qint64 getId() const {return id;}

        };

        void            setName(QString name)   {setAttribute("Name", name);}
        void            setTrack(Track* track)  {tracks()->save(*track);}

        QString         getName()               {return getAttribute<QString>("Name");}
        QList<Track*>   getTracks();

        std::optional<QList<Album> > getAlbums();

//        void    save()                  {push();}

        std::unique_ptr<BelongsToMany<Artist, Track>>
        tracks();
        std::unique_ptr<BelongsToMany<Artist, Album>>
        albums();

        static std::optional<FindParams> findByParams(FindParams params);


        static std::optional<Artist>                 findById(qint64 id);
        static std::optional<Artist>                 findByName(QString name);
        static Artist                                createArtist(QString name);

//        QList<Track>                                get

    private:

        QHash<QString, RelationVisitor> u_relations {
            {"tracks", [](auto &v) { v(&Artist::tracks); }},
            {"albums", [](auto &v) { v(&Artist::albums); }},

        };

        QString u_table {"Artist"};
        QString u_primaryKey {"ArtistId"};

        bool u_timestamps = false;


    };


}

#endif
