#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Scene/SceneGame.h"
#include "../Utility/AsoUtility.h"
#include "CustomerBase.h"

CustomerBase::CustomerBase(void)
{
	imgFileName = "";

	pos_ = { 0,0 };

	size_ = { 0,0 };

	cntAnim_ = 0;

	speedAnim_ = 0.0f;

	customer_ = CUSTOMER::HOTCUP;

	reaction_ = REACTION::NONE;

}

CustomerBase::~CustomerBase(void)
{
}

bool CustomerBase::Init(SceneGame* scenegame)
{
	sceneGame_ = scenegame;

	// �L�����ʂ̃p�����[�^�[�ݒ�
	SetParam();

	// ���ߐF��ύX
	// SetTransColor(255, 0, 255);

	// �摜�̓ǂݍ���
	std::string path = "Data/GameScene/Customer/";
	path = path + imgFileName;

	image_ = LoadGraph(path.c_str());
	if (image_ == -1)
	{
		OutputDebugString("png�摜��������Ȃ�");
		return false;
	}

	int ret;

	ret = LoadDivGraph(
		path.c_str(),
		5 * NUM_ANIM,
		NUM_ANIM,
		5,
		size_.x,
		size_.y,
		&(imgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("�摜�̏��������s");
		return false;
	}

	// �����ʒu
	//pos_ = { 0,0 };

	// �A�j���[�V�����J�E���^�̃��Z�b�g
	cntAnim_ = 0;

	speedAnim_ = 0.2f;

	animNum_ = 0;
	increasing = true;

	time = 0;

	blink_ = 0;
	rand_ = 0;

	wink_ = WINK::NONE;

	winkRand_ = false;

	drink_ = 0;

	return true;
}

void CustomerBase::Update(void)
{
	Wink();

	// �t�F�[�Y����Update����
	switch (sceneGame_->GetFase())
	{
	case SceneGame::FASE::TALK:
		UpdateTalk();
		break;

	case SceneGame::FASE::MAKE:
		UpdateMake();
		break;

	case SceneGame::FASE::DRINK:
		UpdateDrink();
		break;

	case SceneGame::FASE::TALK2:
		UpdateTalk2();
		break;
	}

}

void CustomerBase::UpdateTalk(void)
{

}

void CustomerBase::UpdateHot(void)
{
}

void CustomerBase::UpdateIce(void)
{
}

void CustomerBase::UpdateMake(void)
{
}

void CustomerBase::UpdateDrink(void)
{
}

void CustomerBase::UpdateTalk2(void)
{
}

void CustomerBase::Draw(void)
{

	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// �A�j���[�V�����X�s�[�h
	int animNum = static_cast<int>(
		static_cast<float>(cntAnim_) * speedAnim_)
		% 4;

	// �摜�̍���ł͂Ȃ����S���W
	DrawRotaGraph(
		pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,		// �g��
		0.0f,		// ��]
		//image_
		imgs_[0][0],
		true,
		false);

}

bool CustomerBase::Release(void)
{
	for (int y = 0; y < numY; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}

	return true;
}

void CustomerBase::SetParam(void)
{
	// �摜�̃t�@�C����
	imgFileName = ".png";

	//�\�����W�̐ݒ�
	pos_ = { POS_X + 50,POS_Y };

	// �T�C�Y�̐ݒ�
	size_ = { SIZE_X,SIZE_Y };

	numY = 5;

	// �A�j���[�V�������x
	speedAnim_ = 1.0f;

	// ���X����q�̎��
	customer_ = CUSTOMER::HOTCUP;

	// ���i��n�����Ƃ��̔���
	reaction_ = REACTION::NONE;

}

void CustomerBase::Wink(void)
{
	int time = sceneGame_->GetTime();

	if ((time / 1000) % 5 == 0)
	{

		if (!winkRand_)
		{
			rand_ = GetRand(100);
		}
		winkRand_ = true;
	}
	else
	{
		winkRand_ = false;
	}

	if (rand_ > 90)
	{
		wink_ = WINK::NONE;
	}
	else if (rand_ > 50)
	{
		wink_ = WINK::ONCE;
	}
	else
	{
		wink_ = WINK::TWICE;
	}

	switch (wink_)
	{
	case CustomerBase::WINK::NONE:
		animNum_ = 0;
		blink_ = 0;
		cntAnim_ = 0;
		break;

	case CustomerBase::WINK::ONCE:
		cntAnim_++;

		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% 7;

		if (animNum_ > 5)
		{
			rand_ = 100;
			wink_ = WINK::NONE;
		}

		break;

	case CustomerBase::WINK::TWICE:
		cntAnim_++;

		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% 7;

		if (animNum_ == 0)
		{
			blink_++;
		}
		if (blink_ > 4 && animNum_ == 6)
		{
			rand_ = 100;
			wink_ = WINK::NONE;
		}

		break;

	default:
		break;
	}
}

CustomerBase::CUSTOMER CustomerBase::GetCustomer(void)
{
	return customer_;
}

CustomerBase::REACTION CustomerBase::GetReaction(void)
{
	return reaction_;
}

void CustomerBase::SetDrink(int value)
{
	drink_ = value;
}

