#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
	std::ifstream Input("input.txt");

	std::vector<std::vector<bool>> VisitedTiles;

	// Just make the starting point large enough so that the coordinates won't ever go negative
	std::size_t HeadX = 500;
	std::size_t HeadY = 500;

	std::size_t TailX = HeadX;
	std::size_t TailY = HeadY;

	VisitedTiles.resize(TailX + 1);
	VisitedTiles[TailX].resize(TailY + 1);
	VisitedTiles[TailX][TailY] = true;

	while (Input.peek() != EOF)
	{
		char Letter;
		std::uintmax_t Steps;

		Input >> Letter >> Steps;
		Input.ignore(1);

		static const std::unordered_map<char, std::pair<std::int8_t, std::int8_t>> Directions{
			{'U', {0, -1}},
			{'D', {0, 1}},
			{'L', {-1, 0}},
			{'R', {1, 0}},
		};

		const auto& Direction = Directions.at(Letter);

		for (std::size_t Index = 0; Index != Steps; ++Index)
		{
			HeadX += Direction.first;
			HeadY += Direction.second;

			std::intmax_t DeltaX = HeadX - TailX;
			std::intmax_t DeltaY = HeadY - TailY;

			if (std::abs(DeltaX) > 1 || std::abs(DeltaY) > 1)
			{
				TailX += (DeltaX > 0) - (DeltaX < 0);
				TailY += (DeltaY > 0) - (DeltaY < 0);

				VisitedTiles.resize(std::max(VisitedTiles.size(), TailX + 1));
				VisitedTiles[TailX].resize(std::max(VisitedTiles[TailX].size(), TailY + 1));

				VisitedTiles[TailX][TailY] = true;
			}
		}
	}

	std::size_t VisitedTileCount = 0;

	for (const auto& Row : VisitedTiles)
	{
		for (bool Tile : Row)
		{
			VisitedTileCount += Tile;
		}
	}

	std::cout << VisitedTileCount << std::endl;
}