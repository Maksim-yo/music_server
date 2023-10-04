#include(GoogleTest)



set(tests
    connection_test
    message_test)

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
    target_link_libraries(${test_target} PRIVATE servernetwork Qt6::Concurrent Qt6::Test)

    add_test(NAME    ${test_target}
             COMMAND ${test_target})
endforeach()
