#pragma once

class Vector2;

class Vector2F
{
public:

	// �f�t�H���g�R���X�g���N�^
	Vector2F(void);
	
	// �R���X�g���N�^
	Vector2F(float ix, float iy);

	// �f�X�g���N�^
	~Vector2F(void);

	// Vector2�֕ϊ�
	Vector2 ToVector2(void);


	float x;
	float y;

private:
};