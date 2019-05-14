#include "Random.h"



Random::Random()
	:gen(rd())
{

}


Random::~Random()
{
}


int Random::getNumber(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}