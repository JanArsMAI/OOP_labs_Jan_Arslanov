
#include "../include/extendedVisitor.h"
#include "../include/ork.h"
#include "../include/squirell.h"
#include "../include/druids.h"
#include <algorithm>
#include <random>

int ExtendedVisitor::RollDice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}
ExtendedVisitor::ExtendedVisitor( 
    std::vector<std::shared_ptr<NPC>> &list_of_npcs, 
    std::vector<std::shared_ptr<Observer>> &list_of_observers
) : list_of_npcs(list_of_npcs), list_of_observers(list_of_observers) {}

void ExtendedVisitor::Visit(Druids &druid) {
    for (const auto &npc : list_of_npcs) {
        if (auto squirrel = dynamic_cast<Squirell *>(npc.get())) {
            if (IsInRange(*squirrel, druid)) {
                int attackRoll = RollDice();
                int defenseRoll = RollDice();

                if (attackRoll > defenseRoll) {
                    ToLogEvent("Squirrel killed by Druid: " + squirrel->getNpcName());
                    squirrel->killNPC();
                } else {
                    ToLogEvent("Squirrel survived the attack by Druid: " + squirrel->getNpcName());
                }
            }
        }
    }
}

void ExtendedVisitor::Visit(Squirell &sq) {
    for (const auto &npc : list_of_npcs) {
        if (auto ork = dynamic_cast<Ork *>(npc.get())) {
            if (IsInRange(*ork, sq)) {
                int attackRoll = RollDice();
                int defenseRoll = RollDice();

                if (attackRoll > defenseRoll) {
                    ToLogEvent("Squirrel killed by Ork: " + sq.getNpcName());
                    sq.killNPC();
                } else {
                    ToLogEvent("Squirrel survived the attack by Ork: " + sq.getNpcName());
                }
            }
        }
    }
}

void ExtendedVisitor::Visit(Ork &ork) {
    for (const auto &npc : list_of_npcs) {
        if (auto druid = dynamic_cast<Druids *>(npc.get())) {
            if (IsInRange(*druid, ork)) {
                int attackRoll = RollDice();
                int defenseRoll = RollDice();

                if (attackRoll > defenseRoll) {
                    ToLogEvent("Druid killed by Ork: " + druid->getNpcName());
                    druid->killNPC();
                } else {
                    ToLogEvent("Druid survived the attack by Ork: " + druid->getNpcName());
                }
            }
        }
    }
}
bool ExtendedVisitor::AreAllOutOfRange() {
    for (const auto &npc_1 : list_of_npcs) {
        for (const auto &npc_2 : list_of_npcs) {
            if (npc_1 != npc_2 && IsInRange(*npc_1, *npc_2)) {
                return false;
            }
        }
    }
    return true;
}

bool ExtendedVisitor::IsInRange(NPC &npc_1, NPC &npc_2) {
    auto npc_1_cord = npc_1.getCoordinates();
    int range;
    auto npc_2_cord = npc_2.getCoordinates();
    if (npc_1.getNpcType() == "Ork"){
        range = 10;
    }
    if (npc_1.getNpcType() == "Squirell"){
        range = 5;
    }
    if (npc_1.getNpcType() == "Druid"){
        range = 10;
    }
    return std::abs(npc_1_cord.first - npc_2_cord.first) +
           std::abs(npc_1_cord.second - npc_2_cord.second) <= range;
}

void ExtendedVisitor::ToLogEvent(const std::string &event) {
    if (list_of_observers.empty()) {
        std::cerr << "No observers to log event: " << event << std::endl;
        return;
    }
    for (auto &observer : list_of_observers) {
        observer->EventUpdater(event);
    }
}
