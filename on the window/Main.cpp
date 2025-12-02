# include <Siv3D.hpp> // Siv3D v0.6.16 (描画や入力、時間管理のために利用します)
#include "Raindrop.h"
#include "Enemy.h"

void Main()
{
	Window::Resize(1280, 730);

	P2World world;

	P2Body body;
	Array<Enemy> enemies;

	double spawnTimer = 0.0;
	const double spawnInterval = 2.0;

	//プレイヤーの初期位置を自作のMyVec2で定義
	const Vec2 playerStartPos = { static_cast<double> (Scene::Center().x), 360.0 };
	Raindrop player(playerStartPos);

	Enemy enemy({ playerStartPos.x + 200.0, playerStartPos.y });
	//ガラスの傾斜角
	const double tilAngle = 180_deg;
	//重力の強さ
	const double gravityMagnitude = 120.0;

	//傾斜を考慮した重力ベクトルを自作のVec2で定義
	const Vec2 gravity =
	{
		gravityMagnitude * Sin(tilAngle),	// x成分
		gravityMagnitude * Cos(tilAngle)	// y成分
	};
	double carSpeed = 30.0;

	// --- ゲームループ ---
	while (System::Update())
	{
		double dt = Scene::DeltaTime();

		spawnTimer += dt;
		if (spawnTimer >= spawnInterval)
		{
			spawnTimer -= spawnInterval; // タイマーをリセット

			// 画面の上端のランダムな位置に出現させる
			double randomX = Random(0.0, (double)Scene::Width());
			Vec2 spawnPos(randomX, -50.0); //画面の少し上から

			//敵を生成してリストに追加
			Enemy newEnemy(spawnPos);

			//パラメータ
			/*newEnemy.setMaxSpeed(200.0);
			newEnemy.setMaxAccel(100.0);
			newEnemy.setStopDistance(100.0);*/

			enemies << newEnemy;	//配列に追加
		}
		//更新処理
		player.update(gravity, carSpeed, dt);

		for (auto& e : enemies)
		{
			//プレイヤーの位置を取得し、敵の移動計算を行う
			enemy.update(player.getPosition(), dt);
		}
		
		//難易度上昇
		carSpeed += dt * 1.01;

		//描画処理
		Scene::SetBackground(ColorF(0.1, 0.2, 0.3));
		player.draw();
		for (const auto& e : enemies)
		{
			enemy.draw();
		}
		

		//デバッグ表示
		ClearPrint();
		Print(U"Speed: {:.0f}"_fmt(carSpeed));
	}
}
