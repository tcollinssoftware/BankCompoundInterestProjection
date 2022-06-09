#pragma once
class Account
{
	//declare private vars per
	private:
		double initialInvestment;
		double monthlyDeposit;
		int annualInterest;
		int numberYears;

	//public methods
	public:
		//constructor
		Account(double initialInvestment, double monthlyDeposit, int annualInterest, int numberYears);

		//declarations of setters per
		void setInitialInvestment(double initialInvestmentAmount);
		void setMonthlyDeposit(double monthlyDepositAmount);
		void setAnnualInterest(int annualInterestPercentage);
		void setNumberYears(int numberYearsAmount);
		
		//primary non-get/set functions
		void inputPrompt();
		void balanceAndInterestWODeposit();
		void balanceAndInterestWDeposit();

		//declarations of getters per
		double getInitialInvestment() { return initialInvestment; }
		double getMonthlyDeposit() { return monthlyDeposit; }
		int getAnnualInterest() { return annualInterest; }
		int getNumberYears() { return numberYears; }
};

