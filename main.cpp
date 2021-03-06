#include <iostream>
#include "bank.h"
#include <vector>
//#include "bankAccount.h"
#include <cstdlib>
#include <fstream>
using namespace std;

/*long getBankAccountNumber() {
    return rand() % 100000000;
}*/
//if we do random number generator, we'll have to check for repeats, so instead lets just increment consecutively up from 100000000
void displayMessage(){
		string s = "Hello, and welcome to Rui's Bank. Press any key to Continue:\n[1] Open New Bank Account\n[2] Close Your Bank Account\n[3] Deposit Money\n[4] Withdraw Money\n[5] Change Your Password\n[6] Transfer Money to Another Account\n[7] Change Account Ownership\n[8] Check Balance\nPress any other key to exit.\n";
		cout << s;
}
void loadData(Bank* myBankPtr){
    ifstream file ("database.log");
    string first_name, last_name, DOB, password, number, balance;
    int i;
    file >> first_name >> last_name >> DOB >> password >> number >> balance;

    while(first_name != "stop") {
        myBankPtr->openBankAccount(first_name + " " + last_name, DOB, password, stol(number));
        myBankPtr->deposit(stol(number), stod(balance));
        file >> first_name >> last_name >> DOB >> password >> number >> balance;
    }

    file.close();
}

void saveData(Bank* myBankPtr){
    ofstream file ("database.log");
    for (int i = 0; i < myBankPtr->getAccounts().size(); i++) {
        file << myBankPtr->getAccounts()[i].get_owner() << endl;
        file << myBankPtr->getAccounts()[i].get_owner_DOB() << endl;
        file << myBankPtr->getAccounts()[i].get_password() << endl;
        file << myBankPtr->getAccounts()[i].getNumber() << endl;
        file << myBankPtr->getAccounts()[i].get_balance() << endl;
    }
    file << "stop" << endl;
    file.close();
}

