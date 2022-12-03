#include <fstream>
#include <iostream>

enum class EResponse
{
	Rock = 1,
	Paper = 2,
	Scissors = 3,
};

constexpr std::uint64_t WinPoints = 6;
constexpr std::uint64_t DrawPoints = 3;
constexpr std::uint64_t LosePoints = 0;

std::uint64_t CalculatePoints(EResponse OpponentResponse, EResponse YourResponse)
{
	std::uint64_t GameResultPoints = LosePoints;

	if (OpponentResponse == YourResponse)
	{
		GameResultPoints = DrawPoints;
	}
	else if (YourResponse == EResponse::Paper && OpponentResponse == EResponse::Rock
		|| YourResponse == EResponse::Scissors && OpponentResponse == EResponse::Paper
		|| YourResponse == EResponse::Rock && OpponentResponse == EResponse::Scissors)
	{
		GameResultPoints = WinPoints;
	}

	return static_cast<std::uint64_t>(YourResponse) + GameResultPoints;
}

int main()
{
	std::ifstream Input("input.txt");

	std::uint64_t TotalScore = 0;

	while (Input.peek() != EOF)
	{
		EResponse OpponentResponse = static_cast<EResponse>(Input.get() - 64);
		Input.ignore(1);

		EResponse YourResponse = static_cast<EResponse>(Input.get() - 87);
		Input.ignore(1);

		TotalScore += CalculatePoints(OpponentResponse, YourResponse);
	}

	std::cout << TotalScore << std::endl;
}