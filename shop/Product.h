
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
	void		setName(std::string);
	double		getPrice() const;
	void		setPrice(double);
};