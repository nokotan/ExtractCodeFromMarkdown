# include <Siv3D.hpp>

void Main()
{
	for (const auto& info : System::EnumerateMicrophones())
	{
		Print << U"[{}] {} {} {}"_fmt(info.microphoneIndex, info.name, info.sampleRates, info.preferredSampleRate);
	}

	while (System::Update())
	{

	}
}
