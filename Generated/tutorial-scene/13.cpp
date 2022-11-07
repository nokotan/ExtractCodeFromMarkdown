# include <Siv3D.hpp>

void Main()
{
	// 接続されているモニタの情報一覧を取得
	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	for (const auto& monitor : monitors)
	{
		Print << U"name: " << monitor.name;
		Print << U"displayRect: " << monitor.displayRect << U" workArea: " << monitor.workArea;
		Print << U"fullscreenResolution: " << monitor.fullscreenResolution << U" sizeMillimeter: " << monitor.sizeMillimeter;
		Print << U"scaling: " << monitor.scaling << U" refreshRate: " << monitor.refreshRate;
		Print << U"isPrimary: " << monitor.isPrimary;
		Print << U"-----";
	}

	while (System::Update())
	{

	}
}
