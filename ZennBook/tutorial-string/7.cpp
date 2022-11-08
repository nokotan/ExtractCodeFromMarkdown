# include <Siv3D.hpp>

void Main()
{
	const std::string str = "Siv3D";
	const std::wstring wstr = L"Siv3D";

	const String text1 = Unicode::Widen(str);
	const String text2 = Unicode::FromWstring(wstr);

	Print << text1;
	Print << text2;

	while (System::Update())
	{

	}
}
