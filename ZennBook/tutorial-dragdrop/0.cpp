# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{		
		if (DragDrop::HasNewFilePaths())
		{
			for (const auto& dropped : DragDrop::GetDroppedFilePaths())
			{
				Print << dropped.path // ファイルやディレクトリの絶対パス
					<< U" @" << dropped.pos // ドロップされた座標
					<< U" :" << dropped.timeMillisec; // ドロップされたタイミング（Time::GetMillisec())
			}
		}
	}
}
