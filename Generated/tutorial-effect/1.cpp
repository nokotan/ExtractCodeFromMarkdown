# include <Siv3D.hpp>

void Main()
{
	Effect effect;

	while (System::Update())
	{
		ClearPrint();

		// アクティブなエフェクトの数
		Print << U"Active effects: {}"_fmt(effect.num_effects());

		if (MouseL.down())
		{
			// エフェクトを発生
			effect.add([pos = Cursor::Pos(), color = RandomColorF()](double t)
			{
				// 時間に応じて大きくなる輪
				Circle{ pos, (t * 100) }.drawFrame(4, color);

				// 1 秒未満なら継続
				return (t < 1.0);
			});
		}

		// アクティブなエフェクトのプログラム IEffect::update() を実行
		effect.update();
	}
}
