#pragma once
#include "NPC.h"
#include "visitor.h"
#include <memory>

class Druids : public NPC {
public:
    Druids(std::string name, int x, int y);
    void ToVisit(Visitor &visitor) override;
    std::unique_ptr<NPC> Clone() const override {
        return std::make_unique<Druids>(*this);
    }
};