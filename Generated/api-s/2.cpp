# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.3, 0.5, 0.4 });
	const Texture texture1{ U"🐥"_emoji };
	const Texture texture2{ U"🐢"_emoji };

	SimpleAnimation a1;
	a1.setLoop(12s)
		.set(U"r", { 0.5s, 0 }, { 1.5s, 1 }, EaseOutBounce)
		.set(U"g", { 1s, 0 }, { 2s, 1 }, EaseOutBounce)
		.set(U"b", { 1.5s, 0 }, { 2.5s, 1 }, EaseOutBounce)
		.set(U"angle", { 3s, 0_deg }, { 8.5s, 720_deg }, EaseOutBounce)
		.set(U"size", { 0s, 0 }, { 0.5s, 320 }, EaseOutExpo)
		.set(U"size", { 9s, 320 }, { 9.5s, 0 }, EaseOutExpo)
		.start();

	SimpleAnimation a2;
	a2.setLoop(6s)
		.set(U"x", { 1s, 150 }, { 3s, 650 }, EaseInOutExpo)
		.set(U"y", { 0s, 350 }, { 1s, 150 }, EaseOutBack)
		.set(U"y", { 3s, 150 }, { 4s, 350 }, EaseInQuad)
		.set(U"t", { 0s, 0 }, { 4s, 12_pi }, EaseInOutQuad)
		.set(U"a", { 5s, 1 }, { 6s, 0 }, EaseOutCubic)
		.start();

	SimpleAnimation a3;
	a3.setLoop(6s)
		.set(U"x", { 0s, 100 }, { 3s, 700 }, EaseInOutQuad)
		.set(U"x", { 3s, 700 }, { 6s, 100 }, EaseInOutQuad)
		.set(U"mirrored", { 0s, 1 }, { 3s, 1 })
		.set(U"mirrored", { 3s, 0 }, { 6s, 0 })
		.start();

	while (System::Update())
	{
		Triangle{ Scene::Center(), a1[U"size"], a1[U"angle"] }
		.draw(ColorF{ a1[U"r"], 0, 0 }, ColorF{ 0, a1[U"g"], 0 }, ColorF{ 0, 0, a1[U"b"] });

		texture1
			.drawAt(a2[U"x"], a2[U"y"] + Math::Sin(a2[U"t"]) * 20.0, ColorF{ 1, a2[U"a"] });

		texture2
			.mirrored(a3[U"mirrored"])
			.drawAt(a3[U"x"], 500);
	}
}
