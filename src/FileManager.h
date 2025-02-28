#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
private:
    fs::path currentDirectory;

public:
    FileManager(); // Constructor declaration

    void help();
    void cd(const std::string& path);
    void ls();
    void pwd();
    void mkfil(const std::string& fileName);
    void rmfil(const std::string& fileName);
    void openfil(const std::string& fileName);
    void renamefil(const std::string& oldFileName, const std::string& newFileName);
    void mvfil(const std::string& sourceFileName, const std::string& destinationFileName);
    void inffil(const std::string& fileName);
    void wtf(const std::string& fileName);
    void mkdir(const std::string& path);
    void rmdir(const std::string& path);
};

#endif // FILE_MANAGER_H