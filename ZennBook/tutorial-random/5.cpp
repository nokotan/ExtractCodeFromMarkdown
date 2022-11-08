# include <Siv3D.hpp>

void Main()
{
	Array<ColorF> colors;

	for (int32 i = 0; i < 10; ++i)
	{
		// ランダムな色
		colors << RandomColor();
	}

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 20, 20 }))
		{
			for (auto& color : colors)
			{
				color = RandomColor();
			}
		}

		for (size_t i : step(colors.size()))
		{
			Circle{ (50 + i * 50.0), 100, 20 }.draw(colors[i]);
		}
	}
}
