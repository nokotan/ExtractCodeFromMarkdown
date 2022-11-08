# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const double t = Scene::Time();

		Circle{ Scene::Center(), 100 }
			.drawArc((t * 90_deg), 320_deg, 10, 10);
	}
}
