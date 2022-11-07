# include <Siv3D.hpp>

void Main()
{
# if SIV3D_PLATFORM(WINDOWS)

	// 子プロセスを作成（パイプライン処理）
	ChildProcess child{ U"console.exe", Pipe::StdInOut };

# else

	// 子プロセスを作成（パイプライン処理）
	ChildProcess child{ U"console", Pipe::StdInOut };

# endif

	if (not child)
	{
		throw Error{ U"Failed to create a process" };
	}

	child.ostream() << 10 << std::endl;
	child.ostream() << 20 << std::endl;

	int32 result;
	child.istream() >> result;
	Print << U"result: " << result;

	while (System::Update())
	{

	}
}
