#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>

void currentDirectory();
void createFile();
void openFile();
void deleteFile();

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
        std::cout << "4. Exit" << std::endl;
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
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

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
    } catch (const std::filesystem::filesystem_error& ex) {
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
}
