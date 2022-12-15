#include <fstream>
#include <iostream>
#include <vector>

int main()
{
	std::ifstream Input("input.txt");

	constexpr std::size_t SandSourceX = 500;
	constexpr std::size_t SandSourceY = 0;

	constexpr std::size_t MaxWidth = 750;
	constexpr std::size_t MaxHeight = 250;

	std::vector<std::vector<bool>> RockFormations;

	RockFormations.resize(MaxHeight);
	
	for (auto& Row : RockFormations)
	{
		Row.resize(MaxWidth);
	}

	bool FirstPoint = true;

	// process input rock formations
	while (Input.peek() != EOF)
	{
		std::size_t PreviousCoordinateX, PreviousCoordinateY;
		while (true)
		{
			std::size_t CoordinateX, CoordinateY;
			Input >> CoordinateX;
			Input.ignore(1);
			Input >> CoordinateY;

			if (!FirstPoint)
			{
				std::size_t IndexX = PreviousCoordinateX;
				std::size_t IndexY = PreviousCoordinateY;

				const std::intmax_t StepX = (CoordinateX > PreviousCoordinateX) - (CoordinateX < PreviousCoordinateX);
				const std::intmax_t StepY = (CoordinateY > PreviousCoordinateY) - (CoordinateY < PreviousCoordinateY);

				while (true)
				{
					RockFormations[IndexY][IndexX] = true;

					if (IndexX == CoordinateX && IndexY == CoordinateY)
					{
						break;
					}

					IndexX += StepX;
					IndexY += StepY;
				}
			}

			PreviousCoordinateX = CoordinateX;
			PreviousCoordinateY = CoordinateY;
			FirstPoint = false;

			if (Input.peek() == '\n')
			{
				FirstPoint = true;
				Input.ignore(1);
				break;
			}

			Input.ignore(4);
		}
	}

	
	std::size_t SandUnitsAtRest = 0;
	bool FellIntoAbyss = false;

	// time to simulate the sand
	while (!FellIntoAbyss)
	{
		// spawn sand
		std::size_t SandIndexX = SandSourceX;
		std::size_t SandIndexY = SandSourceY;

		// simulate falling
		while (true)
		{
			if (RockFormations[SandIndexY + 1][SandIndexX] == false)
			{
				if (SandIndexY >= 200)
				{
					FellIntoAbyss = true;
					break;
				}

				SandIndexY++;
				continue;
			}

			if (RockFormations[SandIndexY + 1][SandIndexX - 1] == false)
			{
				SandIndexX--;
				SandIndexY++;
				continue;
			}

			if (RockFormations[SandIndexY + 1][SandIndexX + 1] == false)
			{
				SandIndexX++;
				SandIndexY++;
				continue;
			}

			// we can assume the sand is at rest here
			// the resting sand can be treated as a rock
			RockFormations[SandIndexY][SandIndexX] = true;
			SandUnitsAtRest++;
			break;
		}
	}

	std::cout << SandUnitsAtRest << std::endl;
}