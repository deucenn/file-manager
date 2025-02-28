#include <iostream>
#include <string>
#include <sstream>
#include "FileManager.h"

int main()
{
    FileManager fm;

    std::string command;
    do
    {
        std::cout << "> ";
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "help")
        {
            fm.help();
        }
        else if (cmd == "cd")
        {
            std::string path;
            iss >> path;
            fm.cd(path);
        }
        else if (cmd == "mkdir")
        {
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
        }
        else if (cmd == "rmfil")
        {
            std::string fileName;
            iss >> fileName;
            fm.rmfil(fileName);
        }
        else if (cmd == "openfil")
        {
            std::string fileName;
            iss >> fileName;
            fm.openfil(fileName);
        }
        else if (cmd == "head")
        {
            std::string fileName;
            iss >> fileName;
            fm.head(fileName);
        }
        else if (cmd == "renamefil")
        {
            std::string oldFileName, newFileName;
            iss >> oldFileName >> newFileName;
            fm.renamefil(oldFileName, newFileName);
        }
        else if (cmd == "mvfil")
        {
            std::string sourceFileName, destinationFileName;
            iss >> sourceFileName >> destinationFileName;
            fm.mvfil(sourceFileName, destinationFileName);
        }
        else if (cmd == "inffil")
        {
            std::string fileName;
            iss >> fileName;
            fm.inffil(fileName);
        }
        else if (cmd == "wtf")
        {
            std::string fileName;
            iss >> fileName;
            fm.wtf(fileName);
        }
        else if (cmd == "mkdir")
        {
            std::string path;
            iss >> path;
            fm.mkdir(path);
        }
        else if (cmd == "rmdir")
        {
            std::string path;
            iss >> path;
            fm.rmdir(path);
        }
        else if (cmd == "exit" || cmd == "quit")
        {
            break;
        }
        else if (!cmd.empty())
        { // Ignore empty lines.
            std::cout << "Unknown command: " << cmd << std::endl;
        }

    } while (true);

    return 0;
}
