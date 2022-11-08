# include <Siv3D.hpp>

void Main()
{
	VideoReader reader{ U"example/video/river.mp4" };
	VideoWriter writer{ U"output.mp4", reader.getSize(), reader.getFPS() };
	Image frame;

	for (size_t i = 0; i < reader.getFrameCount(); ++i)
	{
		Console << U"{} フレーム目"_fmt(i);
		reader.readFrame(frame);
		writer.writeFrame(frame.grayscale());
	}
}
