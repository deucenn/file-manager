#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <format>

void currentDirectory();
void createFile();
void openFile();
void deleteFile();
void renameFile();
void getFileInfo();
void moveFile();
void createFolder();
void deleteFolder();

int main()
{
    int choice;
    do
    {
        std::cout << "File Manager" << std::endl;
        std::cout << "0. Current directory" << std::endl;
        std::cout << "1. Create a new file" << std::endl;
        std::cout << "2. Open an existing file" << std::endl;
        std::cout << "3. Delete file" << std::endl;
        std::cout << "4. Rename file" << std::endl;
        std::cout << "5. Get file information" << std::endl;
        std::cout << "6. Move file" << std::endl;
        std::cout << "7. Create folder" << std::endl;
        std::cout << "8. Delete folder" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            currentDirectory();
            break;
        case 1:
            createFile();
            break;
        case 2:
            openFile();
            break;
        case 3:
            deleteFile();
            break;
        case 4:
            renameFile();
            break;
        case 5:
            getFileInfo();
            break;
        case 6:
            moveFile();
            break;
        case 7:
            createFolder();
            break;
        case 8:
            deleteFolder();
            break;
        case 9:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 9);

    return 0;
}

void currentDirectory()
{
    try
    {
        std::cout << "Current Directory: " << std::filesystem::current_path() << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        std::cin.get();
    }
    catch (const std::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
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

        if (!std::filesystem::exists(current_file_name)) {
            std::cerr << "Error: File '" << current_file_name << "' does not exist." << std::endl;
            return;
        };

        std::filesystem::path new_folder_path_obj(new_folder_name);

        if (!std::filesystem::exists(new_folder_path_obj)) {
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