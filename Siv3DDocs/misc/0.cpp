# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (SimpleGUI::Button(U"[0.0, 1.0)", Vec2{ 200, 20 }))
		{
			ClearPrint();

			for (int32 i = 0; i < 10; ++i)
			{
				// 0.0 以上 1.0 未満のランダムな double 型
				Print << Random();
			}
		}

		if (SimpleGUI::Button(U"int32", Vec2{ 200, 60 }))
		{
			ClearPrint();

			for (int32 i = 0; i < 10; ++i)
			{
				// 0～100 の範囲のランダムな整数
				Print << Random(100);
			}
		}

		if (SimpleGUI::Button(U"double", Vec2{ 200, 100 }))
		{
			ClearPrint();

			for (int32 i = 0; i < 10; ++i)
			{
				// -100.0～100.0 の範囲のランダムな浮動小数点数
				Print << Random(-100.0, 100.0);
			}
		}

		if (SimpleGUI::Button(U"char32", Vec2{ 200, 140 }))
		{
			ClearPrint();

			for (int32 i = 0; i < 10; ++i)
			{
				// A～Z の範囲のランダムな文字
				Print << Random(U'A', U'Z');
			}
		}
	}
}
