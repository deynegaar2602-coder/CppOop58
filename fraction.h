#pragma once
#include <string>

class fraction_t {
private:
	int numerator;
	int denominator;
public:
	int get_numerator();
	int get_denominator();
	void set_numerator(int);
	void set_denominator(int);
	std::string to_string();

};