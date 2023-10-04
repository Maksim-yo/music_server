#include "utils/ImagePNG.h"
//#include "utils/QtLogger.h"
#include "utils/Services.h"
#include "utils/Utils.h"
#include <QUrl>
#include <QDebug>

namespace Image {

    extern std::map<Type, bool(*)(const char*, int)> imageValidations;

    // TODO: REFACTOR
    template <Type T>
    std::unique_ptr<Image> create(QString path, Type type, QSize size) {

        if (type == Type::UNDEFINED){
            std::string ext = Helper::getExtension(path.toStdString());
            type = convertString(ext.c_str());
        }

        switch (type){

            case Type::PNG:
            try {

                auto img = std::make_unique<ImagePNG>(path);
                img->_rawData = img->serlialize();
                return img;
            }
            catch (const std::exception& e){

                qDebug() << e.what();
            }

            case Type::JPEG:
            try {

                auto img = std::make_unique<ImageJPEG>(path);
                img->_rawData = img->serlialize();
                return img;
            }
            catch (const std::exception& e){

                qDebug() << e.what();
            }
            default:

                qDebug() << "Cannot create image. Unsupported type. path: " << path.toStdString().c_str();
                return {};
        }
    }

    // TODO: REFACTOR
    template <Type T>
    std::unique_ptr<Image> decodeImage(QByteArray* data, Type type, QSize size){


        auto guessingType = [&data, &type]() {
            for (auto elm: imageValidations){
                if (elm.second(data->data(), data->size()))
                    type = elm.first;
            }
        };

        guessingType();

        switch (type){

            case Type::PNG:
            {
                try {
                    std::unique_ptr<ImagePNG> img = std::make_unique<ImagePNG>();
                    img->deserialize(data);
                    img->_rawData = data;
                    return img;
                }
                catch (const std::exception& e){

                    qDebug() << e.what();

                }
            }

            case Type::JPEG:
            {
                std::unique_ptr<ImageJPEG> img;
                try {
                    img = std::make_unique<ImageJPEG>();
                    img->deserialize(data);
                    img->_rawData = data;
                    return img;
                }
                catch (const std::exception& e){

                    qDebug() << e.what();
                    break;

                }


            }

        }
        return {};

    }


    QByteArray* encodeImage(Image* img){


        try {

            return img->serlialize();
        }
        catch (const std::exception& e){

            qDebug() << e.what();

        }
        return {};

    }

    QString convertType(Type type)
    {
        switch (type){

        case Type::JPEG:
            return "jpeg";
        case Type::PNG:
            return "png";
        default:
            return "";
        }

    }

    Type convertString(QString str)
    {
        if (str == "png")
            return Type::PNG;
        if (str == "jpeg" || str == "jpg")
            return Type::JPEG;
        return Type::UNDEFINED;
    }


    template std::unique_ptr<Image> decodeImage<Type::PNG>(QByteArray* data,  Type type, QSize size);
    template std::unique_ptr<Image> decodeImage<Type::JPEG>(QByteArray* data, Type type, QSize size);
    template std::unique_ptr<Image> decodeImage<Type::UNDEFINED>(QByteArray* data, Type type, QSize size);


    template std::unique_ptr<Image> create<Type::PNG>(QString path,  Type type, QSize size);
    template std::unique_ptr<Image> create<Type::JPEG>(QString path,  Type type, QSize size);
    template std::unique_ptr<Image> create<Type::UNDEFINED>(QString path,  Type type, QSize size);



}

