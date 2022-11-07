# include <Siv3D.hpp>

void Main()
{
	constexpr Rect rect{ 100, 350, 500, 200 };

	while (System::Update())
	{
		// RectF(100, 100, 200, 100) の角を 10px 丸めた角丸長方形
		RoundRect{ 100, 100, 200, 100, 10 }.draw();

		// RectF(Arg::center(400, 300), 200, 80) の角を 5px 丸めた角丸長方形
		RoundRect{ Arg::center(400, 300), 200, 80, 5 }.draw(Palette::Skyblue);

		// 長方形 rect の角を 40px 丸めた角丸長方形
		rect.rounded(40).draw(Palette::Orange);
	}
}
