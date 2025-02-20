#include <iostream>
#include <fstream>
#include <string>
#include <limits>

int main()
{
    std::cout << "File Manager" << std::endl;
    std::cout << "1. Create a new file" << std::endl;
    std::cout << "2. Open an existing file" << std::endl;
    std::cout << "3. Delete file" << std::end;
    std::cout << "4. Exit" << std::endl;

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1)
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
    }
    else if (choice == 2)
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
        }

        else
            std::cout << "Unable to open file '" << file_name << "'." << std::endl;
    }
    else if (choice == 3)
    {
        std::cout << "Deleting file..." << std::endl;
        std::cout << "Enter the name of the file (inlcuding extensions): " << std::endl;
        std::string file_name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, file_name);
    }
    else if (choice == 4)
    {
        std::cout << "Exiting the program..." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Invalid choice. Please try again." << std::endl;
        main();
    }
    return 0;
}