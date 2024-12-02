#include "../include/squirell.h"

Squirell::Squirell(std::string name, int x, int y): NPC("Squirell", name, x, y){};
void Squirell::ToVisit(Visitor &visitor){
    visitor.Visit(*this);
}