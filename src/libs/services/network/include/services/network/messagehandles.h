#ifndef MESSAGEHANDLES_H
#define MESSAGEHANDLES_H
#include "Constants.h"

struct ping_message;
class QString;
class QDateTime;
struct message;

class BaseHandle{

public:
    virtual bool is_success();
    virtual void proccess(message& msg, Owner owner);
};


class PingHandle: BaseHandle {


public:
    PingHandle();
    void proccess(message& msg, Owner owner ) override;
    bool is_success() override;
    void reset();
private:
    static bool success;
    static int count;
    static QDateTime start_time;
    static QDateTime end_time;
};




#endif // MESSAGEHANDLES_H
