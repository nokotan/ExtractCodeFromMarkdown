# include <Siv3D.hpp>

void Main()
{
	// コンソール画面に出力
	Console << U"Hello, Console!";

	// ログに出力 (Visual Studio の場合「出力」ウィンドウ）
	Logger << U"Hello, Logger!";

	// 必要に応じて読み上げ言語を設定（OS に読み上げエンジンがインストールされていない場合は使えない）
	TextToSpeech::SetDefaultLanguage(LanguageCode::EnglishUS);
	//TextToSpeech::SetDefaultLanguage(LanguageCode::Japanese);

	// 音声読み上げ出力
	Say << U"Hello, Say!";

	while (System::Update())
	{

	}
}
