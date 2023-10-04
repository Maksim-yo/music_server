#include "metadata/IParser.h"
#include "metadata/TagLib.h"

namespace Metadata {

    std::unique_ptr<IParser> createParser(ParserType type, ParserSpeed speed){


        switch(type){

            case ParserType::Taglib:
                return std::make_unique<TaglibParser>(speed);

        }
    }

}
