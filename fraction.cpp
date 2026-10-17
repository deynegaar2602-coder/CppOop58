
#define _CRT_SECURE_NO_WARNINGS
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
		size_t len = strlen(other.name) + 1;
		this->name = new char[len];
		strcpy(this->name, other.name);
		std::cout << "Copy constructor: copy from " << (void*)other.name << " to "
		<< (void*)(this->name) << std::endl;
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

	 Аналогічна ситуація виникає при присвоюванні: A = B - так само необхідно 
	 створювати копії полів - покажчиків.
	 Поєднання конструнтора, копіювання да відповідного оператора "="
	 називають "симантикою копіювання".

	*/
}

fraction_t::fraction_t(fraction_t&& other) noexcept {
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
	std::cout << "Move constructor: take from " << (void*)other.name << std::endl;
}

char* fraction_t::get_name() const {
	return name;
}

void fraction_t::set_name(char* name) {
	this->name = name;
}

int fraction_t::get_numerator() const {
	return numerator;
}

int fraction_t::get_denominator() const {
	return denominator;
}

void fraction_t::set_numerator(int numerator) {
	this->numerator = numerator;
	// this - це покажчик на об'єкт, неявний параметр, що передається у нестатичні методи класу.
}

void fraction_t::set_denominator(int denominator) {
	this->denominator = denominator;
}

std::string fraction_t::to_string() const {
	// Форматування рядків - заповнення "формату" - рядка з плейсхолдером
	//					 v   v	- placeholders
	return std::format("({0}/{1}{2})", numerator, denominator, (name == NULL ? "" : name));
	//								  ^			   ^
	//				Дані, які будуть підставлені на місце плейсхолдерів
}

fraction_t::~fraction_t() {
	// Задача деструктору - звільнити ресурси об'єкту.
	if (name != NULL) {
		delete[] name;
	}
}

fraction_t fraction_t::operator +(const fraction_t& other) {
	char* new_name = NULL;
	if (this->name != NULL && other.name != NULL) {
		// якщо в обох дробах є імена, то поєднаємо їх через "+"
		size_t len1 = strlen(this->name);
		size_t len = len1 + strlen(other.name) + 2;
		new_name = new char[len];                 // [__________]
		strcpy(new_name, this->name);             // [Half______]
		strcpy(new_name + len1, "+");             // [Half+_____]
		strcpy(new_name + len1 + 1, other.name);  // [Half+Decil]
	}
	return fraction_t(
		this->numerator * other.denominator + this->denominator * other.numerator,
		this->denominator * other.denominator,
		new_name);
	// a/b + c/d = (ad+bc)/bd
}

fraction_t& fraction_t::operator =(const fraction_t& other) {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	if (other.name != NULL) {
		size_t len = strlen(other.name) + 1;
		this->name = new char[len];
		strcpy(this->name, other.name);
		std::cout << "Copy assignment: copy from " << (void*)other.name << " to "
			<< (void*)(this->name) << std::endl;
	}
	else {
		this->name = NULL;
	}
	return *this;
}

fraction_t& fraction_t::operator =(fraction_t&& other) noexcept {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	this->name = other.name;
	other.name = NULL;
	std::cout << "Move assignment: take from " << (void*)this->name << std::endl;
	return *this;
}

fraction_t operator *(const fraction_t& f1, const fraction_t& f2) {
	return fraction_t(
		f1.numerator* f2.numerator,     // дружні функції мають доступ
		f1.denominator* f2.denominator  // до приватних полів об'єкту
	);
}
fraction_t operator /(const fraction_t& f1, const fraction_t& f2) {
	return fraction_t(
		f1.get_numerator() * f2.get_denominator(),  // функції, що не є дружніми
		f1.get_denominator() * f2.get_numerator()   // мають доступ лише до аксессорів
	);
}

std::ostream& operator <<(std::ostream& out, const fraction_t& f) {
	out << f.to_string();
	return out;
}

fraction_t operator -(const fraction_t& f) {
	return fraction_t(
		-f.get_numerator(),
		f.get_denominator()
	);
}
void fraction_t::operator += (const fraction_t& other) {
	this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	this->denominator = this->denominator * other.denominator;
	reduce();
}
void fraction_t::operator += (int n) {
	this->numerator += n * this->denominator;
	reduce();
}

int fraction_t::gcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a > b) return gcd(b, a);
	if (a == 0) return b;
	return gcd(b, a % b);
}

void fraction_t::reduce(){
	int g = gcd(numerator, denominator);
		if (g != 1) {
			numerator /= g;
			denominator /= g;
		}
}

/*
 Правила опису класів:
 При описі класів необхідно обов'язково включити до списку
 - Конструктор за замовчуванням
 - Конструктор копіювання
 - Конструктор перенесення 
 - Оператор = копіювання
 - Оператор = перенесення
 - Деструктор
 ~ Інколи додається параметризований конструктор

*/