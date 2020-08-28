#pragma once

class Adress
{
    size_t i;
    size_t j;
public:	
    Adress(size_t _j, size_t _i) : i(_i), j(_j) {}
    size_t getZoneNumber() const { return j; }
    size_t getQuestionNumber() const { return i; }
};
