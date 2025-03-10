#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <vector>

FileManager::FileManager() : currentDirectory(fs::current_path()) {}

void FileManager::help()
{
    std::cout << "File Manager Commands:" << std::endl;
    std::cout << "help: Display this help message." << std::endl;
    std::cout << "cd [path]: Change the current directory to the specified path." << std::endl;
    std::cout << "ls: List the files and directories in the current directory." << std::endl;
    std::cout << "pwd: Print the current working directory." << std::endl;
    std::cout << "mkfil [filename]: Create a new file with the specified name." << std::endl;
    std::cout << "rmfil [filename]: Delete the specified file." << std::endl;
    std::cout << "openfil [filename]: Open the specified file in a text editor." << std::endl;
    std::cout << "head [filename]: Display the head of the file." << std::endl;
    std::cout << "tail [filename]: Display the tail of the file." << std::endl;
    std::cout << "renamefil [oldfilename] [newfilename]: Rename the specified file." << std::endl;
    std::cout << "mvfil [filename] [destination]: Move the selected file to the specified destination." << std::endl;
    std::cout << "inffil [filename]: See the metadata of specified file." << std::endl;
    std::cout << "wtf [filename]: Write to the specified file." << std::endl;
    std::cout << "mkdir [pathname]: Create a new directory with the specified name." << std::endl;
    std::cout << "rmdir [pathname]: Remove the specified directory." << std::endl;
};

