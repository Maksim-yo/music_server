#ifndef URLS_HPP
#define URLS_HPP
#include <orm/tiny/model.hpp>
#include <services/database/Directory.h>
#include <services/database/Track.h>

namespace Database::Model {


    using Orm::Tiny::Model;
    using Orm::Tiny::Relations::BelongsTo;
    using Orm::Tiny::Relations::HasOne;

    class Track;

    class Url final: public Model<Url, Directory, Track>{

        friend Model;
        using Model::Model;

    public:

        void        setDirectory(Directory* _directory)      {directory()->associate(*_directory);}
        void        setPath(QString path)                    {setAttribute("Path", path);}

        Directory*  getDirectory()                           {return getRelationValue<Directory, Orm::One>("directory");}
        QString     getPath()                                {return getAttribute<QString>("Path");}

        std::unique_ptr<BelongsTo<Url, Track>>
        track()
        {
            return belongsTo<Track>("Url", "Urlid");
        }

        std::unique_ptr<BelongsTo<Url, Directory>>
        directory()
        {
            return belongsTo<Directory>("Directory", "DirectoryId");
        }

    private:
        QHash<QString, RelationVisitor> u_relations {
            {"directory", [](auto &v) { v(&Url::directory); }},
            {"track", [](auto &v) { v(&Url::track); }},
        };

        QString u_table {"Urls"};
        QString u_primaryKey {"UrlId"};
        inline static QStringList u_fillable {
            "Path",
        };
        bool u_timestamps = false;


    };




}
#endif
