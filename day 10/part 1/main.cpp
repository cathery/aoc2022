#include <fstream>
#include <iostream>

int main()
{
	std::ifstream Input("input.txt");

	std::intmax_t X = 1;

	std::size_t CycleCount = 0;

	std::intmax_t SignalStrengthSum = 0;

	while (Input.peek() != EOF)
	{
		std::intmax_t Parameter = 0;
		std::size_t CyclesToComplete;

		// addx
		if (Input.get() == 'a')
		{
			Input.ignore(4);
			Input >> Parameter;
			Input.ignore(1);

			CyclesToComplete = 2;
		}
		// noop
		else
		{
			Input.ignore(4);

			CyclesToComplete = 1;
		}

		for (std::size_t Cycle = 0; Cycle != CyclesToComplete; ++Cycle)
		{
			CycleCount++;

			if (CycleCount == 20 || (CycleCount > 20 && (CycleCount - 20) % 40 == 0))
			{
				const std::intmax_t SignalStrength = X * CycleCount;

				SignalStrengthSum += SignalStrength;
			}
		}

		X += Parameter;
	}

	std::cout << SignalStrengthSum << std::endl;
}