
#pragma once
#include <string>
// інша традиція - іменування - CamelCase
// імена змінних, полів та методів - LowerCamelCase -
// перша літера маленька, далі у поєднанні - великі
// імена класів - CapitalCamelCase - перша літера велика

class Product {
private:
	std::string name;
	double price;

public:
	std::string getName() const;
	Product*	setName(std::string);
	double		getPrice() const;
	Product*	setPrice(double);

	virtual std::string toString() const = 0;  // pure virtual OR abstract method
};