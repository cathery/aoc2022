#include <fstream>
#include <iostream>

int main()
{
	std::ifstream Input("input.txt");

	std::uintmax_t PairCount = 0;

	while (Input.peek() != EOF)
	{
		std::uintmax_t FirstMin, FirstMax, SecondMin, SecondMax;

		Input >> FirstMin;
		Input.ignore(1);
		Input >> FirstMax;
		Input.ignore(1);
		Input >> SecondMin;
		Input.ignore(1);
		Input >> SecondMax;
		Input.ignore(1);

		if ((FirstMin <= SecondMin && FirstMax >= SecondMax)
		|| (SecondMin <= FirstMin && SecondMax >= FirstMax)
		|| (FirstMin <= SecondMin && FirstMax >= SecondMin)
		|| (SecondMin <= FirstMin && SecondMax >= FirstMin))
		{
			PairCount++;
		}
	}

	std::cout << PairCount << std::endl;
}