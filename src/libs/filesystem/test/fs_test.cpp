#include "filesystem/PrimitiveFileSystem.h"
#include <QTest>



using namespace FileSystemNamespace;


class FileSystemTest: public QObject {

    Q_OBJECT

private slots:
    void initTestCase(){

        std::filesystem::create_directory(std::filesystem::current_path() / "bucket");
        fs = craeteFileSystem(std::filesystem::current_path() / "bucket", FileSystemType::Primitive);
        mount_path = fs->getMountPoint();
        file_name1 = "testing";
        file_name2 = mount_path / "testing";
        file_name3 = std::filesystem::path("Hi") / "hello";
        dir_name1 = "ws";
        dir_name2 = "testing";
        dir_name3 = "123" / std::filesystem::path("456") / std::filesystem::path("789");

    }

    void test_create(){

        std::error_code er1_file;
        std::error_code er2_file;
        std::error_code er3_file;
        std::error_code er1_dir;
        std::error_code er2_dir;
        std::error_code er3_dir;
        QByteArray data{"Hello"};

        fs->createFile(file_name1, er1_file, data, CreateFlags::Default);
        fs->createFile(file_name2, er2_file, data, CreateFlags::Default);
        fs->createFile(file_name3, er3_file, data, CreateFlags::Recursive);

        fs->createDirectory(dir_name1, er1_dir, CreateFlags::Default);
        fs->createDirectory(dir_name2, er2_dir, CreateFlags::Default);
        fs->createDirectory(dir_name3, er3_dir, CreateFlags::Recursive);

        QVERIFY(er1_file == std::error_code());
        QVERIFY(er2_file == std::error_code());
        QVERIFY(er3_file == std::error_code());

        QVERIFY(er1_dir == std::error_code());
        QVERIFY(er2_dir != std::error_code());
        QVERIFY(er3_dir == std::error_code());
    }




    void test_get_file(){

        std::error_code er1_file;
        std::error_code er1_dir;
        File file1 = fs->getFile(file_name1, er1_file);
        File file2 = fs->getFile(dir_name3, er1_dir);

        QVERIFY(file1.name == file_name1);
        QVERIFY(file1.format == Format::UNDEFINED);
        QVERIFY(file1.data == "Hello");
        QVERIFY(er1_file == std::error_code());

        QVERIFY(file2.name == "");
        QVERIFY(file2.format == Format::UNDEFINED);
        QVERIFY(file2.data == "");
        QVERIFY(er1_dir != std::error_code());





    }


    void test_rename(){

        std::error_code er1_file;
        std::error_code er2_file;
        std::error_code er3_file;
        std::error_code er1_dir;
        std::error_code er2_dir;
        std::error_code er3_dir;

        fs->renameFile(file_name1, "Hello", er1_file);
        fs->renameFile(file_name3, "RENAMED", er2_file);
        fs->renameFile(file_name2, {"test"}, er3_file);
        fs->renameFile(dir_name1, "TESTING", er1_dir);
        fs->renameFile({"123"}, "TESING", er2_dir);
        fs->renameFile(dir_name2, "TEST", er3_dir);

        QVERIFY(er1_file == std::error_code());
        QVERIFY(er2_file == std::error_code());
        QVERIFY(er3_file != std::error_code());

        QVERIFY(er1_dir == std::error_code());
        QVERIFY(er2_dir == std::error_code());
        QVERIFY(er3_dir == std::error_code());

    }


    void test_delete(){

        std::error_code er1_file;
        std::error_code er2_file;
        std::error_code er3_file;
        std::error_code er4_file;
        std::error_code er1_dir;
        std::error_code er2_dir;
        std::error_code er3_dir;
        std::error_code er4_dir;

        fs->deleteDirectory(dir_name1, er1_dir, CreateFlags::Default);
        fs->deleteDirectory(dir_name2, er2_dir, CreateFlags::Default);
        fs->deleteDirectory({"123"}, er3_dir, CreateFlags::Recursive);
        fs->deleteDirectory({"Hi"}, er3_dir, CreateFlags::Recursive);


        fs->deleteFile(file_name1, er1_file);
        fs->deleteFile(file_name2, er2_file);
        fs->deleteFile(file_name3, er3_file);
        fs->deleteFile("non-existing", er4_file);

        fs->deleteDirectory(mount_path, er4_dir, CreateFlags::Recursive);

        QVERIFY(er1_file == std::error_code());
        QVERIFY(er2_file == std::error_code());
        QVERIFY(er3_file == std::error_code());
        QVERIFY(er4_file == std::error_code());

        QVERIFY(er1_dir == std::error_code());
        QVERIFY(er2_dir == std::error_code());
        QVERIFY(er3_dir == std::error_code());
    }


private :
    std::filesystem::path file_name1;
    std::filesystem::path file_name2;
    std::filesystem::path file_name3;
    std::filesystem::path dir_name1;
    std::filesystem::path dir_name2;
    std::filesystem::path dir_name3;
    std::filesystem::path rename1;
    std::filesystem::path rename2;
    std::filesystem::path rename3;
    std::unique_ptr<IFileSystem> fs;
    std::filesystem::path mount_path;

};


QTEST_MAIN(FileSystemTest)
#include "fs_test.moc"


