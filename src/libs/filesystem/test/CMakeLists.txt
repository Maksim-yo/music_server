add_library(filesystem_test SHARED)
set_target_properties(filesystem_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(filesystem_test PUBLIC filesystem)
#target_include_directories(filesystem_test INTERFACE "${PROJECT_SOURCE_DIR}/src/libs/services/filesystem/impl")
#target_include_directories(filesystem_test INTERFACE "${PROJECT_SOURCE_DIR}/src/libs/services/filesystem/include")

set_target_properties(filesystem_test PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(tests
    fs_test
#    wrapper_test
    )

foreach(test_target ${tests})
    if(EXISTS "${PROJECT_SOURCE_DIR}/${test_target}.h")
        add_executable(${test_target} "${test_target}.cpp" "${test_target}.h" )
    else()
        add_executable(${test_target} "${test_target}.cpp" )
    endif()
    set_target_properties(${test_target} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )
    target_link_libraries(${test_target} PRIVATE filesystem_test Qt6::Test)

    add_test(NAME    ${test_target}
             COMMAND ${test_target})
endforeach()
