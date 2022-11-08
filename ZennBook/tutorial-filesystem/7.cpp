# include <Siv3D.hpp>

void Main()
{
	for (const auto& path : FileSystem::DirectoryContents(U"example/font"))
	{
		Console << path;
	}

	Console << U"---";

	for (const auto& path : FileSystem::DirectoryContents(U"example/font", Recursive::No))
	{
		Console << path;
	}

	while (System::Update())
	{

	}
}
