#ifndef H_lib_TempDirectory
#define H_lib_TempDirectory
#include "lib/TempFile.hpp"
#include <memory>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------

class TempDirectory {
    public:
    /// Constructors
    TempDirectory(std::string const& parent);
    TempDirectory(int parentDir, std::string const& name, std::string parent);
    TempDirectory(const TempDirectory&) = delete;
    TempDirectory& operator=(const TempDirectory&) = delete;
    TempDirectory(TempDirectory&&) = delete;
    TempDirectory& operator=(TempDirectory&&) = delete;
    ~TempDirectory();

    /// create a file
    std::shared_ptr<TempFile> createFile(std::string const& name) const;
    /// return the file descriptor
    int getFileDescriptor() const;
    /// return the parent path
    std::string getParent() const;
    /// return the name of the directory
    std::string getName() const;
    /// return the whole path
    std::string getPath() const;

    private:
    /// store the file descriptor
    int fileDescriptor = 0;
    /// store the name of the directory
    std::string name = "";
    /// store the parent path
    std::string parent = "";
};

//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
#endif
