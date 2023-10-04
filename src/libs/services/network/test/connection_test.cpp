#include <QTcpServer>
#include <QTcpSocket>
#include <QGlobalStatic>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>
#include <QTest>
#include <QSignalSpy>
#include <queue>
#include <memory>
#include <thread>

#include "services/network/tcpconnection.h"
#include "services/network/message.h"
#include "services/network/sendqueue.h"
#include "services/network/IConnection.h"

using namespace Network;

struct Operation;

class Server: public QTcpServer{

    Q_OBJECT
public:
    Server()    {

        bool isSuccess = this->listen(QHostAddress::Any, 65511);
        QVERIFY(isSuccess == true);
    }


    std::queue<TCPConnection*>& getConnections(){

        return connections;
    }

public slots:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE {

        QTcpSocket* clientSocket = new QTcpSocket();
        clientSocket->setSocketDescriptor(socketDescriptor);
        TCPConnection* con = new TCPConnection(clientSocket);
        SendQueue* queue = new SendQueue(con);
        con->setQueue(queue);
        connections.emplace(con);


    }

private:
    std::queue<TCPConnection*> connections;

};




struct Operation{


    int send(messageParams& msg){

        sizeMessageOut = msg.getMessage()->get_size();
        outgoingMesssage = *msg.getMessage();
        queue->sendData(std::move(msg));
        int written = Conn->send(sizeMessageOut);
        testSignal();
        return written;

    }

    void testSignal(){

        QSignalSpy spy(&Conn->_signals, &IConnectionSignals::bytesWritten);
        bool res = spy.wait();
        QVERIFY(res == true);

    }
    QByteArray getIncomingMessage(){

        return Conn->getRecieveMessages();
    }

    QByteArray getOutgoingMessage(){

        return *outgoingMesssage.serialize();

    }
    int recieve(int bytes){

        sizeMessageIn = bytes;
        return Conn->recieve(bytes);

    }

    TCPConnection*& getConn(){

        return Conn;
    }

public:
    TCPConnection*& Conn;
    SendQueue*& queue;
    int sizeMessageOut{0};
    int sizeMessageIn{0};
    message outgoingMesssage;

};


class Client: public QTcpSocket{


public:
    Client(::Server*& server) {

        QSignalSpy spy(server, &Server::newConnection);

        QTimer timer;
        timer.setSingleShot(true);

        socket = new QTcpSocket();
        socket->connectToHost(QHostAddress::LocalHost, 65511);
        bool isSuccess = socket->waitForConnected();
        QVERIFY(isSuccess == true);
        client = new TCPConnection(socket);
        queueClient = new SendQueue(client);
        client->setQueue(queueClient);
        QTRY_VERIFY_WITH_TIMEOUT(spy.count() == 1, 1000);
        servConn = server->getConnections().front();
        QByteArray data{"Hello"};
        auto temp = data.remove(0,2);
    }

    SendQueue*& getQueue(){
        return queueClient;
    }


    std::pair<Operation, Operation> getConnections(){

        return std::make_pair(Operation{client, queueClient}, Operation{servConn, servConn->getQueue()});

    }
private:
    QTcpSocket* socket;
    TCPConnection* servConn;
    TCPConnection* client;
    SendQueue* queueClient;
};

class TestConenction: public QObject{

    Q_OBJECT
private slots:


    void testFunc(){


            ::Server* server = new ::Server;
            QThread* pThread = new QThread;
            server->moveToThread(pThread);
            pThread->start();
            ::Client client{server};

            auto[_client, _server] = client.getConnections();
            int messageTypeSize = sizeof(std::underlying_type<MessageType>::type);
            messageParams msg = {messageParams::Priorety::High, std::make_unique<message>(MessageType::Ping)};
            auto msg_size = msg.getMessage()->get_size();
            int bytesWritten = _client.send(msg);           //message not sending
            QVERIFY(20 == msg_size);
            int readBytes = _server.recieve(bytesWritten);
            qDebug() << "Written: " << bytesWritten << " Read: " << readBytes;
            QVERIFY(bytesWritten == readBytes);
            qDebug() << "Sending message: " <<  _client.getOutgoingMessage() << " Recieving message: " << _server.getIncomingMessage();
            QVERIFY(_client.getOutgoingMessage() == _server.getIncomingMessage());
    }


    void testSendQueue(){


        SendQueue queue;
        messageParams msg = {messageParams::Priorety::High, std::make_unique<message>(MessageType::Ping)};
        QByteArray* initialeMsg = msg.getMessage()->serialize();
        queue.sendData(std::move(msg));

        QByteArray arr;
        std::optional<QByteArray*> data;
        while (!queue.isEmpty()){            // unnecessary
            data = queue.getMessages(5);
            arr.append(*(data.value()));
        }
        QVERIFY(*initialeMsg == arr);

    }


};


QTEST_MAIN(TestConenction)
#include "connection_test.moc"

