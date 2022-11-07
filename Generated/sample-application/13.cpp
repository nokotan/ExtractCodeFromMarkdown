# include <Siv3D.hpp>

void Main()
{
	Texture texture;

	while (System::Update())
	{
		// ファイルがドロップされた
		if (DragDrop::HasNewFilePaths())
		{
			// ファイルを画像として読み込めた
			if (const Image image{ DragDrop::GetDroppedFilePaths().front().path })
			{
				// 画面のサイズに合うように画像を拡大縮小
				texture = Texture{ image.fitted(Scene::Size()) };
			}
		}

		if (texture)
		{
			texture.drawAt(Scene::Center());
		}
	}
}
