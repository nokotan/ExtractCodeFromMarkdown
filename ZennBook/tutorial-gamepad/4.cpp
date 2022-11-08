# include <Siv3D.hpp>

void Main()
{
	for (const auto& info : System::EnumerateGamepads())
	{
		Print << U"[{}] {} ({:#x} {:#x})"_fmt(info.playerIndex, info.name, info.vendorID, info.productID);
	}

	while (System::Update())
	{

	}
}
