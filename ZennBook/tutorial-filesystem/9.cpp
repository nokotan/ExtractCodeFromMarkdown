# include <Siv3D.hpp>

void Main()
{
	// ディレクトリを作成
	FileSystem::CreateDirectories(U"bbb/");

	// bbb/ ディレクトリ内でのイベントを監視
	const DirectoryWatcher watcher{ U"bbb/" };

	while (System::Update())
	{
		// 絶対パスと、アクションの内容
		for (auto [path, action] : watcher.retrieveChanges())
		{
			Print << path;

			if (action == FileAction::Added)
			{
				Print << U"Added";
			}
			else if (action == FileAction::Removed)
			{
				Print << U"Removed";
			}
			else if (action == FileAction::Modified)
			{
				Print << U"Modified";
			}
			if (action == FileAction::Unknown)
			{
				Print << U"Unknown";
			}
		}
	}
}
