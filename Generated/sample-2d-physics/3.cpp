# include <Siv3D.hpp>

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.4, 0.7, 1.0 });

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 2D 物理演算のワールド
	P2World world;

	// [_] 地面
	Array<P2Body> floors;
	{
		floors << world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -1600, 0, 1600, 0 });

		for (auto i : Range(1, 5))
		{
			if (IsEven(i))
			{
				floors << world.createLine(P2Static, Vec2{ 0, 0 }, Line{ 0, -i * 200, 1600, -i * 200 - 300 });
			}
			else
			{
				floors << world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -1600,  -i * 200 - 300, 0, -i * 200 });
			}
		}
	}

	// [🚙] 車
	const P2Body carBody = world.createRect(P2Dynamic, Vec2{ -1500, -1450 }, SizeF{ 200, 40 });
	const P2Body wheelL = world.createCircle(P2Dynamic, Vec2{ -1550, -1430 }, 30);
	const P2Body wheelR = world.createCircle(P2Dynamic, Vec2{ -1450, -1430 }, 30);
	const P2WheelJoint wheelJointL = world.createWheelJoint(carBody, wheelL, wheelL.getPos(), Vec2{ 0, -1 })
		.setLinearStiffness(4.0, 0.7)
		.setLimits(-5, 5).setLimitsEnabled(true);
	const P2WheelJoint wheelJointR = world.createWheelJoint(carBody, wheelR, wheelR.getPos(), Vec2{ 0, -1 })
		.setLinearStiffness(4.0, 0.7)
		.setLimits(-5, 5).setLimitsEnabled(true);

	// マウスジョイント
	P2MouseJoint mouseJoint;

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -1200 }, 0.25 };

	while (System::Update())
	{
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			world.update(stepSec);
		}

		// 2D カメラの更新
		camera.update();
		{
			// 2D カメラから Transformer2D を作成
			const auto t = camera.createTransformer();

			if (MouseL.down())
			{
				mouseJoint = world.createMouseJoint(carBody, Cursor::PosF())
					.setMaxForce(carBody.getMass() * 5000.0)
					.setLinearStiffness(2.0, 0.7);
			}
			else if (MouseL.pressed())
			{
				mouseJoint.setTargetPos(Cursor::PosF());
			}
			else if (MouseL.up())
			{
				mouseJoint.release();
			}

			// 地面を描く
			for (const auto& floor : floors)
			{
				floor.draw(ColorF{ 0.0, 0.5, 0.0 });
			}

			carBody.draw(Palette::Gray);
			wheelL.draw(Palette::Gray).drawWireframe(1, Palette::Yellow);
			wheelR.draw(Palette::Gray).drawWireframe(1, Palette::Yellow);

			mouseJoint.draw();
			wheelJointL.draw();
			wheelJointR.draw();
		}

		// 2D カメラの操作を描画
		camera.draw(Palette::Orange);
	}
}
