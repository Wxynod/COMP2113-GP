#include "graphic.h"
#include "generateCard.h"

// generate a new poker card using PRNG
// @return c Card generated
Card generateCard(){
    int random = rand();
    Card c;
    string suits[] = {"♠", "♥", "♣", "♦"};
    c.suits = suits[random % 4];
    
    // determine the color of the card
    if (random % 2 == 1) {
        c.color = "red";
    }
    else {
        c.color = "black";
    }
    
    // determine the face value and converted value of the card
    string faceVals[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int i = random % 13;
    c.faceVal = faceVals[i];
    if (i > 9) {
        c.val = 0;
    }
    else {
        c.val = i + 1;
    }

    return c;
}