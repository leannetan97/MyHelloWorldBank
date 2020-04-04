#include "NormalState.h"

// Define NormalState (Subclass of State)
NormalState::NormalState(AccountInterface* account)
	:m_account((Account*)account)
{
	m_account->setUpNormalState(this);
}

// Methods
std::string NormalState::getStateName() {
	return "Normal State";
}


std::string NormalState::withdraw(const double& amount) {
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

std::string NormalState::deposit(const double& amount) {
	(m_account)->increaseBalance(amount);
	return std::string("RM") + std::to_string(amount) + std::string(" is added to the account\nCurrent Account State: ") + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance: RM") + std::to_string(m_account->getBalance()) + std::string("\n");
}

void NormalState::updateState() {
	if (m_account->getBalance() < 50) {
		m_account->setState(m_account->getLockState());
	}
}