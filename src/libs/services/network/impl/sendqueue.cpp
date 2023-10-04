#include "services/network/sendqueue.h"
#include <QTimer>
#include <algorithm>


namespace Network {


SendQueue::SendQueue(QObject* parent): QObject(parent), throttleTimer(std::move(new QTimer(this)))
{

//    connect(throttleTimer, &QTimer::timeout, this, &SendQueue::throttleExpired);

}
void SendQueue::sendData(messageParams msg){


    _sendQueue[msg.getPiorety()].emplace_back(msg.release()->serialize());
    if(_state==State::Idle)
        emit readyToSend();

}


std::optional<QByteArray*> SendQueue::getMessages(int bytes){


    QByteArray* msgBuffer = new QByteArray();
    QDataStream in(msgBuffer , QIODevice::ReadWrite);

    if (_state !=State::Idle)
        return std::nullopt;

    bool isMessagesReady = false;

    for (auto& [priorety, messages] : _sendQueue){

        if (isMessagesReady)
            break;

        for (auto msg : messages){

            messages.pop_front();
            if (bytes < msgBuffer->size() + msg->size())            //slicing data
            {
                auto temp = new QByteArray(msg->left(bytes - msgBuffer->size()));
                _sendQueue[priorety].emplace_front(new QByteArray(std::move(msg->right(msg->size() - bytes - msgBuffer->size()))));
                msg = temp;
            }

            msgBuffer->append(*msg);
            if (msgBuffer->size() >= bytes){
                isMessagesReady = true;
            }


        }
    }

    clearQueue();


    return msgBuffer;



}


void SendQueue::clearQueue(){

    if(_sendQueue[messageParams::Priorety::High].size() == 0) _sendQueue.erase(messageParams::Priorety::High);
    if(_sendQueue[messageParams::Priorety::Normal].size() == 0) _sendQueue.erase(messageParams::Priorety::Normal);
    if(_sendQueue[messageParams::Priorety::Low].size() == 0) _sendQueue.erase(messageParams::Priorety::Low);

}



void SendQueue::throttleExpired(){

    _state = State::Idle;
    qDebug() << "throttle expired";
}


void SendQueue::throttle(std::chrono::seconds duration){


    assert(_state==State::Idle);

    _state = State::Throttled;
    throttleTimer->start(duration);
    qDebug() << "throttle started for duration: " << duration.count();

    }
}
