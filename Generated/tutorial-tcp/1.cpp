# include <Siv3D.hpp>

void Main()
{
	// 接続先の IPv4 アドレス（今回は自身の PC なので Localhost）
	const IPv4Address ip = IPv4Address::Localhost();

	// ポート番号
	constexpr uint16 port = 50000;

	bool connected = false;

	TCPClient client;

	// 接続を試行
	client.connect(ip, port);

	Window::SetTitle(U"TCPClient: Waiting for connection...");

	Point serverPlayerPos{ 0, 0 };

	while (System::Update())
	{
		const Point clientPlayerPos = Cursor::Pos();

		if (client.isConnected())
		{
			if (not connected) // 接続された
			{
				connected = true;

				Window::SetTitle(U"TCPClient: Connection established!");
			}

			// 送信
			client.send(clientPlayerPos);

			// 受信
			while (client.read(serverPlayerPos));
		}

		if (client.hasError()) // 切断/接続エラー
		{
			client.disconnect();

			connected = false;

			Window::SetTitle(U"TCPClient: Waiting for connection...");

			// 接続を再試行
			client.connect(ip, port);
		}

		Circle{ clientPlayerPos, 30 }.draw(Palette::Skyblue);

		Circle{ serverPlayerPos, 30 }.draw(Palette::Orange);
	}
}
