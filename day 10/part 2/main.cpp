#include <fstream>
#include <iostream>
#include <vector>

int main()
{
	std::ifstream Input("input.txt");

	std::intmax_t X = 1;

	std::size_t CycleCount = 0;

	std::vector<bool> PixelMap;

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
			PixelMap.resize(CycleCount + 1);

			const std::intmax_t RowPosition = CycleCount % 40;

			PixelMap[CycleCount] = RowPosition == X || std::abs(RowPosition - X) == 1;

			CycleCount++;
		}

		X += Parameter;
	}

	for (std::size_t Index = 0; Index != PixelMap.size(); ++Index)
	{
		std::cout << (PixelMap[Index] ? '#' : '.');

		if ((Index + 1) % 40 == 0)
		{
			std::cout << std::endl;
		}
	}
}