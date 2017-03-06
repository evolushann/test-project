#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>

#include "ACO.cpp"

#define ITERACO			(int) 50000

#define ALPHA			(int) 2
#define BETA			(int) 5
#define RO				(double) 0.80
#define INITCITY		(int) 0

int main() {
	//edit to cater to file inputs
	//9 = number of vehicles
	//240 = number of locations/customers
	//5646.46 = expected best value
	ACO *test = new ACO(9, 240,
		ALPHA, BETA, 5646.46, RO,
		INITCITY);

	//add cities and connections here
	//all cities connected?

	return 0;
}