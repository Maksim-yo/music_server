#ifndef FILESYSTEMWRAPPER_H
#define FILESYSTEMWRAPPER_H


#include <QByteArray>
#include "utils/Utils.h"
#include "filesystem/IFileSystem.h"


namespace Database::Model {

class Track;

}

namespace FileSystemNamespace {
    using namespace Database::Model;



    class FileSystemWrapper
    {
    public:
        FileSystemWrapper() = delete;
        FileSystemWrapper(FileSystemWrapper&&) = delete;
        FileSystemWrapper(const FileSystemWrapper&) = delete;
        FileSystemWrapper& operator=(const FileSystemWrapper&) = delete;
        FileSystemWrapper& operator=(FileSystemWrapper&&) = delete;

        static File       getTrack(Track& track, qint64 _start, qint64 _end);
        static void       createTrack(Track*& track, QByteArray& data, Format format, std::error_code& err);
        static void       deleteTrack(Track*& track, std::error_code& err);
    };

}
#endif // FILESYSTEMWRAPPER_H
