# include <Siv3D.hpp>

void Main()
{
	// 絶対パスを取得
	Print << FileSystem::FullPath(U"example/windmill.png");
	Print << FileSystem::FullPath(U"example/video/");

	while (System::Update())
	{

	}
}
