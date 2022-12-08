#include <fstream>
#include <iostream>
#include <vector>

int main()
{
	std::ifstream Input("input.txt");

	std::vector<std::vector<std::uint8_t>> Trees;

	std::size_t CurrentX = 0;
	std::size_t CurrentY = 0;

	while (true)
	{
		const char CurrentChar = Input.get();

		if (CurrentChar == EOF)
		{
			break;
		}
		else if (CurrentChar == '\n')
		{
			CurrentX = 0;
			CurrentY++;
			continue;
		}
		else
		{
			Trees.resize(CurrentY + 1);
			Trees[CurrentY].resize(CurrentX + 1);
			Trees[CurrentY][CurrentX] = CurrentChar - '0';
			CurrentX++;
		}
	}

	const std::size_t VerticalSize = Trees.size();
	const std::size_t HorizontalSize = Trees[0].size();

	std::size_t VisibleTrees = (VerticalSize * 2) + (HorizontalSize * 2) - 4;

	for (std::size_t VerticalIndex = 1; VerticalIndex != VerticalSize - 1; ++VerticalIndex)
	{
		for (std::size_t HorizontalIndex = 1; HorizontalIndex != HorizontalSize - 1; ++HorizontalIndex)
		{
			const std::uint8_t CurrentTree = Trees[VerticalIndex][HorizontalIndex];

			constexpr std::pair<std::int8_t, std::int8_t> Directions[]{
				{-1, 0},
				{0, -1},
				{1, 0},
				{0, 1},
			};

			for (const auto& Direction : Directions)
			{
				bool IsTreeVisible = true;

				std::size_t AdjacentY = VerticalIndex;
				std::size_t AdjacentX = HorizontalIndex;

				while (AdjacentY != 0 && AdjacentY != VerticalSize - 1 && AdjacentX != 0 && AdjacentX != HorizontalSize - 1)
				{
					AdjacentY += Direction.first;
					AdjacentX += Direction.second;

					if (Trees[AdjacentY][AdjacentX] >= CurrentTree)
					{
						IsTreeVisible = false;
						break;
					}
				}

				if (IsTreeVisible)
				{
					VisibleTrees++;
					break;
				}
			}
		}
	}

	std::cout << VisibleTrees << std::endl;
}