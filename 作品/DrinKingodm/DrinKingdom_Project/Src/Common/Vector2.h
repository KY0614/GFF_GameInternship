#pragma once

class Vector2F;

class Vector2
{
public:
	// �����o�[�֐�

	// �f�t�H���g�R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int ix, int iy);

	// �f�X�g���N�^
	~Vector2(void);

	// Vector2F �֕ϊ�
	Vector2F ToVector2F(void);

	// �����o�[�ϐ�
	int x;
	int y;
};