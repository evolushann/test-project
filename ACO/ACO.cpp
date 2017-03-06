#include "ACO.h"

#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>

using namespace std;

ACO::ACO (int vehicles, int customers,
	double alpha, double beta, double q, double ro,
	int initCity) {
	VEHICLES 		= vehicles;
	CUSTOMERS 		= customers;
	ALPHA 			= alpha;
	BETA 			= beta;
	Q 				= q;
	RO 				= ro;
	TAU 			= getTau();
	INITIALCITY		= initCity;
}
ACO::~ACO () {
	for(int i=0; i<CUSTOMERS; i++) {
		delete[] GRAPH[i];
		delete[] CITIES[i];
		delete[] PHEROMONES[i];
		delete[] DELTAPHEROMONES[i];
		if(i < CUSTOMERS - 1) {
			delete[] PROBABILITIES[i];
		}
	}
	delete[] GRAPH;
	delete[] CITIES;
	delete[] PHEROMONES;
	delete[] DELTAPHEROMONES;
	delete[] PROBABILITIES;
}

void ACO::init() {
	GRAPH 			= new int*[CUSTOMERS];
	CITIES 			= new float*[CUSTOMERS];
	PHEROMONES 		= new double*[CUSTOMERS];
	DELTAPHEROMONES = new double*[CUSTOMERS];
	PROBABILITIES	= new double*[CUSTOMERS - 1];
	ROUTES			= new int*[VEHICLES];
	BESTLENGTH		= (double) INT_MAX;
	BESTROUTE		= new int[CUSTOMERS];

	for(int i = 0; i < CUSTOMERS; i ++) {
		GRAPH[i] 			= new int[CUSTOMERS];
		CITIES[i]			= new float[2];					//x-coordinate and y-coordinate
		PHEROMONES[i]		= new double[CUSTOMERS];
		DELTAPHEROMONES[i]	= new double[CUSTOMERS];
		PROBABILITIES[i]	= new double[2];

		for(int j = 0; j < 2; j ++) {
			CITIES[i][j]		= -1.0;
			PROBABILITIES[i][j]	= -1.0;
		}

		for(int j = 0; j < CUSTOMERS; j ++) {
			GRAPH[i][j] 			= 0;
			PHEROMONES[i][j]		= 0.0;
			DELTAPHEROMONES[i][j] 	= 0.0;
		}
	}


	//init ROUTES
	for (int i = 0; i < VEHICLES; i++) {
		ROUTES[i] = new int[CUSTOMERS];
		for (int j = 0; j < CUSTOMERS; j ++) {
			ROUTES[i][j] = -1;
		}
	}

	//init BESTROUTE
	for (int i = 0; i < CUSTOMERS; i ++) {
		BESTROUTE[i] = -1;	
	}
}

float ACO::getTau() {
	int visited[CUSTOMERS];
	int Lnn = 0.0;

	visited[0] = 1;

	for(int i = 1; i < CUSTOMERS; i ++) {
		visited[i] = 0;
	}

	Lnn = visit(0, visited);

	return CUSTOMERS / Lnn;
}

float ACO::visit(int current, int visited[]) {
	float dist = INT_MAX;
	int next = 0;
	visited[current] = 1;

	for(int i = 0; i < CUSTOMERS; i ++) {
		if(exists(current, i) && visited[i] == 0) {
			if(distance(current, i) < dist) {
				dist = distance(current, i);
				next = i;
			}
		}
	}

	if(next == 0)
		return 0;
	else
		return dist + visit(next, visited);
}

void ACO::connectCities(int cityi, int cityj) {
	GRAPH[cityi][cityj] = 1;
	GRAPH[cityj][cityi] = 1;
	PHEROMONES[cityi][cityj] = TAU;
	PHEROMONES[cityj][cityi] = TAU;
}

void ACO::setCity(int city, float x, float y) {
	CITIES[city][0] = x;
	CITIES[city][1] = y;
}

float ACO::distance (int cityi, int cityj) {
	return (float) 
		sqrt (pow (CITIES[cityi][0] - CITIES[cityj][0], 2) +
			pow (CITIES[cityi][1] - CITIES[cityj][1], 2));
}

bool ACO::exists(int cityi, int cityc) {
	return (GRAPH[cityi][cityc] == 1);
}

bool ACO::visited(int ant, int city) {
	for(int i = 0; i < CUSTOMERS; i ++) {
		if(ROUTES[ant][i] == -1)
			break;

		if(ROUTES[ant][i] == city)
			return true;
	}

	return false;
}

