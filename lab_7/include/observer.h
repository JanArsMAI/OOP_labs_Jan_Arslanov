#pragma once
#include <string>


class Observer{
    public:
    virtual void EventUpdater(const std::string event)=0;
    virtual ~Observer() = default;
};