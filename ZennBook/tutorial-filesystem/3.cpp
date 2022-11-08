# include <Siv3D.hpp>

void Main()
{
	// 親ディレクトリを取得
	Print << FileSystem::ParentPath(U"example/windmill.png");
	Print << FileSystem::ParentPath(U"example/video/river.mp4");
	Print << FileSystem::ParentPath(U"./");

	while (System::Update())
	{

	}
}
