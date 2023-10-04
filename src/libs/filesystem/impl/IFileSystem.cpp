#include "filesystem/IFileSystem.h"
#include "filesystem/PrimitiveFileSystem.h"


namespace FileSystemNamespace {

    std::unique_ptr<IFileSystem> craeteFileSystem(std::filesystem::path mount_path, FileSystemType fs_type) {

        switch(fs_type){

        case FileSystemType::Primitive :
            return std::make_unique<FileSystem>(mount_path);
        }
    }

}


