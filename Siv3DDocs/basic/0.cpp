# include <Siv3D.hpp>

void Main()
{
	// ウィンドウの閉じるボタンを押すか、System::Exit() を呼ぶ操作を終了操作に設定,
	// エスケープキーを押しても終了しないようになる
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	while (System::Update())
	{

	}
}
