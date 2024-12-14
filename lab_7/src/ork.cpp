#include "../include/ork.h"


Ork::Ork(std::string name, int x, int y): NPC("Ork", name, x, y){};
void Ork::ToVisit(Visitor &visitor){
    visitor.Visit(*this);
}