# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 問題文のリスト
	const Array<String> texts =
	{
		U"Practice makes perfect.",
		U"Don't cry over spilt milk.",
		U"Faith will move mountains.",
		U"Nothing ventured, nothing gained.",
		U"Bad news travels fast.",
	};

	String target = texts.choice(), input;

	const Font font{ 40, Typeface::Bold };

	while (System::Update())
	{
		// テキスト入力（TextInputMode::DenyControl: エンターやタブ、バックスペースは受け付けない）
		TextInput::UpdateText(input, TextInputMode::DenyControl);

		// 誤った入力が含まれていたら削除
		while (not target.starts_with(input))
		{
			input.pop_back();
		}

		// 一致したら次の問題へ
		if (input == target)
		{
			target = texts.choice();
			input.clear();
		}

		font(target).draw(40, 270, ColorF{ 0.75 });

		font(input).draw(40, 270, ColorF{ 0.1 });
	}
}
