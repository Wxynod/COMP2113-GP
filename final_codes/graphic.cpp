// Graphical output
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "graphic.h"
#include <ctime>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

// Print the cards out (a visualized version)
// The cards in the Card vector will be showed out visually
// The result will be like:
// _____
// |10 |
// | ♠ |
// | 10|
// @param vector storing the cards‾‾
void startboard(vector<Card> bankers_cards) {
    if (bankers_cards.size() == 0) {
        printf("No cards on dealer's side yet!\n");
    } else {
        for (int i = 0; i < bankers_cards.size(); i++) {
            cout << "_____  ";
        }
        cout << endl;
        for (int i = 0; i < bankers_cards.size(); i++) {
            cout << "|";
            if (bankers_cards[i].color == "red") {
                cout << "\033[31m" << bankers_cards[i].faceVal << "\033[0m";
            } else {
                cout << bankers_cards[i].faceVal;
            }
            if (bankers_cards[i].faceVal != "10") {cout << "  |  ";}
            else {cout << " |  ";}
        }
        cout << endl;
        for (int i = 0; i < bankers_cards.size(); i++) {
            cout << "| ";
            if (bankers_cards[i].color == "red") {
                cout << "\033[31m" << bankers_cards[i].suits << "\033[0m";
            } else {
                cout << bankers_cards[i].suits;
            }
            cout << " |  ";
        }
        cout << endl;
        for (int i = 0; i < bankers_cards.size(); i++) {
            if (bankers_cards[i].faceVal != "10") {cout << "|  ";}
            else {cout << "| ";}
            if (bankers_cards[i].color == "red") {
                cout << "\033[31m" << bankers_cards[i].faceVal << "\033[0m";
            } else {
                cout << bankers_cards[i].faceVal;
            }
            cout << "|  ";
        }
        cout << endl;
        for (int i = 0; i < bankers_cards.size(); i++) {
            cout << "‾‾‾‾‾  ";
        }
        cout << endl;
    }
}

// Print out the loss_per_cent table using the given data.
// @param loss_per_cent map storing the payout ratios
void loss_per_cent_table(map<string, string> loss_per_cent) {
    printf("The Table: \n");
    printf("____________________________________________\n");
    printf("|                                          |\n");
    printf("|                   \033[1;32mTIE 和\033[0m                 |\n");
    printf("|                   %-23s|\n", loss_per_cent["TIE"].c_str());
    printf("|                                          |\n");
    printf("|--------------------------+---------------|\n");
    printf("|                          |               |\n");
    printf("|        \033[1;31mBANKER 莊\033[0m         |  BANKER PAIR  |\n");
    printf("|        %-18s|  %-13s|\n", loss_per_cent["BANKER WIN"].c_str(), loss_per_cent["BANKER PAIR"].c_str());
    printf("|                          |               |\n");
    printf("|--------------------------+---------------|\n");
    printf("|                          |               |\n");
    printf("|        \033[1;34mPLAYER 閒\033[0m         |  PLAYER PAIR  |\n");
    printf("|        %-18s|  %-13s|\n", loss_per_cent["PLAYER WIN"].c_str(), loss_per_cent["PLAYER PAIR"].c_str());
    printf("|                          |               |\n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}

// Print out both the cards in the banker's and player's hands
// @param user vector storing the user's cards
// @param dealer vector storing the banker's cards
void printAll(vector<Card> user, vector<Card> dealer) {
    sleep(2);
    system("clear");
    cout << "User's Card(s): " << endl;
    startboard(user);
    cout << "Banker's Card(s): " << endl;
    startboard(dealer);
}

// Print out the win and loss table in this game
// @param vector storing the records of the game
void showTable(vector<Record> rcd) {
    system("clear");
    printf(">-->-->-->-->-{Dash·board}-<--<--<--<--<\n");
    printf("________________________________________\n");
    printf("|Win |");
    int a=0, b=0;
    for (auto i:rcd) {
        if (i.w){
            a += 1;
        } else {
            b += 1;
        }
    }
    for (int m=0; m<a; m++) {printf("●");}
    for (int m=0; m<(33-a); m++) {printf(" ");}
    printf("|\n");
    printf("|--------------------------------------|\n");
    printf("|Loss|");
    for (int m=0; m<b; m++) {printf("●");}
    for (int m=0; m<(33-b); m++) {printf(" ");}
    printf("|\n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}

// Print out the specific detail of the current record:
// Player's and Banker's cards
// Result and Net amount of winnings
void Record::showRecord() {
    system("clear");
    printf("%s: \n", game.c_str());
    cout << "Player's Card(s): " << endl;
    startboard(Player);
    cout << "Banker's Card(s): " << endl;
    startboard(Dealer);
    printf("The Result: %s\n", result.c_str());
    printf(">-->-->-->-->-{Bet·Records}-<--<--<--<--<\n");
    printf("|%7s|%7s|%7s|%7s|%7s|\n", "Ply Win", "Bnk Win", "Ply Pir", "Bnk Pir", "Tie  ");
    printf("|       |       |       |       |       |\n");
    printf("|%7s|%7s|%7s|%7s|%7s|\n", bet[0].c_str(), bet[1].c_str(), bet[3].c_str(), bet[4].c_str(), bet[2].c_str());
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}


// Check if the inputted string is an integer or not
// @param s the string to be checked
// @return true if it can be converted to an integer (since after checking we would have stoi() for further processing)
// @return false if it cannot be converted to an integer (i.e., cannot be passed to the stoi() function)
bool isInteger(string s) {
    for (int i = 0;i < s.size();i++) {
        if (s.at(i) > '9' || s.at(i) < '0')
            return false;
    }
    return true;
}

// Convert the inputted float number into a string
// @param inp the float to be converted
// @return str the resulting string
string floatTostring(float inp) {
    ostringstream oss;
    oss << inp;
    string str(oss.str());
    return str;
}

// Convert the inputted integer number into a string
// @param inp the integer to be converted
// @return str the resulting string
string intTostring(int inp) {
    ostringstream oss;
    oss << inp;
    string str(oss.str());
    return str;
}