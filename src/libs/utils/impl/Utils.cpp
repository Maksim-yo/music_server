#include "include/utils/Utils.h"

namespace Helper {

    QDateTime getCurrentTime()
    {
        return QDateTime::currentDateTime();
    }

    std::string getExtension(std::filesystem::path filename)
    {
        filename = filename.filename();
        std::string str = filename.string();
        auto start = std::find(str.begin(), str.end(), '.');
        if(start == str.end())
            return "";
        return std::string(start + 1, str.end());
    }
}
