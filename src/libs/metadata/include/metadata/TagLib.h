#ifndef _TAGLIB_H
#define _TAGLIB_H

#define TAGLIB_STATIC
#include <taglib/audioproperties.h>
#include "metadata/IParser.h"

namespace Database::Model{

    class Track;
}

namespace Metadata {

    class TaglibParser: public IParser {

    public:
          TaglibParser(ParserSpeed speed);
          std::optional<Track> parse(std::filesystem::path file) override;

    private:
          void processTag(Track& track, std::string tag, std::vector<std::string> values) override;
          TagLib::AudioProperties::ReadStyle parsingSpeed;
        };
}

#endif
