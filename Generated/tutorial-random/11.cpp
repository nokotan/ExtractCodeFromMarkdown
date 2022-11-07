# include <Siv3D.hpp>

void Main()
{
    while (System::Update())
    {
        if (SimpleGUI::Button(U"Reset", Vec2{ 200, 20 }))
        {
            ClearPrint();

            // ランダムに 3 個選択
            Print << Sample(3, { 1, 2, 5, 10, 20, 50, 100 });
        }
    }
}
