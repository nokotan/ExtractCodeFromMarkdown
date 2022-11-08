# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// Pro コントローラーを取得
		if (const auto pro = ProController(0))
		{
			// 各ボタンの状態を表示
			Print << U"A: " << pro.buttonA.pressed();
			Print << U"B: " << pro.buttonB.pressed();
			Print << U"X: " << pro.buttonX.pressed();
			Print << U"Y: " << pro.buttonY.pressed();
			Print << U"L: " << pro.buttonL.pressed();
			Print << U"R: " << pro.buttonR.pressed();
			Print << U"ZL: " << pro.buttonZL.pressed();
			Print << U"ZR: " << pro.buttonZR.pressed();
			Print << U"-: " << pro.buttonMinus.pressed();
			Print << U"+: " << pro.buttonPlus.pressed();
			Print << U"LS: " << pro.buttonLStick.pressed();
			Print << U"RS: " << pro.buttonRStick.pressed();
			Print << U"Screenshot: " << pro.buttonScreenshot.pressed();
			Print << U"Home: " << pro.buttonHome.pressed();
			Print << U"LStick: " << pro.LStick();
			Print << U"RStick: " << pro.RStick();
			Print << U"POV: " << pro.povD8();
		}
		else
		{
			Print << U"No Pro Controller found";
		}
	}
}
