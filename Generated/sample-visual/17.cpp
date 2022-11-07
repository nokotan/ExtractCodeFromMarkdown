# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture texture{ U"example/spritesheet/siv3d-kun-16.png" };
	constexpr int32 patterns[4] = { 1, 2, 1, 0 };

	while (System::Update())
	{
		const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };

		const uint64 t = Time::GetMillisec();
		const int32 x = ((t / 2000 % 2) * 3);
		const int32 y = (t / 4000 % 4);
		const int32 n = (t / 250 % 4);

		Rect{ ((patterns[n] + x) * 20 * 4), (y * 28 * 4), (20 * 4), (28 * 4) }
			.draw(ColorF{ 0.3, 0.9, 0.8 });

		texture.scaled(4).draw();

		Rect{ 520, 60, (20 * 8 + 80), (28 * 8 + 80) }
			.draw(ColorF{ 0.5, 0.9, 0.5 });

		texture((patterns[n] + x) * 20, (y * 28), 20, 28)
			.scaled(8).draw(560, 100);
	}
}
