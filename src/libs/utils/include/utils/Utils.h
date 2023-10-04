#ifndef UTILS_H
#define UTILS_H
#include <QDateTime>
#include <QMetaEnum>
#include <filesystem>

namespace  Helper {


    QDateTime getCurrentTime();
    template<typename QEnum>
    std::string QtEnumToString(const QEnum value)
    {
      return std::string(QMetaEnum::fromType<QEnum>().valueToKey(value));
    }

    std::string getExtension(std::filesystem::path filename);


}
#endif // UTILS_H
