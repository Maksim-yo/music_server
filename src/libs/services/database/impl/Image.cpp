#include "services/database/Album.h"

namespace Database::Model {

    std::unique_ptr<BelongsToMany<Image, Album> > Image::album()
    {
        return belongsToMany<Album>("Album_image","Image", "Album", "Id", "Id", QString::fromUtf8(__func__));

    }
}
