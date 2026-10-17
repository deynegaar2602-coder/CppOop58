
#pragma once
#include <string>
// інша традиція - іменування - CamelCase
// імена змінних, полів та методів - LowerCamelCase -
// перша літера маленька, далі у поєднанні - великі
// імена класів - CapitalCamelCase - перша літера велика

class product {
private:
	std::string name;
	double price;

public:
	std::string getName();
	void		setName(std::string);
	double		getPrice();
	void		setPrice(double);
};