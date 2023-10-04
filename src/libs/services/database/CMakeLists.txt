
add_library(database SHARED
    include/services/database/Artist.h
    include/services/database/Album.h
    include/services/database/Playlist.h
    include/services/database/Track.h
    include/services/database/Lyric.h
    include/services/database/Genre.h
    include/services/database/Url.h
    include/services/database/Directory.h
    include/services/database/UserAccount.h
    include/services/database/Year.h
    include/services/database/Image.h
    include/services/database/UserRole.h
    include/services/database/Utils.h

    impl/Artist.cpp
    impl/Album.cpp
    impl/Playlist.cpp
    impl/Track.cpp
    impl/Lyric.cpp
    impl/Genre.cpp
    impl/Url.cpp
    impl/Directory.cpp
    impl/UserAccount.cpp
    impl/Year.cpp
    impl/Image.cpp
    impl/UserRole.cpp
    )

set_target_properties(database PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_include_directories(database INTERFACE
        include
        )

target_include_directories(database PRIVATE
        include
        impl
        )

target_link_libraries(database PUBLIC tinyorm)


#if(BUILD_TESTING)
#        add_subdirectory(test)
#endif()

install(TARGETS database DESTINATION lib)

