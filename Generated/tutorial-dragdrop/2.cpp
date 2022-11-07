# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{		
		if (DragDrop::HasNewFilePaths())
		{
			// ドロップされたアイテムの情報を消去
			DragDrop::Clear();

			// 消去されているので、何も取得されない
			for (const auto& dropped : DragDrop::GetDroppedFilePaths())
			{
				Print << dropped.path
					<< U" @" << dropped.pos
					<< U" :" << dropped.timeMillisec;
			}
		}
	}
}
