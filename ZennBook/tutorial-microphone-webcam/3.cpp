# include <Siv3D.hpp>

void Main()
{
	for (const auto& info : System::EnumerateWebcams())
	{
		Print << info.cameraIndex;
		Print << info.name;
		Print << info.uniqueName;
	}

	while (System::Update())
	{

	}
}
