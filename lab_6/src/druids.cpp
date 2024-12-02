#include "../include/druids.h"

Druids::Druids(std::string name, int x, int y): NPC("Druid", name, x, y) {}
void Druids::ToVisit(Visitor &visitor){
    visitor.Visit(*this);
}