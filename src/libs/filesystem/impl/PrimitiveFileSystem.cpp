#include "filesystem/PrimitiveFileSystem.h"
#include <fstream>


//add error handlers
namespace FileSystemNamespace {

    static std::string make_file_name(std::filesystem::path filename){

        filename = filename.filename();
        std::string str = filename.string();
        int slice = str.find('.');
        return str.substr(0, slice - 1);
    }

    static Format convertToFormat(std::string str){

        if (str == "mp3")
            return Format::MP3;
        else
            return Format::UNDEFINED;
    }

    FileSystem::FileSystem(std::filesystem::path mount_point): IFileSystem(std::move(mount_point))
    {

    }

    // - not handle symbol '/' for ending path
    // - not working if file and directory have the same name
    bool FileSystem::createFile(std::filesystem::path path, std::error_code &err_handler, QByteArray& data, CreateFlags flag)
    {

      auto _path = getRelativePathToMount(path);
      auto test = _path.parent_path();
//        auto _path = std::filesystem::canonical(temp_path, err_handler);
        if (!createDirectory(_path.parent_path(), err_handler, flag)) {
                err_handler.assign(ENOENT, std::system_category());         //no_such_file_or_directory
            return false;
        }

        std::ofstream ofstr = std::ofstream(_path.c_str(), std::ios_base::binary) << data.data();

        if (ofstr.is_open()) {
            err_handler = std::error_code();
            return true;
        }
        err_handler.assign(ENOENT, std::system_category());         //no_such_file_or_directory
        return false;
    }

    bool FileSystem::createDirectory(std::filesystem::path path, std::error_code & err, CreateFlags flags)
    {
            auto _path = getRelativePathToMount(path);
             if (std::filesystem::exists(path))
                return true;
            switch(flags) {

            case CreateFlags::Default:
            {
                if (!std::filesystem::exists(_path.parent_path(), err))
                    return false;

                std::filesystem::create_directory(_path, err);
                return true;
            }
            case CreateFlags::Recursive:
            {
                bool res = std::filesystem::create_directories(_path, err);

                return res || !res && err == std::error_code() ? true : false;
            }
        }
    }

    bool FileSystem::deleteDirectory(std::filesystem::path path, std::error_code& err, CreateFlags flag)
    {

        auto _path = getRelativePathToMount(path);

        switch (flag) {

        case CreateFlags::Default: {


            return std::filesystem::remove(_path, err);

        }

        case CreateFlags::Recursive: {

            return std::filesystem::remove_all(_path, err);

            }
        }
    }


    bool FileSystem::deleteFile(std::filesystem::path path, std::error_code &err_handler)
    {
        return std::filesystem::remove(getRelativePathToMount(path), err_handler);
    }

    bool FileSystem::renameFile(std::filesystem::path path, std::string newName, std::error_code &err_handler)
    {
        auto absolute_path = getRelativePathToMount(path);
        auto new_path = std::filesystem::canonical(absolute_path.parent_path()) / newName;
         std::filesystem::rename(absolute_path, new_path, err_handler);
         if (err_handler == std::error_code())
             return true;
         return false;
    }

    File FileSystem::getFile(std::filesystem::path _path, std::error_code& er, std::optional<offset> offset)
    {
       auto path = getRelativePathToMount(_path);
       if(!std::filesystem::exists(path)){
           er = std::error_code(ENOENT, std::system_category());
           return {};
       }
       std::string data;
       std::ifstream ifstr = std::ifstream(path.c_str(), std::ios_base::binary);
       if (!offset.has_value())
           ifstr >> data;
       else
       {   qint64 upper_bound = std::max(static_cast<qint64>(std::filesystem::file_size(path) - offset->_start), offset->_end);
           ifstr.seekg(offset->_start);
           ifstr.read(data.data(), upper_bound);
       }
       if (!ifstr.is_open()){
           er = std::error_code(ENOENT, std::system_category());
           return File{};
       }

       return File{data, make_file_name(path), convertToFormat(path.extension().string())};
    }
    //todo: handle relative with trailing slash at the end
    bool FileSystem::copy(std::filesystem::path src, std::filesystem::path relative, std::error_code err)
    {
        if (!std::filesystem::exists(src, err) )
            return false;

        auto res = createDirectory(relative, err, CreateFlags::Recursive);
        if(!res)
            return false;

        auto mount_point = getMountPoint();
        auto new_path = std::filesystem::canonical(mount_point / relative);

        if (!std::filesystem::is_directory(relative))
            new_path /= relative.filename();
        else
            new_path /= src.filename();

        std::filesystem::copy(src, new_path);
        return true;
    }

    std::filesystem::path FileSystem::getRelativePathToMount(std::filesystem::path& path)
    {
        std::filesystem::path temp_path = std::filesystem::proximate(path, mount_point);
        return mount_point / temp_path;
    }






}
