#include "Genetic.h"
#include <algorithm>
#include <iostream>

Genetic::Genetic(Mtrx m, int sizeOfPopulation, int amountOfGenerations, int amountOfCrossovers, int amountOfMutations)
{
	this->m = m;
	problemSize = m.size();
	this->sizeOfPopulation = sizeOfPopulation;
	this->amountOfGenerations = amountOfGenerations;
	crossoversPerGeneration = amountOfCrossovers;
	mutationsPerGeneration = amountOfMutations;
	minCost = INT_MAX;
}

std::vector<int> Genetic::OX(std::vector<int> p1, std::vector<int> p2)
{
	std::vector<int> child1, child2;

	// Krok 1
	int k1, k2;
	k1 = rand() % (problemSize - 3) + 1;
	do
		k2 = rand() % (problemSize - 2) + 1;
	while (k2 <= k1);

	std::vector<int> swathP1 = std::vector<int>(p1.begin() + k1, p1.begin() + k2 + 1);
	std::vector<int> swathP2 = std::vector<int>(p2.begin() + k1, p2.begin() + k2 + 1);

	// Child 1
	child1.push_back(0);
	for (int i = 0; i < k1 - 1; i++)
	{
		child1.push_back(-1);
	}

	child1.insert(child1.end(), swathP2.begin(), swathP2.end());

	for (int j = k2 + 1; j < problemSize - 1; j++)
	{
		child1.push_back(-1);
	}
	child1.push_back(0);

	// Child 2
	child2.push_back(0);
	for (int i = 0; i < k1 - 1; i++)
	{
		child2.push_back(-1);
	}

	child2.insert(child2.end(), swathP1.begin(), swathP1.end());

	for (int j = k2 + 1; j < problemSize - 1; j++)
	{
		child2.push_back(-1);
	}
	child2.push_back(0);

	// Krok 2
	// od k2+1
	int i = k2 + 1;
	while(std::find(child1.begin(), child1.end(), -1) != child1.end())
	{
		int tmpI = i;
		if (i >= problemSize - 1)
			tmpI = i - (problemSize - 2);
			// Child 1
			if (std::find(child1.begin(), child1.end(), p1[tmpI]) == child1.end())
				child1[tmpI] = p1[tmpI];
			else
			{
				int index = tmpI;
				do
				{
					index++;
					if (index >= problemSize - 1) index -= (problemSize - 2);
				} while (std::find(child1.begin(), child1.end(), p1[index]) != child1.end());
				child1[tmpI] = p1[index];
			}

			// Child 2
			if (std::find(child2.begin(), child2.end(), p2[tmpI]) == child2.end())
				child2[tmpI] = p2[tmpI];
			else
			{
				int index = tmpI;
				do
				{
					index++;
					if (index >= problemSize - 1) index -= (problemSize - 2);
				} while (std::find(child2.begin(), child2.end(), p2[index]) != child2.end());
				child2[tmpI] = p2[index];
			}
			i++;
	}
	return tc(child1) >= tc(child2) ? child2 : child1;
}
std::vector<int> Genetic::PMX(std::vector<int> p1, std::vector<int> p2)
{
	std::vector<int> child1, child2;

	// Krok 1
	int k1, k2;
	k1 = rand() % (problemSize - 3) + 1;
	do
		k2 = rand() % (problemSize - 2) + 1;
	while (k2 <= k1);

	std::vector<int> swathP1 = std::vector<int>(p1.begin() + k1, p1.begin() + k2 + 1);
	std::vector<int> swathP2 = std::vector<int>(p2.begin() + k1, p2.begin() + k2 + 1);

	// Child 1
	child1.push_back(0);
	for (int i = 0; i < k1-1; i++)
	{
		child1.push_back(-1);
	}

	child1.insert(child1.end(), swathP2.begin(), swathP2.end());

	for (int j = k2 + 1; j < problemSize - 1; j++)
	{
		child1.push_back(-1);
	}
	child1.push_back(0);

	// Child 2
	child2.push_back(0);
	for (int i = 0; i < k1 - 1; i++)
	{
		child2.push_back(-1);
	}

	child2.insert(child2.end(), swathP1.begin(), swathP1.end());

	for (int j = k2 + 1; j < problemSize - 1; j++)
	{
		child2.push_back(-1);
	}
	child2.push_back(0);

	// Krok 2
	//(od 1 bo pomijamy pierwszy wierzcholek)
	for (int i = 1; i < problemSize-1; i++)
	{
		if (i < k1 || i > k2)
		{
			// Child 1
			if (std::find(child1.begin(), child1.end(), p1[i]) == child1.end())
				child1[i] = p1[i];
			else
			{
				int temp = p1[i];
				int index = i;
				do
				{
					auto indPtr = std::find(p2.begin(), p2.end(), temp);
					index = std::distance(p2.begin(), indPtr);
					temp = p1[index];
				} while (std::find(child1.begin(), child1.end(), temp) != child1.end());
				child1[i] = temp;
			}

			// Child 2
			if (std::find(child2.begin(), child2.end(), p2[i]) == child2.end())
				child2[i] = p2[i];
			else
			{
				int temp = p2[i];
				int index = i;
				do
				{
					auto indPtr = std::find(p1.begin(), p1.end(), temp);
					index = std::distance(p1.begin(), indPtr);
					temp = p2[index];
				} while (std::find(child2.begin(), child2.end(), temp) != child2.end());
				child2[i] = temp;
			}
		}
	}
	return tc(child1) >= tc(child2) ? child2 : child1;
}

