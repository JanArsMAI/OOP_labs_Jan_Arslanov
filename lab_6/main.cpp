#include "include/BattleArena.h"
#include "include/ConsoleObserver.h"
#include "include/druids.h"
#include "include/extendedVisitor.h"
#include "include/ork.h"
#include "include/squirell.h"
#include "include/FileObserver.h"

void ShowActions(){
    std::cout << "\n-Actions of Arena\n"
              << "1. Add NPC\n"
              << "2. Print NPCs\n"
              << "3. Start battle\n"
              << "4. Save NPCs to file\n"
              << "5. Load NPCs from file\n"
              << "-1. Exit\n"
              << "Choose an option: ";
}
bool valid_coord(int x, int y) {
    return (x < 0 || x > 500 || y < 0 || y > 500);
}

int main()
{
    
    Arena arena(500, 500);
    auto consoleLogger = std::make_shared<ConsoleObserver>();
    auto fileLogger = std::make_shared<FileObserver>();
    arena.AddObserver(consoleLogger);
    arena.AddObserver(fileLogger);
    int choice;
    while(choice != -1){
        ShowActions();
        std::cin >> choice;
        switch (choice)
        {
        case 1: {
            std::string name, type;
            int x, y;
            std::cout << "Enter NPC type (Ork, Druid, Squirell): ";
            std::cin >> type;
            std::cout << "Enter NPC name: ";
            std::cin >> name;
            std::cout << "Enter X and Y coordinates (0-500): ";
            std::cin >> x >> y;
            if (valid_coord(x, y)) {
                std::cout << "Invalid coordinates. Must be between 0 and 500." << std::endl;
                break;
            }
            arena.SpawnNPC(type, name, x, y);
            std::cout << "NPC added successfully." << std::endl;
            break;
        }
        case 2:
            std::cout << "NPCs in the arena:" << std::endl;
            arena.ShowAllNPCs();
            break;
        case 3:{
            int range;
            std::cout << "Enter battle range: ";
            std::cin >> range;
            arena.ToStartBattle(range);
            std::cout << "Battle is over." << std::endl;
            break;
        }
        case 4:{
            std::string filename;
            std::cout << "Enter file name to save NPCs: ";
            std::cin >> filename;
            arena.SaveToFile(filename);
            std::cout << "NPCs saved to file.\n";
            break;
        }
        case 5:{
            std::string filename;
            std::cout << "Enter file name for loading NPCs: ";
            std::cin >> filename;
            arena.LoadNpcFromFile(filename);
            std::cout << "NPCs loaded from file.\n";
            break;
        }
        case -1:
            std::cout << "Exiting from the programm...\n";
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
    return 0;
}