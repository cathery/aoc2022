#include <fstream>
#include <iostream>

int main()
{
	std::ifstream Input("input.txt");

	std::uint64_t CurrentTotalCalories = 0;
	std::uint64_t MaxTotalCalories = 0;

	std::uint64_t CurrentFoodCalories;

	while (Input.peek() != EOF)
	{
		while (Input.peek() != '\n' && Input.peek() != EOF)
		{
			Input >> CurrentFoodCalories;
			Input.ignore(1);

			CurrentTotalCalories += CurrentFoodCalories;
		}

		Input.ignore(1);

		if (CurrentTotalCalories > MaxTotalCalories)
		{
			MaxTotalCalories = CurrentTotalCalories;
		}

		CurrentTotalCalories = 0;
	}

	std::cout << MaxTotalCalories << std::endl;
}