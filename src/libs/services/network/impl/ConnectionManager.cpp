#include <QNetworkDatagram>
#include <QThread>
#include <QGlobalStatic>
#include <QTcpServer>
#include <vector>
#include <QTimerEvent>

#include "services/network/tcpconnection.h"
#include "services/network/proccessmessage.h"
#include "services/network/ConnectionManager.h"
#include "services/network/Constants.h"
#include "services/network/sendqueue.h"

namespace Network {


ConnectionManager::ConnectionManager(QTcpServer* serv, QObject *parent): QObject(parent), _serv(serv), rateController{new RateController()}
{





}


ConnectionManager* ConnectionManager::get_instance(){

    return this;
}


void ConnectionManager::run() {

    connect(_serv, &QTcpServer::newConnection, this, &ConnectionManager::_pendingIncomingConnection);

}

void ConnectionManager::deleteSession(){

    IConnection* conn = qobject_cast<TCPConnection*>(sender());
    connections.erase(std::remove_if(connections.begin(), connections.end(), [&conn](Session*& session){return session->get_connection() == conn;}), connections.end());
}

//need to make multithreading
void ConnectionManager::_pendingIncomingConnection(){

    QTcpSocket *clientsocket = _serv->nextPendingConnection();
    Session* session = createSession(clientsocket, Constants::Owner::Server,this);
    IConnection* connection = session->get_connection();
    rateController->addConenction(connection);
    qDebug() << "New conncetion: " << clientsocket->socketDescriptor();
//    connect(clientsocket, &QTcpSocket::disconnected, clientsocket, &QTcpSocket::deleteLater);
//    connect(clientsocket, &QTcpSocket::readyRead, session, &Session::socketReadyRead);
    connect(&connection->_signals, &IConnectionSignals::dropConnection, this, &ConnectionManager::deleteSession);
    connections.append(std::move(session));

}
}
