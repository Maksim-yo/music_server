#include "services/network/messagehandles.h"
#include "services/network/message.h"


bool BaseHandle::is_success(){ throw std::exception(); }
void BaseHandle::proccess(message& msg, Owner owner){throw std::exception();}



void PingHandle::proccess(message& msg, Owner owner) {


//    ping_message* _msg = reinterpret_cast<ping_message*>(&msg);
//    if (QDateTime() != start_time)
//        start_time = QDateTime::currentDateTime();
//    if (count == -1)
//        count = _msg->get_count();


//    QDateTime send_time = _msg->get_head().get_time_send();
//    QDateTime cur_time = QDateTime::currentDateTime();
//    quint64 time_diff = cur_time.toMSecsSinceEpoch()- send_time.toMSecsSinceEpoch();

//    if(owner == _msg->get_owner())
//        qDebug() << "ping to: " << _msg->get_ip_dest() << time_diff << " ms.";
//    else {
//        count--;
//        _msg->decrease_count();
//    }
}

bool PingHandle::is_success()
{
    return success;
}

void PingHandle::reset(){

    success = false;
    count = -1;
    start_time = QDateTime();
    end_time = QDateTime();
}

QDateTime PingHandle::start_time = QDateTime();
QDateTime PingHandle::end_time = QDateTime();
bool PingHandle::success = false;
int PingHandle::count = -1;



