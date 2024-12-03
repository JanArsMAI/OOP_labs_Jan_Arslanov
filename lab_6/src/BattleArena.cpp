#include "../include/BattleArena.h"
#include <random>
#include <stdexcept>
#include <iostream>

Arena::Arena(int width, int height) : width(width), height(height) {}
Arena::Arena(int height) : width(height), height(height) {}
void Arena::AddNPC(std::unique_ptr<NPC> npc){
    ListOfNPCs.push_back(std::move(npc));
}

void Arena::AddObserver(std::shared_ptr<Observer> observer)
{
    ListOfObservers.push_back(observer);
}

void Arena::ToStartBattle(int range)
{
    if (range > height || range > width){
        throw std::out_of_range("range is more than size of arena");
    }
    std::cout << "Starting battle with range: " << range << std::endl;

    for (auto &observer : ListOfObservers)
    {
        observer->EventUpdater("The battle has started with range: " + std::to_string(range));
    }

    ExtendedVisitor extendedVisitor(range, ListOfNPCs, ListOfObservers);
    std::vector<NPC *> npcsToVisit;
    for (auto &npc : ListOfNPCs)
    {
        npcsToVisit.push_back(npc.get());
    }

    for (auto it = npcsToVisit.begin(); it != npcsToVisit.end();)
    {
        NPC *npc = *it;
        auto found = std::find_if(
            ListOfNPCs.begin(), ListOfNPCs.end(),
            [npc](const std::unique_ptr<NPC> &original)
            { return original.get() == npc; });
        if (found != ListOfNPCs.end())
        {
            npc->ToVisit(extendedVisitor);
        }
        ++it;
    }

    if (ListOfNPCs.empty())
    {
        for (auto &observer : ListOfObservers)
        {
            observer->EventUpdater("All NPCs have been eliminated. The battle is over.");
        }
    }
    else
    {
        std::string survivors = "The battle is over. Surviving NPCs: ";
        for (const auto &npc : ListOfNPCs)
        {
            survivors += npc->getNpcName() + " ";
        }
        for (auto &observer : ListOfObservers)
        {
            observer->EventUpdater(survivors);
        }
    }
}
bool Arena::CheckForDuplicate(std::string name, int x, int y){
    for (auto it = ListOfNPCs.begin(); it != ListOfNPCs.end(); ++it){
        if ((*it).get()->getNpcName() == name){
            return false;
        }
        std::pair<int, int> coord = (*it).get()->getCoordinates();
        int coor_x = coord.first;
        int coor_y = coord.second;
        if (x == coor_x && y == coor_y){
            return false;
        }
    }
    return true;
}
void Arena::SpawnNPC(const std::string &type, const std::string &name, int x, int y)
{
    if (!CheckForDuplicate(name, x, y)){
        throw std::invalid_argument("Wrong NPC characteristics");
    }
    if (x == -1 || y == -1){
        x = createRandomValue(0, width);
        y = createRandomValue(0, height);
    }
    if (x > 500 || y > 500){
        throw std::out_of_range("Unable to add this coordinates");
    }
    auto npc = NPCFactory::NpcCreator(type, name, x, y);
    if (npc){
        AddNPC(std::move(npc));
    }
    else{
        std::cerr << "Failed to spawn NPC of type: " << type << "\n";
    }
}

int Arena::createRandomValue(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void Arena::ShowAllNPCs(){
    if (ListOfNPCs.size() == 0){
        std::cout << "No NPCs are on the Arena now" << std::endl;
        return;
    }
    for (const auto &npc: ListOfNPCs){
        std::cout << "Name of NPC: " + npc.get()->getNpcName() << std::endl;
        std::cout << "Type of NPC: " + npc.get()->getNpcType() << std::endl;
        std::pair<int, int> coord = npc.get()->getCoordinates();
        int x = coord.first;
        int y = coord.second;
        std::cout << "NPC coordinates: " <<  x << ", " << y << std::endl;
        std::cout << "...................................." <<std::endl;
    }
}

void Arena::LoadNpcFromFile(std::string &filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Unable to open file for loading NPCs");
    }
    std::string line;
    while (std::getline(file, line)){
        std::istringstream stream(line);
        std::string name, type;
        int x, y;
        if (!(stream >> name >> x >> y >> type)){
            std::cerr << "Skipping invalid line: " << line << std::endl;
            continue;
        }
        auto npc = NPCFactory::NpcCreator(type, name, x, y);
        if (!npc){
            std::cerr << "Unable type of NPC: " << type << std::endl;
        }
        else{
            AddNPC(std::move(npc));
        }
    }
    file.close();
}

void Arena::SaveToFile(std::string &filename){
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file for saving NPCs");
    }
    for (const auto &npc : ListOfNPCs)
    {
        std::pair<int, int> coord = npc.get()->getCoordinates();
        int x = coord.first;
        int y = coord.second;
        file << npc->getNpcName() << " " << x << " " << y << " " << npc->getNpcType() << "\n";
    }
    file.close();
}

void Arena::RemoveNPC(const std::string& npcName) {
    for (auto it = ListOfNPCs.begin(); it != ListOfNPCs.end(); ++it) {
        if ((*it)->getNpcName() == npcName) {
            ListOfNPCs.erase(it);
            break;
        }
    }
}

std::vector<std::unique_ptr<NPC>> Arena::GetAllNPCsCopy() const {
    std::vector<std::unique_ptr<NPC>> copies;
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