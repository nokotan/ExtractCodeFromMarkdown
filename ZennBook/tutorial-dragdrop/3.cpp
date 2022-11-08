# include <Siv3D.hpp>

void Main()
{
	const Texture icon{ 0xf15b_icon, 40 };

	while (System::Update())
	{
		// ウィンドウ上でドラッグ中のアイテムがある
		if (const auto status = DragDrop::DragOver())
		{
			if (status->itemType == DragItemType::FilePaths)
			{
				// アイコンを表示
				icon.drawAt(status->cursorPos, ColorF{ 0.5 });
			}
		}

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
