#pragma once
#include "Adress.h"

#include <memory>
#include <ostream>
#include <string>
#include <vector>


class q_zone
{
    std::vector<std::string>  questions;
    int z_property;
private:
    size_t LoadZoneText(std::istream &is, int pro);

    void push_back(std::string q);
public:
    size_t LoadZoneBin( std::istream & is);
    //size_t q_number() const {return 1;}
    int difficult() const;
    // for binary input
    q_zone();
    // for text input
    q_zone(std::istream &is, int pro);

    size_t size() const;
    std::string operator[](size_t n) const;
    void SaveToBinFile( std::ostream &is) const;
    //friend std::ostream& operator <<(std::ostream& os, const q_zone & z);
};

class Settings;
class Database {
    std::vector<q_zone> zones;
public:
    // make private
    std::unique_ptr<Settings> set;
    size_t LoadFromBinFile( std::istream &is);
    size_t LoadFromTextFile( std::istream &is);
    void SaveToBinFile( std::ostream &os) const ;
    size_t size() const;// {return zones.size();}
    q_zone & operator[](size_t n)  { return zones[n];}
    q_zone  operator[]  (size_t n) const { return zones[n];}
};
