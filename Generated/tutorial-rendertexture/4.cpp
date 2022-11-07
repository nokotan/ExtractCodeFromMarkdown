# include <Siv3D.hpp>

void Main()
{
	const Texture texture{ U"example/windmill.png" };
	const RenderTexture internalTexture{ texture.size() };
	const RenderTexture renderTexture{ texture.size() };

	Shader::GaussianBlur(texture, internalTexture, renderTexture);

	while (System::Update())
	{
		renderTexture.draw();
	}
}
