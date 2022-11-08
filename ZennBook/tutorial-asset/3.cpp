# include <Siv3D.hpp>

void Main()
{
	const String preloadText = U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	FontAsset::Register(U"MyFont", FontMethod::MSDF, 64, Typeface::Bold);
	TextureAsset::Register(U"MyTexture", U"example/bay.jpg");
	AudioAsset::Register(U"MyAudio", Audio::Stream, U"example/test.mp3");
	AudioAsset::Register(U"MyMIDI", U"example/midi/test.mid");

	// 事前ロード
	FontAsset::Load(U"MyFont", preloadText);
	TextureAsset::Load(U"MyTexture");
	AudioAsset::Load(U"MyAudio");
	AudioAsset::Load(U"MyMIDI");

	// ロードが完了したか
	Print << FontAsset::IsReady(U"MyFont");
	Print << TextureAsset::IsReady(U"MyTexture");
	Print << AudioAsset::IsReady(U"MyAudio");
	Print << AudioAsset::IsReady(U"MyMIDI");

	while (System::Update())
	{

	}
}
