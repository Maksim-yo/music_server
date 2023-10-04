#ifndef MESSAGEHANDLES_H
#define MESSAGEHANDLES_H
#include <QVector>
#include <functional>

#include "services/network/Constants.h"
#include "services/network/message.h"
#include "utils/Utils.h"

//TODO: move to another service

namespace Network {

    using temp = std::optional<messageParams>;

    //need to reimplemente
    static std::string parseClassName(std::string name){

        auto clsNameEnd = std::find_if(name.begin() + 1, name.end(), [&](const char& elm){
            return std::isupper(elm);
        });
        return std::string(name.begin(), clsNameEnd - 1);

    }

    template<typename T>
    concept InterfaceCompatible = requires(T& t) {

    {t.proccessGet( std::declval<std::unique_ptr<message>>())} ->std::same_as<std::optional<messageParams>>;
    {t.proccessPost( std::declval<std::unique_ptr<message>>())} ->std::same_as<std::optional<messageParams>>;

    };

    typedef std::optional<messageParams> FuncPointer(std::unique_ptr<message>);

    using map_type = std::map<std::string, QVector<FuncPointer*>>;


    struct TrackHandler{

        static std::optional<messageParams> proccessGet(std::unique_ptr<message> req);
        static std::optional<messageParams> proccessPost(std::unique_ptr<message> req);

    };

    struct ArtistHandler {

        static std::optional<messageParams> proccessGet(std::unique_ptr<message> req);
        static std::optional<messageParams> proccessPost(std::unique_ptr<message> req);

    };

    class MessageHandler {

    public:
        template<typename T>
        requires(InterfaceCompatible<T>)
        static void registerClass(std::string name){

            QVector<FuncPointer*> vec = QVector<FuncPointer*>(std::numeric_limits<enum Constants::MessageHttpType>::max());
            vec[Constants::MessageHttpType::Get] = &T::proccessGet;
            vec[Constants::MessageHttpType::Post] = &T::proccessPost;
            getMap()->insert(std::make_pair(name, vec));
        }

        static std::optional<messageParams> proccess(std::unique_ptr<message> req, Constants::MessageHttpType type);
    static map_type* getMap() {

        if(!map) { map = new map_type; }
        return map;
    }

    private:
        static map_type* map;

    };

    std::unique_ptr<MessageHandler> createMessageHandler();
};



#endif // MESSAGEHANDLES_H
