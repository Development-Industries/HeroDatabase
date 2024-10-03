#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Hero.h"
#include "enums.h"


class HeroesDB : public JSONBase
{
public:
    HeroesDB();


    //mergeSort
    void mergeSort(int left, int right);
    std::vector<Hero> merge(const std::vector<Hero>& left, const std::vector<Hero>& right, SortBy sortBy);
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }
    //SortByNameDescending
    void SortByNameDescending();
    //SortByAttrubute
    void SortByAttribute(SortBy sortBy);
    //findHero
    int findHero(const std::string& searchTerm, int low, int high);
    //FindHeroByName
    int FindHeroByName(const std::string& heroName);
    //GroupHeroes
    void GroupHeroes();  
    //PriuntGroupCounts
    void PrintGroupCounts();
    //FindHeroesByLetter
    void FindHeroesByLetter(char letter);
    //RemoveHero
    void RemoveHero(const std::string& heroName);


private:
    std::vector<Hero> _heroes;
    std::map<char, std::vector<Hero>> _groupedHeroes;

    std::vector<Hero> mergeSort(const std::vector<Hero>& m, SortBy sortBy);

    void merge(int left, int mid, int right);

    static std::string toUpper(const std::string& str);
    static std::string toUpper2(const std::string& str);
    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};
