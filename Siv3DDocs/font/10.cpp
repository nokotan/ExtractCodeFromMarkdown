# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50 };
	constexpr Vec2 pos{ 400,300 };
	const String text = U"Hello, Siv3D!";
	size_t index = 0;

	while (System::Update())
	{
		SimpleGUI::RadioButtons(index,
			{ U"topLeft", U"bottomLeft", U"bottomRight", U"bottomCenter", U"leftCenter", U"center" },
			Vec2{20,20});

		Circle{ pos, 2 }.draw(Palette::Red);

		if (index == 0)
		{
			font(text).draw(pos);
		}
		else if (index == 1)
		{
			// 左下を基準にする
			font(text).draw(Arg::bottomLeft = pos);
		}
		else if (index == 2)
		{
			// 右下を基準にする
			font(text).draw(Arg::bottomRight = pos);
		}
		else if (index == 3)
		{
			// 下辺中央を基準にする
			font(text).draw(Arg::bottomCenter = pos);
		}
		else if (index == 4)
		{
			// 左辺中央を基準
			font(text).draw(Arg::leftCenter = pos);
		}
		else
		{
			// 中央を基準
			font(text).drawAt(pos);
		}
	}
}
