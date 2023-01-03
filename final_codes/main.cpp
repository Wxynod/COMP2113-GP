#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <exception>
#include <ctime>

#include "graphic.h"
#include "fileIO.h"
#include "generateCard.h"
#include "check_card.h"

// check whether the environment is Windows or Linux, include corresponding package to implement the sleep function
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

// set timeout in the execution
// @param milliseconds duration for timeout
void sleepcp(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

// get current time of the user to customize greeting message
// @return greeting message component
string getTimeGreeting() {
    time_t curr_time;
	curr_time = time(NULL);
	tm *tm_local = localtime(&curr_time);
	int localHour = tm_local->tm_hour + 0;
	if(localHour >= 0 && localHour < 12) {
	    return "MORNING";
	}
	if(localHour >= 12 && localHour < 17) {
	    return "AFTERNOON";
	}
	return "EVENING";
}

// structure of a user in the playing state
struct user {
    // the cards that the user receives
    vector<Card> user_re;
    // bets placed by the user for the current round
    int betarray[5]; 
    // winnings for the current round
    int win=0;
};

// take bets from the user and check whether it is valid
// @param bet[] stores the bets
// @param index indicates what the user is placing bets on
void takeValidatedBet(int bet[], int index) {
    int res = 0;
    while(true) {
        cin >> res;
        if(res < 0) {
            cout << "Invalid bet, try again" << endl;
            continue;
        }
        else {
            bet[index] = res;
            break;
        }
    }
}

int main()
{
    string t;
    vector<Record> rcd;
    int gameCount = 0;
    system("clear");
    printf("To make sure the contents can display correctly on screen, please use full screen mode or make the window as big as possible.\n");
    printf("Input anything to continue (e.g., 'continue' then 'enter')...\n");
    getline(cin, t);
    system("clear");
    
    srand((unsigned)time(NULL));
    double odds[5] = {2, 1.95, 9, 12, 12}; 

    vector<Account> accountList;

    accountList = getAccounts();

    string name;
    int balance;
    cout << "===========================" << endl;
    cout << "TO START, PLEASE INPUT YOUR NAME: ";
    cin >> name; // shouln't contain space if using cin
    system("clear");
    
    Account* tempacct=NULL;

    // check whether an account associated with the username is already created
    bool checked=false;
    for (int i = 0; i < accountList.size(); i++)
    {
        if (name == accountList[i].name)
        {
            checked=true;
            tempacct=&accountList[i];
            balance = accountList[i].balance;
        }
    }
    
    if (checked) {
        // greeting message for existing user
        cout << "===========================" << endl;
        cout << "GOOD " << getTimeGreeting() << ", " << name << endl;
        cout << "===========================" << endl;
        cout << "WELCOME BACK!" << endl;
        cout << "===========================" << endl;
    } 
    else {
        // greeting message for new user
        tempacct=new Account();
        tempacct->name=name;
        tempacct->balance=10000;
        balance=10000;

        cout << "GOOD " << getTimeGreeting() << ", " << name << endl;
        cout << "===========================" << endl;
        cout << "WELCOME TO BACCARAT TABLE" << endl;
        cout << "===========================" << endl;
    }
    
    string checkresult;
    bool endg = true;
    char cont;

    // this loop will keep running as long as the user does not terminate this programme
    while (endg) {
        struct user User1;
        gameCount++;
        vector<Card> banker_re; 
        cout << "YOUR CURRENT BALANCE: $" << balance << endl;
        map<string, string> loss_per_cent;
        loss_per_cent["TIE"] = "8:1";
        loss_per_cent["BANKER WIN"] = "0.95:1";
        loss_per_cent["PLAYER WIN"] = "1:1";
        loss_per_cent["BANKER PAIR"] = "11:1";
        loss_per_cent["PLAYER PAIR"] = "11:1";
        string c1 = "";

        while (c1 != "Bet") {
            printf("Please input your choice: \n");
            printf("\t1. Start betting. (type 'Bet' then press [enter])\n");
            printf("\t2. Check out the records. (type 'Check' then press [enter])\n");
            cin >> c1;
            if (c1 == "Check") {
                string c2 = "";
                while (c2 != "Quit") {
                    showTable(rcd);
                    printf("Warning: This Record function only show records of current run and will be erased after exiting the program!\n");
                    printf("Please input your choice: \n");
                    printf("\t1. Type the game number that you would like to check. (type the number only and press [enter])\n");
                    printf("\t2. Exit the table. (type 'Quit' and press [enter])\n");
                    int length = rcd.size();
                    printf("Total Game Played since launch: %d\n", length);
                    cin >> c2;
                    string c3;
                    while (c2 != "Quit") {
                        int idx;
                        bool check=false;
                        if (isInteger(c2)) {
                            idx = stoi(c2);
                            if (idx > length || idx == 0) {
                                check=true;
                            } else {
                                rcd[idx-1].showRecord();
                                printf("Type 'Quit' and then press [enter] to quit.\n");
                                cin >> c3;
                                break;
                            }
                        } else {
                            check = true;
                        }
                        if (check) {
                            system("clear");
                            printf("Wrong Input Style or Game Does Not Exist!\n");
                            printf("Please input your choice: \n");
                            printf("\t1. Type the game number that you would like to check. (type the number only and press [enter])\n");
                            printf("\t2. Exit the table. (type 'Quit' and press [enter])\n");
                            printf("Total Game Played since launch: %d\n", length);
                            cin >> c2;
                        }
                    }
                }
            }
        }
    
        system("clear");
        Record tempRcd;
        loss_per_cent_table(loss_per_cent);
        int sum = balance+1;
        
        // take bets from the user
        while (sum > balance)
        {
            sum=0;
            cout << "PLACE YOUR BET" << endl;
            
            cout << "1. BET ON PLAYER: ";
            takeValidatedBet(User1.betarray,0);
            cout << "2. BET ON BANKER: ";
            takeValidatedBet(User1.betarray,1);
            cout << "3. BET ON TIE: ";
            takeValidatedBet(User1.betarray,2);
            cout << "4. BET ON PLAYER PAIR: ";
            takeValidatedBet(User1.betarray,3);
            cout << "5. BET ON BANKER PAIR: ";
            takeValidatedBet(User1.betarray,4);
            
            for (int i = 0; i < 5; i++) {
                sum += User1.betarray[i];
            }
            
            // check whether the total bets exceed user's total balance
            if(sum > balance) {
                cout << "Insufficient balance, try again" << endl;
                continue;
            }
        }
        
        for (int i=0; i<5; i++) {
            tempRcd.bet[i] = intTostring(User1.betarray[i]);
        }
        
        cout << "\033[1;32mBETS ACCEPTED\033[0m\n";

        // game initialization (two cards for player and banker)
        User1.user_re.push_back(generateCard());
        printAll(User1.user_re, banker_re);
        User1.user_re.push_back(generateCard());
        printAll(User1.user_re, banker_re);
        banker_re.push_back(generateCard());
        printAll(User1.user_re, banker_re);
        banker_re.push_back(generateCard());
        printAll(User1.user_re, banker_re);
        
        checkresult=checkCard(User1.user_re, banker_re);

        // follow-up logic: whether extra cards are needed
        if (checkresult.find('5') < checkresult.length() || checkresult.find('6') < checkresult.length()) {   
            if (checkresult.find('5') < checkresult.length()) {
                cout << "\033[1;34mExtra card for player\033[0m\n";
                User1.user_re.push_back(generateCard());
                printAll(User1.user_re, banker_re);
                
                checkresult = checkCard(User1.user_re, banker_re);
                if(checkresult.find('5') < checkresult.length() || checkresult.find('6') < checkresult.length()) {
                    cout << "\033[1;31mExtra card for banker\033[0m\n";
                    banker_re.push_back(generateCard());
                    printAll(User1.user_re, banker_re);
                }
            }
            else {
                cout << "\033[1;31mExtra card for banker\033[0m\n";
                banker_re.push_back(generateCard());
                printAll(User1.user_re, banker_re);
                
                checkresult = checkCard(User1.user_re, banker_re);
                if(checkresult.find('5') < checkresult.length() || checkresult.find('6') < checkresult.length()){
                    User1.user_re.push_back(generateCard());
                    printAll(User1.user_re, banker_re);
                }
            }
        }
        
        // get final game outcome
        checkresult=checkCard(User1.user_re, banker_re);
        
        int bankerVal = getSum(banker_re);
        int playerVal = getSum(User1.user_re);
        
        // print outcome in the screen
        sleepcp(800);
        cout << "PLAYER: " << playerVal << "    " << "閒" << playerVal << "點" << endl;
        cout << "BANKER: " << bankerVal << "    " << "莊" << bankerVal << "點" << endl;
        
        tempRcd.Player = User1.user_re;
        tempRcd.Dealer = banker_re;
        
        if(checkresult.find('0') < checkresult.length()) {
            cout << "\033[1;34mPLAYER WINS  閒贏\033[0m\n";
            tempRcd.result = "Player Wins";
        }
        else if(checkresult.find('1') < checkresult.length()) {
            cout << "\033[1;31mBANKER WINS  莊贏\033[0m\n";
            tempRcd.result = "Banker Wins";
        } 
        else if(checkresult.find('2') < checkresult.length()) {
            cout << "\033[1;32mTIE  和局\033[0m\n";
            tempRcd.result = "Tie";
        }
        
        // balance calculation
        for (int i = 0; i < 5; i++)
        {
            char res = '0'+i;
            if (checkresult.find(res) < checkresult.length()) {   
                User1.betarray[i] = odds[i] * User1.betarray[i];
            }
            else {
                if((i == 0 || i == 1) && checkresult.find('2') < checkresult.length()) {
                    User1.betarray[i] = 1 * User1.betarray[i];    
                }
                else {
                    User1.betarray[i] = 0;
                }
            }

            User1.win += User1.betarray[i];
        }

        cout << "TOTAL WIN: $" << User1.win << endl;

        tempRcd.result += (", Net Win: " + floatTostring(User1.win));
        tempRcd.game = ("Game " + intTostring(gameCount));
        if ((User1.win - sum) > 0) {
            tempRcd.w = true;
        } else {
            tempRcd.w = false;
        }

        balance=balance - sum + User1.win;
        cout << "YOUR CURRENT BALANCE IS: $" << balance << endl;
        cout << "PLAY AGAIN? Y/N " << endl;
        cin >> cont;
        rcd.push_back(tempRcd);
        system("clear");

        // save game state and terminate the game
        if (cont != 'Y') {
            endg = false;
            cout << "YOUR BALANCE IS SAVED WITH US." << endl;
            cout << "THANK YOU FOR PLAYING! HAVE A GOOD " << getTimeGreeting() << "." << endl;
        } 
    }
 
    tempacct->balance=balance;
    
    if (!checked){
        accountList.push_back(*tempacct);
        delete tempacct;
    }
    writeToFile(accountList);
    return 0;
}