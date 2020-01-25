#include <iostream>
#include <stdio.h>
#include "LMatrix.h"
#include "TimeCounter.h"
#include "Genetic.h"

int main()
{
	srand(time(NULL));
	LMatrix* lm = new LMatrix();
	TimeCounter tc;
	while (true) {
		system("CLS");
		std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+ Projektowanie efektywnych algorytmow +" << std::endl;
		std::cout << "+ Projekt: Problem Komiwojazera        +" << std::endl;
		std::cout << "+ Algorytm genetyczny                  +" << std::endl;
		std::cout << "+ Autor: Arkadiusz Carzynski 241335    +" << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
		std::cout << "1. Wczytaj macierz" << std::endl;
		std::cout << "2. Rozpocznij dzialanie algorytmu genetycznego" << std::endl;
		std::cout << "3. Wyjscie" << std::endl;
		std::cout << "Wybor: ";
		char choice;
		std::cin >> choice;

		switch (choice)
		{
		case '1':
		{
			system("CLS");
			lm = new LMatrix();
			std::string input;
			std::cout << "Podaj nazwe pliku z danymi testowymi: ";
			std::cin >> input;
			(*lm).load_from_file(input + ".txt");
			(*lm).print();
			std::cout << "\nWcisnij przycisk aby powrocic...";
			getchar();
			getchar();
			break;
		}

		case '2':
		{
			system("CLS");
			if ((*lm).get_problem_size() == 0)
			{
				std::cout << "Nie wczytano macierzy!" << std::endl;
				std::cout << "Wcisnij przycisk aby powrocic...";

			}
			else {
				int sizeOfPopulation, amountOfGenerations, amountOfCrossovers, amountOfMutations;
				std::cout << "Wczytana macierz: data" << (*lm).get_problem_size() << std::endl;
				std::cout << "Podaj wielkosc populacji: ";
				std::cin >> sizeOfPopulation;
				std::cout << "Podaj liczbe pokolen: ";
				std::cin >> amountOfGenerations;
				std::cout << "Podaj liczbe krzyzowan na pokolenie: ";
				std::cin >> amountOfCrossovers;
				std::cout << "Podaj liczbe mutacji na pokolenie: ";
				std::cin >> amountOfMutations;

				Genetic* genetic = new Genetic((*lm).get_loaded_matrix(), sizeOfPopulation, amountOfGenerations, amountOfCrossovers, amountOfMutations);

				tc.startTimer();
				genetic->genetic_algorithm();
				tc.stopTimer();
				std::cout << "Algorytm genetyczny dla problemu " << (*lm).get_problem_size() << " wierzcholkow wykonal sie w czasie: " << tc.timePassed() <<"ms" << std::endl;
				std::cout << std::endl << "Wcisnij przycisk aby powrocic...";
			}
			getchar();
			getchar();
			break;

		}
		case '3':
		{
			exit(0);
		}

		default: {
			break;
		}
		}
	}

}

