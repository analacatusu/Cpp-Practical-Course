#include "lib/CommandLine.hpp"
#include <iostream>
//---------------------------------------------------------------------------
namespace raii {
//---------------------------------------------------------------------------
// Check whether there are still files in the directory
bool CommandLine::existFiles(int fd) const {
    for (auto const& file : files) {
        if (file.get()->getDirFD() == fd) {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
// Delete a file
void CommandLine::deleteFile(size_t n, std::string& name) {
    auto iterator = files.begin();
    std::advance(iterator, n);
    int fd = iterator->get()->getDirFD();
    name = iterator->get()->getName();
    files.erase(iterator);

    if (!existFiles(fd))
        dirs.erase(dirs.begin());
}
//---------------------------------------------------------------------------
// Print the files
void CommandLine::printFiles() const {
    size_t i = 0;
    for (auto const& file : files) {
        std::cout << "[" << i << "] " << file.get()->getPath() << std::endl;
        i++;
    }
}
//---------------------------------------------------------------------------
// Update paths
static void update(std::string& current, std::string& parent, std::string const& name) {
    if (current == parent) {
        current += "/" + name;
    } else {
        parent = current;
        current += "/" + name;
    }
}
//---------------------------------------------------------------------------
// Run command-line
void CommandLine::run(std::string const& baseDir) {
    std::string parent = baseDir;
    std::string current = baseDir;
    currentDir = std::make_shared<raii::TempDirectory>(baseDir);
    std::string command;
    size_t nrDirs = 0;
    size_t nrFiles = 0;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "quit") {
            std::cout << "quitting" << std::endl;
            break;
        }

        if (command == "enter") {
            std::string name = "dir" + std::to_string(nrDirs);
            nrDirs++;

            parentDir = std::move(currentDir);
            currentDir = std::make_shared<TempDirectory>(parentDir.get()->getFileDescriptor(), name, current);
            update(current, parent, name);

            if (parentDir->getPath() == (baseDir + "/"))
                dirs.push_back(std::move(parentDir));
            else
                dirs.push_front(std::move(parentDir));

            std::cout << "entering directory " << current << std::endl;
        }

        if (command == "current") {
            std::cout << "current directory: " << current << std::endl;
        }

        if (command == "leave") {
            if (dirs.empty()) {
                std::cout << "quitting" << std::endl;
                break;
            }

            if (existFiles(currentDir->getFileDescriptor()))
                dirs.push_front(std::move(currentDir));

            if (parent == baseDir) {
                currentDir = std::move(dirs.back());
                dirs.pop_back();
            } else {
                currentDir = std::move(dirs.front());
                dirs.pop_front();
            }

            std::cout << "leaving directory " << current << std::endl;
            current = parent;
            parent = currentDir->getParent();
        }

        if (command == "create") {
            std::string name = "file" + std::to_string(nrFiles);
            nrFiles++;
            files.push_back(currentDir->createFile(name));
            std::cout << "created file " << current << "/" << name << std::endl;
        }

        if (command == "remove") {
            size_t N;
            std::cin >> N;
            std::string name = "";
            deleteFile(N, name);
            std::cout << "removed file " << current << "/" << name << std::endl;
        }

        if (command == "list") {
            printFiles();
        }
    }
}

//---------------------------------------------------------------------------
} // namespace raii
//---------------------------------------------------------------------------
