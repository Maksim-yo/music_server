#ifndef STREAMCONNECTION_H
#define STREAMCONNECTION_H


//#include "message.h"
//#include <QAbstractSocket>
#include <QTcpSocket>

#include "services/network/Constants.h"
#include "services/network/IConnection.h"
#include "services/network/sendqueue.h"

#define VERBOSE_STATES


//connection is a general class for client and server side
//if dropConnectionTimer is set is a server side else client
//guess:: make an explicit server and client type;
class QTimer;

namespace Network {

class message;
class TCPConnection: public QTcpSocket, public IConnection
{
    Q_OBJECT
public:

    TCPConnection(const TCPConnection&) = delete;
    TCPConnection(const TCPConnection&&) = delete;
    TCPConnection& operator=(const TCPConnection&) = delete;
    TCPConnection& operator=(const TCPConnection&&)=delete;

    TCPConnection(QTcpSocket*& socketowner);

    void setQueue(SendQueue*& queue) override;
    //TODO: best? size for reading and writing messages for concrete connection
    qint64 send(qint64 bytes) override;
    qint64 recieve(qint64 bytes) override;
    QTcpSocket* get_socket() override;
    void isConnected() override;                         //socket can be already connected
    QAbstractSocket::SocketState get_state() override {return _socket->state();}
    qint64 socketBytesAvailable() override { return _socket->bytesAvailable();}
    void setDropConnectionTimer();
    void setConnectionEstablishingTimer() override;
    qint64 bytesToWrite() override { return _socket->bytesToWrite();}
    bool canTransferMore() override;

signals:

//    void readyToSend();


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
};
}

#endif // STREAMCONNECTION_H
