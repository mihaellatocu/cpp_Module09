#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& other) : v(other.v), d(other.d) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        v = other.v;
        d = other.d;
    }
    return *this;
}

void PmergeMe::printStackV()
{
	std::cout <<"Before: ";
	std::vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout <<std::endl;
}

void PmergeMe::printStackD()
{
	std::cout <<"Before: ";
	std::deque<int>::iterator it;
	for (it = d.begin(); it != d.end(); it++)
		std::cout << *it << " ";
	std::cout <<std::endl;
}

template <typename Container>
void PmergeMe::printContainer(const Container& c) const
{
	std::cout << B "After:  ";
	typename Container::const_iterator it;
	for (it = c.begin(); it != c.end(); it++)
		std::cout << *it << " ";
	std::cout << RST << std::endl;
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

		// if (!seen.insert(nr).second) // return true or false - if duplicate throw an error 
		// 	throw std::runtime_error("Duplicate argument " + str); 
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
    //      PROCESS VECTOR
	clock_t startVec = clock();
	mergeInsertSortVector(v);
	clock_t endVec = clock();
	double vectorSortTime = static_cast<double>(endVec-startVec); // / CLOCKS_PER_SEC * 1e6; //timpul e in microsecunde

	printContainer(v);
	std::cout << "Time to process a range of " << v.size()
			<< " elements with std::vector: " << std::fixed << std::setprecision(5)
			<< vectorSortTime << " µs" << std::endl;

    //      PROCESS DEQUE
	clock_t startDeq = clock();
	mergeInsertSortDeque(d);
	clock_t endDeq = clock();
	double dequeSortTime = static_cast<double>(endDeq - startDeq);

	printContainer(d);
	std::cout << "Time to process a range of " << d.size()
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

void PmergeMe::insertion(int insertPoz, int pozGroup, int pairs, std::vector<int>& vec)
{
	std::vector<int> temp;	
	for (int p = 1; p <= pairs; p++)
		temp.push_back(vec[p + pozGroup - pairs]);
	for (int i = pozGroup; i > insertPoz; i--)
		vec[i] = vec[i - pairs];
	for (int i = 0; i < pairs; i++)
	{
		vec[insertPoz - i] = temp.back();
		temp.pop_back();
	}
}

static int checkInsertion(int pend, std::vector<int> vec, int pairs) // check where the group should be added inside main, return the poz
{
	for (int i = pairs - 1; i <= pend; i+= pairs)
	{
		if (vec[i] < vec[pend])
			continue;
		else
			return i;
	}
	return pend;
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& vec)
{
   	int level = 1;
	int pairs = 1;
	while (pairs * 2 <= static_cast<int>(vec.size())) // first faze of sorting by groups
	{
		for (int i = 0 ; i + pairs < static_cast<int>(vec.size()); i+= pairs * 2)
		{
			// Verificare de siguranță
			if (i + 2 * pairs > static_cast<int>(vec.size()))
				continue; // nu e o pereche completă		
			if(vec[i + pairs - 1] > vec[i + pairs * 2 - 1])
				swapV(i, i + pairs, pairs, vec); // pairs +2
		}
		pairs *= 2;
		level++;
	}
	
	while (level > 2)
	{
		int poz =(vec.size() / pairs) * pairs; //poz from where we have pending remaining items
		pairs /= 2;
		
		if ((static_cast<int>(vec.size()) - poz) >= pairs)
		{
			for (size_t i = poz + pairs - 1; i < vec.size(); i += pairs) //  pleaca de la 11 si de ver poz 7 restul de 3 elem
			{
				int insertPoz = checkInsertion(i, vec, pairs);
				// std::cout << "poz of insertion " << insertPoz << std::endl;
				insertion(insertPoz, i, pairs, vec);	
			}
		}
		level--;
	}

    if (vec.size() <= 1)
    return;
    
    std::vector<int> mainChain, pendChain;
    for (size_t i = 0; i + 1 < vec.size(); i+= 2)
    {
       int a = vec[i];
       int b = vec[i + 1];
       if (a < b)
       {
        pendChain.push_back(a);
        mainChain.push_back(b);
       }
       else
       {
        pendChain.push_back(b);
        mainChain.push_back(a);
       }
    }
    if (vec.size() % 2 != 0)
        mainChain.push_back(vec.back());

    mergeInsertSortVector(mainChain);

    for (size_t i = 0; i < pendChain.size(); i++)
    {
        int val = pendChain[i];
        std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), val);
        mainChain.insert(it, val);
    }
    vec = mainChain;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;

    std::deque<int> mainChain, pendChain;
    for (size_t i = 0; i + 1 < deq.size(); i+= 2)
    {
        int a = deq[i];
        int b = deq[i + 1];
        if (a < b)
        {
            pendChain.push_back(a);
            mainChain.push_back(b);
        }
        else
        {
            mainChain.push_back(a);
            pendChain.push_back(b);
        }
    }
    if (deq.size() % 2 != 0)
        mainChain.push_back(deq.back());

    mergeInsertSortDeque(mainChain);

    for (size_t i = 0; i < pendChain.size(); i++)
    {
        int val = pendChain[i];
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), val);
        mainChain.insert(it, val);
    }
    deq = mainChain;
}
