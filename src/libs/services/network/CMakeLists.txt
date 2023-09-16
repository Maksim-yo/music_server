set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(GeneralNetwork_HRS
    include/services/network/Constants.h
    include/services/network/message.h
    include/services/network/messagehandles.h
    include/services/network/session.h
    include/services/network/iproccessmessage.h
    include/services/network/tcpconnection.h
    include/services/network/sendqueue.h
    include/services/network/ratecontroller.h
    include/services/network/IConnection.h

    )

set(GeneralNetwork_SRC
    impl/message.cpp
    impl/messagehandles.cpp
    impl/session.cpp
    impl/tcpconnection.cpp
    impl/sendqueue.cpp
    impl/ratecontroller.cpp
    impl/proccessmessage.cpp
    impl/IConnection.cpp
)

add_library(servernetwork SHARED
    impl/ConnectionManager.cpp
    impl/proxy.cpp
    impl/server.cpp

    include/services/network/ConnectionManager.h
    include/services/network/proxy.h
    include/services/network/server.h
    include/services/network/proccessmessage.h
    ${GeneralNetwork_SRC}
    ${GeneralNetwork_HRS}
    )

add_library(generalnet SHARED
    ${GeneralNetwork}
    )

set_target_properties(generalnet PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(servernetwork PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


FILE(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/include/include/services/network)
FILE(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/include/impl)

foreach(_item ${GeneralNetwork_HRS})
    set(TEMP_PATH "${CMAKE_SOURCE_DIR}/${_item}")
    message("ITEM ${TEMP_PATH}")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${_item} DESTINATION ${CMAKE_SOURCE_DIR}/include/include/services/network)

endforeach()

foreach(_item ${GeneralNetwork_SRC})
    set(TEMP_PATH "${CMAKE_SOURCE_DIR}/${_item}")
    message("ITEM ${TEMP_PATH}")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${_item} DESTINATION ${CMAKE_SOURCE_DIR}/include/impl/)

endforeach()

add_library(generalnet::generalnet ALIAS generalnet)

target_link_libraries(generalnet PUBLIC Qt6::Network Qt6::Core)

target_include_directories(servernetwork INTERFACE
        include
        )

target_include_directories(servernetwork PRIVATE
        include
        impl
        )
target_include_directories(generalnet PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

target_link_libraries(servernetwork PUBLIC Qt6::Network Qt6::Core utils database filesystem)
#set(BUILD_TESTING ON)

#if(BUILD_TESTING)
#        add_subdirectory(test)
#endif()

install(TARGETS servernetwork DESTINATION lib)
install(TARGETS generalnet
        EXPORT generalnetTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
#install(FILES ${GeneralNetwork_HRS} DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/generalnet)

install(EXPORT generalnetTargets
        FILE generalnetConfig.cmake
        NAMESPACE generalnet::
        DESTINATION ${PROJECT_SOURCE_DIR}/export/generalnet/cmake
)

install(
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"

    DESTINATION
        include
)
