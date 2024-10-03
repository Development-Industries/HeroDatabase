#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <string_view>
#include <locale>
#include <cctype>
#include <Tester.cpp>




HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}


// Merge Sort
void HeroesDB::mergeSort(int left, int right)
{
}
std::vector<Hero> HeroesDB::mergeSort(const std::vector<Hero>& m, SortBy sortBy) {
	if (m.size() <= 1) {
		return m;
	}
	
	std::vector<Hero> left, right;
	auto middle = m.begin() + m.size() / 2;

	left.assign(m.begin(), middle);
	right.assign(middle, m.end());

	left = mergeSort(left, sortBy);
	right = mergeSort(right, sortBy);

	return merge(left, right, sortBy);
}


// merge
std::vector<Hero> HeroesDB::merge(const std::vector<Hero>& left, const std::vector<Hero>& right, SortBy sortBy) {
	std::vector<Hero> result;
	auto i = left.begin();
	auto j = right.begin();

	while (i != left.end() && j != right.end()) {
		if (Hero::Compare(*i, *j, sortBy) <= 0) {
			result.push_back(*i);
			++i;
		}
		else {
			result.push_back(*j);
			++j;
		}
	}


	// Consume remaining elements
	while (i != left.end()) {
		result.push_back(*i);
		++i;
	}
	while (j != right.end()) {
		result.push_back(*j);
		++j;
	}

	return result;
}


