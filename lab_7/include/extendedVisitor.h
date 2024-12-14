#pragma once

#include <memory>
#include <vector>
#include "visitor.h"
#include "observer.h"
#include "NPC.h"

class ExtendedVisitor : public Visitor {
public:
    ExtendedVisitor(
        std::vector<std::shared_ptr<NPC>> &list_of_npcs, 
        std::vector<std::shared_ptr<Observer>> &list_of_observers
    );

    void Visit(Druids &druid) override;
    void Visit(Ork &ork) override;
    void Visit(Squirell &squirell) override;
    bool AreAllOutOfRange();

private:
    int RollDice();
    std::vector<std::shared_ptr<NPC>> &list_of_npcs;
    std::vector<std::shared_ptr<Observer>> &list_of_observers;
    void ToLogEvent(const std::string &event);
    bool IsInRange(NPC &npc1, NPC &npc2);
};