#include "../include/ConsoleObserver.h"
#include <stdexcept>
#include <iostream>

void ConsoleObserver::EventUpdater(std::string event){
    std::cout << event << std::endl;
}