//To Upper
std::string HeroesDB::toUpper(const std::string& str)
{
	std::string copy = str;
	std::transform(copy.begin(),
		copy.end(),
		copy.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return copy;
}

std::string HeroesDB::toUpper2(const std::string& str)
{
	std::string copy = str;
	for (auto& c : copy) c = toupper(c);
	return copy;
}


//Sort by Name Descending
void HeroesDB::SortByNameDescending()
{
	std::vector<Hero> sorted(_heroes); //clone the list

	size_t n = sorted.size();
	bool swapped;
	do
	{
		swapped = false;
		for (size_t i = 1; i <= n - 1; i++)
		{
			int compResult = _stricmp(sorted[i - 1].Name().c_str(), sorted[i].Name().c_str());
			//int compResult = toUpper(sorted[i - 1].Name()).compare(toUpper(sorted[i].Name()));
			if (compResult < 0)
			{
				swapped = true;
				std::swap(sorted[i - 1], sorted[i]);

				//int temp = vec[i - 1];
				//vec[i - 1] = vec[i];
				//vec[i] = temp;
			}
		}
		--n;
	} while (swapped);

	for (auto& hero : sorted)
	{
		std::cout << hero.Id() << ": " << hero.Name() << std::endl;
	}
	std::cout << std::endl;
}


//Sort By Attribute
void HeroesDB::SortByAttribute(SortBy sortBy)
{
	std::vector<Hero> sortedHeroes = mergeSort(_heroes, sortBy);

	for (const auto& hero : sortedHeroes) {
		std::string attributeValue = hero.GetSortByAttribute(sortBy); // Sort Heroes by Attribute and Value of Attribute
		std::cout << "Id: " << hero.Id() << " " << attributeValue << " " << hero.Name() << std::endl;
	}
}


//Find Hero
int HeroesDB::findHero(const std::string& searchTerm, int low, int high) {
	while (low <= high) {
		int mid = low + (high - low) / 2;
		std::string midName = _heroes[mid].Name(); 

		// Convert both searchTerm and midName to lower case for case-insensitive comparison
		std::string searchTermLower = searchTerm;
		std::string midNameLower = midName;
		std::transform(searchTermLower.begin(), searchTermLower.end(), searchTermLower.begin(), ::tolower);
		std::transform(midNameLower.begin(), midNameLower.end(), midNameLower.begin(), ::tolower);

		if (searchTermLower < midNameLower) {
			high = mid - 1;
		}
		else if (searchTermLower > midNameLower) {
			low = mid + 1;
		}
		else {
			return mid;  // Found searchTerm
		}
	}

	return -1;  // searchTerm not found
}


//Find Hero By Name(Wrapper work-around)
int HeroesDB::FindHeroByName(const std::string& heroName) {

	return findHero(heroName, 0, _heroes.size() - 1);
}
bool HeroesDB::charComparer(char c1, char c2)
{
	return std::tolower(c1, std::locale()) == std::tolower(c2, std::locale());
}
bool HeroesDB::isPrefix(const std::string& prefix, const std::string& word)
{
	return  (std::mismatch(prefix.begin(), prefix.end(),
		word.begin(), word.end(),
		charComparer)).first == prefix.end();
}


//Group Heroes
void HeroesDB::GroupHeroes() {
	for (const auto& hero : _heroes) {
		if (!hero.Name().empty()) {  // Check if the hero's name is not empty
			char firstLetter = std::tolower(hero.Name().front());  // Convert the first letter to lowercase

			// Check if the key exists in the map
			auto it = _groupedHeroes.find(firstLetter);
			if (it != _groupedHeroes.end()) {
				// Key exists, add hero to the existing vector
				it->second.push_back(hero);
			}
			else {
				// Key doesn't exist, create a new vector and add the hero
				_groupedHeroes[firstLetter] = std::vector<Hero>{ hero };
			}
		}
	}
	}


//Print Group Counts
void HeroesDB::PrintGroupCounts() {
	if (_groupedHeroes.empty()) {
		GroupHeroes(); 
	}

	for (const auto& group : _groupedHeroes) {
		std::cout << group.first << ": " << group.second.size() << std::endl;
	}
}


//Find Hero By Letter
void HeroesDB::FindHeroesByLetter(char letter) {
	if (_groupedHeroes.empty()) {
		GroupHeroes();  
	}

	letter = std::tolower(letter);  // Convert letter to lowercase for case-insensitive comparison

	auto it = _groupedHeroes.find(letter);
	if (it == _groupedHeroes.end()) {
		std::cout << "No heroes were found that start with the letter " << letter << "." << std::endl;
	}
	else {
		for (const auto& hero : it->second) {
			std::cout << "Id: " << hero.Id() << ", Name: " << hero.Name() << std::endl;
		}
	}
}


// Remove Hero
void HeroesDB::RemoveHero(const std::string& heroName) {
	if (_groupedHeroes.empty()) {
		GroupHeroes();  // Ensure heroes are grouped if not already done
	}

	char firstLetter = std::tolower(heroName[0]);  // Convert first letter to lowercase for case-insensitive comparison

	auto& heroesGroup = _groupedHeroes[firstLetter];
	auto it = std::find_if(heroesGroup.begin(), heroesGroup.end(), [&heroName](const Hero& hero) {
		// Assuming Hero::Name() returns the hero's name and you want case-insensitive comparison
		std::string lowerHeroName = hero.Name();
		std::transform(lowerHeroName.begin(), lowerHeroName.end(), lowerHeroName.begin(), ::tolower);
		return lowerHeroName == heroName;
		});

	if (it != heroesGroup.end()) {
		// Remove hero from the group vector
		heroesGroup.erase(it);

		// If the group is now empty, remove the key from the map
		if (heroesGroup.empty()) {
			_groupedHeroes.erase(firstLetter);
		}

		// Remove the hero from the main _heroes vector
		_heroes.erase(std::remove_if(_heroes.begin(), _heroes.end(), [&heroName](const Hero& hero) {
			std::string lowerHeroName = hero.Name();
			std::transform(lowerHeroName.begin(), lowerHeroName.end(), lowerHeroName.begin(), ::tolower);
			return lowerHeroName == heroName;
			}), _heroes.end());

		std::cout << "Hero " << heroName << " was removed." << std::endl;
	}
	else {
		std::cout << "Hero " << heroName << " was not found." << std::endl;
	}
}


//Deserialize
bool HeroesDB::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	if (!doc.IsArray())
		return false;


	_heroes.reserve(doc.Size());

	for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
	{
		rapidjson::Value& node = doc[i];
		Hero myHero(node);
		_heroes.push_back(myHero);
	}

	//JsonNodePrinter::PrintNode(doc, 4);


	return true;
}


//Serialize
bool HeroesDB::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	//writer->StartArray();

	//for (std::list<Product>::const_iterator it = _products.begin(); it != _products.end(); it++)
	//{
	//	(*it).Serialize(writer);
	//}
	//writer->EndArray();

	return true;
}