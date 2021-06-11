#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<stdio.h>
#include <deque>

std::vector<std::string> getInput()
{
    std::vector<std::string> input;
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        std::string tp;
        while (std::getline(newfile, tp)) {  //read data from file object and put it into std::string.
            input.push_back(tp);
        }
        newfile.close();   //close the file object.
    }
    return input;
}

int calculateScore(std::deque<int>& cards)
{
    int multiplier = cards.size();
    int score = 0;
    for (auto it = cards.begin(); it != cards.end(); it++)
    {
        score = score + (*it) * multiplier;
        multiplier--;
    }
    return score;
}

int main()
{
    std::deque<int> player_one_cards;
    std::deque<int> player_two_cards;
    const auto input = getInput();
    //add player one start cards
    auto it = input.begin();
    it++; //skip first line
    for (it; it != input.end(); it++)
    {
        try
        {
            player_one_cards.push_back(std::stoi(*it));
        }
        catch(...)
        {
            break;
        }
    }
    //add player two start cards
    it++; //skip break
    it++; //skip "player 2"
    for (it; it != input.end(); it++)
    {
        try
        {
            player_two_cards.push_back(std::stoi(*it));
        }
        catch (...)
        {
            break;
        }
    }
    while (player_one_cards.size() && player_two_cards.size())
    {
        const int p1 = player_one_cards.front();
        player_one_cards.pop_front();
        const int p2 = player_two_cards.front();
        player_two_cards.pop_front();
        if (p1 > p2)
        {
            player_one_cards.push_back(p1);
            player_one_cards.push_back(p2);
        }
        if(p1 < p2)
        {
            player_two_cards.push_back(p2);
            player_two_cards.push_back(p1);
        }
    }
    if (player_one_cards.size())
    {
        std::cout << "Player 1 score: " << calculateScore(player_one_cards);
    }
    else
    {
        std::cout << "Player 2 score: " << calculateScore(player_two_cards);
    }
    return 0;
}