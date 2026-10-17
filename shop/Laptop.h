
#pragma once
#include "Electrical.h"

class Laptop : public Electrical {
private:
	std::string hardware;
public:
	std::string getHardware() const;
	void		setHardware(std::string);
	std::string toString();
};