#include <iostream>
#include <iomanip>
#include <exception>
#include "LockState.h"
#include "NormalState.h"
#include "ServiceFees.h"


double inputValidation(std::string& input) {
	try {
		return stod(input);
	}
	catch (std::exception& e) {
		return 0;
	}
}

double optionValidation(std::string& input) {
	try {
		return stoi(input);
	}
	catch (std::exception& e) {
		return 0;
	}
}

int main()
{
  std::cout << "========== Hello World Bank ==========" << std::endl;
	ServiceFeesInterface* fees = new ServiceFees();
	AccountInterface* account = new Account(fees);
	State* lockState = new LockState(account);
	State* normalState = new NormalState(account);

	std::cout << "Welcome to Hello World Bank:" << std::endl;
	while (true) {
		double amount;
		std::cout << "1. Deposit\n2. Withdraw\n3. View Balance\n4. Exit" << "\nChoose Option (1 - 4):" << std::endl;

		try {
			std::string input;
			int option;
			std::getline(std::cin, input);
			option = optionValidation(input);

			switch (option) {
			case 1:
				std::cout << "Please enter deposit amount:" << std::endl;
				std::getline(std::cin, input);
				amount = inputValidation(input);

				while (amount <= 0) {
					std::cout << "Deposit amount cannot be 0 or less than 0. Please enter the deposit amount." << std::endl;

					std::getline(std::cin, input);
					amount = inputValidation(input);
				}
				std::cout << account->deposit(amount) << std::endl;
				break;
			case 2:
				std::cout << "Please enter withdrawal amount:\n(Note: 1% of addition service charge will be charged if the withdrawal amount more than or equal to RM1000)" << std::endl;
				std::getline(std::cin, input);
				amount = inputValidation(input);
				while (amount <= 0) {
					std::cout << "Withdrawal amount cannot be 0 or less than 0. Please enter the withdrawal amount." << std::endl;
					std::getline(std::cin, input);
					amount = inputValidation(input);
				}
				std::cout << account->withdraw(amount) << std::endl;
				break;
			case 3:
				std::cout << "Account Balance: " << std::setprecision(2) << std::fixed << account->getBalance() << std::endl << std::endl;
				break;
			case 4:
				std::cout << "Thank you for choosing Hello World Bank. Have a nice day! Thank you. :)" << std::endl;
				break;
			default:
				std::cout << "Sorry, Invalid option. Please choose again." << std::endl;
				break;
			}
			if (option == 4) {
				break;
			}
		}
		catch (std::exception& e) {
			std::cout << "Opps, Invalid input, Please choose again." << std::endl;
		}
	}

	delete fees;
	delete lockState;
	delete normalState;
	delete account;
}