int main()
{
    Bank* myBankPtr = new Bank("Nameless Bank",100000000000, true);
    loadData(myBankPtr);
    long account_number = 10000000 + myBankPtr->getAccounts().size();
    bool goAgain = true;
    do{
            displayMessage();
            int choice;
            cin >> choice;
            switch(choice){
            //it might make it a bit easier for input if we just asked for the account number rather than name, DOB, and password
            //just something to consider
            case 1: { //open account
                cout << "Enter Your First Name: ";
				string firstName;
				cin >> firstName;
				cout << "Enter Your Last Name: ";
				string lastName;
				cin >> lastName;
				/*cout << "Enter Your Birth Year:";
				int year;
				cin >> year;
                */
				string dob;
				cout << "Enter your date of birth (mm-dd-yyyy): ";
				cin >> dob;
				cout << "Choose a Password: ";
				string password;
				cin >> password;
				//long acctNum = getBankAccountNumber();
				//cout << acctNum << endl;
				myBankPtr->openBankAccount(firstName + " " + lastName,dob,password,++account_number);
				cout << "Your account number is: " << account_number << endl;
				//generate bank account number later
				//cout << myBankPtr->getAccounts().size() << endl;
				break;
            }
            case 2: { //close account
                long account_number;
                cout << "Enter your account number: ";
                cin >> account_number;
                BankAccount* acctToDeletePtr = myBankPtr->getPtrByNumber(account_number);
                cout << "Enter Your First Name: ";
				string firstName;
				cin >> firstName;
				cout << "Enter Your Last Name: ";
				string lastName;
				cin >> lastName;
				/*cout << "Enter Your Birth Year:";
				int year;
				cin >> year;
                */
				string dob;
				cout << "Enter your date of birth (mm-dd-yyyy): ";
				cin >> dob;
				bool hasPassword = false;
				string password;
				string correctName = acctToDeletePtr->get_owner();
				string correctPassword = acctToDeletePtr->get_password();
				string correctDOB = acctToDeletePtr->get_owner_DOB();
				if(correctName != (firstName + " " + lastName) && correctDOB != dob) {
                    cout << "You have entered incorrect information. Try again later." << endl;
                    break;
				}
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(correctPassword == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                //long acct_num = myBankPtr->findByNameAndDOB(firstName + " " + lastName,dob).getNumber();
				myBankPtr->closeBankAccount(firstName + " " + lastName,dob,password,account_number);
                //goAgain = false;
                cout << "Account Closed" << endl;
                //cout << myBankPtr->getAccounts().size() << endl;
                break;
            }
            case 3: { //deposit money
                cout << "Enter your account number:";
                cin >> account_number;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNumber(account_number).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                double amount;
                cout << "Enter an amount to deposit: ";
                cin >> amount;
				myBankPtr->deposit(account_number,amount);
                cout << "Thank you for the transaction. Your new balance is: " << myBankPtr->findByNumber(account_number).get_balance() << endl;
                break;
            }
            case 4: { //withdraw money
                cout << "Enter your account number:";
                cin >> account_number;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNumber(account_number).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                double amount;
                cout << "Enter an amount to withdraw: ";
                cin >> amount;
				myBankPtr->withdraw(account_number,password,amount);
                cout << "Thank you for the transaction. Your new balance is: " << myBankPtr->findByNumber(account_number).get_balance() << endl;
                break;
            }
            case 5: { //change password
                cout << "Enter Your First Name: ";
				string firstName;
				cin >> firstName;
				cout << "Enter Your Last Name: ";
				string lastName;
				cin >> lastName;
				/*cout << "Enter Your Birth Year:";
				int year;
				cin >> year;
                */
				string dob;
				cout << "Enter your date of birth (mm-dd-yyyy): ";
				cin >> dob;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNameAndDOB(firstName + " " + lastName,dob).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                string newPass;
                cout << "Enter your new password: ";
                cin >> newPass;
                myBankPtr->getPtrByNameAndDOB(firstName + " " + lastName,dob)->change_password(newPass);
                cout << "Password changed successfully." << endl;
                break;
            }
            case 6: { //transfer money to another account
                cout << "Enter Your First Name: ";
				string firstName;
				cin >> firstName;
				cout << "Enter Your Last Name: ";
				string lastName;
				cin >> lastName;
				/*cout << "Enter Your Birth Year:";
				int year;
				cin >> year;
                */
				string dob;
				cout << "Enter your date of birth (mm-dd-yyyy): ";
				cin >> dob;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNameAndDOB(firstName + " " + lastName,dob).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }

                cout << "Enter in the number of the account to which you would like to transfer funds: " << endl;
                long acctNum;
                cin >> acctNum;
                double amount;
                cout << "Enter how much money you would like to transfer: ";
                cin >> amount;
                myBankPtr->getPtrByNameAndDOB(firstName + " " + lastName,dob)->withdraw(amount);
                myBankPtr->getPtrByNumber(acctNum)->deposit(amount);
                break;
            }
            case 7: { //change account ownership
                //I'm implementing this by just changing the name of the person who holds the account
                //this is what it's supposed to be, right?
                cout << "Enter Your First Name: ";
				string firstName;
				cin >> firstName;
				cout << "Enter Your Last Name: ";
				string lastName;
				cin >> lastName;
				/*cout << "Enter Your Birth Year:";
				int year;
				cin >> year;
                */
				string dob;
				cout << "Enter your date of birth (mm-dd-yyyy): ";
				cin >> dob;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNameAndDOB(firstName + " " + lastName,dob).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                string newFirstName;
                string newLastName;
                cout << "Enter the new owner's first name: ";
                cin >> newFirstName;
                cout << "Enter the new owner's last name: ";
                cin >> newLastName;
                myBankPtr->getPtrByNameAndDOB(firstName + " " + lastName,dob)->change_owner(newFirstName + " " + newLastName);
                break;
            }
            case 8: {
                cout << "Enter your account number:";
                cin >> account_number;
				bool hasPassword = false;
				string password;
				for(int i = 0; i < 3; i++) {
                    cout << "Enter your Password: ";
                    cin >> password;
                    if(myBankPtr->findByNumber(account_number).get_password() == password) {
                        hasPassword = true;
                        break;
                    } else if(i < 2) {
                        cout << "You have entered your password incorrectly." << endl;
                        cout << "You have ";
                        cout << 2 - i;
                        cout << " attempts left before you must try again later." << endl;
                    }
                }
                if(!hasPassword) {
                    cout << "You have run out of attempts to enter in your password. Try again later." << endl;
                    break;
                }
                cout << "Your balance is: " << myBankPtr->findByNumber(account_number).get_balance() << endl;
                break;
            }
            default: {
                goAgain = false;
                break;
            }
        }
    }while(goAgain);
    saveData(myBankPtr)
    //cout << myBankPtr->getBalance() << endl;
    //myBankPtr->openBankAccount("Michael Feffer","12-18-1995","#sol33t",1234567890);
    //cout << ((myBankPtr->getAccounts())[0]).get_owner() << endl;
    //cout << "Hello world!" << endl;
    delete(myBankPtr);
    return 0;
}
