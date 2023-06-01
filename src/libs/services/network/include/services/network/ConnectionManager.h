#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include "session.h"
#include <vector>
#include <QObject>
#include <QList>
#include <QThread>


class QNetworkDatagram;
class QTcpServer;

class ManagerThread: public QThread         //manage certain amount of connections
{
    Q_OBJECT
public:
signals:
public slots:
protected:
private:
    
};

class ListeningThread: public QThread 
{
    Q_OBJECT
public:
signals:
public slots:
protected:
private:
    
};

class ConnectionManager: public QObject
{
    Q_OBJECT
public:
    ConnectionManager(QTcpServer* serv, QObject *parent = nullptr);
    ConnectionManager* get_instance();
//    void set_socket(QTcpSocket& sock);
    void run();

protected:
//    void timerEvent(QTimerEvent *event);

public slots:
    void _pendingIncomingConnection();
    void deleteSession();
private:
    QTcpSocket* _socket;
    QTcpServer* _serv;
    QVector<Session*> connections;          //guess: need to replace container
    QVector<ListeningThread> listens_thread;
    QVector<ManagerThread> mana;
};

#endif // CONNECTIONMANAGER_H
