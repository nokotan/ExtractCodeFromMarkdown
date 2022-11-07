# include <Siv3D.hpp>

void ShowStatus(const VideoReader& video)
{
	if (not video)
	{
		return;
	}

	Print << U"file: " << FileSystem::FileName(video.path());
	Print << U"size: " << video.getSize();
	Print << U"fps: " << video.getFPS();
	Print << U"time: {:.2f}s/{:.2f}s"_fmt(video.getPosSec(), video.getLengthSec());
	Print << U"progress: {:.0f} %"_fmt(video.getProgress() * 100.0);
	Print << U"frame: {}/{}"_fmt(video.getCurrentFrameIndex(), video.getFrameCount());
	Print << U"reachedEnd: " << video.reachedEnd();
}

void Main()
{
	Window::Resize(1280, 720);

	VideoReader video;
	Image frameImage;
	DynamicTexture frameTexture;

	double frameDeltaSec = 0.0;
	double frameTimeSec = 0.0;
	bool playing = false;

	while (System::Update())
	{
		ClearPrint();
		ShowStatus(video);

		if (playing)
		{
			frameTimeSec += Scene::DeltaTime();
		}

		if (video && (frameDeltaSec <= frameTimeSec))
		{
			video.readFrame(frameImage);
			frameTexture.fill(frameImage);
			frameTimeSec -= frameDeltaSec;
		}

		if (frameTexture)
		{
			frameTexture.fitted(Scene::Size()).draw();
		}

		if (SimpleGUI::Button(U"Open", Vec2{ 40, 640 }))
		{
			playing = false;

			if (const auto path = Dialog::OpenFile({ FileFilter::AllVideoFiles() }))
			{
				video = VideoReader{ *path };

				if (video)
				{
					video.readFrame(frameImage);
					frameTexture = DynamicTexture{ frameImage };
					frameDeltaSec = video.getFrameDeltaSec();
					frameTimeSec = 0.0;
					playing = true;
				}
			}
		}

		if (SimpleGUI::Button(U"Reset", Vec2{ 140, 640 }))
		{
			video.setCurrentFrameIndex(0);
			video.readFrame(frameImage);
			frameTexture.fill(frameImage);
			frameTimeSec = 0.0;
		}

		if (SimpleGUI::Button((playing ? U"■" : U"▶"), Vec2{ 240, 640 }))
		{
			playing = (not playing);
			frameTimeSec = 0.0;
		}
	}
}
