#include "NPC.h"
#include "visitor.h"
#include <memory>
#pragma once

class Squirell: public NPC{
    public:
        Squirell(std::string name, int x, int y);
        void ToVisit(Visitor &visitor) override;
        std::unique_ptr<NPC> Clone() const override {
        return std::make_unique<Squirell>(*this);
        }
};