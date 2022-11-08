# include <Siv3D.hpp>

void Main()
{
	const String preloadText = U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	FontAsset::Register(U"MyFont", FontMethod::MSDF, 64, Typeface::Bold);
	TextureAsset::Register(U"MyTexture", U"example/bay.jpg");
	AudioAsset::Register(U"MyAudio", Audio::Stream, U"example/test.mp3");
	AudioAsset::Register(U"MyMIDI", U"example/midi/test.mid");

	// 非同期ロードを開始
	FontAsset::LoadAsync(U"MyFont", preloadText);
	TextureAsset::LoadAsync(U"MyTexture");
	AudioAsset::LoadAsync(U"MyAudio");
	AudioAsset::LoadAsync(U"MyMIDI");

	while (System::Update())
	{
		ClearPrint();

		// ロードが完了したか
		Print << FontAsset::IsReady(U"MyFont");
		Print << TextureAsset::IsReady(U"MyTexture");
		Print << AudioAsset::IsReady(U"MyAudio");
		Print << AudioAsset::IsReady(U"MyMIDI");
	}
}
