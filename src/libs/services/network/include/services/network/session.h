#ifndef SESSION_H
#define SESSION_H

#include <QObject>

#include "services/network/Constants.h"
#include "services/network/IConnection.h"
#include "services/network/iproccessmessage.h"

class QTimer;
class QTcpSocket;

namespace Network {

class Connection;
class IProccessMessage;
class message;
class TCPConnection;


class Session: public QObject
{
    Q_OBJECT
public:
    Session(std::unique_ptr<IConnection>, std::unique_ptr<IProccessMessage>, Constants::Owner owner, QObject* parent = nullptr);
    void get_state();
    IConnection* get_connection();
    void write(messageParams msg);
//    void read();



    void ping(qint64 count);
signals:
    void socketReadyRead();
    void socketReadyWrite();

private slots:
    void readMessage();
    void handleMessage();
//    void dbgRecieve(message*& msg);
//    void dbgSend(message*& msg);

private:
    std::unique_ptr<IConnection> conn;
    QTimer* timer;
    bool is_auth = false;
    std::unique_ptr<IProccessMessage> proccess_msg;
    QByteArray partialMessage;
    Constants::Owner owner;

};

    Session* createSession(QTcpSocket*& socket, Constants::Owner owner, QObject* parent = nullptr, ConnType type = ConnType::TCP);
}
#endif // SESSION_H
