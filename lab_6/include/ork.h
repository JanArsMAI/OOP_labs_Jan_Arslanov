#include "NPC.h"
#include "visitor.h"
#include <memory>
#pragma once

class Ork: public NPC{
    public:
        Ork(std::string name, int x, int y);
        void ToVisit(Visitor &visitor) override;
        std::unique_ptr<NPC> Clone() const override {
        return std::make_unique<Ork>(*this);
    }
};