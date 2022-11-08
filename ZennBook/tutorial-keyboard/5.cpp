# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// [Ctrl + C] または [Command + C] が押された
		if ((KeyControl + KeyC).down()
			|| (KeyCommand + KeyC).down())
		{
			Print << U"Ctrl + C / Command + C";
		}
	}
}
