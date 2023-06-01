#ifndef IPROCCESSMESSAGE_H
#define IPROCCESSMESSAGE_H
//#include "../music_server/message.h"
//#include "../music_server/session.h"

class QByteArray;
class Session;
class IProccessMessage
{
public:
    virtual void proccess(QByteArray*&) = 0;
    virtual void set_session(Session* session) = 0;
    IProccessMessage(){}
    ~IProccessMessage(){}
protected:
    Session* _session;

};

#endif // IPROCCESSMESSAGE_H
