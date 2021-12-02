#include "lib/TempFile.hpp"
#include "lib/OSApi.hpp"
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------
// Constructor
TempFile::TempFile(std::string const& name, int dirFD, std::string path) : name(name), dirFD(dirFD), path(std::move(path)) {
    fileDescriptor = osapi::openFile(dirFD, name.c_str());
}
//---------------------------------------------------------------------------
// Destructor
TempFile::~TempFile() {
    osapi::closeFd(fileDescriptor);
    osapi::removeFile(dirFD, name.c_str());
}
//---------------------------------------------------------------------------
// File descriptor of the file
int TempFile::getFD() const {
    return fileDescriptor;
}
//---------------------------------------------------------------------------
// Name of the file
std::string TempFile::getName() const {
    return name;
}
//---------------------------------------------------------------------------
// File descriptor of the directory
int TempFile::getDirFD() const {
    return dirFD;
}
//---------------------------------------------------------------------------
// Path of the file
std::string TempFile::getPath() const {
    return path;
}
//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
