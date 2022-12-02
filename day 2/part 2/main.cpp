#include <fstream>
#include <iostream>

enum class EResponse
{
	Rock = 1,
	Paper = 2,
	Scissors = 3,
};

enum class EGameResult
{
	Lose,
	Draw,
	Win,
};

constexpr std::uint64_t GameResultPoints[]{0,3,6};

constexpr std::uint64_t WinningResponse[]{0, 2, 3, 1};
constexpr std::uint64_t LosingResponse[]{0, 3, 1, 2};


std::uint64_t CalculatePoints(EResponse OpponentResponse, EGameResult RequiredResult)
{
	const std::uint64_t ResultPoints = GameResultPoints[static_cast<std::size_t>(RequiredResult)];
	std::uint64_t ResponsePoints = 0;

	switch (RequiredResult)
	{
	case EGameResult::Draw:
		ResponsePoints = static_cast<std::uint64_t>(OpponentResponse);
		break;
	case EGameResult::Win:
		ResponsePoints = WinningResponse[static_cast<std::size_t>(OpponentResponse)];
		break;
	case EGameResult::Lose:
		ResponsePoints = LosingResponse[static_cast<std::size_t>(OpponentResponse)];
		break;
	default:
		break;
	}

	return ResultPoints + ResponsePoints;
}

int main()
{
	std::ifstream Input("input.txt");

	std::uint64_t TotalScore = 0;

	while (Input.peek() != EOF)
	{
		EResponse OpponentResponse = static_cast<EResponse>(Input.get() - 64);
		Input.ignore(1);
		EGameResult RequiredResult = static_cast<EGameResult>(Input.get() - 88);
		Input.ignore(1);

		TotalScore += CalculatePoints(OpponentResponse, RequiredResult);
	}

	std::cout << TotalScore << std::endl;
}