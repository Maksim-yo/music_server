add_executable(server
		 main.cpp 
		 )
target_link_libraries(server PRIVATE
    Qt6::Core)
target_link_libraries(server PUBLIC servernetwork)

install(TARGETS server DESTINATION bin)
