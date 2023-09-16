#include "services/database/Url.h"


namespace Database::Model {


    std::unique_ptr<HasMany<Directory, Url>>
    Directory::urls()
    {
        return hasMany<Url>("Directory", "DirectoryId");
    }

}
