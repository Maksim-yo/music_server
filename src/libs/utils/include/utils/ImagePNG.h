#ifndef IMAGEPNG_H
#define IMAGEPNG_H
#include "Image.h"

namespace Image {



    template<Type T>
    class ImageImpl: public Image {


    public:

        ~ImageImpl() {}
        // TODO: make private
        // TODO: make private
        ImageImpl(QString path);
        ImageImpl();
        void        resize(QSize)                                           override;
        QSize       getSize()                                               override;
        bool        isNull()                                                override;
        bool        isValid()                                               override;
        QImage&     get()                                                   override;
        QByteArray* serlialize()                                            override;
        Type        type()                                                  override;
        void deserialize(QByteArray*& data)                                 override;
        QByteArray* rawData()              const noexcept                   override;
        friend std::unique_ptr<Image> decodeImage<T>(QByteArray* data, Type type, QSize size);
        friend std::unique_ptr<Image> create<T>(QString path, Type type, QSize size);

        // TODO: make private
        QByteArray* _rawData;
    protected:
        
        QImage img;
        Type _type{T};

    };

    using ImagePNG = ImageImpl<PNG>;
    using ImageJPEG = ImageImpl<JPEG>;


}
#endif // IMAGEPNG_H
