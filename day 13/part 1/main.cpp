#include <fstream>
#include <iostream>
#include <vector>

struct Object_t;
using List_t = std::vector<Object_t>;
using Integer_t = std::size_t;

struct Object_t
{
	bool IsList : 1;

	union
	{
		List_t* List;
		Integer_t Integer;
	};
};

std::istream& operator>>(std::istream& Input, Object_t& Object);

std::istream& operator>>(std::istream& Input, List_t& List)
{
	Input.ignore(1);

	while (Input.peek() != ']')
	{
		Input >> List.emplace_back();

		if (Input.peek() == ',')
		{
			Input.ignore(1);
		}
	}

	Input.ignore(1);

	return Input;
}

std::istream& operator>>(std::istream& Input, Object_t& Object)
{
	char PeekedChar = Input.peek();
	if (PeekedChar == '[')
	{
		Object.IsList = true;

		// lmao
		Object.List = new List_t;

		Input >> *Object.List;
	}
	else if (std::isdigit(PeekedChar))
	{
		Object.IsList = false;
		Input >> Object.Integer;
	}
	else
	{
		std::abort();
	}

	return Input;
}


enum class EComparisonResult
{
	Equal,
	LesserThan,
	GreaterThan,
};

EComparisonResult CompareObjects(const Object_t& FirstObject, const Object_t& SecondObject);

EComparisonResult CompareLists(const List_t& FirstList, const List_t& SecondList)
{
	for (std::size_t CurrentIndex = 0; ; ++CurrentIndex)
	{
		const bool ReachedFirstEnd = CurrentIndex == FirstList.size();
		const bool ReachedSecondEnd = CurrentIndex == SecondList.size();

		if (ReachedFirstEnd && ReachedSecondEnd)
		{
			return EComparisonResult::Equal;
		}

		if (ReachedFirstEnd)
		{
			return EComparisonResult::LesserThan;
		}

		if (ReachedSecondEnd)
		{
			return EComparisonResult::GreaterThan;
		}

		EComparisonResult Result = CompareObjects(FirstList[CurrentIndex], SecondList[CurrentIndex]);

		if (Result != EComparisonResult::Equal)
		{
			return Result;
		}
	}
}

EComparisonResult CompareObjects(const Object_t& FirstObject, const Object_t& SecondObject)
{
	if (FirstObject.IsList && SecondObject.IsList)
	{
		return CompareLists(*FirstObject.List, *SecondObject.List);
	}

	if (!FirstObject.IsList && !SecondObject.IsList)
	{
		return FirstObject.Integer == SecondObject.Integer ? EComparisonResult::Equal : 
		FirstObject.Integer < SecondObject.Integer ? EComparisonResult::LesserThan : EComparisonResult::GreaterThan;
	}

	if (FirstObject.IsList && !SecondObject.IsList)
	{
		List_t TempList;
		TempList.emplace_back(SecondObject);

		return CompareLists(*FirstObject.List, TempList);
	}

	if (!FirstObject.IsList && SecondObject.IsList)
	{
		List_t TempList;
		TempList.emplace_back(FirstObject);

		return CompareLists(TempList, *SecondObject.List);
	}

	std::abort();
}

int main()
{
	std::ifstream Input("input.txt");

	std::size_t SumOfIndices = 0;

	for (std::size_t PairIndex = 1; ; ++PairIndex)
	{
		List_t Lists[2];

		for (std::size_t LineIndex = 0; LineIndex != 2; ++LineIndex)
		{
			Input >> Lists[LineIndex];
			Input.ignore(1);
		}

		Input.ignore(1);

		const bool PairInRightOrder = CompareLists(Lists[0], Lists[1]) == EComparisonResult::LesserThan;

		SumOfIndices += PairIndex * PairInRightOrder;

		if (Input.peek() == EOF)
		{
			break;
		}
	}

	std::cout << SumOfIndices << std::endl;
}