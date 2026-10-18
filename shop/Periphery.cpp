
#include "Periphery.h"

std::string Periphery::getConnection() const {
	return connection;
}

Periphery* Periphery::setConnection(std::string connection) {
	this->connection = connection;
	return this;
}