#pragma once
#include <cmath>
#include <algorithm>
class Raindrop
{
private:
	Vec2 m_position;	//位置
	Vec2 m_velocity;	//速度

	double m_radius = 10.0;	//あたり判定の半径

public:
	//コンストラクタ
	Raindrop(const Vec2& startPos)
		: m_position(startPos)
		, m_velocity(0, 0){ }

	// 敵が追うための位置を取得
	Vec2 getPosition() const noexcept
	{
		return m_position;
	}
	//更新処理(物理演算)
	void update(const Vec2& gravity, double carSpeed, double deltaTime)
	{
		Vec2 playerInputForce(0, 0); //プレイヤー入力による力

		//難易度に応じて入力を増やす
		const double baseControl = 500.0;		//難易度最小の上限

		const double difficultyScale = 1.1;		//carSpeed 1.0あたりの増分
		const double maxControl = 1500.0;		//難易度最大の上限

		//プレイヤー入力による力の大きさを計算
		double playerControlMagitude = baseControl + carSpeed * difficultyScale;
		playerControlMagitude = std::clamp(playerControlMagitude, baseControl, maxControl);

		if (KeyA.pressed())
			playerInputForce.x -= playerControlMagitude; //左に押す

		if (KeyD.pressed())
			playerInputForce.x += playerControlMagitude; //右に押す

		if (KeyS.pressed())
			playerInputForce.y += playerControlMagitude; //下に押す

		if (KeyW.pressed())
			playerInputForce.y -= playerControlMagitude; //上に押す

		//ベクトルのじょうげんを500に設定
		const double len = std::hypot(playerInputForce.x, playerInputForce.y);
		if (len > 0.0)
		{
			const double scale = playerControlMagitude / len;
			// scaleが1.0未満ならば縮小, 1.0より大きければ拡大
			playerInputForce = playerInputForce * scale;
		}
		//物理演算
		//空気抵抗
		const Vec2 airResistanceForce(0, -(carSpeed * 1.0));

		//合力 = 重力 + 空気抵抗
		const Vec2 totalForce = gravity + airResistanceForce + playerInputForce;

		//力を速度に加算(速度 = 現在の位置 + 力 * 時間)
		m_velocity += totalForce * deltaTime;

		//速度を位置に反映(位置 = 現在の位置 + 速度 * 時間)
		m_position += m_velocity * deltaTime;

		//摩擦(速度をすこしずつ減衰)
		const double friction = 1.0;
		m_velocity *= (1.0 - friction * deltaTime);

		//画面外にでないように位置を制限
		m_position.x = Clamp(m_position.x, 0.0, (double)Scene::Width());
		m_position.y = Clamp(m_position.y, 0.0, (double)Scene::Height());
	}

	//描画処理
	void draw() const
	{
		const Vec2 pos(m_position.x, m_position.y);
		const Circle collider(pos, m_radius);

		const Circle body(pos, m_radius);
		body.draw(ColorF(0.2, 0.6, 1.0, 0.8));

		body.drawFrame(1.5, ColorF(1.0, 1.0, 1.0, 0.5));

		const double shineOffset = m_radius * 0.35;
		const double shineRadius = m_radius * 0.3;

		Circle(pos.x - shineOffset, pos.y - shineOffset, shineRadius).draw(ColorF(1.0, 1.0, 1.0, 0.7));
	}
};
