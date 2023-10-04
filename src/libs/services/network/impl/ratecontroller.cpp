#include <QTimer>

#include "services/network/ratecontroller.h"
#include "services/network/tcpconnection.h"

namespace Network{

//  NOT THREAD SAFE

RateController::RateController()
{

}

void RateController::addConenction(IConnection *con){


    connect(&con->_signals, &IConnectionSignals::readyToSend, this, &RateController::scheduleTransfer);
    connections << con;
    scheduleTransfer();
}

//todo: make a new algorithm, because this is not rational
//realize flow control
void RateController::transfer(){


    qint64 msecs = 1000;
    if (stopWatch.isValid())
        msecs = qMin(msecs, stopWatch.elapsed());

    qint64 bytesToWrite = (upLimit * msecs) / 1000;
    qint64 bytesToRead = (downLimit * msecs) / 1000;
    if (bytesToWrite == 0 && bytesToRead == 0) {
        scheduleTransfer();
        return;
    }

    QSet<IConnection *> pendingSockets;
    for (IConnection *client : qAsConst(connections)) {
        if (client == nullptr )
            continue;
        if (client->canTransferMore())
            pendingSockets << client;
    }
    if (pendingSockets.isEmpty())
        return;

    stopWatch.start();
    bool canTransferMore;

    do {

        canTransferMore = false;
        qint64 writeChunk = qMax<qint64>(1, bytesToWrite / pendingSockets.size());
        qint64 readChunk = qMax<qint64>(1, bytesToRead / pendingSockets.size());

    for (auto it = connections.begin(), end = connections.end(); it != end; it++) {

        IConnection* socket = *it;
        bool dataTransferred = false;
        qint64 available = qMin<qint64>(socket->socketBytesAvailable(), readChunk);

        if (available > 0) {
            qint64 readBytes = socket->recieve(qMin<qint64>(available, bytesToRead));
            if (readBytes > 0) {
                bytesToRead -=  readBytes;
                dataTransferred = true;
            }
        }


        if (upLimit * 2 > socket->bytesToWrite()) {
            qint64 chunkSize = qMin<qint64>(writeChunk, bytesToWrite);
            qint64 toWrite = qMin(upLimit * 2 - socket->bytesToWrite(), chunkSize);
            if (toWrite > 0) {
                qint64 writtenBytes = socket->send(toWrite);
                if (writtenBytes > 0) {
                    bytesToWrite -= writtenBytes;
                    dataTransferred = true;
                }
            }
        }

        if (dataTransferred && socket->canTransferMore())
            canTransferMore = true;
        else
            it = pendingSockets.erase(it);
        }
    } while (canTransferMore && (bytesToWrite > 0 || bytesToRead > 0) && !pendingSockets.isEmpty());

    if (canTransferMore || bytesToWrite == 0 || bytesToRead == 0)
        scheduleTransfer();
}


void RateController::scheduleTransfer(){

    if (transferSchedule)
        return;

    transferSchedule = true;
    ::QTimer::singleShot(50, this, &RateController::transfer);


}


}
