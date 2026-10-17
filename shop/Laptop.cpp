
#include <format>
#include "Laptop.h"

std::string Laptop::getHardware() const {
	return hardware;
}

void Laptop::setHardware(std::string hardware) {
	this->hardware = hardware;
}

std::string Laptop::toString() {
	return std::format("{} {}hrn, {} ({} W)",
		getName(),
		getPrice(),
		hardware,
		getPower()
	);
}