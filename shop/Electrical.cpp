
#include "Electrical.h"

double Electrical::getPower() const {
	return power;
}

Electrical* Electrical::setPower(double power) {
	this->power = power;
	return this;
}