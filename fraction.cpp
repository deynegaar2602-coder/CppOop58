
#include "fraction.h"
#include <format>
#include <iostream>

fraction_t::fraction_t() {			// Конструктор без параметрів - конструктор за замовчуванням
	numerator = 0;
	denominator = 1;
	name = NULL;
}
fraction_t::fraction_t(int n) {  // конструктор з параметрами, його слід зазначати
	numerator = n;               // прямо (не за замовчанням) f = new fraction_t(10)
	denominator = 1;             // Присвоювання значень
	name = NULL;
}

fraction_t::fraction_t(int numerator, int denominator) : // ініціалізація полів
	numerator{ numerator }, denominator{ denominator }   // на відміну від присвоювання
{                                                        // дозволяє задавати значення
	name = NULL;										 // незмінним полям (константам)
}                                                        // і комбінується з присвоєнням

fraction_t::fraction_t(int numerator, int denominator, char* name) :
	numerator{ numerator }, denominator{ denominator }, name{ name } {
}

fraction_t::fraction_t(fraction_t& other) {
	// Конструктор копіювання (copy constructor), який будує новий об'єкт за зразком іншого об'єкту.
	// Проблема: просте присвоєння полів об'єкта - зв'язка правильно працює для полів зі значенняи,
	// але неправильно - для покажчиків. Присвоєння this->name = other.name - створить другий покажчик 
	// на одне і те саме ім'я. Деструктор одного об'єкту видаляє ресурс, а деструктор - другого об'єкту
	// призведе до помилки. Також другий об'єкт продовжить працювати з видаленною пам'яттю.
	// Копіювання - це утворення копій усіх ресурсів покажчиків.
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	// Для референсного ресурсу створюємо копію
	if (other.name != NULL) {
		this->name = new char[strnlen_s(other.name, 100) + 1];
		strcpy_s(this->name, 100, other.name);
		//std::cout << "Copy constructor: copy from " << (void*)other.name << "to"
		//	<< (void*)this->name << std::endl;
	}
	else {
		this->name = NULL;
	}

	// 0x123("Half")					0x567("Half\0")
	// A[1/2"Half"] - A[1,2,0x123]		|
	// B = copy A	- B[1,2,0x123] - strcpy - B[1,2,0x567]
	// delete A - звільнення 0x123 --> B посилається на видаленний ресурс.

	/*
				A			   B			   0x123
	 ------[1,2,0x123]----[1,2,0x123]---------"Half\0"--------------------
	 

	 A.name = "1/2"
				A			   B			   0x123
	 ------[1,2,0x123]----[1,2,0x123]---------"1/2\0"---------------------
	 B.name = "1/2" - неправильно

				A			   B			   0x123		   0x567
	 ------[1,2,0x123]----[1,2,0x567]---------"Half\0"--------"Half\0"----
	*/

}

fraction_t::fraction_t(fraction_t&& other) {
	/*

	* Конструктор перенесення (move constructor) викликається тоді, 
	* коли об'єкт (other) підлягає знищенню, наприклад, коли він передається
	* як результат роботи функції.
 
	* Конструктор перенесення може "забрати" ресурс іншого об'єкта замість того,
	* щоб створювати копію. Але, щоб знищення не запустилось автоматично,
	* слід підмімити ресурс іншого об'єкта на NULL.
	*/
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	this->name = other.name;
	other.name = NULL;
}

char* fraction_t::get_name() {
	return name;
}
void fraction_t::set_name(char* name) {
	this->name = name;
}

int fraction_t::get_numerator() {
	return numerator;
}
int fraction_t::get_denominator() {
	return denominator;
}
void fraction_t::set_numerator(int numerator) {
	this->numerator = numerator;
	// this - це покажчик на об'єкт, неявний параметр, що передається у нестатичні методи класу.
}
void fraction_t::set_denominator(int denominator) {
	this->denominator = denominator;
}

std::string fraction_t::to_string() {
	// Форматування рядків - заповнення "формату" - рядка з плейсхолдером
	//					 v   v	- placeholders
	return std::format("({0}/{1})", numerator, denominator);
	//								  ^			   ^
	//				Дані, які будуть підставлені на місце плейсхолдерів
}
fraction_t::~fraction_t() {
	// Задача деструктору - звільнити ресурси об'єкту.
	if (name != NULL) {
		delete[] name;
	}
}