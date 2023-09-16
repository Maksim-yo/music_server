#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <vector>
#include <QObject>
#include <QList>
#include <QThread>

#include "services/network/session.h"
#include "services/network/ratecontroller.h"

class QNetworkDatagram;
class QTcpServer;

namespace Network {

    
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
    
        QTcpServer* _serv;
        RateController* rateController;
        QVector<Session*> connections;          //guess: need to replace container
        QVector<ListeningThread> listens_thread;
        QVector<ManagerThread> mana;
    };

}
#endif // CONNECTIONMANAGER_H
