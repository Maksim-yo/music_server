#include "utils/ImagePNG.h"
#include "utils/Image.h"
#include <QObject>
#include <QTest>

//using namespace Image;

class TestImage : public QObject {

    Q_OBJECT


    private slots:
        void loadImage(){

             img = Image::create(img_path);
             auto image = QImage(img_path);

             qDebug() << "Loading image: " << img_path;
             QVERIFY(img->isNull() == false);
             QVERIFY(img->get() == image);
        }

    void serializeImage(){

        auto image = Image::create(img_path);
        encoded_img = Image::encodeImage(image.get());
    }

    void deserializeImage(){

        auto _img = Image::decodeImage(encoded_img,Image::Type::PNG, img->getSize());
        QVERIFY(img->get() == _img->get());

    }

    void resizeImage(){

        std::unique_ptr<Image::Image>_img = Image::create(img_path, Image::Type::PNG, QSize(100,100));
        _img->resize(QSize(200,200));

        QVERIFY(_img->isNull() == false);
        QVERIFY(_img->getSize() == QSize(200,200));
    }

    void test_error(){

//        std::error_code err = ImageErr::UnsupportedExt;
//        QVERIFY(err == ImageErr::UnsupportedExt);

    }

private:
    QString img_path{"C:/Users/lyzlo/Downloads/images.jpg"};
    std::unique_ptr<Image::Image> img;
    QByteArray* encoded_img;
};


QTEST_MAIN(TestImage)
#include "image_test.moc"
