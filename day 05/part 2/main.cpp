#include <fstream>
#include <iostream>
#include <deque>
#include <limits>

int main()
{
	std::ifstream Input("input.txt");

	using Crate = char;
	using Stack = std::deque<Crate>;

	Stack Stacks[9]{};

	std::uintmax_t CurrentStack = 0;

	// Parse the stacks
	while (Input)
	{
		if (Input.get() == '[')
		{
			// Get the crate from the current cell
			Stacks[CurrentStack].emplace_back(Input.get());
			Input.ignore(1);
		}
		//if we found the end of the starting stacks input, skip two lines and proceed to the operations
		else if (isdigit(Input.peek()))
		{
			Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		else
		{
			// this should be two spaces
			Input.ignore(2);
		}

		CurrentStack++;

		if (Input.get() == '\n')
		{
			CurrentStack = 0;
		}
	}

	// Parse the stack operations
	while (Input.peek() != EOF)
	{
		std::uintmax_t CratesCount;
		std::size_t StartStackIndex, EndStackIndex;

		Input.ignore(5);
		Input >> CratesCount;
		Input.ignore(6);
		Input >> StartStackIndex;
		Input.ignore(4);
		Input >> EndStackIndex;
		Input.ignore(1);

		Stack TempStack;

		Stack& StartStack = Stacks[StartStackIndex - 1];
		Stack& EndStack = Stacks[EndStackIndex - 1];

		// Move all of the crates to a temporary stack, and then pop them in the same order later
		for (std::uintmax_t Index = 0; Index != CratesCount; ++Index)
		{
			Crate CurrentCrate = StartStack.front();
			StartStack.pop_front();
			TempStack.push_back(CurrentCrate);
		}

		while (!TempStack.empty())
		{
			EndStack.push_front(TempStack.back());
			TempStack.pop_back();
		}
	}

	for (auto& Stack : Stacks)
	{
		std::cout << Stack.front();
	}

	std::cout << std::endl;
}