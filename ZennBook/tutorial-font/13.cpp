# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50, Typeface::Bold };

	const String text = U"The quick brown fox\njumps over the lazy dog.";

	while (System::Update())
	{
		// 文字カウントを 0.1 秒ごとに増やす
		const size_t length = static_cast<size_t>(Scene::Time() / 0.1);

		// text の文字数以上の length は切り捨てられる
		font(text.substr(0, length)).draw(50, 50);
	}
}
