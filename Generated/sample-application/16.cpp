# include <Siv3D.hpp>

double Diff(const Image& a, const Image& b)
{
	const Color* pA = a.data();
	const Color* const pAEnd = a.data() + a.num_pixels();
	const Color* pB = b.data();

	double d = 0.0;

	while (pA != pAEnd)
	{
		d += AbsDiff(pA->r, pB->r) + AbsDiff(pA->g, pB->g) + AbsDiff(pA->b, pB->b);
		++pA;
		++pB;
	}

	return d;
}

void Main()
{
	const Image target = Dialog::OpenImage().fit(Scene::Size());
	Image image{ target.size(), Palette::White };
	Image old = image;

	DynamicTexture texture{ old };
	double d1 = Diff(target, image);

	while (System::Update())
	{
		for (int32 i = 0; i < 100; ++i)
		{
			const Point pos = RandomPoint(Rect{ image.size() });
			const ColorF color{ Random(), Random(), Random(), Random() };
			const int32 size = Random(1, 10);

			Circle{ pos, size }.paint(image, color);
			const double d2 = Diff(target, image);

			if (d2 < d1)
			{
				d1 = d2;
				old = image;
			}
			else
			{
				image = old;
			}
		}

		texture.fill(image);
		texture.draw();

		if (SimpleGUI::Button(U"Save", Vec2{ 520, 430 }, 100))
		{
			image.saveWithDialog();
		}
	}
}
