#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include <locale>
#include "Tester.h"

int main()
{
    Tester v2Test;
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Sort by Name (descending)", "2. Sort By", "3. Find Hero (Binary Search)", "4. Print Group Counts", "5. Find All Heroes by first letter", "6. Remove Hero", "7. Exit" };
    std::vector<std::string> sortByOptions { "1. Intelligence", "2. Strength", "3. Speed", "4. Durability", "5. Power", "6. Combat" };

    do
    {
        Console::Clear();
        menuSelection = Input::GetMenuSelection(menuOptions);
        Console::Clear();

        switch (menuSelection)
        {


        case 1:
        {
            heroDB.SortByNameDescending();
            break;
        }


        case 2:
        {int sortBySelection = Input::GetMenuSelection(sortByOptions, "Sort by? ");
        SortBy sortByChoice = (SortBy)sortBySelection;
           heroDB.SortByAttribute(sortByChoice);
            break;
        }


        case 3:
        {
            std::cout << "Enter the name of the hero to find: ";
            std::string heroName = Input::GetString("Enter hero name: "); // 
            int heroIndex = heroDB.FindHeroByName(heroName);  // Wrapper Added. Wasn't sure if allowed, but couldnt find how to directly push due to encapsulation1 

            if (heroIndex != -1) {
                std::cout << "Hero found at index: " << heroIndex << std::endl;
            }
            else {
                std::cout << "Hero not found." << std::endl;
            }
            break;
        }


        case 4:
        {heroDB.PrintGroupCounts();  //Call PrintGroupCounts to print grouped heroes counts

            break;
        }


        case 5:
        {std::cout << "Enter the first letter of the hero names to find: ";
        std::string input = Input::GetString("Search By Letter: ");
        if (!input.empty()) {
            char firstLetter = input[0];  // Use the first character of the input
            heroDB.FindHeroesByLetter(firstLetter);
        }
        else {
            std::cout << "No letter was entered." << std::endl;
        }

            break;
        }


        case 6:
        {   std::string heroName = Input::GetString("Enter the name of the hero to remove: ");  
       heroDB.RemoveHero(heroName);
        break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());
}