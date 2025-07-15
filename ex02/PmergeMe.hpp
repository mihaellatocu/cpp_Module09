#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h> //atoi atol
#include <stdexcept> //try catch
#include <stdint.h> // pt INT32_MAX
#include <set>
#include <ctime>
#include <iomanip>


class PmergeMe
{
private:
	std::vector<int> v;
	std::deque<int> d;

public:
	PmergeMe(int ac, char** av);
	void run();
	~PmergeMe();

	void printStackV();
	void printStackD();

	template <typename Container>
	void printContainer(const Container& c) const;

	void mergeInsertSortVector(std::vector<int>& vec);
	void mergeInsertSortDeque(std::deque<int>& deqCopy);
};

