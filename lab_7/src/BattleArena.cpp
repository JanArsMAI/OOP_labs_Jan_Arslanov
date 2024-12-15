#include "../include/BattleArena.h"
#include <random>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include <sstream>
#include <chrono>

void Arena::AddNPC(std::shared_ptr<NPC> npc) {
    if (!npc) {
        throw std::invalid_argument("Attempted to add a null NPC");
    }
    ListOfNPCs.push_back(std::move(npc));
}

void Arena::AddObserver(std::shared_ptr<Observer> observer) {
    if (!observer) {
        throw std::invalid_argument("Attempted to add a null observer");
    }
    ListOfObservers.push_back(observer);
}

void Arena::ToStartBattle() {
    isRunning = true;
    std::vector<std::string> types = {"Ork", "Druid", "Squirell"};
    for (int i = 0; i < 50; ++i) {
        int x, y;
        do {
            x = createRandomValue(0, width - 1);
            y = createRandomValue(0, height - 1);
        } while (!CheckForDuplicate("", x, y));

        int c = createRandomValue(0, types.size() - 1);
        std::string type = types[c];
        std::string name = "NPC_" + type + std::to_string(i);
        try {
            SpawnNPC(type, name, x, y);
        } catch (const std::exception& e) {
            std::cerr << "Failed to spawn NPC: " << e.what() << std::endl;
        }
    }
    for (auto &observer : ListOfObservers) {
        try {
            observer->EventUpdater("The battle has started");
        } catch (const std::exception& e) {
            std::cerr << "Observer error: " << e.what() << std::endl;
        }
    }

    try {
        startMovementThread();
        StartFightThread();
    } catch (const std::exception& e) {
        std::cerr << "Error starting threads: " << e.what() << std::endl;
        StopBattle();
    }
    auto startTime = std::chrono::steady_clock::now();
    while (isRunning) {
        
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 30) {
            StopBattle();
        }
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        printMap(ListOfNPCs, width, height);
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Arena::StopBattle() {
    isRunning = false;
    try {
        if (movementThread.joinable()) {
            movementThread.join();
        }
        if (fightThread.joinable()) {
            fightThread.join();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error stopping battle threads: " << e.what() << std::endl;
    }
}
void Arena::MovingFunction() {
    try {
        while (isRunning) {
            std::vector<std::shared_ptr<NPC>> npcs;
            {
                std::shared_lock<std::shared_mutex> lock(npcMutex);
                for (const auto& npc : ListOfNPCs) {
                    if (npc->isAliveStatus()) {
                        npcs.push_back(std::shared_ptr<NPC>(npc.get(), [](NPC*) {}));
                    }
                }
            }
            for (const auto& npc : npcs) {
                npc->move_coord(width, height,
                                npc->getNpcType() == "Druid"   ? 10 :
                                npc->getNpcType() == "Ork"     ? 20 :
                                npc->getNpcType() == "Squirell" ? 5 : 0);

                for (const auto& otherNpc : npcs) {
                    if (npc != otherNpc) {
                        double dist = npc->distanceTo(*otherNpc);
                        if ((dist <= 10.0 && (npc->getNpcType() == "Druid" || npc->getNpcType() == "Ork")) ||
                            (dist <= 5.0 && npc->getNpcType() == "Squirell")) {
                            std::lock_guard<std::mutex> queueLock(fightQueueMutex);
                            fightQueue.push({npc, otherNpc});
                        }
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during movement function: " << e.what() << std::endl;
    }
}
void Arena::printMap(const std::vector<std::shared_ptr<NPC>>& listOfNPCs, int width, int height) {
    try {
        std::shared_lock<std::shared_mutex> lock(npcMutex);
        std::vector<std::vector<char>> map(height, std::vector<char>(width, '.'));
        for (const auto& npc : listOfNPCs) {
            if (!npc->isAliveStatus()) continue;
            int x = npc->getCoordinates().first;
            int y = npc->getCoordinates().second;
            if (x >= 0 && x < width && y >= 0 && y < height) {
                map[y][x] = npc->getNpcName()[0];
            }
        }
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << map[y][x] << ' ';
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error printing map: " << e.what() << std::endl;
    }
}

void Arena::RemoveDeadNPCs() {
    try {
        std::unique_lock<std::shared_mutex> lock(npcMutex);
        ListOfNPCs.erase(
            std::remove_if(
                ListOfNPCs.begin(),
                ListOfNPCs.end(),
                [](const std::shared_ptr<NPC>& npc) { return !npc->isAliveStatus(); }
            ),
            ListOfNPCs.end()
        );
        std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> cleanedQueue;
        while (!fightQueue.empty()) {
            auto fightPair = fightQueue.front();
            fightQueue.pop();
            if (fightPair.first && fightPair.second &&
                fightPair.first->isAliveStatus() && fightPair.second->isAliveStatus()) {
                cleanedQueue.push(fightPair);
            }
        }
        fightQueue = std::move(cleanedQueue);

    } catch (const std::exception& e) {
        std::cerr << "Error removing dead NPCs: " << e.what() << std::endl;
    }
}

void Arena::FightFunction() {
    while (isRunning) {
        std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> fightPair;
        bool hasFight = false;

        {
            std::lock_guard<std::mutex> lock(fightQueueMutex);
            if (!fightQueue.empty()) {
                fightPair = fightQueue.front();
                fightQueue.pop();
                hasFight = true;
            }
        }

        if (hasFight) {
            auto npc1 = fightPair.first;
            auto npc2 = fightPair.second;
            if (npc1 && npc2 && npc1->isAliveStatus() && npc2->isAliveStatus()) {
                ExtendedVisitor extendedVisitor(ListOfNPCs, ListOfObservers);
                try {
                    npc1->ToVisit(extendedVisitor);
                    npc2->ToVisit(extendedVisitor);
                } catch (const std::exception& e) {
                    std::cerr << "Error during NPC fight: " << e.what() << std::endl;
                }
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        RemoveDeadNPCs();
    }
}
bool Arena::CheckForDuplicate(std::string name, int x, int y) {
    try {
        for (auto it = ListOfNPCs.begin(); it != ListOfNPCs.end(); ++it) {
            if ((*it).get()->getNpcName() == name) {
                return false;
            }
            std::pair<int, int> coord = (*it).get()->getCoordinates();
            int coor_x = coord.first;
            int coor_y = coord.second;
            if (x == coor_x && y == coor_y) {
                return false;
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error checking for duplicates: " << e.what() << std::endl;
        return false;
    }
}

void Arena::SpawnNPC(const std::string& type, const std::string& name, int x, int y) {
    std::unique_lock<std::shared_mutex> lock(npcMutex);
    try {
        if (!CheckForDuplicate(name, x, y)) {
            throw std::invalid_argument("Wrong NPC characteristics");
        }
        if (x == -1 || y == -1) {
            x = createRandomValue(0, width);
            y = createRandomValue(0, height);
        }
        if (x > 500 || y > 500) {
            throw std::out_of_range("Unable to add this coordinates");
        }
        auto npc = NPCFactory::NpcCreator(type, name, x, y);
        if (npc) {
            AddNPC(std::move(npc));
        } else {
            throw std::runtime_error("Failed to spawn NPC of type: " + type);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error spawning NPC: " << e.what() << std::endl;
    }
}

int Arena::createRandomValue(int min, int max) {
    try {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    } catch (const std::exception& e) {
        std::cerr << "Error generating random value: " << e.what() << std::endl;
        return -1;
    }
}


void Arena::startMovementThread() {
    try {
        movementThread = std::thread([this]() { MovingFunction(); });
    } catch (const std::exception& e) {
        std::cerr << "Error starting movement thread: " << e.what() << std::endl;
        throw;
    }
}

void Arena::StartFightThread() {
    try {
        fightThread = std::thread([this]() { FightFunction(); });
    } catch (const std::exception& e) {
        std::cerr << "Error starting fight thread: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::shared_ptr<NPC>> Arena::GetAllNPCsCopy() const {
    std::vector<std::shared_ptr<NPC>> copies;
    for (const auto& npc : ListOfNPCs) {
        copies.push_back(npc->Clone());
    }
    return copies;
}

int Arena::getSizeObservers(){
    int res = 0;
    for (const auto &i: ListOfObservers){
        ++res;
    }
    return res;
}

void Arena::RemoveNPC(const std::string& npcName) {
    for (auto it = ListOfNPCs.begin(); it != ListOfNPCs.end(); ++it) {
        if ((*it)->getNpcName() == npcName) {
            ListOfNPCs.erase(it);
            break;
        }
    }
}