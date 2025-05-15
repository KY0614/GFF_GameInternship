#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class Map
{
public:
	// �萔
	// �}�b�v�̃T�C�Y
	static constexpr int SIZE_X = 2400;
	static constexpr int SIZE_Y = 960;

	// �e��}�b�v�̈ʒu
	// �}�b�v�㕔
	static constexpr int TALK_POS_X = 800;
	static constexpr int TALK_POS_Y = 0;

	// �}�b�v�����E
	static constexpr int COFFEE_POS_X = 800;
	static constexpr int COFFEE_POS_Y = 480;

	// �}�b�v������
	static constexpr int JUICE_POS_X = 0;
	static constexpr int JUICE_POS_Y = 480;

	// filter�֘A
	static constexpr int FILTER_POS_X = 1285;
	static constexpr int FILTER_POS_Y = 645;

	// �}�b�v�^�C�v
	enum class TYPE
	{
		NONE,
		TALK,
		COFFEE,
		JUICE
	};

	Map(void);
	~Map(void);

	bool Init(SceneGame* parent);
	void Update(void);
	void Draw(void);		// �`�揈��
	bool Release(void);		// �������

	// �}�b�v��ʂ�Ԃ�
	TYPE GetMapType(void);

	// �}�b�v�ύX
	void ChangeMap(TYPE value);

	Vector2 GetMapPos(void);

private:
	int mapimg_;

	// ���ݒn
	Vector2 pos_;

	// �������Ă���}�b�v�̎�� 
	TYPE type_;

	SceneGame* sceneGame_;

};

