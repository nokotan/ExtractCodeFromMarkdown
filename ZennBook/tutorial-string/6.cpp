# include <Siv3D.hpp>

void Main()
{
	const String text = U"Hello, Siv3D!";
	const std::string str = text.narrow();
	const std::wstring wstr = text.toWstr();

	Print << (str == "Hello, Siv3D!");
	Print << (wstr == L"Hello, Siv3D!");

	while (System::Update())
	{

	}
}
