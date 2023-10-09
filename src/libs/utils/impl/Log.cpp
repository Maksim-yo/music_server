#include "utils/Log.h"

const char* getSeverityName(Severity sev)
{
    switch (sev)
    {
        case Severity::FATAL:		return "fatal";
        case Severity::ERROR:		return "error";
        case Severity::WARNING:		return "warning";
        case Severity::INFO:		return "info";
        case Severity::DEBUG:		return "debug";
    }
    return "";
}

Log::Log(Logger* logger, Severity severity)
    : _severity {severity},
      _logger {logger}
{}

Log::~Log()
{
    if (_logger)
        _logger->processLog(*this);
}

std::string
Log::getMessage() const
{
    return _oss.str();
}
