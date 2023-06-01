
add_library(servernetwork STATIC
    impl/connection.cpp
    impl/ConnectionManager.cpp
    impl/message.cpp
    impl/messagehandles.cpp
    impl/proxy.cpp
    impl/session.cpp
    impl/server.cpp
    impl/proccessmessage.cpp

    include/services/network/connection.h
    include/services/network/ConnectionManager.h
    include/services/network/Constants.h
    include/services/network/message.h
    include/services/network/messagehandles.h
    include/services/network/proxy.h
    include/services/network/session.h
    include/services/network/server.h
    include/services/network/proccessmessage.h
    include/services/network/iproccessmessage.h

    )

target_include_directories(servernetwork INTERFACE
        include
        )

target_include_directories(servernetwork PRIVATE
        include
        imp
        )

target_link_libraries(servernetwork PUBLIC Qt6::Network)


if(BUILD_TESTING)
        add_subdirectory(test)
endif()

install(TARGETS servernetwork DESTINATION lib)

