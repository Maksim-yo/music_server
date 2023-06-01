#ifndef SESSION_H
#define SESSION_H
//#include "message.h"
//#include "../utils/iproccessmessage.h"
#include "Constants.h"
#include <QObject>

class message;
class IProccessMessage;
class QTimer;
class QTcpSocket;
class Connection;
class Session: public QObject
{
    Q_OBJECT
public:
    Session(QTcpSocket*&, IProccessMessage*,Owner own, QObject* parent = nullptr);
    Session(Connection*&, IProccessMessage*, QObject* parent = nullptr);
    void get_state();
    Connection* get_connection();
    void write(message* msg);
    void read(message*& msg);

    QByteArray* get_last_msg_out();
    QByteArray* get_first_msg_out();
    QByteArray* get_last_msg_in();
    QByteArray* get_first_msg_in();

    QString local_address();
    QString peer_address();

    /*void add_first_msg_in(message* msg) {incoming.append(msg);}*/
    void add_last_msg_in(message* msg);
//    void add_first_msg_out(message* msg);
    void add_last_msg_out(message* msg) ;


    void ping(qint64 count);
signals:
    void socketReadyRead();
    void socketReadyWrite();

private slots:
    void readMessage();
//    void dbgRecieve(message*& msg);
//    void dbgSend(message*& msg);

private:
    Connection* conn;
    QTimer* timer;
    bool is_auth = false;
    IProccessMessage* proccess_msg;

};

#endif // SESSION_H
