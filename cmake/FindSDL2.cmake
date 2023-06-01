#include(FindPackageHandleStandardArgs)



#find_library(SDL2_LIBRARY NAMES SDL2)

#find_package_handle_standard_args(SDL2 REQUIRED_VARS SDL2_LIBRARY)

#if (SDL2_FOUND)
##  mark_as_advanced(SDL2_LIBRARY)
#  message("Dirs: ${SDL2_LIBRARY}")
#endif()

#if (SDL2_FOUND AND NOT TARGET SDL2::SDL2)
#  add_library(SDL2 )
#  set_property(TARGET SDL2 PROPERTY LOCATION ${SDL2_LIBRARY})
#endif()
