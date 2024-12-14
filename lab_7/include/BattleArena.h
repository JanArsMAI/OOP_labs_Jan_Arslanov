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
#include <shared_mutex>
#include <fstream>
#include <sstream>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>

class Arena {
public:
    Arena() : width(100), height(100), isRunning(true) {}

    ~Arena() {
        std::cerr << "Destructing Arena..." << std::endl;
        StopBattle();  
        ListOfNPCs.clear();
        std::cerr << "Arena destructed!" << std::endl;
    }
    void ToStartBattle();
    void AddNPC(std::shared_ptr<NPC> npc);
    void AddObserver(std::shared_ptr<Observer> observer);
    std::vector<std::shared_ptr<NPC>> GetAllNPCsCopy() const;
    void SpawnNPC(const std::string &type, const std::string &name, int x = -1, int y = -1);
    void RemoveNPC(const std::string &name);
    int getSizeObservers();
    bool CheckForDuplicate(std::string name, int x, int y);
    void startMovementThread();
    void StartFightThread();

private:
    void printMap(const std::vector<std::shared_ptr<NPC>>& listOfNPCs, int width, int height);
    int createRandomValue(int a, int b);
    void MovingFunction();
    void FightFunction();
    void StopBattle();
    void RemoveDeadNPCs();
    int width, height;
    std::vector<std::shared_ptr<Observer>> ListOfObservers;
    std::vector<std::shared_ptr<NPC>> ListOfNPCs; 
    std::shared_mutex npcMutex;                   
    std::atomic<bool> isRunning{false};                
    std::thread movementThread;                  
    std::thread fightThread;                      
    std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> fightQueue;
    std::mutex fightQueueMutex;
    std::mutex coutMutex;
};
