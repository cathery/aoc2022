#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

int main()
{
	std::ifstream Input("input.txt");

	std::uint64_t CurrentTotalCalories = 0;
	std::array<std::uint64_t, 3> TopElvesMaxTotalCalories{};

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

		std::sort(TopElvesMaxTotalCalories.begin(), TopElvesMaxTotalCalories.end());

		if (CurrentTotalCalories > TopElvesMaxTotalCalories[0])
		{
			TopElvesMaxTotalCalories[0] = CurrentTotalCalories;
		}

		CurrentTotalCalories = 0;
	}

	std::uint64_t TotalDeerMaxCalories = 0;
	for (const auto ElfMaxTotalCalories : TopElvesMaxTotalCalories)
	{
		TotalDeerMaxCalories += ElfMaxTotalCalories;
	}

	std::cout << TotalDeerMaxCalories << std::endl;
}