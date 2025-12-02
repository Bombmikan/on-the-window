#pragma once
#include <cmath>
#include "MyVector.h"

class Enemy
{
private:
	Vec2 m_pos;
	Vec2 m_vel;
	double m_radius = 12.0;

	//挙動パラメータ
	double m_maxSpeed = 250.0;				// ピクセル/ 秒
	double m_maxAccel = 200.0;				// 加速度 速度 / 秒
	double m_stopDistance = 100.0;			// プレイヤーとの距離

public:
	Enemy(const Vec2& startPos)
		: m_pos(startPos)
		, m_vel(0, 0)
	{ }

	//プレイヤー位置を向かって追従
	void update(const Vec2& playerPos, double deltaTime)
	{
		// プレイヤー方向ベクトル
		Vec2 toPlayer = playerPos - m_pos;
		double dist = std::hypot(toPlayer.x, toPlayer.y);

		// 目標速度を計算
		Vec2 desired(0, 0);
		if (dist > 1e-6 && dist > m_stopDistance)
		{
			desired = toPlayer * (m_maxSpeed / dist);	// 正規化してm_maxspeed×
		}
		// steering = desired - current velocity
		Vec2 steering = desired - m_vel;

		// steering の大きさを制限(加速度上限)
		double steerLen = std::hypot(steering.x, steering.y);
		double maxStep = m_maxAccel * deltaTime;
		if (steerLen > maxStep && steerLen > 0.0)
		{
			steering = steering * (maxStep / steerLen);
		}

		// 速度更新
		m_vel += steering;

		//速度を制限(最大速度)
		double velLen = std::hypot(m_vel.x, m_vel.y);
		if(velLen > m_maxSpeed && velLen > 0.0)
		{
			m_vel = m_vel * (m_maxSpeed / velLen);
		}

		//位置更新
		m_pos += m_vel * deltaTime;

		//画面内に制限
		m_pos.x = Clamp(m_pos.x, 0.0, (double)Scene::Width());
		m_pos.y = Clamp(m_pos.y, 0.0, (double)Scene::Height());

		
	}
	void draw() const
	{
		const s3d::Vec2 pos((float)m_pos.x, (float)m_pos.y);
		const s3d::Circle c(pos, m_radius);
		c.draw(ColorF(1.0, 0.4, 0.4, 0.9));
		c.drawFrame(1, Palette::White);
	}

	Vec2 getPosition() const { return m_pos; }

	//チューニング用setter
	void setMaxSpeed(double s) noexcept { m_maxSpeed = s;}
	void setMaxAccel(double a) noexcept { m_maxAccel = a; }
	void setStopDistance(double d) noexcept { m_stopDistance = d; }
};
