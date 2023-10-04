#ifndef GENRES_HPP
#define GENRES_HPP
#include <orm/tiny/model.hpp>



namespace Database::Model {

    using Orm::Tiny::Model;

    class Genre final: public Model<Genre>{

        friend Model;
        using Model::Model;

    private:
        QString u_table {"Genres"};
        bool u_timestamps = false;
        QString u_primaryKey {"GenreId"};


    };
}
#endif
