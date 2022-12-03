#include <fstream>
#include <iostream>

std::uintmax_t GetPriority(char Letter)
{
	if (Letter >= 'A' && Letter <= 'Z')
	{
		return Letter - 38;
	}
	else if (Letter >= 'a' && Letter <= 'z')
	{
		return Letter - 96;
	}

	std::abort();
}

int main()
{
	std::ifstream Input("input.txt");

	std::uintmax_t PrioritySum = 0;

	std::string CurrentRucksack;

	while (Input >> CurrentRucksack)
	{
		const std::size_t CompartmentSize = CurrentRucksack.length() / 2;
		std::string_view FirstHalf(CurrentRucksack.data(), CompartmentSize);
		std::string_view SecondHalf(CurrentRucksack.data() + CompartmentSize, CompartmentSize);

		bool BreakCondition = false;
		for (auto FirstHalfLetter : FirstHalf)
		{
			for (auto SecondHalfLetter : SecondHalf)
			{
				if (FirstHalfLetter == SecondHalfLetter)
				{
					BreakCondition = true;
					PrioritySum += GetPriority(FirstHalfLetter);
					break;
				}
			}

			if (BreakCondition)
			{
				break;
			}
		}
	}

	std::cout << PrioritySum << std::endl;
}