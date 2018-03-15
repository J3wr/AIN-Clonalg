#include "declaration.h"

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>

template<typename T>
void init(std::vector<std::vector<T> > &S,
	std::vector<std::vector<T> > &Ag,
	std::vector<std::vector<T> > &Ab,
	std::vector<T> &affin)
{
	S.resize(3);
	for (size_t i = 0; i < S.size(); ++i)
		S[i].resize(12);
	S = {
			{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
			{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1 },
			{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 }
	};

	Ag.resize(3);
	for (size_t i = 0; i < Ag.size(); ++i)
		Ag[i].resize(12);
	Ag = S;

	Ab.resize(6);
	for (size_t i = 0; i < Ab.size(); ++i)
		Ab[i].resize(12);

	srand(time(0));
	for (size_t i = 0; i < Ab.size(); ++i)
		for (size_t j = 0; j < Ab[0].size(); ++j)
			Ab[i][j] = rand() % 2;

	affin.reserve(Ab.size());
}

void print(const std::string &str)
{
	std::cout << str << std::endl;
}

template<typename T>
int affinity(vector<T> &Ab,
	vector<T> &Ag)
{
	int aff = 0;
	for (size_t j = 0; j < Ab.size(); ++j)
	{
		if (Ag[j] != Ab[j])
			++aff;
	}

	return aff;
}

template<typename T>
vector<vector<T> > select(vector<vector<T> > &Ab,
	vector<T> &aff, size_t n)
{

	vector<vector<T> > Ab_n;
	Ab_n = Ab;
	sort_by_affin(aff, Ab_n);

	if (n > Ab.size())
		n = Ab.size();
	Ab_n.resize(n);
	for (size_t i = 0; i < n; ++i)
		Ab_n[i] = Ab[i];

	return Ab_n;
}

template<typename T>
vector<vector<T> > clone(vector<vector<T> > &Ab_n,
	vector<T> &strParent)
{
	std::vector<std::vector<T>> C;

	size_t count;
	size_t Betta = 10;

	for (size_t i = 0; i < Ab_n.size(); ++i)
	{
		count = (Ab_n.size() * Betta) / (i + 1);
		for (; count != 0; --count)
		{
			C.push_back(Ab_n[i]);
			strParent.push_back(i + 1);
		}
	}

	return C;
}

template<typename T>
vector<vector<T> > mutate(vector<vector<T> > &C,
	vector<T> &strParent)
{
	vector<vector<T> > C_n;
	C_n.resize(C.size());
	for (size_t i = 0; i < C.size(); ++i)
		C_n[i].resize(C[i].size());
	C_n = C;

	float p_mutMax = 50;
	float Betta = 1;
	float p_mut;
	float round = 0.5;

	size_t quantity = 0;
	std::vector<int> isMutate;
	isMutate.reserve(C[0].size());
	int body;
	srand(time(0));
	for (size_t i = 0; i < C.size(); ++i)
	{
		p_mut = (p_mutMax * ((Betta * (strParent[i])) / 6));//C.size()));
		quantity = ((p_mut / 100) * C[0].size()) + round;

		for (size_t j = 0; j < quantity; ++j)
		{
			body = rand() % 12;
			if (wasMutated(isMutate, body))
			{
				--j;
				continue;
			}
			else
			{
				C_n[i][body] = !C[i][body];
				isMutate.push_back(body);
			}
		}
		isMutate.clear();
	}

	return C_n;
}

template<typename T>
void replace(vector<T> &Ab,
	vector<T> &Best_Ab,
	vector<T> &Ag)
{
	size_t affBest_Ab;
	size_t affAb;

	affBest_Ab = affinity(Best_Ab, Ag);
	affAb = affinity(Ab, Ag);

	if (affAb > affBest_Ab)
		Ab = Best_Ab;
	else
		return;
}

template<typename T>
vector<vector<T> > &edit(vector<vector<T> > &Ab,
	int countNewAb)
{
	srand(time(0));
	for (size_t i = countNewAb; i < Ab.size(); ++i)
		for (size_t j = 0; j < Ab[0].size(); ++j)
			Ab[i][j] = rand() % 2;

	return Ab;
}

template<typename T>
void sort_by_affin(vector<T> &aff,
	vector<vector<T> > &vectForSort)
{
	std::multimap<int, std::vector<T> > sortMap;
	for (size_t i = 0; i < aff.size(); ++i)
		sortMap.insert(std::pair<int, std::vector<T> >(aff[i], vectForSort[i]));

	size_t size = vectForSort.size();
	vectForSort.clear();
	vectForSort.resize(size);
	aff.clear();
	//std::multimap<int, std::vector<int>>::iterator it;
	auto it = sortMap.begin();
	for (size_t i = 0; i < vectForSort.size(); ++i, ++it)
	{
		aff.push_back(it->first);
		vectForSort[i] = it->second;
	}
}

template<typename T>
bool wasMutated(vector<T> &bodys, T currBody)
{
	//std::vector<int>::iterator it;

	auto it = std::find(bodys.begin(), bodys.end(), currBody);

	return it != bodys.end() ? true : false;
}

template<typename T>
vector<vector<T> > &algorithm(vector<vector<T> > &Ab,
	vector<vector<T> > &Ag,
	vector<T> &aff,
	int generation)
{
	vector<vector<T> > Ab_n;
	vector<int> numberOfStrAb_nForMutate;
	vector<vector<T> > C;

	while (generation != 0)
	{
		for (size_t i = 0; i < Ag.size(); ++i)
		{
			//Высчитываем аффинность
			for (size_t j = 0; j < Ab.size(); ++j)
				aff.push_back(affinity(Ab[j], Ag[i]));

			Ab_n = select(Ab, aff, 4);

			C = clone(Ab_n, numberOfStrAb_nForMutate);

			aff.clear();
			for (size_t j = 0; j < C.size(); ++j)
				aff.push_back(affinity(C[j], Ag[i]));

			sort_by_affin(aff, C);

			C = mutate(C, numberOfStrAb_nForMutate);

			aff.clear();
			for (size_t j = 0; j < C.size(); ++j)
				aff.push_back(affinity(C[j], Ag[i]));

			Ab_n = select(C, aff, 1);

			replace(Ab[i], Ab_n[0], Ag[i]);

			edit(Ab, 3);
			aff.clear();
			C.clear();
			numberOfStrAb_nForMutate.clear();
		}
		--generation;
	}

	return Ab;
}


template void init(vector<vector<int> > &,
	vector<vector<int> > &,
	vector<vector<int> > &,
	vector<int> &);

template int affinity(vector<int> &,
	vector<int> &);

template vector<vector<int> > select(vector<vector<int> > &,
	vector<int> &, size_t);

template vector<vector<int> > clone(vector<vector<int> > &,
	vector<int> &);

template vector<vector<int> > mutate(vector<vector<int> > &,
	vector<int> &);

template void replace(vector<int> &, vector<int> &,
	vector<int> &);

template vector<vector<int> > &edit(vector<vector<int> > &,
	int);

template void sort_by_affin(vector<int> &,
	vector<vector<int> > &);

template bool wasMutated(vector<int> &, int);

template vector<vector<int> > &algorithm(vector<vector<int> > &,
	vector<vector<int> > &,
	vector<int> &,
	int);
