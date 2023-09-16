#ifndef SERVER_H
#define SERVER_H
#include <memory>
#include <QObject>

class QTcpSocket;
class unique_ptr;
class QTcpServer;

class Proxy;

namespace Network {
class ConnectionManager;


class Server: public QObject
{

    Q_OBJECT

public:
    void run();
    int set_proxy(Proxy proxy);
    static Server* get_instance();
    Server();
private:
     bool set_socket(std::string ip, int port = 0);
     void connect_socket();
//     void readPendingDatagrams();
//     void processTheDatagram(QNetworkDatagram datagram);
//     void incomingConnection(qintptr socketDescriptor) override;
//     std::vector<ConnectionManager<QTcpSocket>*> manager;
     QTcpSocket* _socket;
     ConnectionManager* con_manager;
     QTcpServer* serv;
};

}
#endif // SERVER_H
