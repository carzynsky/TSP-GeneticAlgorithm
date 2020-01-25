#pragma once
#include <vector>
typedef std::vector<std::vector<int>> Mtrx;
class Genetic
{
private:
	Mtrx m;
	int problemSize;
	int sizeOfPopulation;
	int amountOfGenerations;
	int crossoversPerGeneration;
	int mutationsPerGeneration = 1;
	int q = 5;
	std::vector<std::pair<std::vector<int>, int>> population;
	std::vector<std::pair<std::vector<int>, int>> previousPopulation;
	std::vector<int> shortestRoute;
	int minCost;

public:
	Genetic(Mtrx m, int sizeOfPopulation, int amountOfGenerations, int amountOfCrossovers, int amountOfMutations);
	std::vector<int> PMX(std::vector<int> p1, std::vector<int> p2);
	std::vector<int> OX(std::vector<int> p1, std::vector<int> p2);
	void crossover_and_mutate();
	std::vector<std::pair<std::vector<int>, int>> selection(std::vector<std::pair<std::vector<int>, int>> previousPopulation);
	int tc(std::vector<int> route);
	void generate_population();
	void genetic_algorithm();
	void rate_population();
};

