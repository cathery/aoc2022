#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <algorithm>

enum class EOperationType
{
	AddToSelf,
	MultiplySelf,
	SquareSelf,
};

struct Item
{
	std::size_t WorryLevel;
};

struct Monkey
{
	std::deque<Item> Items;

	EOperationType OperationType;
	std::size_t OperationValue;

	std::size_t DivisibleByValue;

	std::size_t MonkeyToThrowToWhenSucceeded;
	std::size_t MonkeyToThrowToWhenFailed;
};

int main()
{
	std::ifstream Input("input.txt");

	std::vector<Monkey> Monkeys;

	// Parse the input
	while (Input.peek() != EOF)
	{
		Monkey& NewMonkey = Monkeys.emplace_back();

		// "Monkey X:\n"
		Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// "  Starting items: "
		Input.ignore(18);

		while (true)
		{
			Item NewItem;

			Input >> NewItem.WorryLevel;

			NewMonkey.Items.push_back(NewItem);

			if (Input.get() == '\n')
			{
				break;
			}
		}

		// "  Operation: new = old "
		Input.ignore(23);

		// read the operator and ignore a whitespace
		char Operator = Input.get();
		Input.ignore(1);

		// if the operation is "old * old"
		if (Input.peek() == 'o')
		{
			NewMonkey.OperationType = EOperationType::SquareSelf;

			// "old\n"
			Input.ignore(4);
		}
		else
		{
			NewMonkey.OperationType = Operator == '+' ? EOperationType::AddToSelf : EOperationType::MultiplySelf;
			Input >> NewMonkey.OperationValue;

			// "\n"
			Input.ignore(1);
		}

		// "  Test: divisible by X"
		Input.ignore(21);
		Input >> NewMonkey.DivisibleByValue;

		// "\n    If true: throw to monkey X\n"
		Input.ignore(30);
		Input >> NewMonkey.MonkeyToThrowToWhenSucceeded;

		// "\n    If false: throw to monkey X\n\n"
		Input.ignore(31);
		Input >> NewMonkey.MonkeyToThrowToWhenFailed;
		Input.ignore(2);
	}


	std::vector<std::size_t> InspectionCounts(Monkeys.size());

	// Simulate rounds
	for (std::size_t Round = 0; Round != 20; ++Round)
	{
		for (std::size_t CurrentMonkeyIndex = 0; CurrentMonkeyIndex != Monkeys.size(); ++CurrentMonkeyIndex)
		{
			Monkey& CurrentMonkey = Monkeys[CurrentMonkeyIndex];

			// Process each item the monkey is holding
			while (!CurrentMonkey.Items.empty())
			{
				Item CurrentItem = CurrentMonkey.Items.front();
				CurrentMonkey.Items.pop_front();

				switch (CurrentMonkey.OperationType)
				{
				case EOperationType::SquareSelf:
					CurrentItem.WorryLevel *= CurrentItem.WorryLevel;
					break;
				case EOperationType::MultiplySelf:
					CurrentItem.WorryLevel *= CurrentMonkey.OperationValue;
					break;
				case EOperationType::AddToSelf:
					CurrentItem.WorryLevel += CurrentMonkey.OperationValue;
					break;
				default:
					std::abort();
				}

				InspectionCounts[CurrentMonkeyIndex]++;

				CurrentItem.WorryLevel /= 3;

				const bool TestSucceeded = CurrentItem.WorryLevel % CurrentMonkey.DivisibleByValue == 0;
				const std::size_t MonkeyToPassTo = TestSucceeded ? CurrentMonkey.MonkeyToThrowToWhenSucceeded : CurrentMonkey.MonkeyToThrowToWhenFailed;

				Monkeys[MonkeyToPassTo].Items.push_back(CurrentItem);
			}
		}
	}

	std::sort(InspectionCounts.rbegin(), InspectionCounts.rend());

	std::size_t MonkeyBusiness = 1;
	for (std::size_t Index = 0; Index != 2; ++Index)
	{
		MonkeyBusiness *= InspectionCounts[Index];
	}

	std::cout << MonkeyBusiness << std::endl;
}