# include <Siv3D.hpp>

void Main()
{
# if SIV3D_PLATFORM(WINDOWS)

	// 子プロセスを作成
	ChildProcess child{ U"C:/Windows/System32/notepad.exe" };

# elif SIV3D_PLATFORM(MACOS)

	// 子プロセスを作成
	ChildProcess child{ U"/System/Applications/Calculator.app/Contents/MacOS/Calculator" };

# elif SIV3D_PLATFORM(LINUX)

	// 子プロセスを作成
	ChildProcess child{ U"/usr/bin/firefox", U"www.mozilla.org" };

# endif

	if (not child)
	{
		throw Error{ U"Failed to create a process" };
	}

	while (System::Update())
	{
		ClearPrint();

		// プロセスが実行中かを取得
		Print << child.isRunning();

		// プロセスが終了した場合、その終了コード
		Print << child.getExitCode();

		if (child.isRunning())
		{
			if (SimpleGUI::Button(U"Terminate", Vec2{ 600, 20 }))
			{
				// プロセスを強制終了
				child.terminate();
			}
		}
	}
}
