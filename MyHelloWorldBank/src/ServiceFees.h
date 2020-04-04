#pragma once

#include"ServiceFeesInterface.h"
class ServiceFees : public ServiceFeesInterface {

public:
	double serviceCharge(const double& amount) override;

};