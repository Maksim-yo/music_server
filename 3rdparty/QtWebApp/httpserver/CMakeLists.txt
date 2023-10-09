add_library(httpserver SHARED
    include/httpserver/httpglobal.h
    include/httpserver/httplistener.h
    include/httpserver/httpconnectionhandler.h
    include/httpserver/httpconnectionhandlerpool.h
    include/httpserver/httprequest.h
    include/httpserver/httpresponse.h
    include/httpserver/httpcookie.h
    include/httpserver/httprequesthandler.h
    include/httpserver/httpsession.h
    include/httpserver/httpsessionstore.h
    include/httpserver/staticfilecontroller.h
    impl/httpglobal.cpp
    impl/httplistener.cpp
    impl/httpconnectionhandler.cpp
    impl/httpconnectionhandlerpool.cpp
    impl/httprequest.cpp
    impl/httpresponse.cpp
    impl/httpcookie.cpp
    impl/httprequesthandler.cpp
    impl/httpsession.cpp
    impl/httpsessionstore.cpp
    impl/staticfilecontroller.cpp
)

target_include_directories(httpserver PRIVATE include/httpserver)
set_target_properties(httpserver PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_link_libraries(httpserver PRIVATE Qt6::Network)

