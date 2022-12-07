#include <fstream>
#include <iostream>
#include <unordered_map>

struct File
{
	std::size_t Size;
};

struct Directory
{
	Directory* ParentDirectory = nullptr;
	std::unordered_map<std::string, Directory> Subdirectories;
	std::unordered_map<std::string, File> Files;
};

Directory RootDirectory;
Directory* CurrentDirectory = nullptr;

void MoveUpDirectory()
{
	CurrentDirectory = CurrentDirectory->ParentDirectory;
}

void MoveToRootDirectory()
{
	CurrentDirectory = &RootDirectory;
}

void MoveToSubdirectory(const std::string& SubdirectoryName)
{
	CurrentDirectory = &CurrentDirectory->Subdirectories[SubdirectoryName];
}

void AddDirectory(const std::string& SubdirectoryName)
{
	CurrentDirectory->Subdirectories.emplace(SubdirectoryName, Directory{.ParentDirectory = CurrentDirectory});
}

void AddFile(const std::string& FileName, std::size_t FileSize)
{
	CurrentDirectory->Files.emplace(FileName, File{.Size = FileSize});
}

std::size_t GetSizeOfDirectory(const Directory& TargetDirectory)
{
	std::size_t TotalSum = 0;

	for (const auto& [FileName, File] : TargetDirectory.Files)
	{
		TotalSum += File.Size;
	}

	for (const auto& [SubdirectoryName, Subdirectory] : TargetDirectory.Subdirectories)
	{
		TotalSum += GetSizeOfDirectory(Subdirectory);
	}

	return TotalSum;
}

std::size_t SumTotalOfSmallDirectories(const Directory& TargetDirectory)
{
	constexpr std::size_t MaxTotalSize = 100000;

	std::size_t TotalSum = 0;

	const std::size_t SelfSize = GetSizeOfDirectory(TargetDirectory);

	if (SelfSize < MaxTotalSize)
	{
		TotalSum += SelfSize;
	}

	for (const auto& [SubdirectoryName, Subdirectory] : TargetDirectory.Subdirectories)
	{
		TotalSum += SumTotalOfSmallDirectories(Subdirectory);
	}

	return TotalSum;
}

int main()
{
	std::ifstream Input("input.txt");

	while (Input)
	{
		const char PeekedChar = Input.peek();

		if (PeekedChar == '$')
		{
			// ignore "$ "
			Input.ignore(2);

			std::string Command;
			Input >> Command;

			if (Command == "cd")
			{
				std::string DirectoryName;
				Input >> DirectoryName;

				if (DirectoryName == "..")
				{
					MoveUpDirectory();
				}
				else if (DirectoryName[0] == '/')
				{
					MoveToRootDirectory();
				}
				else
				{
					MoveToSubdirectory(DirectoryName);
				}
			}
		}
		else if (PeekedChar == 'd')
		{
			// ignore "dir "
			Input.ignore(4);

			std::string DirectoryName;
			Input >> DirectoryName;

			AddDirectory(DirectoryName);
		}
		else if (std::isdigit(PeekedChar))
		{
			std::size_t FileSize;
			std::string FileName;

			Input >> FileSize >> FileName;

			AddFile(FileName, FileSize);
		}
		else if (PeekedChar == EOF)
		{
			break;
		}
		else
		{
			std::abort();
		}

		// ignore the \n
		Input.ignore(1);
	}

	std::cout << SumTotalOfSmallDirectories(RootDirectory) << std::endl;
}