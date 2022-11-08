# include <Siv3D.hpp>

void Main()
{
	// 選択肢
	const Array<String> options =
	{
		U"$0",
		U"$1",
		U"$5",
		U"$20",
		U"$100",
		U"$500",
		U"$2000",
	};

	// 選択肢に対応する確率分布
	// （$0 は $2000 よりも 1000 倍出やすい）
	DiscreteDistribution distribution(
	{
		1000,
		200,
		50,
		10,
		5,
		2,
		1,
	});

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 200, 20 }))
		{
			ClearPrint();

			for (int32 i = 0; i < 10; ++i)
			{
				// 確率分布に基づいてランダムに選択
				Print << DiscreteSample(options, distribution);
			}
		}
	}
}
