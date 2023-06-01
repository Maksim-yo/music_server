#include "services/network/ConnectionManager.h"
#include <QNetworkDatagram>
#include <QThread>
#include <QGlobalStatic>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <QTimerEvent>
#include "services/network/connection.h"
#include "services/network/proccessmessage.h"

#include "services/network/Constants.h"

ConnectionManager::ConnectionManager(QTcpServer* serv, QObject *parent): QObject(parent), _serv(serv)
{




}


ConnectionManager* ConnectionManager::get_instance(){

    return this;
}


void ConnectionManager::run() {

    connect(_serv, &QTcpServer::newConnection, this, &ConnectionManager::_pendingIncomingConnection);


}


void ConnectionManager::deleteSession(){

    Connection* conn = qobject_cast<Connection*>(sender());
    connections.erase(std::remove_if(connections.begin(), connections.end(), [&conn](Session*& session){return session->get_connection() == conn;}), connections.end());
}
void ConnectionManager::_pendingIncomingConnection(){


    QTcpSocket *clientsocket = _serv->nextPendingConnection();
    Connection* connection = new Connection(clientsocket, Owner::Server);
    connection->setDropConnectionTimer();
    ProccessMessage* prc = new ProccessMessage(Owner::Server);
    Session* session = new Session(connection, prc);
    qDebug() << "New conncetion: " << clientsocket->socketDescriptor();
//    connect(clientsocket, &QTcpSocket::disconnected, clientsocket, &QTcpSocket::deleteLater);
//    connect(clientsocket, &QTcpSocket::readyRead, session, &Session::socketReadyRead);
    connect(connection, &Connection::dropConnection, this, &ConnectionManager::deleteSession);
    connections.append(std::move(session));

}
