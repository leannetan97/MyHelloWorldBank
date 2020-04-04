#pragma once
class ServiceFeesInterface{

public:
	ServiceFeesInterface() {}

	virtual ~ServiceFeesInterface() {}

	// Methods
	virtual double serviceCharge(const double& amount) = 0;
};