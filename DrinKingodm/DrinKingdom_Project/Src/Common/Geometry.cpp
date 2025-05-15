#include <DxLib.h>
#include<cmath>
#include "../Common/Geometry.h"

void Rect::Draw(unsigned int color)
{
	DrawBox(Left(),Top(),	// ����
		Right(), Bottom(),	// �E��
		color,true);
}

Vector2D Vector2D::operator*(float scale) const
{
	return { x * scale,y * scale };
}

void Vector2D::operator += (const Vector2D& vec)
{
	x = x + vec.x;
	y = y + vec.y;
}

void Vector2D::operator -= (const Vector2D& vec)
{
	x = x - vec.x;
	y = y - vec.y;
}

Vector2D Vector2D::operator-() const
{
	return { -x,-y };
}

float Vector2D::Length() const
{
	// return sqrtf(x*x + y*y)���hypot���g�����ق����ǂ�
	return std::hypot(x, y);
}

void Vector2D::Normalize()
{
	auto len = Length();
	if (len == 0.0f)
	{
		x = 0.0f;
		y = 0.0f;
		return;
	}
	x /= len;
	y /= len;

	// ���̏������͂ǂ�ǂ񏬂����Ȃ��Ă����̂Ń_��
	// x /= Length()
	// y /= Length()
}

Vector2D Vector2D::Normalized() const
{
	auto len = Length();
	return { x / len,y / len };
}

void Circle::Draw(unsigned int color)
{
	DrawCircleAA(pos.x, pos.y,	// ���W
		radius,		// ���a
		32,			// ���_��
		color, true);
}