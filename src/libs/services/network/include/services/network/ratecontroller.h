#ifndef RATECONTROLLER_H
#define RATECONTROLLER_H
#include <QSet>
#include <QObject>
#include <QElapsedTimer>

namespace Network{

class IConnection;

class RateController: public QObject
{
    Q_OBJECT
public:
    RateController();
    void addConenction(IConnection* con);
    void removeConnection(IConnection* con);
    inline int uploadLimit() const { return upLimit; }
    inline int downloadLimit() const { return downLimit; }
    inline void setUploadLimit(int bytesPerSecond) { upLimit = bytesPerSecond; }
    void setDownloadLimit(int bytesPerSecond);

private:
    void transfer();
    void scheduleTransfer();

    int upLimit{0};
    int downLimit{0};
    QElapsedTimer stopWatch;
    QSet<IConnection*> connections;
    bool transferSchedule{false};
};
}
#endif // RATECONTROLLER_H
