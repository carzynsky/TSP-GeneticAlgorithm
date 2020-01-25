#pragma once

#include <vector>
#include <string>

typedef std::vector<std::vector<int>> Mtrx;
class LMatrix
{
private:
	Mtrx m;
	int problemSize;
public:
	LMatrix();
	~LMatrix();
	void load_from_file(std::string file_name);
	void tc_function(std::vector<int>& permutation);
	void print();
	Mtrx get_loaded_matrix();
	int get_problem_size();
};

