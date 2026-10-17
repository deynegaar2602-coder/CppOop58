
#include <string>
#include "Product.h"

std::string Product::getName() const {
	return name;
}

void Product::setName(std::string name) {
	this->name = name;
}

double Product::getPrice() const {
	return price;
}

void Product::setPrice(double price) {
	this->price = price;
}