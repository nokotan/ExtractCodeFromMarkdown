# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// down() / pressed() / up() のいずれかが true になっているキー一覧を取得
		const Array<Input> keys = Keyboard::GetAllInputs();

		for (const auto& key : keys)
		{
			Print << key.name() << (key.pressed() ? U" pressed" : U" up");
		}
	}
}
