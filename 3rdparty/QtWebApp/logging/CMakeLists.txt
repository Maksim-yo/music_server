add_library(logging SHARED
    logglobal.h
    logmessage.h
    logger.h
    filelogger.h
    dualfilelogger.h
    logmessage.cpp
    logger.cpp
    filelogger.cpp
    dualfilelogger.cpp
)

target_include_directories(logging PUBLIC .)

set_target_properties(logging PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_link_libraries(logging PRIVATE Qt6::Core)

