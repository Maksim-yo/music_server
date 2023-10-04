#pragma once
#include <orm/tiny/model.hpp>


#ifndef PLAYLISTS_HPP
#define PLAYLISTS_HPP

namespace Database::Model {
    using Orm::Tiny::Model;

    class PlayList final: public Model<PlayList>{



        friend Model;
        using Model::Model;
    private:
        QString u_table {"Playlists"};
        QString u_primaryKey {"Id"};

        bool u_timestamps = false;


    };
}
#endif
