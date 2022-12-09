#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
	std::ifstream Input("input.txt");

	std::vector<std::vector<bool>> VisitedTiles;

	// Just make the starting point large enough so that the coordinates won't ever go negative
	constexpr std::size_t StartingPointX = 500;
	constexpr std::size_t StartingPointY = 500;

	constexpr std::size_t NumKnots = 10;

	std::size_t KnotsX[NumKnots];
	std::size_t KnotsY[NumKnots];

	for (std::size_t Index = 0; Index != NumKnots; ++Index)
	{
		KnotsX[Index] = StartingPointX;
		KnotsY[Index] = StartingPointY;
	}

	VisitedTiles.resize(StartingPointX + 1);
	VisitedTiles[StartingPointX].resize(StartingPointY + 1);
	VisitedTiles[StartingPointX][StartingPointY] = true;

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

		for (std::size_t StepIndex = 0; StepIndex != Steps; ++StepIndex)
		{
			KnotsX[0] += Direction.first;
			KnotsY[0] += Direction.second;

			for (std::size_t KnotIndex = 1; KnotIndex != NumKnots; ++KnotIndex)
			{
				std::intmax_t DeltaX = KnotsX[KnotIndex - 1] - KnotsX[KnotIndex];
				std::intmax_t DeltaY = KnotsY[KnotIndex - 1] - KnotsY[KnotIndex];

				if (std::abs(DeltaX) > 1 || std::abs(DeltaY) > 1)
				{
					KnotsX[KnotIndex] += (DeltaX > 0) - (DeltaX < 0);
					KnotsY[KnotIndex] += (DeltaY > 0) - (DeltaY < 0);
				}
			}

			const std::size_t LastKnotX = KnotsX[NumKnots - 1];
			const std::size_t LastKnotY = KnotsY[NumKnots - 1];

			VisitedTiles.resize(std::max(VisitedTiles.size(), LastKnotX + 1));
			VisitedTiles[LastKnotX].resize(std::max(VisitedTiles[LastKnotX].size(), LastKnotY + 1));

			VisitedTiles[LastKnotX][LastKnotY] = true;
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