#include <QGlobalStatic>
#include <QUdpSocket>
#include <QtConcurrent/QtConcurrent>

#include "services/network/proxy.h"
#include <QTcpServer>
#include "services/network/ConnectionManager.h"
#include "services/network/server.h"

namespace Network{
Q_GLOBAL_STATIC(class Server, _server)

static const int THREAD_COUNT = QThread::idealThreadCount();




Server::Server()/*: serv(std::move(new QTcpServer(this))), con_manager(std::move(new ConnectionManager(serv))) */{

    serv = new QTcpServer(this);
    con_manager = new ConnectionManager(serv, this);
    std::string localhost = "127.0.0.1";
    int port = 3212;
    bool res = set_socket(localhost, port);
    con_manager->run();

    if (res)
        qDebug() << "Server is started " << serv->serverAddress() << ":" << port << "\n";
    else
        qDebug() << "ERROR: Server cannot started" << "\n";
}

class Server* Server::get_instance() {

    return _server();
}

void Server::run(){


//    for (int i = 0; i < THREAD_COUNT; ++i)
//        QtConcurrent::run(&con_manager, &ConnectionManager::get_instance);
//        QtConcurrent::run(ConnectionManager(this->soc));

}



bool Server::set_socket(std::string ip, int port){

    QString ip_string = QString(ip.c_str());
    QHostAddress _ip = QHostAddress(ip_string);
    return serv->listen(_ip, port);




}

void Server::connect_socket(){



}



int Server::set_proxy(Proxy proxy){

    return 1;

}
}