double ACO::phi(int cityi, int cityj, int ant) {
	double ETAij = (double) pow(1 / distance(cityi, cityj), BETA);
	double TAUij = (double) pow(PHEROMONES[cityi][cityj], ALPHA);

	double sum = 0.0;

	for (int i = 0; i < CUSTOMERS; i ++) {
		if (exists(cityi, i)) {
			if (!visited(ant, i)) {
				double ETA = (double) pow(1 / distance(cityi, i), BETA);
				double TAU = (double) pow(PHEROMONES[cityi][i], ALPHA);
				sum += ETA * TAU;
			}	
		}	
	}

	return (ETAij * TAUij) / sum;
}

double ACO::length(int ant) {
	double sum = 0.0;

	for (int i = 0; i < -1; i++) {
		sum += distance (ROUTES[ant][i], ROUTES[ant][i+1]);	
	}

	return sum;
}

int ACO::city() {
	double xi = rand() / (RAND_MAX + 1.);

	while(xi == 1)
		xi = rand() / (RAND_MAX + 1.);

	int i = 0;
	double sum = PROBABILITIES[i][0];

	while(sum < xi) {
		i ++;
		sum += PROBABILITIES[i][0];
	}

	return (int) PROBABILITIES[i][1];
}

void ACO::route(int ant) {
	ROUTES[ant][0] = INITIALCITY;

	for(int i = 0; i < CUSTOMERS-1; i ++) {		
		int cityi = ROUTES[ant][i];
		int count = 0;

		for(int c = 0; c < CUSTOMERS; c ++) {
			if(cityi == c) {
				continue;	
			}

			if(exists(cityi, c)) {
				if(!visited(ant, c)) {
					PROBABILITIES[count][0] = phi(cityi, c, ant);
					PROBABILITIES[count][1] = (double) c;
					count ++;
				}

			}
		}
		
		// deadlock
		if(count == 0) {
			return;
		}
		
		ROUTES[ant][i+1] = city();
	}
}

int ACO::valid(int ant) {
	for(int i = 0; i < CUSTOMERS-1; i ++) {
		int cityi = ROUTES[ant][i];
		int cityj = ROUTES[ant][i+1];

		if(cityi < 0 || cityj < 0) {
			return -1;					//invalid city
		}

		if(!exists(cityi, cityj)) {
			return -2;					//not connected
		}

		for(int j = 0; j < i-1; j ++) {
			if (ROUTES[ant][i] == ROUTES[ant][j]) {
				return -3;				//same city
			}	
		}
	}
	
	if(!exists(INITIALCITY, ROUTES[ant][CUSTOMERS-1])) {
		return -4;						//incomplete route
	}
	
	return 0;
}

void ACO::updatePHEROMONES() {
	for(int k = 0; k < VEHICLES; k ++) {
		double rlength = length(k);
		for (int r = 0; r < CUSTOMERS-1; r ++) {
			int cityi = ROUTES[k][r];
			int cityj = ROUTES[k][r+1];
			DELTAPHEROMONES[cityi][cityj] += Q / rlength;
			DELTAPHEROMONES[cityj][cityi] += Q / rlength;
		}
	}
	
	for (int i = 0; i < CUSTOMERS; i ++) {
		for (int j = 0; j < CUSTOMERS; j ++) {
			PHEROMONES[i][j] = (1 - RO) * PHEROMONES[i][j] + DELTAPHEROMONES[i][j];
			DELTAPHEROMONES[i][j] = 0.0;
		}	
	}
}

void ACO::optimize(int ITERATIONS) {
	for(int iterations = 1; iterations <= ITERATIONS; iterations++) {
		for (int k = 0; k < VEHICLES; k ++) {
			while (0 != valid(k)) {
				for (int i = 0; i < CUSTOMERS; i ++) {
					ROUTES[k][i] = -1;	
				}

				route(k);
			}
			
			double rlength = length(k);

			if(rlength < BESTLENGTH) {
				BESTLENGTH = rlength;
				for(int i = 0; i < CUSTOMERS; i ++) {
					BESTROUTE[i] = ROUTES[k][i];
				}
			}			
		}		

		updatePHEROMONES ();
		
		for(int i = 0; i < VEHICLES; i ++) {
			for(int j = 0; j < CUSTOMERS; j ++) {
				ROUTES[i][j] = -1;
			}
		}
	}
}

double ACO::returnResult() {
	BESTLENGTH += distance (BESTROUTE[CUSTOMERS-1], INITIALCITY);
	return BESTLENGTH;
}