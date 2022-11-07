# include <Siv3D.hpp>

void Main()
{
# if SIV3D_PLATFORM(WINDOWS)

	const Font font{ 60, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"arial.ttf" };

# elif SIV3D_PLATFORM(MACOS)

	const Font font{ 60, FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"Helvetica.dfont" };

# endif

	while (System::Update())
	{
# if SIV3D_PLATFORM(WINDOWS)

		font(U"Arial").draw(20, 40);

# elif SIV3D_PLATFORM(MACOS)

		font(U"Helvetica").draw(20, 40);

# endif
	}
}
