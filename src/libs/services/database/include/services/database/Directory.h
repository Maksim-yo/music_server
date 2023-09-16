#pragma once

//#include <services/database/Url.h>

#ifndef DIRECTORIES_HPP
#define DIRECTORIES_HPP
#include <orm/tiny/model.hpp>


namespace Database::Model {

    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::HasMany;
    class Url;

    class Directory final: public Model<Directory, Url>{

        friend Model;
        using Model::Model;

    public:

        QString       getPath()                {return getAttribute<QString>("DirectoryPath");}
        QDateTime     getChangeDate()          {return getAttribute<QDateTime>("ChangeDate");}
        void          setPath(QString path)    {setAttribute("DirectoryPath", path);}
        void          setChangeDate(QDateTime time)  {setAttribute("ChangeDate", time);}
        std::unique_ptr<HasMany<Directory, Url>> urls();

    private:
        QHash<QString, RelationVisitor> u_relations {
            {"urls", [](auto &v) { v(&Directory::urls); }},
        };

        QString u_table {"Directories"};
        QString u_primaryKey {"DirectoryId"};

        bool u_timestamps = false;
    };
}
#endif
