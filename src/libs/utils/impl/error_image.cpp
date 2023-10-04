#include "utils/error_image.h"

namespace   {
    struct ImageErrCategory : std::error_category {


      const char* name() const noexcept override;
      std::string message(int ev) const override;
      bool equivalent(
          const std::error_code& code,
          int condition) const noexcept override;
    };



    const char* ImageErrCategory::name() const noexcept
    {
      return "image";
    }

    std::string ImageErrCategory::message(int ev) const
    {
      switch (ev)
      {
      case ImageErr::UnsupportedExt:
        return "unsupported_ext";
      default:
        return "unrecognized error";
      }
    }


    bool ImageErrCategory::equivalent(const std::error_code& ec, int cond) const noexcept
    {

        switch (static_cast<ImageErr>(cond)){

        case ImageErr::UnsupportedExt:
            return true;
        }

        return false;
    }


    const ImageErrCategory imageCategory{};

}

std::error_code make_error_code(ImageErr e)
{
  return {static_cast<int>(e), imageCategory};
}
