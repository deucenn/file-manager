#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <format>
#include <vector>

namespace fs = std::filesystem;

class FileManager
{
private:
    fs::path currentDirectory;

public:
    FileManager() : currentDirectory(fs::current_path()) {}

    void cd(const std::string &path);
    void ls();
    void pwd();
    void mkfil(const std::string &fileName);
    void rmfil(const std::string &fileName);
    void openfil(const std::string &fileName);
    void renamefil(const std::string &oldFileName, const std::string &newFileName);
    void mvfil(const std::string &sourceFileName, const std::string &destinationFileName);
    void inffil(const std::string &fileName);
    void mkdir(const std::string &path);
    void rmdir(const std::string &path);
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
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void FileManager::openfil(const std::string &fileName) {};
void FileManager::renamefil(const std::string &oldFileName, const std::string &newFileName) {};
void FileManager::mvfil(const std::string &sourceFileName, const std::string &destinationFileName) {};
void FileManager::inffil(const std::string &fileName) {};
void FileManager::mkdir(const std::string &path) {};
void FileManager::rmdir(const std::string &path) {};

int main()
{
    FileManager fm; // Create an instance of the FileManager

    std::string command;
    do
    {
        std::cout << "> "; // Prompt
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, command);

        // Parse command (example: "cd myfolder")
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "cd")
        {
            std::string path;
            iss >> path;
            fm.cd(path);
            } else if (cmd == "mkdir") {
                std::string path;
                iss >> path;
                fm.mkdir(path);
        }
        else if (cmd == "ls")
        {
            fm.ls();
        }
        else if (cmd == "pwd")
        {
            fm.pwd();
        }
        else if (cmd == "mkfil")
        {
            std::string fileName;
            iss >> fileName;
            fm.mkfil(fileName);
        } // ... handle other commands

        else if (cmd == "exit" || cmd == "quit")
        {
            break; // Exit the loop
        }
        else if (!cmd.empty())
        { // Ignore empty lines.
            std::cout << "Unknown command: " << cmd << std::endl;
        }

    } while (true);

    return 0;
}

void createFile()
{
    std::cout << "Creating a new file..." << std::endl;
    std::string file_name;
    std::cout << "Enter the name of the file (inlcuding extensions) WARNING: can override files: " << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, file_name);

    std::ofstream file(file_name, std::ios::trunc);

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
        std::cout << "File '" << file_name << "' created successfully" << std::endl;
    }
    else
    {
        std::cerr << "Error: Could not create file '" << file_name << "'." << std::endl;
    }
};

void openFile()
{
    std::cout << "Opening an existing file..." << std::endl;
    std::cout << "Enter the name of the file (inlcuding extensions): " << std::endl;
    std::string file_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, file_name);

    std::ifstream file(file_name);
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::cout << line << '\n';
        }
        file.close();

        std::cout << "\nPress Enter twice to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        std::cin.get();
    }

    else
        std::cout << "Unable to open file '" << file_name << "'." << std::endl;
};

void deleteFile()
{
    std::cout << "Deleting file..." << std::endl;
    std::cout << "Enter the name of the file (inlcuding extensions): " << std::endl;
    std::string file_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, file_name);

    if (remove(file_name.c_str()) != 0)
    {
        std::cout << "Error deleting file" << std::endl;
    }
    else
    {
        std::cout << "File '" << file_name << "' successfully deleted" << std::endl;
    }
};

void renameFile()
{
    std::cout << "Renaming file..." << std::endl;
    std::cout << "Enter the current name of the file (inlcuding extensions) you want to rename: " << std::endl;
    std::string current_file_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, current_file_name);

    std::string new_file_name;
    std::cout << "Enter the new name of the file (inlcuding extensions): " << std::endl;
    std::getline(std::cin, new_file_name);

    try
    {
        if (std::filesystem::exists(new_file_name))
        {
            char overwrite;
            std::cout << "Warning: File '" << new_file_name << "' already exists. Overwrite? (y/n): ";
            std::cin >> overwrite;
            if (tolower(overwrite) != 'y')
            {
                std::cout << "Rename cancelled." << std::endl;
                return;
            }
        }
        std::filesystem::rename(current_file_name, new_file_name);
        std::cout << "File '" << current_file_name << "' successfully renamed to '" << new_file_name << "'.\n"
                  << std::endl;
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error renaming file: " << ex.what() << std::endl;
    }
};

