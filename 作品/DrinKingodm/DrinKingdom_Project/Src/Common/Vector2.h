#pragma once

class Vector2F;

class Vector2
{
public:
	// メンバー関数

	// デフォルトコンストラクタ
	Vector2(void);

	// コンストラクタ
	Vector2(int ix, int iy);

	// デストラクタ
	~Vector2(void);

	// Vector2F へ変換
	Vector2F ToVector2F(void);

	// メンバー変数
	int x;
	int y;
};