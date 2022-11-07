# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// down() / pressed() / up() のいずれかが true になっているマウスボタン一覧を取得
		const Array<Input> buttons = Mouse::GetAllInputs();

		for (const auto& button : buttons)
		{
			Print << button.name() << (button.pressed() ? U" pressed" : U" up");
		}
	}
}
