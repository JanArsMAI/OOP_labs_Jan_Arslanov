#include "include/BattleArena.h"
#include "include/ConsoleObserver.h"
#include "include/druids.h"
#include "include/extendedVisitor.h"
#include "include/ork.h"
#include "include/squirell.h"
#include "include/FileObserver.h"

int main()
{
    
    Arena arena;
    auto consoleLogger = std::make_shared<ConsoleObserver>();
    auto fileLogger = std::make_shared<FileObserver>();
    arena.AddObserver(consoleLogger);
    arena.AddObserver(fileLogger);
    arena.ToStartBattle();
}
        