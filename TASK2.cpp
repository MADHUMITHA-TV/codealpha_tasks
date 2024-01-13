#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void displayMenu() {
    std::cout << "\nCommand-Line File Manager Menu:\n"
              << "1. List files and directories\n"
              << "2. View file content\n"
              << "3. Create directory\n"
              << "4. Copy file\n"
              << "5. Move file\n"
              << "6. Exit\n";
}

void listFilesAndDirectories(const fs::path& currentPath) {
    for (const auto& entry : fs::directory_iterator(currentPath))
        std::cout << entry.path().filename() << '\n';
}

void viewFileContent(const fs::path& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::cout << "File content:\n";
        std::cout << file.rdbuf() << '\n';
        file.close();
    } else {
        std::cout << "Unable to open the file.\n";
    }
}

void createDirectory(const fs::path& currentPath) {
    std::string dirName;
    std::cout << "Enter the directory name: ";
    std::cin >> dirName;
    fs::create_directory(currentPath / dirName);
    std::cout << "Directory created.\n";
}

void copyFile(const fs::path& currentPath) {
    std::string sourceFileName, destinationFileName;
    std::cout << "Enter the source file name: ";
    std::cin >> sourceFileName;
    std::cout << "Enter the destination file name: ";
    std::cin >> destinationFileName;

    fs::copy_file(currentPath / sourceFileName, currentPath / destinationFileName);
    std::cout << "File copied.\n";
}

void moveFile(const fs::path& currentPath) {
    std::string sourceFileName, destinationFileName;
    std::cout << "Enter the source file name: ";
    std::cin >> sourceFileName;
    std::cout << "Enter the destination file name: ";
    std::cin >> destinationFileName;

    fs::rename(currentPath / sourceFileName, currentPath / destinationFileName);
    std::cout << "File moved.\n";
}

int main() {
    fs::path currentPath = fs::current_path();
    int choice;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listFilesAndDirectories(currentPath);
                break;
            case 2: {
                std::string fileName;
                std::cout << "Enter the file name: ";
                std::cin >> fileName;
                viewFileContent(currentPath / fileName);
                break;
            }
            case 3:
                createDirectory(currentPath);
                break;
            case 4:
                copyFile(currentPath);
                break;
            case 5:
                moveFile(currentPath);
                break;
            case 6:
                std::cout << "Exiting the file manager.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
