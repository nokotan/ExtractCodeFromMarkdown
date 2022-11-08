# include <Siv3D.hpp>

void Main()
{
	// ファイルやディレクトリが存在するか
	Print << FileSystem::Exists(U"example/windmill.png");
	Print << FileSystem::Exists(U"example/video/");
	Print << FileSystem::Exists(U"aaa/bbb.txt");

	// ファイルが存在するか
	Print << FileSystem::IsFile(U"example/windmill.png");
	Print << FileSystem::IsFile(U"example/video/");
	Print << FileSystem::IsFile(U"aaa/bbb.txt");

	// ディレクトリが存在するか
	Print << FileSystem::IsDirectory(U"example/windmill.png");
	Print << FileSystem::IsDirectory(U"example/video/");
	Print << FileSystem::IsDirectory(U"aaa/bbb.txt");

	while (System::Update())
	{

	}
}
