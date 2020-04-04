#include "ServiceFees.h"

// Define ServiceFees (Subclass of ServiceFeesInterface)
double ServiceFees::serviceCharge(const double& amount) {
	double charge = amount * 0.01;
	return charge;
}
