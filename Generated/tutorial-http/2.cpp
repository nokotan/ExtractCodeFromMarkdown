# include <Siv3D.hpp>

void Main()
{
	const URL url = U"https://raw.githubusercontent.com/Siv3D/siv3d.docs.images/master/logo/logo.png";
	const FilePath saveFilePath = U"logo2.png";
	Texture texture;

	// ファイルの非同期ダウンロードを開始
	AsyncHTTPTask task = SimpleHTTP::SaveAsync(url, saveFilePath);

	while (System::Update())
	{
		// 非同期タスクが完了した
		if (task.isReady())
		{
			// レスポンスが 200 (OK) なら
			if (task.getResponse().isOK())
			{
				texture = Texture{ saveFilePath };
			}
			else
			{
				Print << U"Failed.";
			}
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
