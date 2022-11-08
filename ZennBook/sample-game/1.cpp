# include <Siv3D.hpp>

// 外周の枠の頂点リストを作成
LineString CreateFrame(const Vec2& leftAnchor, const Vec2& rightAnchor)
{
	Array<Vec2> points = { leftAnchor, Vec2{ -70, -20 } };
	for (auto i : Range(-30, 30))
	{
		points << OffsetCircular(Vec2{ 0.0, -120 }, 70, (i * 3_deg));
	}
	points << Vec2{ 70, -20 } << rightAnchor;
	return LineString{ points };
}

// 接触しているかに応じて色を決定
ColorF GetColor(const P2Body& body, const HashSet<P2BodyID>& list)
{
	return list.contains(body.id()) ? Palette::White : Palette::Orange;
}

void Main()
{
	// 背景色を設定
	Scene::SetBackground(ColorF(0.2, 0.3, 0.4));

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 物理演算用のワールド
	P2World world{ 60.0 };

	// 左右フリッパーの軸の座標
	constexpr Vec2 leftFlipperAnchor{ -25, 10 }, rightFlipperAnchor{ 25, 10 };

	// 固定の枠
	Array<P2Body> frames;
	{
		// 外周
		frames << world.createLineString(P2Static, Vec2{ 0, 0 }, CreateFrame(leftFlipperAnchor, rightFlipperAnchor));
		// 左上の (
		frames << world.createLineString(P2Static, Vec2{ 0, 0 }, LineString{ Range(-25, -10).map([=](int32 i) { return OffsetCircular(Vec2{ 0.0, -120 }, 55, (i * 3_deg)).toVec2(); }) });
		// 右上の )
		frames << world.createLineString(P2Static, Vec2{ 0, 0 }, LineString{ Range(10, 25).map([=](int32 i) { return OffsetCircular(Vec2{ 0.0, -120 }, 55, (i * 3_deg)).toVec2(); }) });
	}

	// バンパー
	Array<P2Body> bumpers;
	{
		// ● x3
		{
			const P2Material material{ .restitution = 1.0, .restitutionThreshold = 0.1 };
			bumpers << world.createCircle(P2Static, Vec2{ 0, -170 }, 5, material);
			bumpers << world.createCircle(P2Static, Vec2{ -20, -150 }, 5, material);
			bumpers << world.createCircle(P2Static, Vec2{ 20, -150 }, 5, material);
		}
		// ▲ x2
		{
			const P2Material material{ .restitution = 0.8, .restitutionThreshold = 0.1 };
			bumpers << world.createTriangle(P2Static, Vec2{ 0, 0 }, Triangle{ -60, -50, -40, -15, -60, -30 }, material);
			bumpers << world.createTriangle(P2Static, Vec2{ 0, 0 }, Triangle{ 60, -50, 60, -30, 40, -15 }, material);
		}
	}

	const P2Material softMaterial{ .density = 0.1, .restitution = 0.0 };

	// 左フリッパー
	P2Body leftFlipper = world.createRect(P2Dynamic, leftFlipperAnchor, RectF{ 0, 0.4, 21, 4.5 }, softMaterial);
	// 左フリッパーのジョイント
	const P2PivotJoint leftJoint = world.createPivotJoint(frames[0], leftFlipper, leftFlipperAnchor).setLimits(-20_deg, 25_deg).setLimitsEnabled(true);

	// 右フリッパー
	P2Body rightFlipper = world.createRect(P2Dynamic, rightFlipperAnchor, RectF{ -21, 0.4, 21, 4.5 }, softMaterial);
	// 右フリッパーのジョイント
	const P2PivotJoint rightJoint = world.createPivotJoint(frames[0], rightFlipper, rightFlipperAnchor).setLimits(-25_deg, 20_deg).setLimitsEnabled(true);

	// スピナー ＋
	const P2Body spinner = world.createRect(P2Dynamic, Vec2{ -58, -120 }, SizeF{ 20, 1 }, softMaterial).addRect(RectF{ Arg::center(0, 0), 1, 20 }, P2Material{ 0.01, 0.0 });
	// スピナーのジョイント
	P2PivotJoint spinnerJoint = world.createPivotJoint(frames[0], spinner, Vec2{ -58, -120 }).setMaxMotorTorque(0.05).setMotorSpeed(0).setMotorEnabled(true);

	// 風車の |
	frames << world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -40, -60, -40, -40 });
	// 風車の羽 ／
	const P2Body windmillWing = world.createRect(P2Dynamic, Vec2{ -40, -60 }, SizeF{ 30, 2 }, P2Material{ 0.1, 0.8 });
	// 風車のジョイント
	const P2PivotJoint windmillJoint = world.createPivotJoint(frames.back(), windmillWing, Vec2{ -40, -60 }).setMotorSpeed(240_deg).setMaxMotorTorque(10000.0).setMotorEnabled(true);

	// 振り子の軸
	const P2Body pendulumbase = world.createPlaceholder(P2Static, Vec2{ 0, -190 });
	// 振り子 ●
	P2Body pendulum = world.createCircle(P2Dynamic, Vec2{ 0, -120 }, 4, P2Material{ 0.1, 1.0 });
	// 振り子のジョイント
	const P2DistanceJoint pendulumJoint = world.createDistanceJoint(pendulumbase, Vec2{ 0, -190 }, pendulum, Vec2{ 0, -120 }, 70);

	// エレベーターの上部 ●
	const P2Body elevatorA = world.createCircle(P2Static, Vec2{ 40, -100 }, 3);
	// エレベーターの床 －
	const P2Body elevatorB = world.createRect(P2Dynamic, Vec2{ 40, -100 }, SizeF{ 20, 2 });
	// エレベーターのジョイント
	P2SliderJoint elevatorSliderJoint = world.createSliderJoint(elevatorA, elevatorB, Vec2{ 40, -100 }, Vec2::Down()).setLimits(5, 50).setLimitEnabled(true).setMaxMotorForce(10000).setMotorSpeed(-100);

	// ボール 〇
	const P2Body ball = world.createCircle(P2Dynamic, Vec2{ -40, -120 }, 4, P2Material{ 0.05, 0.0 });
	const P2BodyID ballID = ball.id();

	// エレベーターのアニメーション用ストップウォッチ
	Stopwatch sliderStopwatch{ StartImmediately::Yes };

	// 2D カメラ
	const Camera2D camera{ Vec2{ 0, -80 }, 2.4 };

	while (System::Update())
	{
		/////////////////////////////////////////
		//
		// 更新
		//

		if (4s < sliderStopwatch)
		{
			// エレベーターの巻き上げを停止
			elevatorSliderJoint.setMotorEnabled(false);
			sliderStopwatch.restart();
		}
		else if (2s < sliderStopwatch)
		{
			// エレベーターの巻き上げ
			elevatorSliderJoint.setMotorEnabled(true);
		}

		// ボールと接触しているボディの ID
		HashSet<P2BodyID> collidedIDs;

		// 物理演算ワールドの更新
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			// 振り子の揺れをおさえる抵抗
			pendulum.applyForce(Vec2{ (pendulum.getVelocity().x < 0.0) ? 0.0001 : -0.0001, 0.0 });

			// 左フリッパーの操作
			leftFlipper.applyTorque(KeyLeft.pressed() ? -80 : 40);

			// 右フリッパーの操作
			rightFlipper.applyTorque(KeyRight.pressed() ? 80 : -40);

			world.update(stepSec);

			// ボールと接触しているボディの ID を格納
			for (auto [pair, collision] : world.getCollisions())
			{
				if (pair.a == ballID)
				{
					collidedIDs.emplace(pair.b);
				}
				else if (pair.b == ballID)
				{
					collidedIDs.emplace(pair.a);
				}
			}
		}

		/////////////////////////////////////////
		//
		// 描画
		//

		// 描画用の Transformer2D
		const auto transformer = camera.createTransformer();

		// 枠の描画
		for (const auto& frame : frames)
		{
			frame.draw(Palette::Skyblue);
		}

		// スピナーの描画
		spinner.draw(GetColor(spinner, collidedIDs));

		// バンパーの描画
		for (const auto& bumper : bumpers)
		{
			bumper.draw(GetColor(bumper, collidedIDs));
		}

		// 風車の描画
		windmillWing.draw(GetColor(windmillWing, collidedIDs));

		// 振り子の描画
		pendulum.draw(GetColor(pendulum, collidedIDs));

		// エレベーターの描画
		elevatorA.draw(GetColor(elevatorA, collidedIDs));
		elevatorB.draw(GetColor(elevatorB, collidedIDs));

		// ボールの描画
		ball.draw(Palette::White);

		// フリッパーの描画
		leftFlipper.draw(Palette::Orange);
		rightFlipper.draw(Palette::Orange);

		// ジョイントの可視化
		leftJoint.draw(Palette::Red);
		rightJoint.draw(Palette::Red);
		spinnerJoint.draw(Palette::Red);
		windmillJoint.draw(Palette::Red);
		pendulumJoint.draw(Palette::Red);
		elevatorSliderJoint.draw(Palette::Red);
	}
}
