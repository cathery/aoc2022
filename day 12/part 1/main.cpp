#include <fstream>
#include <iostream>
#include <vector>

std::size_t MapHeight = 0;
std::size_t MapWidth = 0;

std::vector<std::size_t> Tiles;
std::vector<std::size_t> Steps;

std::size_t StartingIndex = 0;
std::size_t EndingIndex = 0;

std::size_t GetIndex(std::size_t YIndex, std::size_t XIndex)
{
	return YIndex * MapWidth + XIndex;
}

void TraverseMap(std::size_t CurrentIndex, std::size_t StepsTaken)
{
	const std::size_t CurrentTile = Tiles[CurrentIndex];
	if (Steps[CurrentIndex] <= StepsTaken)
	{
		return;
	}

	Steps[CurrentIndex] = StepsTaken++;

	if (CurrentIndex == EndingIndex)
	{
		return;
	}

	std::size_t YIndex = CurrentIndex / MapWidth;
	std::size_t XIndex = CurrentIndex % MapWidth;


	if (YIndex != 0)
	{
		const std::size_t NextIndex = GetIndex(YIndex - 1, XIndex);
		const std::size_t NextTile = Tiles[NextIndex];
		if (NextTile < CurrentTile || NextTile - CurrentTile <= 1)
		{
			TraverseMap(NextIndex, StepsTaken);
		}
	}

	if (XIndex != 0)
	{
		const std::size_t NextIndex = GetIndex(YIndex, XIndex - 1);
		const std::size_t NextTile = Tiles[NextIndex];
		if (NextTile < CurrentTile || NextTile - CurrentTile <= 1)
		{
			TraverseMap(NextIndex, StepsTaken);
		}
	}

	if (YIndex != MapHeight - 1)
	{
		const std::size_t NextIndex = GetIndex(YIndex + 1, XIndex);
		const std::size_t NextTile = Tiles[NextIndex];
		if (NextTile < CurrentTile || NextTile - CurrentTile <= 1)
		{
			TraverseMap(NextIndex, StepsTaken);
		}
	}

	if (XIndex != MapWidth - 1)
	{
		const std::size_t NextIndex = GetIndex(YIndex, XIndex + 1);
		const std::size_t NextTile = Tiles[NextIndex];
		if (NextTile < CurrentTile || NextTile - CurrentTile <= 1)
		{
			TraverseMap(NextIndex, StepsTaken);
		}
	}
}

int main()
{
	std::ifstream Input("input.txt");

	std::size_t YIndex = 0;
	std::size_t XIndex = 0;

	std::size_t StartingY = 0;
	std::size_t StartingX = 0;

	std::size_t EndingY = 0;
	std::size_t EndingX = 0;

	while (true)
	{
		char CurrentLetter = Input.get();

		if (CurrentLetter == EOF)
		{
			break;
		}

		if (CurrentLetter == '\n')
		{
			MapWidth = XIndex;
			YIndex++;
			XIndex = 0;
			continue;
		}

		if (CurrentLetter == 'S')
		{
			CurrentLetter = 'a';
			StartingY = YIndex;
			StartingX = XIndex;
		}

		else if (CurrentLetter == 'E')
		{
			CurrentLetter = 'z';
			EndingY = YIndex;
			EndingX = XIndex;
		}

		Tiles.push_back(CurrentLetter - 'a');
		XIndex++;
	}

	MapHeight = YIndex;

	StartingIndex = GetIndex(StartingY, StartingX);
	EndingIndex = GetIndex(EndingY, EndingX);

	Steps.resize(Tiles.size(), -1);

	TraverseMap(StartingIndex, 0);

	std::cout << Steps[EndingIndex] << std::endl;
}