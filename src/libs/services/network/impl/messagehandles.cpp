#include "services/network/messagehandles.h"
#include "services/network/message.h"
#include "services/database/Track.h"
#include "filesystem/FileSystemWrapper.h"

namespace Network {


    std::optional<messageParams> MessageHandler::proccess(std::unique_ptr<message> req, Constants::MessageHttpType type){

        auto classType = req->get_type();
        std::string clsTypeStr = Helper::QtEnumToString(classType);
        std::string clsNameHandler = parseClassName(clsTypeStr) + "Handler";
        return (*getMap())[clsNameHandler][type](std::move(req));
    }



    std::optional<messageParams> TrackHandler::proccessGet(std::unique_ptr<message> req)
    {
//        TrackMetadata* reqTrack = dynamic_cast<TrackMetadata*>(req.get());
////        Database::Model::Track::FindParams findParams;
////        findParams.setId();
//        auto track = Database::Model::Track::findById(reqTrack ->getId());
//        if (!track.has_value())
//            return {};
//        TrackMetadata* responseMsg = new TrackMetadata();

//        responseMsg->setId(track->getId());
//        responseMsg->setTitle(track->getTitle());
//        auto bitrate = track->getBitrate();
//        auto sampleRate = track->getSampleRate();
//        auto discNumber = track->getDiscNumber();
//        auto trackNumber = track->getTrackNumber();
//        auto releaseDate = track->getReleaseDate();
//        bool isImageNeed = reqTrack ->getIsImageNeed();
//        bool isDataNeed = reqTrack ->getIsDataNeed();
//        FileSystemNamespace::File trackData;

//        if (isImageNeed || isDataNeed){

//            auto album = track->getAlbums().first();
//            if (isDataNeed)
//               trackData = FileSystemNamespace::FileSystemWrapper::getTrack(track.value(), 0, 20000);
////            if(isImageNeed)
//            if(isImageNeed)
//                responseMsg->setIsImageNeed(false);

//        }
//        if(bitrate.has_value()) responseMsg->setBitrate(bitrate.value());
//        if(sampleRate.has_value()) responseMsg->setSampleRate(sampleRate.value());
//        if(discNumber.has_value()) responseMsg->setSampleRate(sampleRate.value());
//        if(trackNumber.has_value()) responseMsg->setTrackNumber(trackNumber.value());
//        if(releaseDate.has_value()) responseMsg->setReleaseDate(releaseDate.value());

//        return std::make_optional<messageParams>(messageParams::High, std::move(std::make_unique<message>(std::move(static_cast<message*>(responseMsg)))));
    return std::nullopt;
    }

    std::optional<messageParams> ArtistHandler::proccessGet(std::unique_ptr<message> req)
    {
        Artist* artist = dynamic_cast<Artist*>(req.get());
        Database::Model::Artist::FindParams findParams;
        findParams.setId(artist->getId());
        findParams.setName(artist->getName());

        auto res = Database::Model::Artist::findByParams(std::move(findParams));
        return std::nullopt;
    }



    std::unique_ptr<MessageHandler> createMessageHandler(){

        std::unique_ptr<MessageHandler> msgHandler = std::make_unique<MessageHandler>();
        msgHandler->registerClass<TrackHandler>("TrackHandler");
        msgHandler->registerClass<ArtistHandler>("ArtistHandler");

        return msgHandler;

    }


}
