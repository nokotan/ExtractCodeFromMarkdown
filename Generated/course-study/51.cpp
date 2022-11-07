# include <Siv3D.hpp>

void Main()
{
	const Font font{ 30 };

	String text;

	constexpr Rect area{ 50, 50, 700, 300 };

	while (System::Update())
	{
		// キーボードからテキストを入力
		TextInput::UpdateText(text);

		// 未変換の文字入力を取得
		const String editingText = TextInput::GetEditingText();

		area.draw(ColorF{ 0.3 });

		font(text + U'|' + editingText).draw(area.stretched(-20));
	}
}
