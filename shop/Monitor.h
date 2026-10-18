
#pragma once
#include "Electrical.h"

class Monitor : public Electrical {
private:
	double diagonal;
public:
	double getDiagonal() const;
	Monitor* setDiagonal(double);
	std::string toString() const override;
};