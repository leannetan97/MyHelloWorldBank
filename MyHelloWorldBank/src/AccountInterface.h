#pragma once

class AccountInterface {
public:
	AccountInterface() {}
	virtual ~AccountInterface() {}

	virtual std::string deposit(const double& amount) = 0;
	virtual std::string withdraw(const double& amount) = 0;
	virtual double getBalance() = 0;
};