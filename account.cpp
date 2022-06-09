#include "account.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace::std;

//declaration of Tuple structure to push into vector
struct Tuple {
	double balance;
	double interest;
};

//constructor to initialize default values per instanced class
Account::Account(double initialInvestment, double monthlyDeposit, int annualInterest, int numberYears)
{
	setInitialInvestment(initialInvestment);
	setMonthlyDeposit(monthlyDeposit);
	setAnnualInterest(annualInterest);
	setNumberYears(numberYears);
}

//pass argument to initial invesment amount per instance
void Account::setInitialInvestment(double initialInvestmentAmount)
{
	initialInvestment = initialInvestmentAmount;
}

//pass argument to monthly deposit amount per instance
void Account::setMonthlyDeposit(double monthlyDepositAmount)
{
	monthlyDeposit = monthlyDepositAmount;
}

//pass argument to interest percentage per instance
void Account::setAnnualInterest(int annualInterestPercentage)
{
	annualInterest = annualInterestPercentage;
}

//pass argument to number of years per instance
void Account::setNumberYears(int numberYearsAmount)
{
	numberYears = numberYearsAmount;
}

//func to prompt for user input to parse and handle data
void Account::inputPrompt()
{
	//declare temp vars for arugments to pass on instantiation of class
	double tempInvestAmount;
	double tempDepositAmount;
	int tempInterestPercent;
	int tempNumberYears;

	//title formatting for Data Input section of UI
	cout << "**************************************************************\n"
		<< "*************************" << " Data Input " << "*************************\n";

	//prompt for var inputs per
	cout << "Initial Investment Amount: $";
	cin >> tempInvestAmount;

	cout << "Monthly Deposit: $";
	cin >> tempDepositAmount;

	cout << "Annual Interest: %";
	cin >> tempInterestPercent;

	cout << "Number of Years: ";
	cin >> tempNumberYears;

	//call setters per instance
	setInitialInvestment(tempInvestAmount);
	setMonthlyDeposit(tempDepositAmount);
	setAnnualInterest(tempInterestPercent);
	setNumberYears(tempNumberYears);
}

//func to process data without monthly deposits
void Account::balanceAndInterestWODeposit()
{
	//declare vector of Tuple structs to iterate over for yearly projections
	vector <Tuple> yearlyProjection;
	//declare and initialize last year's amount as 0
	double lastYearAmount = 0;
	//declare vars for this month's amount and interest
	double thisMonthAmt;
	double thisMonthInt;
	//declare var for last month's amount, set as initial investment so it's only counted once
	//(when the account is opened)
	double lastMonthAmt = getInitialInvestment();
	//define interest percent as inputted int divided by 100 to yield multiplicable float
	double interestPerc = (getAnnualInterest() / 100.0);
	//declare var for this year's interest
	double thisYearInt;
	//declare and initialize last month's interest as 0
	double lastMonthInt = 0;

	//iterate from 1 to inputted years + 1
	for (auto i = 1; i < getNumberYears() + 1; i++) {
		//iterate from 0 to 12 (for months)
		for (auto j = 0; j < 12; j++) {
			//this month's interest equals last month's amount times (interest percent / 12)
			//make sure to not do int div, change any int in formula to float to prevent zeroes
			thisMonthInt = (lastMonthAmt) * ((getAnnualInterest() / 100.0) / 12.0);
			//set this month's amount to last month's plus this month's interest
			thisMonthAmt = lastMonthAmt + thisMonthInt;
			//set last month's amount to this month's amount before next cycle
			lastMonthAmt = thisMonthAmt;
			//set last month's interest to last month's interest plus this month's interest before next cycle
			lastMonthInt = lastMonthInt + thisMonthInt;

		}
		//round last month's interest by taking the floor of last month's interest times 100 plus .5 divided by 100
		lastMonthInt = floor(lastMonthInt * 100 + 0.5) / 100;

		//set yearly amount to this month's amount (outside of monthly iteration) to get yearly total
		double yearlyAmount = thisMonthAmt;

		//create new temporary Tuple
		Tuple tempTuple;
		//pass in the total amount and interest amount
		tempTuple.balance = yearlyAmount;
		tempTuple.interest = lastMonthInt;

		//reset last month's interest to 0 before next cycle
		lastMonthInt = 0;
		//push back the Tuple onto the vector
		yearlyProjection.push_back(tempTuple);
		//set last year's amount as this year's amount before next iteration cycle
		lastYearAmount = yearlyAmount;
	}

	//title formatting for table output of data
	//setting width per column
	cout << "==============================================================\n"
		<< "   " << "Balance and Interest Without Additional Monthly Deposits" << "   \n"
		<< "==============================================================\n"
		<< setw(7) << "Year|" << setw(26) << "Year End Balance|" << setw(27) << "Year End Earned Interest|\n"
		<< "--------------------------------------------------------------\n";

	//iterate from 0 to vector size outputting data per point
	for (auto i = 0; i < yearlyProjection.size(); i++) {
		//fix the formatting of the output, setting double precision to 2 decimal points
		cout << fixed;
		cout << std::setprecision(2);
		cout << setw(6) << i + 1
			<< setw(26) << yearlyProjection[i].balance 
			<< setw(26) << yearlyProjection[i].interest << "\n";
	}
}

