# include <Siv3D.hpp>

void Main()
{
	const URL url = U"https://raw.githubusercontent.com/Siv3D/siv3d.docs.images/master/logo/logo.png";
	const FilePath saveFilePath = DateTime::Now().format(U"mmss\'.png\'");

	if (const auto response = SimpleHTTP::Save(url, saveFilePath))
	{
		Console << U"------";
		Console << response.getStatusLine().rtrimmed();
		Console << U"status code: " << FromEnum(response.getStatusCode());
		Console << U"------";
		Console << response.getHeader().rtrimmed();
		Console << U"------";
	}
	else
	{
		Print << U"Failed.";
	}

	Print << saveFilePath;
	const Texture texture{ saveFilePath };

	while (System::Update())
	{
		texture.draw();
	}
}
