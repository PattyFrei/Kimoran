#include "Connection.h"

Connection::Connection(Node& src, Node& dst, int weight, std::string name)
	: Edge(src, dst), m_weight(weight), m_name(name) {
}

double Connection::getWeight() {
	return m_weight;
}

std::string Connection::getName() const {
	return m_name;
}