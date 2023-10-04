#ifndef IMAGES_HPP
#define IMAGES_HPP
#include <orm/tiny/model.hpp>
#include <orm/tiny/relations/pivot.hpp>

namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsToMany;
    using Orm::Tiny::Relations::Pivot;
    using Orm::Tiny::Relations::HasOne;
    using Orm::Tiny::Relations::BelongsTo;

    class Album;

    class Image final: public Model<Image, Album, Pivot>{


        friend Model;
        using Model::Model;

        std::unique_ptr<BelongsToMany<Image, Album>>           album();


    private:

        QHash<QString, RelationVisitor> u_relations {
            {"album", [](auto &v) { v(&Image::album); }},

        };

        QString u_table {"Images"};
        bool u_timestamps = false;
        QString u_primaryKey {"Id"};


    };
}
#endif
