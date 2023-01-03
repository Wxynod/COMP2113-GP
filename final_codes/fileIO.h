#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

struct Account{
    string name;
    int balance;
    Account(){
        name = "";
        balance = 0;
    }
    Account(string _name, int _balance){
        name = _name;
        balance = _balance;
    }
};

void writeToFile(vector<Account> a);

vector<Account> getAccounts();

#endif