#include "LockState.h"

// Define LockState (Subclass of State)
LockState::LockState(AccountInterface* account)
	:m_account((Account*)account)
{
	m_account->setUpLockState(this);
}

// Methods
std::string LockState::getStateName() {
	return "Lock State";
}


std::string LockState::withdraw(const double& amount) {
	return "Sorry, Unable to perform withdrawal. Account should have minimum RM50 in order to perform withdrawal.\nCurrent Account State: " + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance RM:") + std::to_string(m_account->getBalance()) + std::string("\n");
}

std::string LockState::deposit(const double& amount) {
	(m_account)->increaseBalance(amount);
	if ((m_account)->getBalance() >= 50) {
		(m_account)->setState(m_account->getNormalState());
	}
	return std::string("RM") + std::to_string(amount) + std::string(" is added to the account\nCurrent Account State: ") + ((m_account)->getState())->getStateName() + std::string("\nAccount Balance: RM") + std::to_string((m_account)->getBalance()) + std::string("\n");
}