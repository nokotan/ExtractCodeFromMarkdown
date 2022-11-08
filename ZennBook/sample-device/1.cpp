# include <Siv3D.hpp>

void Main()
{
	// シリアルポートの一覧を取得
	const Array<SerialPortInfo> infos = System::EnumerateSerialPorts();
	const Array<String> options = infos.map([](const SerialPortInfo& info)
	{
		return U"{} ({})"_fmt(info.port, info.description);
	}) << U"none";

	Serial serial;
	size_t index = (options.size() - 1);

	while (System::Update())
	{
		const bool isOpen = serial.isOpen(); // OpenSiv3D v0.4.2 以前は serial.isOpened()

		if (SimpleGUI::Button(U"Write int16", Vec2{ 200, 20 }, 120, isOpen))
		{
			// 2 バイト (int16) のデータを書き込む
			const int16 n = 12300;

			serial.write(n);
		}

		if (SimpleGUI::RadioButtons(index, options, Vec2{ 200, 60 }))
		{
			ClearPrint();

			if (index == (options.size() - 1))
			{
				serial = Serial{};
			}
			else
			{
				Print << U"Open {}"_fmt(infos[index].port);

				// シリアルポートをオープン
				if (serial.open(infos[index].port))
				{
					Print << U"Succeeded";
				}
				else
				{
					Print << U"Failed";
				}
			}
		}

		if (const size_t available = serial.available())
		{
			int16 n;

			if (serial.read(n)) // 2 バイト (int16) のデータを読み込んだら
			{
				Print << U"READ: " << n;
			}
		}
	}
}
