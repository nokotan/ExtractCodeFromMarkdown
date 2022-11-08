# include <Siv3D.hpp>

void Main()
{
	for (const auto& path : EnumResourceFiles())
	{
		Console << path;
	}

	while (System::Update())
	{

	}
}