void getFileInfo()
{
    std::cout << "Getting file information..." << std::endl;
    std::cout << "Enter the name of the file (inlcuding extensions): " << std::endl;
    std::string file_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, file_name);

    try
    {
        if (std::filesystem::exists(file_name))
        {
            std::filesystem::path file_path(file_name);
            std::cout << "File Name: " << file_path.filename() << std::endl;
            std::cout << "File Extension: " << file_path.extension() << std::endl;
            std::cout << "Parent Directory: " << std::filesystem::current_path() << std::endl;
            std::cout << "Is Directory: " << std::filesystem::is_directory(file_path) << std::endl;
            std::cout << "Is Symbolic Link: " << std::filesystem::is_symlink(file_path) << std::endl;
            std::cout << "File Size: " << std::to_string(std::filesystem::file_size(file_path)) << " bytes" << std::endl;

            // Last Modified Time
            // auto last_write_time = std::filesystem::last_write_time(file_path);
            // std::time_t cftime = std::chrono::system_clock::to_time_t(last_write_time);
            // std::cout << "Last Modified: " << std::put_time(std::localtime(&cftime), "%c") << std::endl;
            // auto p = std::filesystem::temp_directory_path();
            // std::filesystem::file_time_type ftime = std::filesystem::last_write_time(p);
            // std::cout << "Last Modified: " << std::format(ftime) << std::endl;

            std::cout << "\nPress Enter twice to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        else
        {
            std::cout << "File '" << file_name << "' does not exist." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error getting file information: " << ex.what() << std::endl;
    }
};

void moveFile()
{
    std::cout << "Moving file..." << std::endl;
    std::cout << "Enter the current name of the file (inlcuding extensions): " << std::endl;
    std::string current_file_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, current_file_name);

    std::string new_folder_name;
    std::cout << "Enter the new parent directory path for the file: " << std::endl;
    std::getline(std::cin, new_folder_name);

    try
    {
        std::filesystem::path current_file_path(current_file_name);

        if (!std::filesystem::exists(current_file_name))
        {
            std::cerr << "Error: File '" << current_file_name << "' does not exist." << std::endl;
            return;
        };

        std::filesystem::path new_folder_path_obj(new_folder_name);

        if (!std::filesystem::exists(new_folder_path_obj))
        {
            std::cerr << "Error: Folder '" << new_folder_name << "' does not exist." << std::endl;
            return;
        };

        std::filesystem::path new_file_path = new_folder_path_obj / current_file_path.filename();

        std::filesystem::rename(current_file_path, new_file_path);
        std::cout << "File '" << current_file_name << "' successfully moved to '" << new_folder_name << "'." << std::endl;
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error getting file information: " << ex.what() << std::endl;
    }
};

void createFolder()
{
    std::cout << "Creating a new folder..." << std::endl;
    std::cout << "Enter the name of the folder: " << std::endl;
    std::string folder_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, folder_name);

    std::filesystem::create_directory(folder_name);

    std::cout << "Folder '" << folder_name << "' created successfully" << std::endl;
};

void deleteFolder()
{
    std::cout << "Deleting folder..." << std::endl;
    std::cout << "Enter the name of the folder: " << std::endl;
    std::string folder_name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, folder_name);

    if (std::filesystem::remove_all(folder_name))
    {
        std::cout << "Folder '" << folder_name << "' successfully deleted" << std::endl;
    }
    else
    {
        std::cout << "Error deleting folder '" << folder_name << "'. It may still contain files." << std::endl;
    }
};

void copyFile() {};

void searchFolder() {};
