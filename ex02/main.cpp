#include "PmergeMe.hpp"

int main(int ac, char* argv[])
{
	if (ac < 2)
	{
		std::cerr << "Error: The arguments are missing.\n";
		return 1;
	}
	try
	{
		PmergeMe sorting(ac, argv);
		sorting.printStackV();
		sorting.printStackD();
		sorting.run();
		
	}
	catch(const std::exception& e)
	{
		std::cerr <<"Error: " << e.what() << '\n';
	}
	
	return(0);
}