void Account::balanceAndInterestWDeposit()
{
	//declare vector of Tuple structs to iterate over for yearly projections
	vector <Tuple> yearlyProjection;
	//declare and initialize last year's amount as 0
	double lastYearAmount = 0;
	//declare vars for this month's amount and interest
	double thisMonthAmt;
	double thisMonthInt;
	//declare var for last month's amount, set as initial investment so it's only counted once
	//(when the account is opened)
	double lastMonthAmt = getInitialInvestment();
	//define interest percent as inputted int divided by 100 to yield multiplicable float
	double interestPerc = (getAnnualInterest() / 100.0);
	//declare var for this year's interest
	double thisYearInt;
	//declare and initialize last month's interest as 0
	double lastMonthInt = 0;

	//iterate from 1 to inputted years + 1
	for (auto i = 1; i < getNumberYears() + 1; i++) {
		//iterate from 0 to 12 (for months)
		for (auto j = 0; j < 12; j++) {
			//this month's interest equals last month's amount times (interest percent / 12)
			//make sure to not do int div, change any int in formula to float to prevent zeroes
			//~~~in this formula, add monthly deposit amount to last month's amount~~~
			thisMonthInt = (lastMonthAmt + getMonthlyDeposit()) * ((getAnnualInterest() / 100.0) / 12.0);
			//set this month's amount to last month's plus this month's interest
			thisMonthAmt = lastMonthAmt + getMonthlyDeposit() + thisMonthInt;
			//set last month's amount to this month's amount before next cycle
			lastMonthAmt = thisMonthAmt;
			//set last month's interest to last month's interest plus this month's interest before next cycle
			lastMonthInt = lastMonthInt + thisMonthInt;

		}
		//round last month's interest by taking the floor of last month's interest times 100 plus .5 divided by 100
		lastMonthInt = floor(lastMonthInt * 100 + 0.5) / 100;

		//set yearly amount to this month's amount (outside of monthly iteration) to get yearly total
		double yearlyAmount = thisMonthAmt;

		//create new temporary Tuple
		Tuple tempTuple;
		//pass in the total amount and interest amount
		tempTuple.balance = yearlyAmount;
		tempTuple.interest = lastMonthInt;

		//reset last month's interest to 0 before next cycle
		lastMonthInt = 0;
		//push back the Tuple onto the vector
		yearlyProjection.push_back(tempTuple);
		//set last year's amount as this year's amount before next iteration cycle
		lastYearAmount = yearlyAmount;
	}

	//title formatting for table output of data
	//setting width per column
	cout << "==============================================================\n"
		<< "   " << "Balance and Interest Without Additional Monthly Deposits" << "   \n"
		<< "==============================================================\n"
		<< setw(7) << "Year|" << setw(26) << "Year End Balance|" << setw(27) << "Year End Earned Interest|\n"
		<< "--------------------------------------------------------------\n";

	//iterate from 0 to vector size outputting data per point
	for (auto i = 0; i < yearlyProjection.size(); i++) {
		//fix the formatting of the output, setting double precision to 2 decimal points
		cout << fixed;
		cout << std::setprecision(2);
		cout << setw(6) << i + 1
			<< setw(26) << yearlyProjection[i].balance
			<< setw(26) << yearlyProjection[i].interest << "\n";
	}
}
