void drawNodeActive() const
{
	getCircle()
		.drawShadow(Vec2{ 1, 1 }, 8, 1)
		.draw(ColorF{ 1.0, 0.9, 0.8 })
		.drawArc(Scene::Time() * 120_deg, 120_deg, 0, 5, Palette::Orange)
		.drawArc(Scene::Time() * 120_deg + 180_deg, 120_deg, 0, 5, Palette::Orange);
}
