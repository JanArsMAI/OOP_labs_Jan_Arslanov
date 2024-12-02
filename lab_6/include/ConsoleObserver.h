#pragma once
#include "observer.h"
class ConsoleObserver: public Observer{
    void EventUpdater(const std::string event) override;
};