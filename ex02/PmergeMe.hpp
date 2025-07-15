#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h> //atoi atol
#include <stdexcept> //try catch
#include <stdint.h> // pt INT32_MAX
#include <set>
#include <ctime>
#include <iomanip>

# define RST "\033[0m"    /* Reset to default color */
# define BOLD "\033[1m"   /* Bold */
# define U "\033[4m"      /* Underline */
# define RED "\033[1;31m" /* Red */
# define G "\033[1;32m"   /* Green */
# define Y "\033[1;33m"   /* Yellow */
# define B "\033[1;34m"   /* Blue */
# define M "\033[1;35m"   /* Magenta */
# define C "\033[1;36m"   /* Cyan */
# define W "\033[1;37m"   /* White */
# define PINK "\033[1;95m"        /* Pink (Bright Magenta) */
# define SALMON      "\033[38;5;210m" 
# define LIGHT_CORAL "\033[1;31m" /* Light Coral */


class PmergeMe
{
private:
	std::vector<int> v;
	std::deque<int> d;

public:
	PmergeMe(int ac, char** av);
    PmergeMe(const PmergeMe& pm);
    PmergeMe& operator=(const PmergeMe& pm);    
	void run();
	~PmergeMe();

	void printStackV();
	void printStackD();

	template <typename Container>
	void printContainer(const Container& c) const;

	void mergeInsertSortVector(std::vector<int>& vec);
	void mergeInsertSortDeque(std::deque<int>& deqCopy);

    void insertion(int insertPoz, int pozGroup, int pairs, std::vector<int>& vec);
};

