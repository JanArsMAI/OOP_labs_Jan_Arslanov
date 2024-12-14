#include <memory>
#include "NPC.h"
#include "druids.h"
#include "squirell.h"
#include "ork.h"

class NPCFactory{
public:
    static std::unique_ptr<NPC> NpcCreator(const std::string &type, const std::string &name, int x, int y) {
    if (type == "Druid") {
        return std::make_unique<Druids>(name, x, y);
    } else if (type == "Ork") {
        return std::make_unique<Ork>(name, x, y);
    } else if (type == "Squirell") {
        return std::make_unique<Squirell>(name, x, y);
    }
    std::cerr << "Unknown NPC type: " << type << "\n";
    return nullptr;
}
};