void Genetic::crossover_and_mutate()
{
	std::pair<std::vector<int>, int> child;
	int randomParent1, randomParent2;
	int randomPopulationToMutate;
	int randomSwapIndex1, randomSwapIndex2;

	// krzy¿owanie
	for (int j = 0; j < crossoversPerGeneration; j++)
	{
		randomParent1 = rand() % sizeOfPopulation;
		do
		{
			randomParent2 = rand() % sizeOfPopulation;
		} while (randomParent1 == randomParent2);

		child.first = PMX(population[randomParent1].first, population[randomParent2].first);
		child.second = tc(child.first);

		population.push_back(child);		
	}
	// mutacja z prawdopodobienstwem 0.6
	if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= 0.6)
	{
		for (int k = 0; k < mutationsPerGeneration; k++)
		{
			do
			{
				randomPopulationToMutate = rand() % population.size();
			} while (population[randomPopulationToMutate].first == shortestRoute);

			randomSwapIndex1 = rand() % (problemSize-2)+1;

			do
			{
				randomSwapIndex2 = rand() % (problemSize-2) + 1;
			} while (randomSwapIndex1 == randomSwapIndex2);

			std::swap(population[randomPopulationToMutate].first[randomSwapIndex1], population[randomPopulationToMutate].first[randomSwapIndex2]);
			population[randomPopulationToMutate].second = tc(population[randomPopulationToMutate].first);
		}
	}
}

std::vector<std::pair<std::vector<int>, int>> Genetic::selection(std::vector<std::pair<std::vector<int>, int>> previousPopulation)
{
	int N = sizeOfPopulation;
	//int q = previousPopulation.size() > (N+3) ? 3 : (previousPopulation.size() % 10);
	int sample = q;
	std::vector<std::pair<std::vector<int>, int>> newPopulation;
	std::vector<std::pair<std::vector<int>, int>> pool;

	// n turniejów
	while(N > 0)
	{
		std::vector<std::pair<std::vector<int>, int>> tournament;
		pool = previousPopulation;
		pool.size() < sample ? sample = pool.size() : sample = q;

		//  wylosuj uczestników turnieju
		for (int j = 0; j < sample; j++)
		{
			std::pair<std::vector<int>, int> participant;

			int participantIndex = rand() % pool.size();

			participant.first = pool[participantIndex].first;
			participant.second = pool[participantIndex].second;

			tournament.push_back(participant);
			pool.erase(pool.begin() + participantIndex);
		}
		// turniej dla sample uczestników
		int tmpBest = tournament[0].second;
		int tmpBestIndex = 0;
		for (int j = 1; j < sample; j++)
		{
			if (tournament[j].second < tmpBest)
			{
				tmpBestIndex = j;
				tmpBest = tournament[j].second;
			}
		}

		newPopulation.push_back(tournament[tmpBestIndex]);
		previousPopulation.erase(std::remove(previousPopulation.begin(), previousPopulation.end(), tournament[tmpBestIndex]), previousPopulation.end());
		N--;
	}
	return newPopulation;
}

void Genetic::generate_population()
{
	std::vector<std::vector<int>> populationVector;
	std::pair<std::vector<int>, int> para;
	{
		populationVector.resize(sizeOfPopulation);
		for (int i = 0; i < sizeOfPopulation; i++)
		{
			populationVector[i].push_back(0);
			for (int j = 1; j < problemSize - 1; j++)
			{
				while (true)
				{
					int randIndex = rand() % (problemSize - 2) + 1;
					if (!(std::find(populationVector[i].begin(), populationVector[i].end(), randIndex) != populationVector[i].end()))
					{
						populationVector[i].push_back(randIndex);
						break;
					}
				}
			}
			populationVector[i].push_back(0);

			para.first = populationVector[i];
			para.second = tc(populationVector[i]);

			population.push_back(para);
		}		
	}
}

int Genetic::tc(std::vector<int> route)
{
	int i = 0, sum = 0;
	for (i = 0; i < route.size() - 1; i++)
	{
		sum += m[route[i]][route[i + 1]];
	}
	sum += m[route[i]][route[0]];
	return sum;
}

void Genetic::rate_population()
{
	int lowestCost = minCost;
	std::vector<int> currentBestResult;
	bool changed = false;
	for (int i = 0; i < population.size(); i++) 
	{
		if (population[i].second < lowestCost) 
		{
			lowestCost = population[i].second;
			currentBestResult = population[i].first;
			changed = true;
		}
	}

	if (changed)
	{
		minCost = lowestCost;
		shortestRoute = currentBestResult;
	}
}

void Genetic::genetic_algorithm()
{
	generate_population();
	rate_population();
	int t = 0;
	while (t < amountOfGenerations)
	{
		previousPopulation = population;
		population = selection(previousPopulation);
		crossover_and_mutate();
		rate_population();
		t++;
	}
	std::cout << std::endl << "Sciezka:" << std::endl;
	std::cout << "[";
	for (int i = 0; i < problemSize-1; i++)
	{
		std::cout << shortestRoute[i] << " -> ";
	}
	std::cout << shortestRoute[problemSize-1] << "]";

	std::cout << std::endl << "Koszt: " << minCost << std::endl;
	std::cout << minCost << std::endl;

}
