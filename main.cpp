#include "declaration.h"

int main()
{
	std::vector<std::vector<int> > S;
	std::vector<std::vector<int> > Ag;
	std::vector<std::vector<int> > Ab;
	std::vector<int> affin;

	int generation = 32500;

	std::stringstream ss;
	init(S, Ag, Ab, affin);
	for (size_t i = 0; i < S.size(); ++i)
	{
		for (size_t j = 0; j < S[0].size(); ++j)
		{
			if (((j) % 3) == 0)
				ss << "\n";
			ss << S[i][j] << " ";
		}
		ss << "\n";
	}
	ss << "\n";
	algorithm(Ab, Ag, affin, generation);
	for (size_t i = 0; i < Ab.size() - 3; ++i)
	{
		for (size_t j = 0; j < Ab[0].size(); ++j)
		{
			if ((j % 3) == 0)
				ss << "\n";
			ss << Ab[i][j] << " ";
		}
		ss << "\n";
	}


	print(ss.str());

	return EXIT_SUCCESS;
}
