#include "check_card.h"

// calculate the total score of cards in a deck
// @param deck vector storing the cards in the deck
// @return total score of cards
int getSum(vector<Card> deck) {
    int sum = 0;
    for(int i=0;i<deck.size();i++) {
        sum += deck[i].val;
    }
    return sum % 10;
}

// check whether the first 2 cards in a deck is a pair
// @param deck vector storing the cards in the deck
// @return true if the first 2 cards is a pair
// @return false if the first 2 cards is not a pair
bool checkPair(vector<Card> deck) {
    if(deck[0].faceVal == deck[1].faceVal) {
        return true;
    }
    return false;
}

// give information when a hand should end and the result
// @param playerVal total score of player's cards 
// @param bankerVal total score of banker's cards
// @param playerCards vector storing player's cards 
// @param bankerCards vector storing banker's cards
// @param &res address of string to store the result
void finalizeRes(int playerVal, int bankerVal, vector<Card> playerCards, vector<Card> bankerCards, string &res) {
    if(playerVal > bankerVal) {
        res += "0";
    }
    else if(playerVal == bankerVal) {
        res += "2";
    }
    else {
        res += "1";
    }
    
    if(checkPair(playerCards)) {
        res += "3";
    }
    if(checkPair(bankerCards)) {
        res += "4";
    }
}

/*
Checks cards on the deck for results 
@param playerCards vector storing player's cards 
@param bankerCards vector storing banker's cards
@return res string to store the result
OP_CODES:
0: player wins
1: banker wins
2: draw
3: player pair
4: banker pair
5: player draw
6: banker draw
*/
string checkCard(vector<Card> playerCards, vector<Card> bankerCards) {
    string res = "";
    int playerVal = getSum(playerCards);
    int bankerVal = getSum(bankerCards);
    
    if(playerCards.size() == 2 && bankerCards.size() == 2) {
        // natural case
        if(playerVal >= 8 || bankerVal >= 8) {
            finalizeRes(playerVal, bankerVal, playerCards, bankerCards, res);
            return res;
        }
        
        // player draws a card
        if(playerVal <= 5) {
            res += "5";
            return res;
        }
        
        if(playerVal == 6 || playerVal == 7) {
            if(bankerVal <=5 ) {
                res += "6";
                return res;
            }
            else {
                finalizeRes(playerVal, bankerVal, playerCards, bankerCards, res);
                return res;
            }
            
        }
    } 
    
    if(playerCards.size() == 2 && bankerCards.size() == 3) {
        finalizeRes(playerVal, bankerVal, playerCards, bankerCards, res);
        return res;
    }
    
    if(playerCards.size() == 3 && bankerCards.size() == 2) {
        if(bankerVal <= 2) {
            res += "6";
            return res;
        }
        else if(bankerVal == 3 && playerCards[2].val != 8) {
            res += "6";
            return res;
        }
        else if(bankerVal == 4 && (playerCards[2].val >= 2 && playerCards[2].val <= 7)) {
            res += "6";
            return res;
        }
        else if(bankerVal == 5 && (playerCards[2].val >= 4 && playerCards[2].val <= 7)) {
            res += "6";
            return res;
        }
        else if(bankerVal == 6 && (playerCards[2].val >= 6 && playerCards[2].val <= 7)) {
            res += "6";
            return res;
        }
        else {
            finalizeRes(playerVal, bankerVal, playerCards, bankerCards, res);
            return res;
        }
    }
    
    if(playerCards.size() == 3 && bankerCards.size() == 3) {
        finalizeRes(playerVal, bankerVal, playerCards, bankerCards, res);
        return res;
    }

    return res;
}

// testing codes for check_card component
/*
int main() {
    vector<Card> playerDeck;
    vector<Card> bankerDeck;
    
    Card playerCard1("K",0);
    Card playerCard2("K",0);
    Card playerCard3("3",3);
    Card bankerCard1("10",0);
    Card bankerCard2("K",0);
    Card bankerCard3("6",6);
    
    playerDeck.push_back(playerCard1);
    playerDeck.push_back(playerCard2);
    playerDeck.push_back(playerCard3);
    
    bankerDeck.push_back(bankerCard1);
    bankerDeck.push_back(bankerCard2);
    bankerDeck.push_back(bankerCard3);
    
    string res = checkCard(playerDeck, bankerDeck);
    cout << res << endl;

}
*/