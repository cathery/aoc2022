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

	constexpr std::size_t RucksacksPerGroup = 3;

	std::string CurrentRucksackGroup[RucksacksPerGroup]{};

	while (Input.peek() != EOF)
	{
		for (auto& CurrentRucksack : CurrentRucksackGroup)
		{
			Input >> CurrentRucksack;
			Input.ignore(1);
		}

		bool BreakCondition = false;
		std::uint8_t UniqueLetterCounts[52]{};

		for (const auto& CurrentRucksack : CurrentRucksackGroup)
		{
			bool UniqueLetters[52]{};
			for (auto CurrentLetter : CurrentRucksack)
			{
				const std::uintmax_t LetterPriority = GetPriority(CurrentLetter);
				const std::uintmax_t LetterIndex = LetterPriority - 1;
				
				if (!UniqueLetters[LetterIndex])
				{
					UniqueLetters[LetterIndex] = true;
					UniqueLetterCounts[LetterIndex]++;

					if (UniqueLetterCounts[LetterIndex] >= RucksacksPerGroup)
					{
						PrioritySum += LetterPriority;
						BreakCondition = true;
						break;
					}
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