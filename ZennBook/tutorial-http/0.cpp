# include <Siv3D.hpp>

void Main()
{
	// Siv3D のロゴ
	const URL url = U"https://raw.githubusercontent.com/Siv3D/siv3d.docs.images/master/logo/logo.png";
	const FilePath saveFilePath = U"logo.png";
	Texture texture;

	// ファイルを同期ダウンロード
	// ステータスコードが 200 (OK) なら
	if (SimpleHTTP::Save(url, saveFilePath).isOK())
	{
		texture = Texture{ saveFilePath };
	}
	else
	{
		Print << U"Failed.";
	}

	while (System::Update())
	{
		if (texture)
		{
			texture.draw();
		}
	}
}
