#pragma once
class MyVec2
{
public:
	double x, y;

	//コンストラクタ
	MyVec2()
		:x(0.0)
		,y(0.0){}

	MyVec2(double _x, double _y)
		:x(_x)
		,y(_y){ }

	// ベクトル同志の足し算(v1 + v2)
	MyVec2 operator+(const MyVec2& other) const
	{
		return MyVec2(x + other.x, y + other.y);
	}

	//ベクトル同士の引き算(v1 - v2)
	MyVec2 operator-(const MyVec2& other) const
	{
		return MyVec2(x - other.x, y - other.y);
	}

	//ベクトルと数値の掛け算(v * 5.0)
	MyVec2 operator*(double scalar) const
	{
		return MyVec2(x * scalar, y * scalar);
	}

	//自分自身に足し込む(v1 += v2)
	MyVec2& operator+=(const MyVec2& other)
	{
		x += other.x;
		y += other.y;
		return *this; //自分自身を返す
	}

	//自分自身に掛け算する(v *= 50)
	MyVec2 operator*=(double scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
};
