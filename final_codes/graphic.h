// graphic.h
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Card
{
    string suits;
    string color;
    string faceVal;
    int val;
};

struct Record {
    vector<Card> Dealer;
    vector<Card> Player;
    string game;
    string result;
    string bet[5];
    bool w;
    
    void showRecord();
};

void startboard(vector<Card> bankers_cards);

void loss_per_cent_table(map<string, string> loss_per_cent);

void printAll(vector<Card> user, vector<Card> dealer);

void showTable(vector<Record> rcd);

bool isInteger(string s);

string floatTostring(float inp);

string intTostring(int inp);

#endif