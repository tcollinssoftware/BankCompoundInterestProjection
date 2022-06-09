#include <iostream>
#include "account.h"

using namespace::std;

int main()
{
    //create new instance of class
    Account newAccount(0.0, 0.0, 0, 0);

    //call prompt for user input
    newAccount.inputPrompt();

    //call func for data without deposits
    newAccount.balanceAndInterestWODeposit();

    //call func for data with deposits
    newAccount.balanceAndInterestWDeposit();
}
