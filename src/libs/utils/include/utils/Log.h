#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>
#include "Services.h"

enum class Severity
{
    FATAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
};


const char* getSeverityName(Severity sev);

class Logger;
class Log
{
    public:
        Log(Logger* logger, Severity severity);
        ~Log();

        Severity getSeverity() const { return _severity; }
        std::string getMessage() const;

        std::ostringstream& getOstream() { return _oss; }

    private:
        Severity _severity;
        std::ostringstream _oss;
        Logger* _logger {};
};

class Logger
{
    public:
        virtual ~Logger() = default;
        virtual void processLog(const Log& log) = 0;
};

#define LOG(severity)		Log(Service<Logger>::get(), Severity::severity).getOstream()

#endif // LOG_H
