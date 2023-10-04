#include <QIODevice>
#include <stdexcept>
#include "utils/ImagePNG.h"
#include <QtDebug>
#include <QBuffer>
namespace Image {


    static bool PNGValidation(const char* data, int size);
    static bool JPEGValidation(const char* data, int size);

    std::map<Type, bool(*)(const char*, int)> imageValidations{
      {Type::PNG, PNGValidation},
      {Type::JPEG, JPEGValidation},
    };

    template<Type type>
    ImageImpl<type>::ImageImpl() { }


    template<Type type>
    ImageImpl<type>::ImageImpl(QString file): img{QImage(file)}
    {
        if (img.isNull())
            throw std::runtime_error("Cannot create image " + file.toStdString());

    }

    template<Type type>
    void ImageImpl<type>::resize(QSize size)
    {
        img = std::move(img.scaled(size));
    }

    template<Type type>
    QSize ImageImpl<type>::getSize()
    {
        return img.size();
    }

    template<enum Type type>
    bool ImageImpl<type>::isNull()
    {
        return img.isNull();
    }

    template<Type T>
    bool ImageImpl<T>::isValid()
    {

        return imageValidations[type()]((rawData()->data()), rawData()->size());
    }

    template<Type type>
    QImage& ImageImpl<type>::get()
    {
        return img;
    }

    //need to test
    template<Type type>
    void ImageImpl<type>::deserialize(QByteArray *&data)
    {
        img = QImage::fromData(*data, convertType(type()).toStdString().c_str());
        if (img.isNull())
            throw std::runtime_error("Cannot deserialize image");

    }

    template<Type T>
    QByteArray *ImageImpl<T>::rawData() const noexcept
    {
        return _rawData;
    }

    template<Type type>
    QByteArray *ImageImpl<type>::serlialize()
    {
        QByteArray* byteArray = new QByteArray();
        {
            QBuffer buffer(byteArray);
            buffer.open(QIODevice::WriteOnly);
            img.save(&buffer, convertType(type()).toStdString().c_str());
        }
        if (byteArray->size() <= 0) {
            throw std::runtime_error("Cannot serialize image");
        }
        return byteArray;
    }

    template<Type T>
    Type ImageImpl<T>::type()
    {
     return _type;
    }


    static bool JPEGValidation(const char* data, int size){

        int c{0};
        return (data[0] == (char)0xff &&
                    data[1] == (char)0xd8 &&
                    data[size-2] == (char)0xff &&
                    data[size-1] == (char)0xd9);
    }

    static bool PNGValidation(const char* data, int size){

        const char pngSignature[] = "\x89\x50\x4e\x47\xd\xa\x1a\xa";


        for (int i = 0; i < sizeof(pngSignature) / sizeof(pngSignature[0]); ++i){

            if (data[i] != (char)pngSignature[i])
                return false;
        }

        return true;
    }

    template class ImageImpl<Type::PNG>;
    template class ImageImpl<Type::JPEG>;

}


