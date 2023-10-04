#ifndef YEARS_HPP
#define YEARS_HPP

#include <orm/tiny/model.hpp>


namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::HasMany;

    class Year final: public Model<Year>{

        friend Model;
        using Model::Model;

    private:
        QString u_table {"Years"};
        QString u_primaryKey {"Id"};
        bool u_timestamps = false;


    };
}
#endif
