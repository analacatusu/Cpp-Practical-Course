#ifndef H_lib_CommandLine
#define H_lib_CommandLine
//---------------------------------------------------------------------------
#include "lib/TempDirectory.hpp"
//#include "lib/TempFile.hpp"
#include <list>
#include <memory>
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------
class CommandLine {
    public:
    /// Constructor
    CommandLine() = default;
    /// function to create & delete files and folders
    void run(std::string const& baseDir);

    private:
    /// print files
    void printFiles() const;
    /// delete a file
    void deleteFile(size_t n, std::string& name);
    /// return whether there are any more files
    bool existFiles(int fd) const;
    /// a list of parent directories
    std::list<std::shared_ptr<TempDirectory>> dirs;
    /// current working directory
    std::shared_ptr<TempDirectory> currentDir;
    /// a list of temporary files
    std::list<std::shared_ptr<TempFile>> files;
    /// parent directory
    std::shared_ptr<raii::TempDirectory> parentDir;
};
//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
#endif
