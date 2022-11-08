# include <Siv3D.hpp>

void Main()
{
	Window::Resize(800, 800);

	const Array<String> indices = Range(0, (Gamepad.MaxPlayerCount - 1)).map(Format);

	// ゲームパッドのプレイヤーインデックス
	size_t playerIndex = 0;

	while (System::Update())
	{
		ClearPrint();

		if (const auto gamepad = Gamepad(playerIndex)) // 接続されていたら
		{
			const auto& info = gamepad.getInfo();

			Print << U"{} (VID: {}, PID: {})"_fmt(info.name, info.vendorID, info.productID);

			for (auto [i, button] : Indexed(gamepad.buttons))
			{
				Print << U"button{}: {}"_fmt(i, button.pressed());
			}

			for (auto [i, axe] : Indexed(gamepad.axes))
			{
				Print << U"axe{}: {}"_fmt(i, axe);
			}

			Print << U"POV: " << gamepad.povD8();
		}

		SimpleGUI::RadioButtons(playerIndex, indices, Vec2{ 500, 20 });
	}
}
