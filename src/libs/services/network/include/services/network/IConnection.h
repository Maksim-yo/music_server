#ifndef ICONNECTION_H
#define ICONNECTION_H
#include <QByteArray>
#include <QList>
#include <QObject>
#include <QAbstractSocket>
#include <memory>
#include "services/network/message.h"

namespace Network {

    class SendQueue;

    enum ConnType{

        TCP,
    };

    class IConnectionSignals: public  QObject{

        Q_OBJECT

    signals:
        void readyToSend();
        void newRecieveMessages();
        void dropConnection();
        void socketStateChanged(QAbstractSocket::SocketState);
        void bytesWritten(qint64);
        void connectionEstablished();
    };

    class IConnection {

    public:

        IConnectionSignals _signals;

        virtual ~IConnection() = default;

        virtual qint64 send(qint64 bytes)=0;
        virtual qint64 recieve(qint64 bytes)=0;
        virtual void isConnected()=0;
        virtual QAbstractSocket* get_socket()=0;
        virtual QAbstractSocket::SocketState get_state()=0;
        virtual bool canTransferMore() = 0;
        virtual qint64 socketBytesAvailable()=0;
        virtual qint64 bytesToWrite()=0;
        virtual void setConnectionEstablishingTimer() = 0;
        virtual void setQueue(SendQueue*& queue) { _sendQueue = queue;}
        QByteArray& getRecieveMessages() {return recieveMessages;}
        SendQueue*& getQueue() {return _sendQueue;}


    protected:

        SendQueue* _sendQueue;                  //should be templated from hardcoding`
        QByteArray recieveMessages;
        int dropConnectionTimer{0};
        int connectionEstablishingTimer{0};
        qint64 start{0};                        //time when started attemping to connect
        qint64 startConnected{0};               //time when connection is established
        qint64 end{0};

    };

    template<typename SocketType>
    std::unique_ptr<IConnection> createConnection(SocketType socket, ConnType type);
}
#endif // ICONNECTION_H
