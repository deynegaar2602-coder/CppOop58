
#pragma once
#include "Electrical.h"

class Laptop : public Electrical {
private:
	std::string hardware;
public:
	std::string getHardware() const;
	Laptop*		setHardware(std::string);
	std::string toString() const override;  // override - переозначення батьківського методу
};