#pragma once
class Druids;
class Ork;
class Squirell;

class Visitor {
public:
    virtual void Visit(Druids &druid) = 0;
    virtual void Visit(Ork &ork) = 0;
    virtual void Visit(Squirell &squirell) = 0;
    virtual ~Visitor() = default;
};