# include <Siv3D.hpp>

void Main()
{
	// 桁区切りを入れる
	Print << ThousandsSeparate(123456789);
	Print << ThousandsSeparate(-123456789);
	Print << ThousandsSeparate(1234567.89);

	while (System::Update())
	{

	}
}
