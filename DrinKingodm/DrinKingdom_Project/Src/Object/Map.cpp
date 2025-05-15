#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Scene/SceneGame.h"
#include "Map.h"

// �f�t�H���g�R���X�g���N�^
Map::Map(void)
{
	sceneGame_ = nullptr;

	mapimg_ = 0;

	pos_ = { 0,0 };

	type_ = TYPE::NONE;

	pos_ = { 0,0 };
}

// �f�X�g���N�^
Map::~Map(void)
{

}


bool Map::Init(SceneGame* parent)
{
	sceneGame_ = parent;
	
	mapimg_ = LoadGraph("Data/GameScene/Map_test.png");
	if (mapimg_ == -1)
	{
		OutputDebugString("map.png�摜��������Ȃ�");
		return false;
	}

	type_ = TYPE::TALK; 
	pos_ = { 0,0 };

	// �����Ŏg���}�b�v���w�肷��
	ChangeMap(TYPE::TALK);

}

void Map::Update(void)
{

	// ���݂̃}�b�v��ʂ��擾����
	Map::TYPE nowMapType = GetMapType();

	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// �}�b�v�^�C�v�̔���
	if (cameraPos.x == TALK_POS_X && cameraPos.y == TALK_POS_Y)
	{
		type_ = TYPE::TALK;
	}
	else if (cameraPos.x == COFFEE_POS_X && cameraPos.y == COFFEE_POS_Y)
	{
		type_ = TYPE::COFFEE;
	}	
	else if (cameraPos.x == JUICE_POS_X && cameraPos.y == JUICE_POS_Y)
	{
		type_ = TYPE::JUICE;
	}
	else if (cameraPos.x == 0 && cameraPos.y == 0)
	{
		type_ = TYPE::NONE;
	}
}

void Map::Draw(void)
{
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	DrawGraph(pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		mapimg_, true);

}

bool Map::Release(void)
{
	DeleteGraph(mapimg_);

	return false;
}

// �}�b�v��ʂ�Ԃ�
Map::TYPE Map::GetMapType(void)
{
	return type_;
}

// �}�b�v�ύX
void Map::ChangeMap(TYPE value)
{
	if (value == TYPE::TALK)
	{
		type_ = TYPE::TALK;		// �����ŗ��p����}�b�v��TALK�}�b�v
	}
	else if (value == TYPE::COFFEE)
	{
		type_ = TYPE::COFFEE;	// �����ŗ��p����}�b�v��COFFEE�}�b�v
	}
	else if (value == TYPE::JUICE)
	{
		type_ = TYPE::JUICE;	// �����ŗ��p����}�b�v��JUICE�}�b�v
	}
}

Vector2 Map::GetMapPos(void)
{
	return pos_;
}
