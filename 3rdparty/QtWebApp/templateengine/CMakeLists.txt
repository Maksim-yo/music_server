add_library(templateengine SHARED
    templateglobal.h
    template.h
    templateloader.h
    templatecache.h
    template.cpp
    templateloader.cpp
    templatecache.cpp
)

set_target_properties(templateengine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_link_libraries(templateengine PRIVATE Qt::Core5Compat Qt::Core)