void FileManager::cd(const std::string &path)
{
    try
    {
        if (path == "..")
        {
            if (currentDirectory.has_parent_path())
            { // Check if we're at the root
                currentDirectory = currentDirectory.parent_path();
            }
            else
            {
                std::cerr << "Already at the root directory." << std::endl;
                return;
            }
        }
        else
        {
            fs::path newPath = currentDirectory / path;
            if (fs::exists(newPath) && fs::is_directory(newPath))
            {
                currentDirectory = newPath;
                pwd();
            }
            else
            {
                std::cerr << "Error: Invalid path or not a directory." << std::endl;
            };
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::ls()
{
    try
    {
        for (const auto &entry : fs::directory_iterator(currentDirectory))
        {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::pwd()
{
    std::cout << "Current Directory: " << currentDirectory << std::endl;
};

void FileManager::mkfil(const std::string &fileName)
{
    try
    {
        std::ofstream file(currentDirectory / fileName);
        if (file.is_open())
        {
            std::cout << "File '" << fileName << "' created successfully" << std::endl;
        }
        else
        {
            std::cerr << "Error: Could not create file '" << fileName << "'." << std::endl;
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::rmfil(const std::string &fileName)
{
    try
    {
        fs::remove(currentDirectory / fileName);
        std::cout << "File '" << fileName << "' deleted successfully" << std::endl;
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::openfil(const std::string &fileName)
{
    try
    {
        if (!fs::exists(currentDirectory / fileName))
        {
            std::cerr << "Error: File '" << fileName << "' does not exist." << std::endl;
            return;
        }
        // Open the file in a text editor (e.g., Notepad++)
        fs::path filePath = currentDirectory / fileName;
        std::string filePathString = filePath.string();

        std::string command = "notepad \"" + filePathString + "\"";

        int result = std::system(command.c_str());
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::head(const std::string &fileName)
{
    try
    {
        if (!fs::exists(currentDirectory / fileName))
        {
            std::cout << "Error: File '" << fileName << "' does not exist." << std::endl;
        }
        std::ifstream file(currentDirectory / fileName);
        if (file.is_open())
        {
            std::string line;
            int lineNumber = 1;
            while (std::getline(file, line))
            {
                std::cout << lineNumber << ": " << line << std::endl;
                lineNumber++;
                if (lineNumber > 10)
                {
                    break;
                }
            }
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::tail(const std::string &fileName)
{
    try {
        if (!fs::exists(currentDirectory / fileName)) {
            std::cerr << "Error: File '" << fileName << "' does not exist." << std::endl;
            return;
        }

        std::ifstream file(currentDirectory / fileName);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file '" << fileName << "'." << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        if (!lines.empty()) {
            std::cout << lines.back() << std::endl; 
        } else {
            std::cerr << "Error: File '" << fileName << "' is empty." << std::endl;
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::renamefil(const std::string &oldFileName, const std::string &newFileName)
{
    try
    {
        if (!fs::exists(currentDirectory / oldFileName))
        {
            std::cerr << "Error: File '" << oldFileName << "' does not exist." << std::endl;
            return;
        };

        if (oldFileName == newFileName)
        {
            std::cerr << "Error: New file name cannot be the same as the old file name." << std::endl;
            return;
        };

        if (fs::exists(currentDirectory / newFileName))
        {
            char overwrite;
            std::cout << "Warning: File '" << newFileName << "' already exists. Overwrite? (y/n): ";
            std::cin >> overwrite;
            if (tolower(overwrite) != 'y')
            {
                std::cout << "Rename cancelled." << std::endl;
                return;
            }
        }
        fs::rename(oldFileName, newFileName);
        std::cout << "File '" << oldFileName << "' successfully renamed to '" << newFileName << "'.\n"
                  << std::endl;
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error renaming file: " << ex.what() << std::endl;
    }
};

void FileManager::mvfil(const std::string &sourceFileName, const std::string &destinationFileName)
{
    try
    {
        std::filesystem::path current_file_path(sourceFileName);

        if (!std::filesystem::exists(sourceFileName))
        {
            std::cerr << "Error: File '" << sourceFileName << "' does not exist." << std::endl;
            return;
        };

        std::filesystem::path new_folder_path_obj(destinationFileName);

        if (!std::filesystem::exists(new_folder_path_obj))
        {
            std::cerr << "Error: Folder '" << destinationFileName << "' does not exist." << std::endl;
            return;
        };

        std::filesystem::path new_file_path = new_folder_path_obj / current_file_path.filename();

        std::filesystem::rename(current_file_path, new_file_path);
        std::cout << "File '" << sourceFileName << "' successfully moved to '" << destinationFileName << "'." << std::endl;
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error getting file information: " << ex.what() << std::endl;
    }
};
void FileManager::inffil(const std::string &fileName)
{
    try
    {
        if (std::filesystem::exists(fileName))
        {
            std::filesystem::path file_path(fileName);
            std::cout << "File Name: " << file_path.filename() << std::endl;
            std::cout << "File Extension: " << file_path.extension() << std::endl;
            std::cout << "Parent Directory: " << std::filesystem::current_path() << std::endl;
            std::cout << "Is Directory: " << std::filesystem::is_directory(file_path) << std::endl;
            std::cout << "Is Symbolic Link: " << std::filesystem::is_symlink(file_path) << std::endl;
            std::cout << "File Size: " << std::to_string(std::filesystem::file_size(file_path)) << " bytes" << std::endl;
        }
        else
        {
            std::cout << "File '" << fileName << "' does not exist." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error getting file information: " << ex.what() << std::endl;
    }
};

void FileManager::wtf(const std::string &fileName)
{
    try
    {
        if (!fs::exists(currentDirectory / fileName))
        {
            std::cerr << "File '" << fileName << "' does not exist." << std::endl;
            return;
        };
        std::ofstream file(currentDirectory / fileName, std::ios::trunc);

        if (file.is_open())
        {
            std::cout << "Enter the content of the file (enter '***END***' on a new line to save):\n"
                      << std::endl;
            std::string line;

            while (std::getline(std::cin, line) && line != "***END***")
            {
                file << line << std::endl;
            }

            file.close();
            std::cout << "Written to '" << fileName << "' successfully" << std::endl;
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error opening file: " << ex.what() << std::endl;
    }
};

void FileManager::mkdir(const std::string &path)
{
    try
    {
        if (fs::exists(path))
        {
            std::cerr << "Error: Folder '" << path << "' already exists." << std::endl;
            return;
        }
        fs::create_directory(path);
        std::cout << "Folder '" << path << "' created successfully" << std::endl;
    }
    catch (fs::filesystem_error &ex)
    {
        std::cerr << "Error creating folder: " << ex.what() << std::endl;
    }
};

void FileManager::rmdir(const std::string &path)
{
    try
    {
        if (!fs::exists(path))
        {
            std::cerr << "Error: Folder '" << path << "' does not exist." << std::endl;
            return;
        }
        if (!fs::is_directory(path))
        {
            std::cerr << "Error: '" << path << "' is not a folder." << std::endl;
            return;
        }
        if (fs::remove_all(path))
        {
            std::cout << "Folder '" << path << "' successfully deleted" << std::endl;
        }
        else
        {
            std::cout << "Error deleting folder '" << path << "'. It may still contain files." << std::endl;
        }
    }
    catch (const fs::filesystem_error &ex)
    {
        std::cerr << "Error deleting folder: " << ex.what() << std::endl;
    }
};