#include "fileIO.h"

// Writes user account info to the file accounts.txt
// @param a vector storing the user accounts
void writeToFile(vector<Account> a){
    ofstream fout;
    fout.open("accounts.txt", ios::trunc);

    if (fout.fail())
    {
        cout << "Error in file opening\n";
        exit(1);
    }

    // write each account as a new line in the pre-defined format
    for (int i=0; i<a.size(); i++){
        fout << "name:" << a[i].name << ";balance:" << a[i].balance << endl;
    }
    fout.close();
}

// Gets user account info from the file accounts.txt
// and stores them into accountList
// @return accountList vector storing the user accounts
vector<Account> getAccounts(){
    vector<Account> accountList;
    string name, bal;
    int pos, balance;
    ifstream fin;
    fin.open("accounts.txt");
    if (fin.fail()){
        cout << "Error in file opening\n";
        exit(1);
    }
    string line;

    // get account details by reading the delimiters
    while (getline(fin, line)){
        pos = line.find(";");
        name = line.substr(0, pos);
        bal = line.substr(pos+1, line.length());
        name = name.substr(name.find(":")+1, pos);
        balance = stoi(bal.substr(bal.find(":")+1, pos));
        Account c(name, balance);
        accountList.push_back(c);
    }
    return accountList;
}

// testing codes for fileIO component
/*
int main(){
    vector<Account> accountList;
    Account a("loridy", 100);
    accountList = getAccounts();
    Account b = accountList[0];
    cout << b.name <<"\n" << b.balance << endl;
}
*/