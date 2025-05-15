#include <cmath>
#include "../Scene/SceneGame.h"
#include "../Manager/Camera.h"
#include "../Object/Player.h"
#include "HotCup.h"

HotCup::HotCup(Player* player,Camera*camera)
{
	player_ = player;
	camera_ = camera;
}

HotCup::~HotCup(void)
{
}

void HotCup::Update(void)
{
	// ���N���X�̊֐����Ă�
	CustomerBase::Update();

}

void HotCup::UpdateHot(void)
{
	Player::HOTMENU  hotdrink = player_->GetHotMenu();
	Player::ICEMENU  icedrink = player_->GetIceMenu();

	switch (hotdrink)
	{
	case Player::HOTMENU::NONE:
		if (icedrink == Player::ICEMENU::NONE)
		{
			reaction_ = REACTION::BAD;
		}
		break;

	case Player::HOTMENU::ESPRESSO:
		reaction_ = REACTION::HAPPY;

		time++;

		break;

	case Player::HOTMENU::AMERICANO:
		reaction_ = REACTION::NORMAL;
		break;

	case Player::HOTMENU::LATTE:
		reaction_ = REACTION::BAD;
		break;

	case Player::HOTMENU::MOCA:
		reaction_ = REACTION::BAD;
		break;

	case Player::HOTMENU::MACCHIATO:
		reaction_ = REACTION::BAD;
		break;

	default:
		break;
	}
}

void HotCup::UpdateIce(void)
{
	Player::HOTMENU  hotdrink = player_->GetHotMenu();
	Player::ICEMENU  icedrink = player_->GetIceMenu();

	switch (icedrink)
	{
	case Player::ICEMENU::NONE:
		if (hotdrink == Player::HOTMENU::NONE)
		{
			reaction_ = REACTION::BAD;
		}
		break;

	case Player::ICEMENU::ESPRESSO:
		reaction_ = REACTION::BAD;
		break;

	case Player::ICEMENU::AMERICANO:
		reaction_ = REACTION::BAD;
		break;

	case Player::ICEMENU::LATTE:
		reaction_ = REACTION::BAD;
		break;

	case Player::ICEMENU::MOCA:
		reaction_ = REACTION::BAD;
		break;

	case Player::ICEMENU::MACCHIATO:
		reaction_ = REACTION::BAD;
		break;

	default:
		break;
	}

}

void HotCup::Draw(void)
{
	Vector2 cameraPos = camera_->GetCameraPos();

	//CustomerBase::Draw();
	//DrawFormatString(0, 60, 0xff0000, "animNum : %d", animNum_);
	//DrawFormatString(0, 20, 0xff0000, "blink : %d", blink_);
	//DrawFormatString(0, 40, 0xff0000, "rand : %d", rand_);
	//DrawFormatString(0, 60, 0xff0000, "WINK : %d", wink_);

	// �摜�̍���ł͂Ȃ����S���W
	DrawRotaGraph(
		pos_.x - cameraPos.x,
		pos_.y - cameraPos.y,
		1.0f,		// �g��
		0.0f,		// ��]
		imgs_[static_cast<int>(reaction_) + drink_][animNum_],
		true,
		false);

	// �摜�̍���ł͂Ȃ����S���W
	//DrawRotaGraph(
	//	pos_.x - cameraPos.x,
	//	pos_.y - cameraPos.y,
	//	1.0f,		// �g��
	//	0.0f,		// ��]
	//	/*imgs_[0][static_cast<int>(reaction_)]*/image_,
	//	true,
	//	false);
}

void HotCup::SetParam(void)
{
	// �摜�̃t�@�C����
	imgFileName = "Hot_Cup.png";

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
