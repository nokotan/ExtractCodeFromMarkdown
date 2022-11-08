# include <Siv3D.hpp>

void Main()
{
	const ManagedScript script{ U"example/script/hello.as" };

	while (System::Update())
	{
		script.run();
	}
}
