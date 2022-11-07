# include <Siv3D.hpp>

void Main()
{
	// ファイルパスのドロップを受け付けないようにする
	DragDrop::AcceptFilePaths(false);

	while (System::Update())
	{		
		// 受け付けないので何もドロップされない
		if (DragDrop::HasNewFilePaths())
		{
			for (const auto& dropped : DragDrop::GetDroppedFilePaths())
			{
				Print << dropped.path
					<< U" @" << dropped.pos
					<< U" :" << dropped.timeMillisec;
			}
		}
	}
}
