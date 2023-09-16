#pragma once
#ifndef LYRICS_HPP
#define LYRICS_HPP
#include <orm/tiny/model.hpp>
//#include "services/database/Track.h"

namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsTo;

    class Track;

    class Lyric final: public Model<Lyric, Track>{

        friend Model;
        using Model::Model;

    public:
        std::unique_ptr<BelongsTo<Lyric, Track>>
        track();

    private:

        QHash<QString, RelationVisitor> u_relations {
            {"track", [](auto &v) { v(&Lyric::track); }},
        };
        QString u_table {"Lyrics"};
        QString u_primaryKey {"Id"};

        bool u_timestamps = false;


    };

}
#endif
