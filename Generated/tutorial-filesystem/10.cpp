# include <Siv3D.hpp>

void Main()
{
	// 更新を検出したいファイルのパス
	const FilePath filePath = U"bbb/test.txt";

	// 絶対パス
	const FilePath fullPath = FileSystem::FullPath(filePath);

	// 親ディレクトリ
	const FilePath parentDirectory = FileSystem::ParentPath(filePath);

	// 親ディレクトリを監視
	const DirectoryWatcher watcher{ parentDirectory };

	if (not watcher)
	{
		// ディレクトリが存在しない
		return;
	}

	while (System::Update())
	{
		for (auto [path, action] : watcher.retrieveChanges())
		{
			if ((path == fullPath)
				&& (action == FileAction::Added || action == FileAction::Modified))
			{
				Print << U"updated!";
			}
		}
	}
}
