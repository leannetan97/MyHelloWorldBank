#pragma once

class State {
public:
	State(){}

	virtual ~State(){}

	virtual std::string getStateName() = 0;
	virtual std::string withdraw(const double& amount) = 0;
	virtual std::string deposit(const double& amount) = 0;
};
