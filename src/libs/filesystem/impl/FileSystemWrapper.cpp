#include "include/filesystem/FileSystemWrapper.h"
#include "services/database/Url.h"
#include "services/database/Image.h"
#include "utils/Services.h"

namespace FileSystemNamespace {

    std::filesystem::path createPath(QString artist, QString album, QString track, std::string format){

        return {artist.toStdString() + '/' + album.toStdString() + '/' + track.toStdString() + '.' + format};

    }



    File FileSystemWrapper::getTrack(Track& track, qint64 _start, qint64 _end)
    {
        auto fs{Service<IFileSystem>::get()};
        Url* url = track.getUrl();
        Directory* dir = url->getDirectory();
        QString relativePath = url->getPath();
        QString directoryPath = dir->getPath();
        std::error_code er;
        std::optional<offset> file_offset = std::make_optional<offset>({_start, _end});
        File file = fs->getFile(fs->getMountPoint() / mergePath(directoryPath, relativePath), er, file_offset);
        return file;

    }

    //   TODO:
    // - refactoring
    // - make a reference to file
    // - make handle of multiple artists

    void FileSystemWrapper::createTrack(Track *&track, QByteArray& data, Format _format, std::error_code& err)
    {

        auto fs{Service<IFileSystem>::get()};
        auto artists = track->getArtists();
        auto albums = track->getAlbums();
        if(artists.size() != 1) {
            err = std::error_code(ENOENT, std::system_category());              //placeholder
            return;
        }
        auto album = albums.front();
        auto artist = artists.front();
        auto format = formatConvert(_format);
        if (!format.has_value()){
            err = std::error_code(ENOENT, std::system_category());              //placeholder
            return;
        }

        std::filesystem::path path = createPath(artist->getName(), album->getName(), track->getTitle(), format.value());
        auto track_path = fs->getMountPoint() / path;
        fs->createFile(track_path, err, data, CreateFlags::Default);
        if (err != std::error_code())
            return;

        QString artist_path = artist->getName() + '/';
        QString _track_path = album->getName() + '/' + track->getTitle();

        auto directory = Directory::firstOrCreate({{"DirectoryPath", artist_path}, {"ChangeDate",""}});
        if (directory.getAttribute("ChangeDate").toDateTime() == QDateTime())
            directory.setAttribute("ChangeDate", Helper::getCurrentTime());

        auto url = Url::create({{"Path", _track_path}, {"Directory", directory.getKey()}});


    }

    void FileSystemWrapper::deleteTrack(Track *&track, std::error_code &err)
    {
        auto fs{Service<IFileSystem>::get()};
        auto url = track->getUrl();
        auto directory = url->getDirectory();
        auto track_path = fs->getMountPoint() / directory->getPath().toStdString() / url->getPath().toStdString();
        fs->deleteFile(track_path, err);

    }



}
