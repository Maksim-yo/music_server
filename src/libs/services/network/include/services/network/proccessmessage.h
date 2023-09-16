#ifndef PROCCESSMESSAGE_H
#define PROCCESSMESSAGE_H
#include "iproccessmessage.h"
//#include "../music_server/message.h"


namespace Network {

class ProccessMessage: public IProccessMessage
{
public:
    ProccessMessage();

    void proccess(QByteArray&, Constants::MessageType type) override;
    void set_session(Session*) override;
private:
    Constants::Owner owner;
};

}

#endif // PROCCESSMESSAGE_H
