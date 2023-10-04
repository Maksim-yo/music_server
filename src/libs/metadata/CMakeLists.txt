add_library(metadatalib SHARED

    include/metadata/IParser.h
    include/metadata/TagLib.h

    impl/TagLib.cpp
    impl/IParser.cpp
    )

set_target_properties(metadatalib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_include_directories(metadatalib INTERFACE
        include
        )

target_include_directories(metadatalib PRIVATE
        include
        impl
        )

target_link_libraries(metadatalib PUBLIC taglib zlib Qt6::Core)


if(BUILD_TESTING)
        add_subdirectory(test)
endif()

install(TARGETS metadatalib  DESTINATION lib)
