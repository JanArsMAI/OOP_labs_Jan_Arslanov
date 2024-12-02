#pragma once
#include "NPC.h"
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
#include "visitor.h"
#include "observer.h"
#include "NPCfactory.h"
#include "druids.h"
#include "squirell.h"
#include "ork.h"
#include <stdexcept>
#include "extendedVisitor.h"
#include <fstream>
#include <sstream>

class Arena{
    public:
        Arena(int ArenaWidth, int ArenaHeight);
        Arena(int ArenaHeight);
        void ToStartBattle(int range);
        void LoadNpcFromFile(std::string &filename);
        void SaveToFile(std::string &filename);
        void AddNPC(std::unique_ptr<NPC> npc);
        void AddObserver(std::shared_ptr<Observer> observer);
        void ShowAllNPCs();
        void SpawnNPC(const std::string &type, const std::string &name, int x = -1, int y = -1);
        std::vector<std::unique_ptr<NPC>> GetAllNPCsCopy() const;
        void RemoveNPC(const std::string& npcName);
        int getSizeObservers();
        bool CheckForDuplicate(std::string name, int x, int y);

    private:
        int width, height;
        std::vector<std::shared_ptr<Observer>> ListOfObservers;
        std::vector<std::unique_ptr<NPC>> ListOfNPCs;
        int createRandomValue(int a, int b);
        
};