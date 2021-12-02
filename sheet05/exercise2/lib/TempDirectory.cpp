#include "lib/TempDirectory.hpp"
#include "lib/OSApi.hpp"
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------
// Constructor from abs path
TempDirectory::TempDirectory(std::string const& parent) : parent(parent) {
    osapi::createDir(parent.c_str());
    fileDescriptor = osapi::openDir(parent.c_str());
}
//---------------------------------------------------------------------------
// Constructor for subdirectory
TempDirectory::TempDirectory(int parentDir, std::string const& name, std::string parent) : name(name), parent(std::move(parent)) {
    osapi::createSubdir(parentDir, name.c_str());
    fileDescriptor = osapi::openSubdir(parentDir, name.c_str());
}
//---------------------------------------------------------------------------
// Destructor
TempDirectory::~TempDirectory() {
    osapi::closeFd(fileDescriptor);
    std::string path = parent + "/" + name;
    osapi::removeDir(path.c_str());
}
//---------------------------------------------------------------------------
// Create a file inside a directory
std::shared_ptr<TempFile> TempDirectory::createFile(std::string const& name) const {
    std::string path = parent + "/" + name + "/" + name;
    return std::make_shared<TempFile>(name, fileDescriptor, path);
}
//---------------------------------------------------------------------------
// File descriptor
int TempDirectory::getFileDescriptor() const {
    return fileDescriptor;
}
//---------------------------------------------------------------------------
// Parent path
std::string TempDirectory::getParent() const {
    return parent;
}
//---------------------------------------------------------------------------
// Name of the directory
std::string TempDirectory::getName() const {
    return name;
}
//---------------------------------------------------------------------------
// Path of the directory
std::string TempDirectory::getPath() const {
    return parent + "/" + name;
}
//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
