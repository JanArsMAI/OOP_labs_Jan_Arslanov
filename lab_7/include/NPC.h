#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <random>
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
        void move_coord(int w, int h, int s) {
        std::random_device rd;
        std::mt19937 gen(rd());

        enum Direction { RIGHT = 1, LEFT, UP, DOWN };

        std::vector<Direction> possibleDirections;

        if (x + s < w) possibleDirections.push_back(RIGHT); 
        if (x - s >= 0) possibleDirections.push_back(LEFT); 
        if (y + s < h) possibleDirections.push_back(UP);   
        if (y - s >= 0) possibleDirections.push_back(DOWN);

        if (possibleDirections.empty()) {
            return;
        }

        std::uniform_int_distribution<> distrib(0, possibleDirections.size() - 1);
        Direction WayToMove = possibleDirections[distrib(gen)];

        switch (WayToMove) {
            case RIGHT:
                x += s;
                break;
            case LEFT:
                x -= s;
                break;
            case UP:
                y += s;
                break;
            case DOWN:
                y -= s;
                break;
        }
    }
    double distanceTo(const NPC& other) const {
        int dx = other.x - x;
        int dy = other.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }
    bool isAliveStatus() {return isAlive;}
    void killNPC(){
        isAlive = false;
    }
    private:
        std::string NpcName;
        bool markedForRemoval = false;
        int x;
        int y;
        std::string npcType;
        bool isAlive = true;
};