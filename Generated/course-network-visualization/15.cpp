void DrawEdge(const Node& from, const Node& to)
{
	const Vec2 p1{ (from.pos.x + to.pos.x) / 2, from.pos.y };
	const Vec2 p2{ (from.pos.x + to.pos.x) / 2, to.pos.y };
	Bezier3{ from.pos, p1, p2, to.pos }
		.draw(3, ColorF{ 0.25 });
}
