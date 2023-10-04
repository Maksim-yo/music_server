add_library(metadatalib_test SHARED)
set_target_properties(metadatalib_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(metadatalib_test  PUBLIC metadatalib)

set_target_properties(metadatalib_test  PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(tests
    metadata_test
    )

set(METADATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

configure_file (cmake_data.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmake_data.h)

foreach(test_target ${tests})
    if(EXISTS "${PROJECT_SOURCE_DIR}/${test_target}.h")
        add_executable(${test_target} "${test_target}.cpp" "${test_target}.h" )
    else()
        add_executable(${test_target} "${test_target}.cpp"  ${QT_RESOURCES})
    endif()
     set_target_properties(${test_target} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )
    target_include_directories(${test_target} PRIVATE cmake_data.h)
    target_link_libraries(${test_target} PRIVATE metadatalib_test  Qt6::Test)

    add_test(NAME    ${test_target}
             COMMAND ${test_target})
endforeach()
