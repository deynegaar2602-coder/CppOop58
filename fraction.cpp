#include "fraction.h"
#include <iostream>

int fraction_t::get_numerator() {
	return numerator;
}
int fraction_t::get_denominator() {
	return denominator;
}
void fraction_t::set_numerator(int numerator) {
	this->numerator = numerator;
}
void fraction_t::set_denominator(int denominator) {
	this->denominator = denominator;
}

std::string fraction_t::to_string() {
	return "";
}