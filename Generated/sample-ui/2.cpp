# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.9, 0.6, 0.3 });

	// 通知ごとに割り振られる ID
	ToastNotificationID latest = -1;

	// 画像を作成・保存
	Emoji::CreateImage(U"🍕").save(U"pizza.png");

	while (System::Update())
	{
		ClearPrint();

		// 通知の状態
		Print << (int32)Platform::Windows::ToastNotification::GetState(latest);

		// アクションボタンの結果
		Print << U"Action: " << Platform::Windows::ToastNotification::GetAction(latest);

		if (SimpleGUI::Button(U"Send a notification", Vec2{ 10, 70 }))
		{
			ToastNotificationItem toast{
				.title = U"Title", // 通知のタイトル
				.message = U"Message", // 通知の本文
				.imagePath = U"pizza.png", // 大きい画像だと使われないことがある
				.actions = { U"Yes", U"No" } // アクションボタン（不要な場合は設定しない）
			};

			// 通知ごとに割り振られる ID を取得
			latest = Platform::Windows::ToastNotification::Show(toast);
		}
	}
}
