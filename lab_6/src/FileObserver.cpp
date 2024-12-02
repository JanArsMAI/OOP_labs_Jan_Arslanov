#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include "../include/FileObserver.h"
#include <cstring>

void FileObserver::EventUpdater(const std::string event) {
    if (!std::filesystem::exists("./logs")) {
        std::filesystem::create_directory("./logs");
    }
    std::ofstream OutFile("./logs/logging.txt", std::ios::app);
    if (!OutFile) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        throw std::ios_base::failure("Failed to open logging file.");
    }
    OutFile << event << std::endl;
    OutFile.flush();
}