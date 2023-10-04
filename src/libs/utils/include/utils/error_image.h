#ifndef ERROR_IMAGE_H
#define ERROR_IMAGE_H
#include <system_error>

enum ImageErr {

    UnsupportedExt = 1,



};

namespace std
{
  template <>
    struct is_error_code_enum<ImageErr> : true_type {};
}

std::error_code make_error_code(ImageErr);




#endif // ERROR_IMAGE_H
