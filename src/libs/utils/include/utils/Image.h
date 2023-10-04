#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <QByteArray>
#include <filesystem>
#include <QSize>
#include <QImage>

//#include "error_image.h"

namespace Image {

    enum Type {

        JPEG,
        PNG,
        UNDEFINED,
    };

    enum class image_error {

        undefined_type,

    };

    QString convertType(Type type);
    Type    convertString(QString str);


    class   Image
    {
    public:
        virtual ~Image() {}
        Image() = default;

        virtual void        resize(QSize) = 0;
        virtual QSize       getSize() = 0;
        virtual bool        isNull()  = 0;
        virtual QImage&     get()     = 0;
        virtual bool        isValid() = 0;
        virtual Type        type()    = 0;
        // TODO: make private
        virtual void        deserialize(QByteArray*& data) = 0;
        virtual QByteArray* serlialize() = 0;
        virtual QByteArray* rawData() const noexcept = 0;


    };
    template <Type T = Type::UNDEFINED>
    std::unique_ptr<Image> decodeImage(QByteArray* data, Type type = Type::UNDEFINED, QSize size = {0,0});
    QByteArray*            encodeImage(Image* img);
    template <Type T = Type::UNDEFINED>
    std::unique_ptr<Image> create(QString path, Type type = Type::UNDEFINED,QSize size = {0,0});
}
#endif // IMAGE_H
