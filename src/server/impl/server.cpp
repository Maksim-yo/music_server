#include <QGlobalStatic>
#include <QUdpSocket>
#include <QtConcurrent/QtConcurrent>

#include "proxy.h"
#include <QTcpServer>
#include "ConnectionManager.h"
#include "server.h"


Q_GLOBAL_STATIC(class Server, _server)

static const int THREAD_COUNT = QThread::idealThreadCount();




Server::Server()/*: serv(std::move(new QTcpServer(this))), con_manager(std::move(new ConnectionManager(serv))) */{

    serv = new QTcpServer(this);
    con_manager = new ConnectionManager(serv, this);
    std::string localhost = "127.0.0.1";
    int port = 3212;
    set_socket(localhost, port);
    qDebug() << "Server is started " << serv->serverAddress() << ":" << port;

}

class Server* Server::get_instance() {

    return _server();
}

void Server::run(){


//    for (int i = 0; i < THREAD_COUNT; ++i)
//        QtConcurrent::run(&con_manager, &ConnectionManager::get_instance);
    con_manager->run();
//        QtConcurrent::run(ConnectionManager(this->soc));

}



void Server::set_socket(std::string ip, int port){

    QString ip_string = QString(ip.c_str());
    QHostAddress _ip = QHostAddress(ip_string);
    serv->listen(_ip, port);




}

void Server::connect_socket(){



}





int Server::set_proxy(Proxy proxy){



}
