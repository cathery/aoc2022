#include <fstream>
#include <iostream>
#include <deque>

int main()
{
	std::ifstream Input("input.txt");

	constexpr std::size_t PacketSize = 4;

	std::deque<char> Packet;

	std::uintmax_t CurrentLetterIndex = 0;

	while (true)
	{
		char CurrentLetter = Input.get();
		CurrentLetterIndex++;

		if (Packet.size() == PacketSize)
		{
			Packet.pop_back();
		}

		Packet.push_front(CurrentLetter);

		if (Packet.size() < PacketSize)
		{
			continue;
		}

		bool RepeatLetter = false;
		for (std::size_t FirstIndex = 0; FirstIndex != PacketSize - 1; ++FirstIndex)
		{
			for (std::size_t SecondIndex = FirstIndex + 1; SecondIndex != PacketSize; ++SecondIndex)
			{
				if (Packet[FirstIndex] == Packet[SecondIndex])
				{
					RepeatLetter = true;
					break;
				}
			}

			if (RepeatLetter)
			{
				break;
			}
		}

		if (!RepeatLetter)
		{
			break;
		}

		if (Input.eof())
		{
			std::abort();
		}
	}

	std::cout << CurrentLetterIndex << std::endl;
}