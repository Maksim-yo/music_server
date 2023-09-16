#include "services/database/Track.h"


namespace Database::Model {

    std::unique_ptr<BelongsTo<Lyric, Track> > Lyric::track()
    {
        auto relation = belongsTo<Track>();
        relation->withDefault();
        return relation;
    }
}
