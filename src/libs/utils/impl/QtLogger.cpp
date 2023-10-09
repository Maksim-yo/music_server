#include "utils/QtLogger.h"
#include "utils/Log.h"
#include <QtDebug>


void QtLogger::processLog(const Log &log)
{
    Severity severity = log.getSeverity();

    switch(severity) {

    case Severity::FATAL:
        qFatal(log.getMessage().c_str());
        break;
    case Severity::ERROR:
        qWarning() << log.getMessage().c_str();

        qCritical(log.getMessage().c_str());
        break;
    case Severity::WARNING:

        qWarning(log.getMessage().c_str());
        break;
    case Severity::INFO:

        qInfo(log.getMessage().c_str());
        break;
    case Severity::DEBUG:

        qDebug(log.getMessage().c_str());
        break;
    }
}

