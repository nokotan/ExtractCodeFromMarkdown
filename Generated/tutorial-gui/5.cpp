# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	TextEditState te0, te1;

	bool avtivateNextTextBox = false;

	while (System::Update())
	{
		// Tab キーの押下と同じフレームで次のテキストボックスをアクティブ化してしまうと
		// その Tab キーの押下でそのテキストボックスも非アクティブ化してしまうため、1 フレーム後にアクティブ化
		if (avtivateNextTextBox)
		{
			// テキストボックスをアクティブ化
			te1.active = true;

			avtivateNextTextBox = false;
		}

		const bool previous = te0.active;

		SimpleGUI::TextBox(te0, Vec2{ 100, 100 }, 200);

		// 非アクティブ化された
		if (previous && (te0.active == false))
		{
			// Tab キーが入力されていた場合、次のテキストボックスをアクティブ化するフラグを true に
			avtivateNextTextBox = TextInput::GetRawInput().includes(U'\t');
		}

		SimpleGUI::TextBox(te1, Vec2{ 100, 140 }, 200);
	}
}
