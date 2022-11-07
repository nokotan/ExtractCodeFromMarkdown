# include <Siv3D.hpp>

void Main()
{
	const Font font{ 24, Typeface::Medium };

	// HTTP 通信の検証用サービス (http://httpbin.org) を利用
	// 1024 バイトのデータを 4 秒かけてダウンロードする URL
	const URL url = U"http://httpbin.org/drip?duration=4&numbytes=1024&code=200&delay=0";
	const FilePath saveFilePath = U"drip.txt";

	AsyncHTTPTask task;

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Download", Vec2{ 20, 20 }, 140, task.isEmpty()))
		{
			task = SimpleHTTP::SaveAsync(url, saveFilePath);
		}

		if (SimpleGUI::Button(U"Cancel", Vec2{ 180, 20 }, 140, (task.getStatus() == HTTPAsyncStatus::Downloading)))
		{
			// タスクをキャンセル
			task.cancel();
		}

		// タスクの進捗
		const HTTPProgress progress = task.getProgress();

		if (progress.status == HTTPAsyncStatus::None_)
		{
			font(U"status: None_").draw(20, 60);
		}
		else if (progress.status == HTTPAsyncStatus::Downloading)
		{
			font(U"status: Downloading").draw(20, 60);
		}
		else if (progress.status == HTTPAsyncStatus::Failed)
		{
			font(U"status: Failed").draw(20, 60);
		}
		else if (progress.status == HTTPAsyncStatus::Canceled)
		{
			font(U"status: Canceled").draw(20, 60);
		}
		else if (progress.status == HTTPAsyncStatus::Succeeded)
		{
			font(U"status: Succeeded").draw(20, 60);
		}

		if (progress.status == HTTPAsyncStatus::Downloading)
		{
			// ダウンロード済みのサイズ（バイト）
			const int64 downloaded = progress.downloaded_bytes;

			// ダウンロードするファイルのサイズ（バイト）。取得できない場合は none
			const Optional<int64> total = progress.download_total_bytes;

			if (total)
			{
				font(U"downloaded: {} bytes / {} bytes"_fmt(downloaded, *total)).draw(20, 100);

				const double progress0_1 = (static_cast<double>(downloaded) / *total);
				const RectF rect{ 20, 140, 500, 30 };
				rect.drawFrame(2, 0);
				RectF{ rect.pos, (rect.w * progress0_1), rect.h }.draw();
			}
			else
			{
				font(U"downloaded: {} bytes"_fmt(downloaded)).draw(20, 100);
			}
		}

		if (task.isReady())
		{
			if (const auto& response = task.getResponse())
			{
				Console << U"------";
				Console << response.getStatusLine().rtrimmed();
				Console << U"status code: " << FromEnum(response.getStatusCode());
				Console << U"------";
				Console << response.getHeader().rtrimmed();
				Console << U"------";

				if (response.isOK())
				{
					Console << FileSystem::FileSize(saveFilePath) << U" bytes";
					Console << U"------";
				}
			}
			else
			{
				Print << U"Failed.";
			}
		}
	}
}
