# include <Siv3D.hpp>

void Main()
{
	// ファイル名を取得
	Print << FileSystem::FileName(U"example/windmill.png");

	// 拡張子を除いたファイル名を取得
	Print << FileSystem::BaseName(U"example/windmill.png");

	// 拡張子を小文字で取得
	Print << FileSystem::Extension(U"example/windmill.png");

	while (System::Update())
	{

	}
}
