#ifndef PRIMITIVEFILESYSTEM_H
#define PRIMITIVEFILESYSTEM_H

#include "filesystem/IFileSystem.h"


namespace FileSystemNamespace {


    class FileSystem : public IFileSystem {




    public:

            FileSystem() = delete;
            FileSystem(std::filesystem::path mount_point);
            bool createFile(std::filesystem::path path, std::error_code & err_handler, QByteArray& data, CreateFlags flag) override;
            bool createDirectory(std::filesystem::path path, std::error_code &, CreateFlags) override;
            bool deleteDirectory(std::filesystem::path path, std::error_code &, CreateFlags) override;
            bool deleteFile(std::filesystem::path path, std::error_code & err_handler) override;
            bool renameFile(std::filesystem::path path, std::string newName, std::error_code & err_handler) override;
            File getFile(std::filesystem::path path, std::error_code& er, std::optional<offset>) override;
            bool copy(std::filesystem::path src, std::filesystem::path relative, std::error_code) override;
            std::filesystem::path getRelativePathToMount(std::filesystem::path& path);

    };
}


#endif // PRIMITIVEFILESYSTEM_H
