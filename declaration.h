#ifndef DECLARATION_H
#define DECLARATION_H

#include <vector>
#include <string>
#include <sstream>

using std::vector;

template<typename T>
void init(vector<vector<T>> &S,
	vector<vector<T>> &Ag,
	vector<vector<T>> &Ab,
	vector<T> &affin);

void print(const std::string &str);

template<typename T>
int affinity(vector<T> &Ab,
	vector<T> &Ag);

template<typename T>
vector<vector<T> > select(vector<vector<T> > &Ab,
	vector<T> &aff, size_t n);

template<typename T>
vector<vector<T> > clone(vector<vector<T> > &Ab_n,
	vector<T> &);


template<typename T>
vector<vector<T> > mutate(vector<vector<T> > &C,
	vector<T> &);

template<typename T>
void replace(vector<T> &Ab,
	vector<T> &Best_Ab,
	vector<T> &Ag);

template<typename T>
vector<vector<T> > &edit(vector<vector<T> > &Ab,
	int countNewAb);

template<typename T>
void sort_by_affin(vector<T> &aff,
	vector<vector<T> > &vectForSort);

template<typename T>
bool wasMutated(vector<T> &bodys, T currBody);

template<typename T>
vector<vector<T> > &algorithm(vector<vector<T> > &Ab,
	vector<vector<T> > &Ag,
	vector<T> &aff,
	int generation);



#endif
