#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

#include <filesystem>
#include <QByteArray>
#include <QString>
//#include
//#include "cmake_data.h"



namespace FileSystemNamespace {

    enum class err_code {

        Success,
        UnsupportedExt,
        Failure,


    };


    enum class Format{

        UNDEFINED,
        MP3,


    };

    enum class CreateFlags{

        Recursive,
        Default

    };

    enum class FileSystemType {

        Primitive,
    };

    struct offset {

        qint64 _start;
        qint64 _end;


    };

    struct File {

        std::string data;
        std::string name;
        Format format;
        std::optional<offset> offset;
    };

    inline std::filesystem::path mergePath(QString path1, QString path2){

        if (!path1.endsWith('/') && !path2.startsWith('/'))
            path1 += "/";
        else if (path1.endsWith('/') && path2.startsWith('/')){

            path1 = path1.remove(path1.size() - 1, 1);

        }

        return std::filesystem::path((path1 + path2).toStdString());
    }


    inline std::optional<std::string> formatConvert(Format format){


        switch(format){

        case Format::MP3:
            return "mp3";
        default :
            return std::nullopt;

        }
    }

    inline Format formatConvert(std::string format){

        if (format == "mp3")
            return Format::MP3;
        return Format::UNDEFINED;

    }


    class IFileSystem {

    public:
        IFileSystem() = delete;
        IFileSystem(std::filesystem::path mount_point) : mount_point(mount_point) {}
        virtual bool createFile(std::filesystem::path path, std::error_code & err_handler, QByteArray& data, CreateFlags) = 0;
        virtual bool createDirectory(std::filesystem::path path, std::error_code &, CreateFlags) = 0;
        virtual bool deleteFile(std::filesystem::path path, std::error_code & err_handler) = 0;
        virtual bool deleteDirectory(std::filesystem::path path, std::error_code &, CreateFlags) = 0;
        virtual bool renameFile(std::filesystem::path path, std::string newName, std::error_code & err_handler) = 0;
        virtual bool copy(std::filesystem::path src, std::filesystem::path relative, std::error_code) = 0;
        virtual File getFile(std::filesystem::path path, std::error_code& er, std::optional<offset> = std::nullopt) = 0;
        virtual std::filesystem::path getMountPoint() {return mount_point;};
    protected:
        std::filesystem::path mount_point;

//        virtual

    };


    std::unique_ptr<IFileSystem> craeteFileSystem(std::filesystem::path mount_path, FileSystemType fs_type);

}

#endif




