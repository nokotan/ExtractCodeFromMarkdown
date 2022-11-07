# include <Siv3D.hpp>

void Main()
{
	const Array<String> animals = { U"cat", U"dog", U"bird" };

	for (auto [i, animal] : Indexed(animals))
	{
		Print << i << U": " << animal;
	}

	while (System::Update())
	{

	}
}
