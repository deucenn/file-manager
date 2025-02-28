# File Manager

This is a simple command-line file manager written in C++. It allows you to perform basic file and directory operations through a text-based interface.

## Features

* **Navigation:**
    * `cd [path]`: Change the current directory. Supports relative and absolute paths, as well as `..` for the parent directory.
    * `pwd`: Print the current working directory.
* **Directory Operations:**
    * `mkdir [path]`: Create a new directory.
    * `rmdir [path]`: Remove a directory (removes all files and subdirectories within).
    * `ls`: List the files and directories in the current directory.
* **File Operations:**
    * `mkfil [filename]`: Create a new empty file.
    * `rmfil [filename]`: Delete a file.
    * `openfil [filename]`: Open a file in Notepad (Windows).
    * `renamefil [oldfilename] [newfilename]`: Rename a file.
    * `mvfil [sourcefilename] [destinationdirectory]`: Move a file to a different directory.
    * `inffil [filename]`: Display information about a file (name, extension, size, etc.).
    * `wtf [filename]`: Write text to a file.
* **Help:**
    * `help`: Display a list of available commands.
* **Exit:**
    * `exit` or `quit`: Exit the file manager.

## Building and Running

### Prerequisites

* A C++ compiler (e.g., g++, Visual Studio)
* C++17 or later support

### Compilation (g++)

1.  Save the source files (`main.cpp`, `FileManager.h`, `FileManager.cpp`) in a directory.
2.  Open a terminal or command prompt in that directory.
3.  Compile the project:

    ```bash
    g++ -std=c++17 main.cpp FileManager.cpp -o file_manager
    ```

4.  Run the executable:

    ```bash
    ./file_manager
    ```

### Compilation (Visual Studio)

1.  Create a new empty console project in Visual Studio.
2.  Add `main.cpp`, `FileManager.h`, and `FileManager.cpp` to the project.
3.  Build the project (F7).
4.  Run the project (Ctrl+F5).

### Usage

Once the file manager is running, you can enter commands at the `>` prompt.

## Example

```bash
pwd
Current Directory: /home/user/documents
ls
file1.txt  folder1/
mkdir newfolder
cd newfolder
mkfil test.txt
wtf test.txt
Enter the content of the file (enter ***END*** on a new line to save):

    This is a test file.
    ***END***
    Written to 'test.txt' successfully

ls
test.txt
cd ..
mvfil newfolder/test.txt ./
File 'newfolder/test.txt' successfully moved to './'.
ls
file1.txt  folder1/ test.txt newfolder/
exit
```

## Notes

* The `openfil` command uses Notepad on Windows. For cross-platform support, you would need to use different commands for other operating systems.
* Error handling is basic. More robust error checking and user feedback could be added.
* This is a simple project and can be extended with more features, such as tab completion, command history, and wildcard support.

## Contributing

Feel free to contribute to this project by submitting pull requests or opening issues.

## License

This project is licensed under the [MIT License](LICENSE.txt). 