# include <Siv3D.hpp>

void Main()
{
	// 出現間隔（秒）
	constexpr double spawnTime = 1.0;

	// 蓄積された時間（秒）
	double accumulator = 0.0;

	while (System::Update())
	{
		accumulator += Scene::DeltaTime();

		// 蓄積時間が出現間隔を超えたら
		if (spawnTime <= accumulator)
		{
			accumulator -= spawnTime;

			Print << U"Spawn!";
		}
	}
}
