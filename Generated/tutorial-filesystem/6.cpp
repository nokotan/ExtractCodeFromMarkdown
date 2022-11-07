# include <Siv3D.hpp>

void Main()
{
	Print << FileSystem::GetFolderPath(SpecialFolder::Desktop);
	Print << FileSystem::GetFolderPath(SpecialFolder::Documents);
	Print << FileSystem::GetFolderPath(SpecialFolder::LocalAppData);
	Print << FileSystem::GetFolderPath(SpecialFolder::Pictures);
	Print << FileSystem::GetFolderPath(SpecialFolder::Music);
	Print << FileSystem::GetFolderPath(SpecialFolder::Videos);
	Print << FileSystem::GetFolderPath(SpecialFolder::SystemFonts);
	Print << FileSystem::GetFolderPath(SpecialFolder::LocalFonts);
	Print << FileSystem::GetFolderPath(SpecialFolder::UserFonts);
	Print << FileSystem::GetFolderPath(SpecialFolder::UserProfile);
	Print << FileSystem::GetFolderPath(SpecialFolder::ProgramFiles);

	while (System::Update())
	{

	}
}
