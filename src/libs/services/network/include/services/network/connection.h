#ifndef CONNECTION_H
#define CONNECTION_H

#include "Constants.h"
//#include "message.h"
//#include <QAbstractSocket>
#include <QTcpSocket>

#define VERBOSE_STATES


//connection is a general class for client and server side
//if dropConnectionTimer is set is a server side else client
//guess:: make an explicit server and client type;


class message;
class QTimer;
class Connection: public QTcpSocket
{
    Q_OBJECT
public:
    Connection(QTcpSocket*& socket, Owner owner);
    void send();
    void recieve();
    QAbstractSocket::SocketState get_state();
    void setDropConnectionTimer();              // for using in server side
    void setConnectionEstablishingTimer();
    QTcpSocket* get_socket();
    void isConnected();                         //socket can be already connected
    QString local_address();
    QString peer_address();

    QByteArray* get_last_msg_out() {return _get_last_msg(outgoing);}
    QByteArray* get_first_msg_out() {return _get_first_msg(outgoing);}
    QByteArray* get_last_msg_in() {return _get_last_msg(incoming);}
    QByteArray* get_first_msg_in() {return _get_first_msg(incoming);}

    void add_first_msg_in(message* msg) ;
    void add_first_msg_out(message* msg);
    void add_last_msg_in(message* msg) ;
    void add_last_msg_out(message* msg);

    QByteArray* _get_last_msg(QList<QByteArray*>&);
    QByteArray* _get_first_msg(QList<QByteArray*>&);

signals:
    void dropConnection();
    void connectionEstablisng();                //for client side checking if connection is established
    void s_connectionEstablished();
    void new_message_income();
    void new_message_outgoing();
public slots:
    void deleteConnection();
    void checkConnectonEstablishing(QAbstractSocket::SocketState);
#ifdef VERBOSE_STATES
    void connectionStateChanged();
#endif


protected:
    void timerEvent(QTimerEvent *event) override;


private:
    QTcpSocket* _socket;
    QDataStream stream;
    int dropConnectionTimer;
    int connectionEstablishingTimer;
    qint64 start;                        //time when started attemping to connect
    qint64 startConnected;               //time when connection is established
    qint64 end;
    QList<QByteArray*> outgoing;
    QList<QByteArray*> incoming;
    Owner owner;
};

#endif // CONNECTION_H
