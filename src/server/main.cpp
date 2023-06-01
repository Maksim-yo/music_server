#include <QCoreApplication>
#include <QDateTime>

//#include "services/network/servernetwork/connection.h"
//#include "libs/
//#include "services/
//#include "services/network/servernetwork/connection.h"


//#include "libs"
//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    QByteArray localMsg = msg.toLocal8Bit();
//    const char *file = context.file ? context.file : "";
//    const char *function = context.function ? context.function : "";
//    QDateTime cur_time = QDateTime::currentDateTime();
//    char* str = cur_time.toString( Qt::ISODateWithMs).toLocal8Bit().data();
//    switch (type) {
//    case QtDebugMsg:
//        fprintf(stdout, "[%s] Debug: %s\n", str, localMsg.constData()/*file, context.line, function*/);
//        break;
//    case QtInfoMsg:
//        fprintf(stdout, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
//        break;
//    case QtWarningMsg:
//        fprintf(stdout, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
//        break;
//    case QtCriticalMsg:
//        fprintf(stdout, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
//        break;
//    case QtFatalMsg:
//        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
//        break;
//    }

//    fflush(stdout);


//}




int main(int argc, char *argv[])
{

//    qInstallMessageHandler(myMessageOutput);


    QCoreApplication a(argc, argv);
//    Server* serv = new Server();
//    serv->run();
//    return a.exec();
}
