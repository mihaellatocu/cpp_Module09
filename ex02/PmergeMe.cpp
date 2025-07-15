#include "PmergeMe.hpp"

void PmergeMe::printStackV()
{
	std::cout <<"List of vectors: ";
	std::vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout <<std::endl;
}

void PmergeMe::printStackD()
{
	std::cout <<"List of deques: ";
	std::deque<int>::iterator it;
	for (it = d.begin(); it != d.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout <<std::endl;
}

template <typename Container>
void PmergeMe::printContainer(const Container& c) const
{
	std::cout <<"List of elements from container: ";
	typename Container::const_iterator it;
	for (it = c.begin(); it != c.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout <<std::endl;
}

PmergeMe::PmergeMe(int ac, char** av)
{
	std::set<int> seen;

	for (int i = 1; i < ac; i++)
	{
		std::string str = av[i];
		for (size_t j = 0; j < str.length(); j++)
		{
			if(!isdigit(str[j]))
				throw std::invalid_argument("Non-integer input: " + str);
		}
		long nr = std::atol(str.c_str());
		if (nr < 0 || nr > INT32_MAX)
			throw std::out_of_range("Input out of range: " + str);

		// if (!seen.insert(nr).second) // return true or false 
		// 	throw std::runtime_error("Duplicate argument " + str); // to be commented
		//or
		if (seen.insert(nr).second)
		{
			v.push_back(static_cast<int>(nr));
			d.push_back(static_cast<int>(nr));
		}
	}
}

PmergeMe::~PmergeMe() {}

void PmergeMe::run()
{
	std::vector<int> vecCopy = v;
	std::deque<int> deqCopy = d;

	clock_t startVec = clock();
	//std::cout << "start " << startVec << std::endl;
	//sortare..!! 
	mergeInsertSortVector(vecCopy);
	clock_t endVec = clock();
	//std::cout << "end " << endVec << std::endl;
	double vectorSortTime = static_cast<double>(endVec-startVec); // / CLOCKS_PER_SEC * 1e6; //timpul e in microsecunde

	printContainer(vecCopy);
	std::cout << "Time to process a range of " << vecCopy.size()
			<< " elements with std::vector: " << std::fixed << std::setprecision(5)
			<< vectorSortTime << " µs" << std::endl;


	clock_t startDeq = clock();
	//if(deq.size(0) > 1)
		//mergeInsertSortDeque(deqCopy);
	clock_t endDeq = clock();
	double dequeSortTime = static_cast<double>(endDeq - startDeq);

	// printContainer(deqCopy);

	std::cout << "Time to process a range of " << deqCopy.size()
			<< " elements with std::deque: " << std::fixed << std::setprecision(5)
			<< dequeSortTime << " µs" << std::endl;
}


static void swapV(int start, int end, int pairs, std::vector<int>& vec)
{
	if (end + pairs > static_cast<int>(vec.size()))
		return; // ieșire de siguranță
	for (int i = 0; i < pairs; i++)
	{
		std::swap(vec[start + i], vec[end + i]);
	}
}

static void swapVreverse(int high, int low, int pairs, std::vector<int>& vec)
{
	for (int i = 0; i < pairs; i++)
	{
		std::swap(vec[high - i], vec[low - i]);
	}
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& vec)
{
	int level = 1;
	int pairs = 1;
	while (pairs * 2 <= static_cast<int>(vec.size()))
	{
		for (int i = 0 ; i + pairs < static_cast<int>(vec.size()); i+= pairs * 2)
		{
			// Verificare de siguranță
			if (i + 2 * pairs > static_cast<int>(vec.size()))
			{
				continue; // nu e o pereche completă
			}			
			if(vec[i + pairs - 1] > vec[i + pairs * 2 - 1])
			{
				swapV(i, i + pairs, pairs, vec); // pairs +2
			}
		}
		pairs *= 2;
		level++;
		std::cout << "Levels " << level << " Pairs "<< pairs <<  "\n";
		printContainer(vec);
	}
	
	while (level > 1)
	{
		int poz =(vec.size() / pairs) * pairs; //poz from where we have pending
		pairs /= 2;
		std::cout << "poz " << poz << "\n";
		std::cout << static_cast<int>(vec.size()) - poz  << "\n"; // 10 5 11 9 3 7 15 14 13 2 12 6 8 4 1
		if ((static_cast<int>(vec.size()) - poz) >= pairs)
		{
			for (int i = poz + pairs - 1; i - pairs >= 0; i -= pairs) // to correct to pick up middle position // pleaca de la 11 si de ver poz 7 si 3
			{
				std::cout << "poz i " << i << "\n";
				if (vec[i] < vec[i - pairs] && vec[i] > vec[i - pairs*2]) // to be corrected
				{
					//std::cout << vec[i] << "\n";
					swapVreverse(i, i - pairs, pairs, vec);
				}
			}
		}
		printContainer(vec);
		level--;
	}
}
	// void PmergeMe::mergeInsertSortDeque(std::deque<int>& deqCopy)
	// {

	// }
