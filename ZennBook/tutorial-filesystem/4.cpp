# include <Siv3D.hpp>

void Main()
{
	// ファイルのサイズを取得
	Print << FileSystem::FileSize(U"example/windmill.png");

	// ディレクトリのサイズを取得
	Print << FileSystem::Size(U"example/");

	while (System::Update())
	{

	}
}
