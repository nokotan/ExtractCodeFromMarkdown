#include <Siv3D.hpp>

void Main()
{
	// PrintScreen または (Ctrl + P) キーでスクリーンショットを保存
	ScreenCapture::SetShortcutKeys({ KeyPrintScreen, (KeyControl + KeyP) });

	const Font font{ 40 };

	while (System::Update())
	{
		font(Scene::FrameCount()).drawAt(Scene::Center());
	}
}
