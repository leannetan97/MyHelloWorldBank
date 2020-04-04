#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

// Interface
class AccountInterface {
public:
	AccountInterface() {}
	virtual ~AccountInterface() {}

	virtual std::string deposit(const double& amount) = 0;
	virtual std::string withdraw(const double& amount) = 0;
	virtual double getBalance() = 0;

};

class State {
//protected:
	/*Account* m_account;*/
public:
	State() //AccountInterface* account
		/*:m_account((Account*)account)*/
	{
	}

	virtual ~State()
	{
	}

	virtual std::string getStateName() = 0;
	virtual std::string withdraw(const double& amount) = 0;
	virtual std::string deposit(const double& amount) = 0;
};

class ServiceFeesInterface {

public:
	ServiceFeesInterface() {

	}

	virtual ~ServiceFeesInterface() {

	}

	// Methods
	virtual double serviceCharge(const double& amount) = 0;
};

// Subclass of AccountInterface
class Account : public AccountInterface {
private:
	ServiceFeesInterface* m_serviceFees;
	State*  m_lockState;
	State* m_normalState;
	State* m_currentState;
	double m_balance = 0;
public:
	Account(ServiceFeesInterface* serviceFees)
		:m_serviceFees(serviceFees), m_lockState(nullptr), m_normalState(nullptr), m_currentState(m_lockState), m_balance(0)
	{
		
	}

	~Account() {
		
	}

	// Methods
	std::string deposit(const double& amount) override {
		std::cout << "DEPOSIT" << std::endl;
		return (*m_currentState).deposit(amount);
	}

	std::string withdraw(const double& amount) override {
		std::cout << "WITHDRAW" << std::endl;
		//or
		//return (*m_currentState).withdraw(amount);
		return m_currentState->withdraw(amount);
	}

	double getBalance() override {
		return m_balance;
	}

	void setState(State* state) {
		m_currentState = state; 
	}

	void setUpLockState(State* lockState) {
		m_lockState = lockState;
		m_currentState = m_lockState;
	}

	void setUpNormalState(State* normalState) {
		m_normalState = normalState;
	}

	void increaseBalance(const double& newBalance) {
		m_balance += newBalance;
	}

	void deductBalance(const double& newBalance) {
		m_balance -= newBalance;
	}

	State* getNormalState() {
		return m_normalState;
	}

	State* getLockState() {
		return m_lockState;
	}

	State* getState() {
		return m_currentState;
	}

	double getServiceCharge(const double& amount) {
		return m_serviceFees->serviceCharge(amount);
	}
};

// Subclass of State
class NormalState : public State {
public:
private:
	Account* m_account;
public:
	NormalState(AccountInterface* account)
		:m_account((Account*)account)
	{
		m_account->setUpNormalState(this);
	}

	// Methods
	std::string getStateName() override {
		return "Normal State";
	}


	std::string withdraw(const double& amount) override {
		double charges = (m_account)->getServiceCharge(amount);
		double total = charges + amount;
		if (amount >= 1000 && total <= (m_account)->getBalance()) {
			(m_account)->deductBalance(total);
			updateState();
			return std::string("RM") + std::to_string(amount) + std::string(" with additional charges RM") + std::to_string(charges) + std::string(" is deduct from the account\nCurrent Account State:") + ((m_account)->getState())->getStateName() + "\nAccount Balance: RM" + std::to_string(m_account->getBalance()) + std::string("\n");
		}
		else if (amount < 1000 && amount <= (m_account)->getBalance()) {
			(m_account)->deductBalance(amount);
			updateState();
			return std::string("RM") + std::to_string(amount) + std::string(" is deduct from the account\nCurrent Account State: ") + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance: RM") + std::to_string((m_account)->getBalance()) + std::string("\n");
		}
		else {
			return "Withdraw amount is more than account balance.\nWithdraw transaction is denied.";
		}
	}

	std::string deposit(const double& amount) override {
		(m_account)->increaseBalance(amount);
		return std::string("RM") + std::to_string(amount) + std::string(" is added to the account\nCurrent Account State: ") + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance: RM") + std::to_string(m_account->getBalance()) + std::string("\n");
	}

	void updateState() {
		if (m_account->getBalance() < 50) {
			m_account->setState(m_account->getLockState());
		}
	}

};

class LockState : public State {
private:
	Account* m_account;
public:
	LockState(AccountInterface* account)
		:m_account((Account*)account)
	{
		m_account->setUpLockState(this);
	}

	// Methods
	std::string getStateName() override {
		return "Lock State";
	}


	std::string withdraw(const double& amount) override {
		return "Sorry, Unable to perform withdrawal. Account should have minimum RM50 in order to perform withdrawal.\nCurrent Account State: " + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance RM:") + std::to_string(m_account->getBalance()) + std::string("\n");
	}

	std::string deposit(const double& amount) override {
		(m_account)->increaseBalance(amount);
		if ((m_account)->getBalance() >= 50) {
			(m_account)->setState(m_account->getNormalState());
		}
		return std::string("RM") + std::to_string(amount) + std::string(" is added to the account\nCurrent Account State: ") + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance: RM") + std::to_string((m_account)->getBalance()) + std::string("\n");
	}


};

// Subclass of ServiceFeesInterface
class ServiceFees : public ServiceFeesInterface {

public:
	double serviceCharge(const double& amount) override {
		double charge = amount * 0.01;
		return charge;
	}

};

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
	std::cout << "========== Hello World Bank (Single) ==========" << std::endl;

	ServiceFeesInterface* fees = new ServiceFees();
	AccountInterface* account = new Account(fees);
	State* lockState = new LockState(account);
	State* normalState = new NormalState(account);
	
	std::cout << "Welcome to Hello World Bank:" << std::endl;
	while (true) {
		double amount;
		std::cout << "1. Deposit\n2. Withdraw\n3. View Balance\n4. Exit" << "\nChoose Option (1 - 4):" << std::endl;

		try{
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