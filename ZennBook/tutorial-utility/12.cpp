# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// テキストを表示
		PutText(DateTime::Now().format(), Scene::Center());
		PutText(U"Hello, Siv3D!", Arg::topLeft = Cursor::Pos());
	}
}
