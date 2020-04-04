#pragma once

#include "AccountInterface.h"
#include "State.h"
#include "ServiceFeesInterface.h"

class Account : public AccountInterface {
	private:
		ServiceFeesInterface* m_serviceFees;
		State*  m_lockState;
		State* m_normalState;
		State* m_currentState;
		double m_balance = 0;
	public:
		Account(ServiceFeesInterface* serviceFees);

		~Account();
	
		// Methods
		std::string deposit(const double& amount) override;
	
		std::string withdraw(const double& amount) override;
	
		double getBalance() override;
	
		void setState(State* state);

		void setUpLockState(State* lockState);
	
		void setUpNormalState(State* normalState);
	
		void increaseBalance(const double& newBalance);
	
		void deductBalance(const double& newBalance);
	
		State* getNormalState();
	
		State* getLockState();

		State* getState();
	
		double getServiceCharge(const double& amount);
	};