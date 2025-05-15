#include <tgmath.h>
#include "Vector2.h"
#include "Vector2F.h"

// �f�t�H���g�R���X�g���N�^
Vector2F::Vector2F(void)
{
	x = 0.0F;
	y = 0.0F;
}

// �R���X�g���N�^
Vector2F::Vector2F(float ix, float iy)
{
	x = ix;
	y = iy;
}

// �f�X�g���N�^
Vector2F::~Vector2F(void)
{
	// OutputDebugString("Vector2�@�f�X�g���N�^\n");
}

// Vector2�֕ϊ�����֐�
Vector2 Vector2F::ToVector2(void)
{
	Vector2 ret;
	ret.x = static_cast<int>(roundf(x));
	ret.y = static_cast<int>(roundf(y));
	return ret;
}