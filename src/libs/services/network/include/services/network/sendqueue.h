#ifndef SENDQUEUE_H
#define SENDQUEUE_H
#include <map>
#include <memory>
#include "services/network/message.h"
#include "services/network/IConnection.h"
#include <memory>
#include <queue>
#include <QObject>
#include <optional>


namespace Network {



class SendQueue: public QObject
{
    Q_OBJECT

public:
    SendQueue(QObject* parent = nullptr);
    SendQueue(const SendQueue&) = delete;
    SendQueue(const SendQueue&&) = delete;
    SendQueue& operator=(const SendQueue&) = delete;
    SendQueue& operator=(const SendQueue&&) = delete;

    //TODO? make message on stack memory
    // faster? What's size Of Stack for 1000 users?
    void sendData(messageParams msg);
    void throttle(std::chrono::seconds duration);
    bool isEmpty() { return _sendQueue.size() == 0; }

    std::optional<QByteArray*> getMessages(int bytes);

private slots:

    void throttleExpired();

signals:
    void readyToSend();

private:

    void clearQueue();

    enum State{
        Idle,
        Throttled,
        Sending
    };

    const std::size_t			_maxRetryCount {2};
    const std::chrono::seconds	_defaultRetryWaitDuration {30};
    const std::chrono::seconds	_minRetryWaitDuration {1};
    const std::chrono::seconds	_maxRetryWaitDuration {300};

    QTimer* throttleTimer;
    std::map<messageParams::Priorety, std::deque<QByteArray*>> _sendQueue;
    State _state{State::Idle};

};


}
#endif // SENDQUEUE_H
