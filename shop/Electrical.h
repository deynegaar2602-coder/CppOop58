
#pragma once
#include "Product.h"

class Electrical : public Product { // ":" означає спадкування
private:							// public - збереження доступності методів
	double power;
public:
	double getPower() const;
	void setPower(double);
};