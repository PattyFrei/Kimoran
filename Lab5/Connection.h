#pragma once
#include <Edge.h>
#include <Node.h>

class Connection : public Edge
{
public:
	Connection(Node& src, Node& dst, int weight, std::string name); // init Connection 
	virtual double getWeight(); // returns cost/"Taler"
	std::string getName() const; // returns Connection name

private:
	int m_weight;
	std::string m_name;
};