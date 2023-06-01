#ifndef PROCCESSMESSAGE_H
#define PROCCESSMESSAGE_H
#include "iproccessmessage.h"
//#include "../music_server/message.h"
#include "Constants.h"



class ProccessMessage: public IProccessMessage
{
public:
    ProccessMessage(Owner owner);
    void proccess(QByteArray*&) override;
    void set_session(Session*) override;
private:
    Owner owner;
};

#endif // PROCCESSMESSAGE_H
