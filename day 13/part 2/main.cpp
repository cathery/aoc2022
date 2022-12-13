#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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

	std::vector<List_t> Packets;

	List_t FirstDividerSubList{Object_t{.IsList = false, .Integer = 2}};
	List_t FirstDivider{Object_t{.IsList = true, .List = &FirstDividerSubList}};

	Packets.emplace_back(FirstDivider);

	List_t SecondDividerSubList{Object_t{.IsList = false, .Integer = 6}};
	List_t SecondDivider{Object_t{.IsList = true, .List = &SecondDividerSubList}};

	Packets.emplace_back(SecondDivider);

	for (std::size_t PairIndex = 1; ; ++PairIndex)
	{
		for (std::size_t LineIndex = 0; LineIndex != 2; ++LineIndex)
		{
			Input >> Packets.emplace_back();
			Input.ignore(1);
		}

		Input.ignore(1);

		if (Input.peek() == EOF)
		{
			break;
		}
	}

	std::sort(Packets.begin(), Packets.end(), [](const List_t& Left, const List_t& Right)
	{
		return CompareLists(Left, Right) == EComparisonResult::LesserThan;
	});

	std::size_t FirstIndex = 0;
	std::size_t SecondIndex = 0;

	for (std::size_t Index = 0; Index != Packets.size(); ++Index)
	{
		if (CompareLists(FirstDivider, Packets[Index]) == EComparisonResult::Equal)
		{
			FirstIndex = Index + 1;
		}
		else if (CompareLists(SecondDivider, Packets[Index]) == EComparisonResult::Equal)
		{
			SecondIndex = Index + 1;
		}
	}

	std::cout << FirstIndex * SecondIndex << std::endl;
}