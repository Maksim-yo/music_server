//#ifndef CONNECTION_TEST_H
//#define CONNECTION_TEST_H
//#include <QTcpServer>
//#include "services/network/tcpconnection.h"
//#include <queue>
//#include <memory>
//#include "services/network/sendqueue.h"


//class Server: public QTcpServer{


//public:
//    Server();

////    static Server* get_instance();

//    std::queue<TCPConnection*> getConnections(){
//        return connections;
//    }


//protected:
//    void incomingConnection(qintptr socketDescriptor){

//        QTcpSocket* clientSocket = new QTcpSocket();
//        clientSocket->setSocketDescriptor(socketDescriptor);
//        TCPConnection* con = new TCPConnection(clientSocket, Owner::Client);
//        SendQueue* queue = new SendQueue(con);
//        con->setQueue(queue);
//        connections.emplace(con);

//    }

//private:
//    QTcpServer* server;
//    std::queue<TCPConnection*> connections;

//};
//#endif // CONNECTION_TEST_H
