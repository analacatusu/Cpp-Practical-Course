#ifndef H_lib_TempFile
#define H_lib_TempFile
#include <string>
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------

class TempFile {
    public:
    /// Constructors
    TempFile(std::string const& name, int dirFD, std::string path);
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    TempFile(TempFile&&) noexcept = default;
    TempFile& operator=(TempFile&&) noexcept = default;
    ~TempFile();
    /// return the file descriptor
    int getFD() const;
    /// return the name of the path
    std::string getName() const;
    /// return the file descriptor of the directory
    int getDirFD() const;
    /// return the path
    std::string getPath() const;

    private:
    /// store the file descriptor
    int fileDescriptor = 0;
    /// store the name of the file
    std::string name = "";
    /// store the file descriptor of the directory
    int dirFD = 0;
    /// store the path
    std::string path = "";
};

//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
#endif
