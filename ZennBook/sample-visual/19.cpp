# include <Siv3D.hpp>

class Font3D
{
public:

	Font3D() = default;

	SIV3D_NODISCARD_CXX20
	explicit Font3D(const Font& font)
		: m_font{ font } {}

	[[nodiscard]]
	Array<MeshGlyph> getGlyphs(StringView s) const
	{
		Array<MeshGlyph> results;

		for (auto ch : s)
		{
			auto it = m_table.find(ch);

			if (it == m_table.end())
			{
				it = m_table.emplace(ch, m_font.createMesh(ch)).first;
			}

			results << it->second;
		}

		return results;
	}

	void drawCylindricalInner(StringView s, const Vec3& center, double r, double scale, double startAngle, const ColorF& color) const
	{
		const double perimeter = (r * Math::TwoPi);
		double penPosX = 0.0;
		startAngle += 90_deg;

		for (auto meshGlyph : getGlyphs(s))
		{
			penPosX += (meshGlyph.xOffset * scale);

			if (meshGlyph.mesh)
			{
				const double angle = (penPosX / perimeter) * 360_deg;
				const Quaternion q = Quaternion::RotateY(-90_deg + angle - startAngle);
				const Vec3 pos = Cylindrical{ r, (-180_deg - angle + startAngle), 0.0 } + center;
				const Mat4x4 mat = Mat4x4::Translate(-meshGlyph.xOffset, 0, 0)
					.scaled(scale)
					.rotated(q)
					.translated(pos);
				meshGlyph.mesh.draw(mat, color);
			}

			penPosX += (meshGlyph.xAdvance - meshGlyph.xOffset) * scale;
		}
	}

	void drawCylindricalOuter(StringView s, const Vec3& center, double r, double scale, double startAngle, const ColorF& color) const
	{
		const double perimeter = (r * Math::TwoPi);
		double penPosX = 0.0;
		startAngle += 90_deg;

		for (auto meshGlyph : getGlyphs(s))
		{
			penPosX += (meshGlyph.xOffset * scale);

			if (meshGlyph.mesh)
			{
				const double angle = (penPosX / perimeter) * 360_deg;
				const Quaternion q = Quaternion::RotateY(90_deg - angle - startAngle);
				const Vec3 pos = Cylindrical{ r, (180_deg + angle + startAngle), 0.0 } + center;
				const Mat4x4 mat = Mat4x4::Translate(-meshGlyph.xOffset, 0, 0)
					.scaled(scale)
					.rotated(q)
					.translated(pos);
				meshGlyph.mesh.draw(mat, color);
			}

			penPosX += (meshGlyph.xAdvance - meshGlyph.xOffset) * scale;
		}
	}

private:

	Font m_font;

	mutable HashTable<char32, MeshGlyph> m_table;
};

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.5, 0.6, 0.6 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };
	const Font3D font3D{ Font{ 60 } };

	while (System::Update())
	{
		const double t = Scene::Time();
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			Graphics3D::SetGlobalAmbientColor(Graphics3D::DefaultGlobalAmbientColor);
			Graphics3D::SetSunColor(ColorF{ 0.75 });

			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			Cylinder{ Vec3{0,0,0}, Vec3{0, 16, 0}, 5.6 }.draw(ColorF{ 0.25 }.removeSRGBCurve());

			// 3D Text Circle
			{
				// 両面描画、ライティング無効化
				const ScopedRenderStates3D rasterizer{ RasterizerState::SolidCullNone, BlendState::Additive };
				Graphics3D::SetGlobalAmbientColor(ColorF{ 1.0 });
				Graphics3D::SetSunColor(ColorF{ 0.0 });

				font3D.drawCylindricalOuter(DateTime::Now().format(U"HH:mm:ss"), Vec3{ 0, 11.5, 0 }, 6 * 1.2, 3.0 * 1.2, (t * -25_deg), ColorF{ 1.0, 0.98, 0.9 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(DateTime::Now().format(U"HH:mm:ss"), Vec3{ 0, 11.5, 0 }, 6 * 1.2, 3.0 * 1.2, (t * -25_deg) + 180_deg, ColorF{ 1.0, 0.98, 0.9 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"Monday, September 27, 2021", Vec3{ 0, 10, 0 }, 6 * 1.2, 1.2 * 1.2, (t * -50_deg), ColorF{ 1.0, 0.98, 0.9 }.removeSRGBCurve());

				font3D.drawCylindricalOuter(U"NIKKEI 225 30,248.81 +609.41", Vec3{ 0, 8, 0 }, 6, 1.0, (t * -72_deg), ColorF{ 0.6, 1.0, 0.8 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"HANG SENG 24,192,16 -318.82", Vec3{ 0, 7, 0 }, 6, 1.0, (t * -62_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"SHANGHAI 3,613.07 -29.15", Vec3{ 0, 6, 0 }, 6, 1.0, (t * -58_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"FTSE 7,051.48 -26.87", Vec3{ 0, 5, 0 }, 6, 1.0, (t * -70_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"CAC 6,638.46 -63.52", Vec3{ 0, 4, 0 }, 6, 1.0, (t * -60_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"DAX 15,531.75 -112.22", Vec3{ 0, 3, 0 }, 6, 1.0, (t * -66_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"NASDAQ 15,047.70 -4.54", Vec3{ 0, 2, 0 }, 6, 1.0, (t * -68_deg), ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());

				font3D.drawCylindricalOuter(U"NIKKEI 225 30,248.81 +609.41", Vec3{ 0, 8, 0 }, 6, 1.0, (t * -72_deg) + 180_deg, ColorF{ 0.6, 1.0, 0.8 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"HANG SENG 24,192,16 -318.82", Vec3{ 0, 7, 0 }, 6, 1.0, (t * -62_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"SHANGHAI 3,613.07 -29.15", Vec3{ 0, 6, 0 }, 6, 1.0, (t * -58_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"FTSE 7,051.48 -26.87", Vec3{ 0, 5, 0 }, 6, 1.0, (t * -70_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"CAC 6,638.46 -63.52", Vec3{ 0, 4, 0 }, 6, 1.0, (t * -60_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"DAX 15,531.75 -112.22", Vec3{ 0, 3, 0 }, 6, 1.0, (t * -66_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
				font3D.drawCylindricalOuter(U"NASDAQ 15,047.70 -4.54", Vec3{ 0, 2, 0 }, 6, 1.0, (t * -68_deg) + 180_deg, ColorF{ 1.0, 0.6, 0.6 }.removeSRGBCurve());
			}
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
