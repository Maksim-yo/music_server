#ifndef IPROCCESSMESSAGE_H
#define IPROCCESSMESSAGE_H
#include <memory>
#include "services/network/Constants.h"

class QByteArray;

namespace Network{



    class Session;

    class IProccessMessage
    {
    public:
        virtual void proccess(QByteArray&, Constants::MessageType type) = 0;
        virtual void set_session(Session* session) = 0;
        IProccessMessage(){}
        ~IProccessMessage(){}
    protected:
        Session* _session;

    };

    std::unique_ptr<IProccessMessage> createProcMsg();
}
#endif // IPROCCESSMESSAGE_H
