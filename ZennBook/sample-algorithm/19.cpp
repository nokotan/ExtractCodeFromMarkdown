# include <Siv3D.hpp>

namespace Hex
{
	inline constexpr Vec2 IndexToPixel(const Point& index, const double hexR) noexcept
	{
		const double tileWidth = (hexR * Math::Sqrt3);
		const double halfWidth = (tileWidth * 0.5);
		const double tileHeight = (hexR * 1.5);
		return{ (index.x * tileWidth + IsOdd(index.y) * halfWidth), (index.y * tileHeight) };
	}

	// 参考
	// https://stackoverflow.com/questions/7705228/hexagonal-grids-how-do-you-find-which-hexagon-a-point-is-in
	inline Point PixelToIndex(const Vec2& _pos, const double hexR)
	{
		const double tileWidth = (hexR * Math::Sqrt3);
		const double halfWidth = (tileWidth * 0.5);
		const double tileHeight = (hexR * 1.5);

		const Vec2 pos{ (_pos.x + halfWidth), (_pos.y + hexR) };
		int32 row = static_cast<int32>(Math::Floor(pos.y / tileHeight));
		const bool rowIsOdd = IsOdd(row);
		int32 column = static_cast<int32>(Math::Floor(rowIsOdd ? ((pos.x - halfWidth) / tileWidth) : (pos.x / tileWidth)));

		const double relY = (pos.y - (row * tileHeight));
		const double relX = (rowIsOdd ? ((pos.x - (column * tileWidth)) - halfWidth) : (pos.x - (column * tileWidth)));
		const double c = (hexR * 0.5);
		const double m = (c / halfWidth);

		if (relY < (-m * relX) + c)
		{
			return{ (column - (not rowIsOdd)), (row - 1) };
		}
		else if (relY < (m * relX) - c)
		{
			return{ (column + rowIsOdd), (row - 1) };
		}

		return{ column, row };
	}
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.5, 0.6, 0.7 });
	const Font font{ 16 };

	constexpr Vec2 offset{ 60, 60 };
	constexpr double hexR = 50.0;
	const Size gridSize{ 8, 7 };

	while (System::Update())
	{
		for (auto p : step(gridSize))
		{
			const Vec2 center = (Hex::IndexToPixel(p, hexR) + offset);

			Shape2D::Hexagon(hexR, center)
				.draw(ColorF(0.75))
				.drawFrame(2);

			Circle{ center, 3 }.draw();

			font(p).drawAt(center.movedBy(0, 12));
		}

		{
			const Point index = Hex::PixelToIndex(Cursor::Pos() - offset, hexR);
			const Vec2 center = (Hex::IndexToPixel(index, hexR) + offset);
			Shape2D::Hexagon(hexR, center).drawFrame(10);
		}
	}
}
