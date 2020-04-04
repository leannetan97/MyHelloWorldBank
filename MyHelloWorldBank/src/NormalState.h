#pragma once

#include <string>
#include "State.h"
#include "AccountInterface.h"
#include "Account.h"

class NormalState : public State {
private:
	Account* m_account;
public:
	NormalState(AccountInterface* account);

	// Methods
	std::string getStateName() override;


	std::string withdraw(const double& amount) override;

	std::string deposit(const double& amount) override;

	void updateState();

};