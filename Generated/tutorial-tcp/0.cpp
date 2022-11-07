# include <Siv3D.hpp>

void Main()
{
	// ポート番号
	constexpr uint16 port = 50000;
	bool connected = false;

	TCPServer server;
	server.startAccept(port);

	Window::SetTitle(U"TCPServer: Waiting for connection...");

	Point clientPlayerPos{ 0, 0 };

	while (System::Update())
	{
		const Point serverPlayerPos = Cursor::Pos();

		if (server.hasSession())
		{
			if (not connected) // クライアントが接続
			{
				connected = true;

				Window::SetTitle(U"TCPServer: Connection established!");
			}

			// 送信
			server.send(serverPlayerPos);

			// 受信
			while (server.read(clientPlayerPos));
		}

		// クライアントが切断
		if (connected && (not server.hasSession()))
		{
			// 切断
			server.disconnect();

			connected = false;

			Window::SetTitle(U"TCPServer: Waiting for connection...");

			// 新たな接続を受け付け開始
			server.startAccept(port);
		}

		Circle{ serverPlayerPos, 30 }.draw(Palette::Skyblue);

		Circle{ clientPlayerPos, 10 }.draw(Palette::Orange);
	}
}
