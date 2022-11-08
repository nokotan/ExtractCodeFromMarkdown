# include <Siv3D.hpp>

void Main()
{
	System::SetTerminationTriggers(UserAction::NoAction);

	while (System::Update())
	{
		const auto userAction = System::GetUserActions();

		if (userAction & UserAction::CloseButtonClicked)
		{
			Print << U"CloseButtonClicked";
		}

		if (userAction & UserAction::EscapeKeyDown)
		{
			Print << U"EscapeKeyDown";
		}

		if (userAction & UserAction::WindowDeactivated)
		{
			Print << U"WindowDeactivated";
		}

		if (userAction & UserAction::AnyKeyDown)
		{
			Print << U"AnyKeyDown";
		}

		if (userAction & UserAction::MouseButtonDown)
		{
			Print << U"MouseButtonDown";
		}

		if (SimpleGUI::Button(U"Exit", Vec2{ 700, 20 }))
		{
			System::Exit();
		}
	}
}
