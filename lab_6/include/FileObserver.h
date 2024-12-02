#pragma once
#include "observer.h"
#include <fstream>

class FileObserver: public Observer{
    void EventUpdater(const std::string event) override;
};