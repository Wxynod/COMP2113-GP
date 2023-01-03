#ifndef CHECK_CARD_H
#define CHECK_CARD_H

#include <iostream>
#include <vector>
#include <string>
#include "graphic.h"

using namespace std;

int getSum(vector<Card> deck);

bool checkPair(vector<Card> deck);

void finalizeRes(int playerVal, int bankerVal, vector<Card> playerCards, vector<Card> bankerCards, string &res);

string checkCard(vector<Card> playerCards, vector<Card> bankerCards);

#endif