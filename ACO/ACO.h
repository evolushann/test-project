class ACO {
public:
	ACO(int vehicles, int customers,
		double alpha, double beta, double q, double ro,
		int initCity);
	virtual ~ACO();

	void init();

	void connectCities(int cityi, int cityj);
	void setCity(int city, float x, float y);

	void optimize(int iterations);
	double returnResult();
	
private:
	float distance(int cityi, int cityj);
	bool exists(int cityi, int cityc);
	bool visited(int ant, int city);
	double phi(int cityi, int cityj, int ant);

	double length(int ant);

	int city ();
	void route (int antk);
	int valid (int antk);

	float getTau();
	float visit(int current, int visited[]);

	void updatePHEROMONES ();

	int VEHICLES, CUSTOMERS, INITIALCITY;
	double ALPHA, BETA, Q, RO;
	float TAU;

	double BESTLENGTH;
	int *BESTROUTE;

	int **GRAPH, **ROUTES;
	float **CITIES;
	double **PHEROMONES, **DELTAPHEROMONES, **PROBABILITIES;
};