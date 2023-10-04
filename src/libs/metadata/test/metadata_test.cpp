#include <QTest>
#include "metadata/TagLib.h"

#include "cmake_data.h"

using namespace Metadata;


class Interface {

public:
    Interface(int b) {
        a = b;
    }
private:
    int a;
};


class A: public Interface {

public:
    A(int a) : Interface(a) {}
private:
    std::vector<int> data{1,2,3,4,5,6,7};
};

class B: public Interface {

public:
    B(int a) : Interface(a ) {}
};

class MetadataTest : public QObject {

    Q_OBJECT

private slots:


    void test_metadata(){

        std::filesystem::path dir{METADATA_DIR};
        std::filesystem::path path1{dir / filename1.toStdString()};
        std::filesystem::path path2{dir / filename2.toStdString()};
        std::filesystem::path path3{dir / filename3.toStdString()};
        std::filesystem::path path4{dir / filename4.toStdString()};
        std::unique_ptr<IParser> parser = createParser(ParserType::Taglib, ParserSpeed::Average);
        parser->parse(std::filesystem::canonical(path1));
        parser->parse(std::filesystem::canonical(path2));
        parser->parse(std::filesystem::canonical(path3));
        parser->parse(std::filesystem::canonical(path4));



    }


    void test(){

        A* a=  new A(5);
        QString temp{"hello"};
        QByteArray* data = new QByteArray();
        {
            QDataStream in(data, QIODevice::ReadWrite);
            in << temp;
        }

        QString src;
        {
            QDataStream out(data, QIODevice::ReadWrite);
            out >> src;
        }
    }


private:
    QString filename1{"Stan.mp3"};
    QString filename2{"Twenty One Pilots - No Chances.mp3"};
    QString filename3{"Twenty One Pilots - Stressed Out.mp3"};
    QString filename4{"Lana_Del_Rey_-_Summertime_Sadness_(musmore.com).mp3"};

};

QTEST_MAIN(MetadataTest)
#include "metadata_test.moc"






