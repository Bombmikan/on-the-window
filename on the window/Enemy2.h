#pragma once
#include <cmath>

class Enemy2
{
private:
	Vec2 m_pos;
	Vec2 m_vel;
	double Radius = 100.0;

	//挙動パラメータ
	double maxSpeed = 100.0;	//最大速度
	double maxAccel = 140.0;	//最大加速度
	double distance = 10.0;
public:
	Enemy2(const Vec2& startPos)
		: m_pos(startPos)
		, m_vel(0, 0)
	{ }
};
