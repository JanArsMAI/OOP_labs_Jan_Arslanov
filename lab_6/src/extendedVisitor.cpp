
#include "../include/extendedVisitor.h"
#include "../include/ork.h"
#include "../include/squirell.h"
#include "../include/druids.h"
#include <algorithm>

ExtendedVisitor::ExtendedVisitor(
    int range, 
    std::vector<std::unique_ptr<NPC>> &list_of_npcs, 
    std::vector<std::shared_ptr<Observer>> &list_of_observers
) : range(range), list_of_npcs(list_of_npcs), list_of_observers(list_of_observers) {}

void ExtendedVisitor::Visit(Druids &druid) {
    for (auto iter = list_of_npcs.begin(); iter != list_of_npcs.end();) {
        if (auto squirel = dynamic_cast<Squirell *>(iter->get())) {
            if (IsInRange(*squirel, druid)) {
                ToLogEvent("Squirel killed by Druid: " + iter->get()->getNpcName());
                ToLogEvent("Removing Squirrel: " + iter->get()->getNpcName());
                iter = list_of_npcs.erase(iter);
            } else {
                ++iter;
            }
        } else {
            ++iter;
        }
    }
}

void ExtendedVisitor::Visit(Squirell &sq) {
    for (auto iter = list_of_npcs.begin(); iter != list_of_npcs.end();) {
        if (auto ork = dynamic_cast<Ork *>(iter->get())) {
            if (IsInRange(*ork, sq)) {
                ToLogEvent("Squirel and Ork at peace: " + iter->get()->getNpcName());
                ToLogEvent("Squirel and Ork peaced");
                ++iter;
            } else {
                ++iter;
            }
        } else {
            ++iter;
        }
    }
}

void ExtendedVisitor::Visit(Ork &ork) {
    for (auto iter = list_of_npcs.begin(); iter != list_of_npcs.end();) {
        if (auto druid = dynamic_cast<Druids *>(iter->get())) {
            if (IsInRange(*druid, ork)) {
                ToLogEvent("Druid killed by Ork: " + iter->get()->getNpcName());
                ToLogEvent("Removing Druid: " + iter->get()->getNpcName());
                iter = list_of_npcs.erase(iter); 
            } else {
                ++iter;
            }
        } else {
            ++iter;
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
    auto npc_2_cord = npc_2.getCoordinates();
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
