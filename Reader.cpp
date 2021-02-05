//
// Created by Selcuk on 13.11.2020.
//

#include "Reader.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Deck.h"
using namespace std;


Reader::Reader() {}
struct Command{
    string command_name;
    string cards[7][52];
};
struct Command Reader::changer(string address,int read_line) {

    struct Command temp_command;
    int x=51;
    ifstream file(address);
    string str;

    if (address=="deck.txt"){
        while (std::getline(file, str)) {
            temp_command.cards[0][x]=str;
            x-=1;
        }
    }
    else if (address=="commands.txt"){
        for (int i = 0; i <=read_line ; i++) {
            std::getline(file, str);
        }
        temp_command.command_name=str;
    }
    return temp_command;
}
