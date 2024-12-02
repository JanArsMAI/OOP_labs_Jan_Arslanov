#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <memory>
#pragma once

class NPC{
    public:
        NPC(std::string type, std::string name, int px, int py) {
            npcType = type;
            NpcName = name;
            x = px;
            y = py;
        }
        virtual ~NPC() = default;
        std::pair<int, int> getCoordinates(){
            return std::pair<int, int>(x, y);
        }
        std::string getNpcName(){
            return NpcName;
        }
        virtual void ToVisit(class Visitor &visitor) = 0;
        std::string getNpcType() const {
            return npcType;
        }
        virtual std::unique_ptr<NPC> Clone() const = 0;
        
    private:
        std::string NpcName;
        bool markedForRemoval = false;
        int x;
        int y;
        std::string npcType;
};