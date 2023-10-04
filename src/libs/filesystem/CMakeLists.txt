add_library(filesystem SHARED
    impl/PrimitiveFileSystem.cpp
    impl/FileSystemWrapper.cpp
    impl/IFileSystem.cpp

    include/filesystem/IFileSystem.h
    include/filesystem/FileSystemWrapper.h
    include/filesystem/PrimitiveFileSystem.h

    )

set_target_properties(filesystem PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_include_directories(filesystem INTERFACE
        include
        )

target_include_directories(filesystem PRIVATE
        include
        impl
        )

target_link_libraries(filesystem PUBLIC Qt6::Core database utils)


if(BUILD_TESTING)
        add_subdirectory(test)
endif()

install(TARGETS filesystem DESTINATION lib)
