#pragma once

#include "LMatrix.h"
#include <iostream>
#include <fstream>

LMatrix::LMatrix()
{
}


LMatrix::~LMatrix()
{
}

Mtrx LMatrix::get_loaded_matrix()
{
	return m;
}
int LMatrix::get_problem_size()
{
	return problemSize;
}

void LMatrix::load_from_file(std::string fileName)
{
	std::ifstream fileStream;
	std::string instanceName;
	fileStream.open(fileName, std::ios::in);
	if (fileStream.good())
	{
		std::cout << "Plik z danymi testowymi zostal otwarty prawidlowo." << std::endl << std::endl;
		std::string line;
		fileStream >> line;
		instanceName = line;
		fileStream >> line;
		problemSize = std::stoi(line);
		std::cout << "Nazwa pliku: " << fileName << std::endl;
		std::cout << "Nazwa instancji problemu: " << instanceName << std::endl;
		std::cout << "Rozmiar instancji problemu: " << problemSize << std::endl << std::endl;
		m.resize(problemSize, std::vector<int>(problemSize));
		while (!fileStream.eof())
		{
			for (int i = 0; i < m.size(); i++)
			{
				for (int j = 0; j < m[i].size(); j++)
				{
					fileStream >> m[i][j];
				}
			}
		}
		fileStream.close();
	}
	else
	{
		std::cout << "Plik tekstowy nie zostal otworzony!" << std::endl;
	}
}
void LMatrix::print() {
	for (int i = 0; i < problemSize; i++) { // wyswietlenie wczytanej macierzy
		for (int j = 0; j < problemSize; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void LMatrix::tc_function(std::vector<int>& permutation) {
	int sum = 0, i = 0;
	for (i = 0; i < permutation.size() - 1; i++) {
		sum += m[permutation[i]][permutation[i + 1]];
	}
	sum += m[permutation[i]][0];

	std::cout << "Podana permutacja: " << std::endl;
	std::cout << "[";
	for (int i = 0; i < permutation.size(); i++) {
		std::cout << permutation[i] << " ";
	}
	std::cout << "]" << std::endl;
	std::cout << "Funkcja celu: " << sum << std::endl;

}

