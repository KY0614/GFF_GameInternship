#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"
#include "../Object/Map.h"
#include "../Object/Player.h"
#include "../Object/Message.h"
#include "../Object/CustomerBase.h"
#include "../Object/HotCup.h"
#include "../Object/IceCup.h"
#include "SceneGame.h"


// �f�t�H���g�R���X�g���N�^
SceneGame::SceneGame(void)
{
	map_ = nullptr;
	player_ = nullptr;
	message_ = nullptr;

	fase_ = FASE::NONE;

	mode_ = MODE::NONE;

	cameraPos_ = { 0,0 };

	dir_ = AsoUtility::DIR::MAX;

	moveSpeedH_ = 0.0f;

	moveSpeedW_ = 0.0f;

	counter_ = 0;
}

// �f�X�g���N�^
SceneGame::~SceneGame(void)
{

}


// ����������
bool SceneGame::Init(void)
{
	cursorImage_ = LoadGraph("Data/cursor.png");
	if (cursorImage_ == -1)
	{
		OutputDebugString("cursor.png�摜��������Ȃ�");
		return false;
	}

	messagecursorImage_ = LoadGraph("Data/Messagecursor.png");
	if (messagecursorImage_ == -1)
	{
		OutputDebugString("Messagecursor.png�摜��������Ȃ�");
		return false;
	}

	imgBack_ = LoadGraph("Data/GameScene/back.png");
	if (imgBack_ == -1)
	{
		OutputDebugString("back.png�摜��������Ȃ�");
		return false;
	}

	bgm_ = LoadSoundMem("Data/Triple-Sec.mp3");
	openBookSound_ = LoadSoundMem("Data/Sound/open book.mp3");
	closeBookSound_ = LoadSoundMem("Data/Sound/close book.mp3");
	// �ǂ݂��񂾉����Đ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(140, bgm_);
	ChangeVolumeSoundMem(255,openBookSound_ );
	ChangeVolumeSoundMem(255,closeBookSound_);

	// Drink�t�F�[�Y�̎��ɏo���摜�̓ǂݍ���
	int ret;
	ret = LoadDivGraph(
		"Data/GameScene/HotDrink.png",
		3,
		3,
		1,
		ANIM_SIZE_X,
		ANIM_SIZE_Y,
		&(animImgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Drink.png�摜��������Ȃ�");
		return false;
	}

	ret = LoadDivGraph(
		"Data/GameScene/IceDrink.png",
		3,
		3,
		1,
		ANIM_SIZE_X,
		ANIM_SIZE_Y,
		&(animIceImgs_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("IceDrink.png�摜��������Ȃ�");
		return false;
	}

	// UI�摜�̓ǂݍ���
	ret = LoadDivGraph(
		"Data/GameScene/MENU.png",
		2,
		2,
		1,
		UI_SIZE_X,
		UI_SIZE_Y,
		&(imgsUI_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("MENU.png�摜��������Ȃ�");
		return false;
	}

	// recipi�摜�̓ǂݍ���
	ret = LoadDivGraph(
		"Data/GameScene/recipe.png",
		2,
		2,
		1,
		400,
		380,
		&(imgRecipe_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("recipe.png�摜��������Ȃ�");
		return false;
	}

	ret = LoadDivGraph(
		"Data/GameScene/backs.png",
		2,
		2,
		1,
		UI_SIZE_X + 5,
		UI_SIZE_Y + 5,
		&(imgBacks_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("backs.png�摜��������Ȃ�");
		return false;
	}
	
	ret = LoadDivGraph(
		"Data/GameScene/next.png",
		2,
		2,
		1,
		UI_SIZE_X + 5,
		UI_SIZE_Y + 5,
		&(imgNext_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("backs.png�摜��������Ȃ�");
		return false;
	}


	// �}�b�v
	if (map_ == nullptr)
	{
		map_ = new Map();
	}
	map_->Init(this);
	
	// �v���C���[
	if (player_ == nullptr)
	{
		player_ = new Player(*map_);
	}
	player_->Init(this);	
	
	// ���b�Z�[�W
	if (message_ == nullptr)
	{
		message_ = new Message();
	}
	message_->Init(this);

	camera_ = new Camera(map_,player_);
	camera_->Init(this);

	// �q 
	auto hotcup = new HotCup(player_, camera_);
	hotcup->Init(this);
	customers_.push_back(hotcup);

	auto iceCup = new IceCup(player_, camera_);
	iceCup->Init(this);
	customers_.push_back(iceCup);

	// �J�n�̏�Ԃ�ݒ肷��
	// �}�b�v�̑I��
	map_->ChangeMap(Map::TYPE::TALK);

	dir_ = AsoUtility::DIR::MAX;

	fase_ = FASE::NONE;

	mode_ = MODE::NONE;

	page_ = PAGE::NONE;

	cameraPos_ = { Application::SCREEN_SIZE_X,0 };

	moveSpeedH_ = 0.0f;

	moveSpeedW_ = 0.0f;

	counter_ = 0;
	cnt_ = -1;

	hot_ = false;
	ice_ = false;
	isMessCursor_ = false;

	startTime = GetNowCount();
	 
	fadeInSpeed_ = 5;

	cntA = 0;

	isUI_ = false;
	isBack_ = false;

	ui_ = 0;

	bookCnt_ = 0;

	return true;
}

// �X�V����
void SceneGame::Update(void)
{
	auto& ins = InputManager::GetInstance();
	counter_++;

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	// �o�ߎ���
	GetTime();

	// �J����
	camera_->Update();

	size_t size = customers_.size();

	// ���q��2�l���ċA������I����ʂ�
	if (cnt_ == 2)
	{
		SceneManager::GetInstance().ChangeScene(
			SceneManager::SCENE_ID::GAMEOVER,
			true
		);
	}

	for (auto customer : customers_)
	{
		customer->Update();
	}

	if (mpos_.x > 50 && mpos_.x < 380 &&
		mpos_.y >50 && mpos_.y < 250)
	{
		isMessCursor_ = true;
	}
	else
	{
		isMessCursor_ = false;
	}

	switch (fase_)
	{
	case FASE::NONE:
		if (counter_ > 10)
		{
			cnt_++;
			cntA = 0;
			// �o�ߎ��Ԃ����Z�b�g
			startTime = GetNowCount();

			// �񋟂������̃��j���[�����Z�b�g 
			if (hot_ == true)
			{
				player_->ResetHotMenu();
			}
			else if (ice_ == true)
			{
				player_->ResetIceMenu();
			}

			// WAIT�t�F�[�Y�֑J��
			fase_ = FASE::WAIT;
		}
		break;

	case FASE::WAIT:
		hot_ = false;
		ice_ = false;
		message_->Update();
		break;

	case FASE::TALK:
		message_->Update();
		break;

	case FASE::MAKE:
		ui_ = 0;
		bookCnt_++;
		if (mpos_.x > 770 - UI_SIZE_X / 2 &&
			mpos_.x < 770 + UI_SIZE_X / 2 &&
			mpos_.y > 30 - UI_SIZE_X / 2 &&
			mpos_.y < 30 + UI_SIZE_X / 2
			)
		{
			ui_ = 1;
			if (isUI_ == false &&
				ins.IsTrgMouseLeft() == true)
			{
				isUI_ = true;
				page_ = PAGE::PAGE1;
				player_->PlaySounds(openBookSound_, 255);
			}
			else if (isUI_ == true&&
				ins.IsTrgMouseLeft() == true)
			{
				isUI_ = false;
				PlaySoundMem(closeBookSound_, DX_PLAYTYPE_BACK);
			}
			
		}

		if (isUI_ == true &&
			page_ == PAGE::PAGE1		&&
			(mpos_.x > 570 - UI_SIZE_X / 2 &&
			mpos_.x < 570 + UI_SIZE_X / 2 &&
			mpos_.y > 400 - UI_SIZE_X / 2 &&
			mpos_.y < 400 + UI_SIZE_X / 2)
			)
		{
			if (ins.IsTrgMouseLeft() == true)
			{
				page_ = PAGE::PAGE2;
				player_->PlaySounds(openBookSound_, 255);
			}
		}
		else if (isUI_ == true &&
			page_ == PAGE::PAGE2 &&
			(mpos_.x > 570 - UI_SIZE_X / 2 &&
				mpos_.x < 570 + UI_SIZE_X / 2 &&
				mpos_.y > 400 - UI_SIZE_X / 2 &&
				mpos_.y < 400 + UI_SIZE_X / 2)
			)
		{
			if (ins.IsTrgMouseLeft() == true)
			{
				isUI_ = false;
				PlaySoundMem(closeBookSound_, DX_PLAYTYPE_BACK);
			}
		}

		if (isUI_ == true)
		{
			return;
		}

		//�J�����J�ڒ��ł͂Ȃ�����
		//���i�����q�̑O�Ɏ����čs���ƒ񋟉�ʂ֑J�ڂ���
		if (mode_ == MODE::NONE && 
			mpos_.x > 460	&&
			mpos_.x < 527	&&
			mpos_.y > 380	&&
			mpos_.y < 460
			)
		{
			if (
				player_->GetHotCup() == Player::HOTCUP::TAKE  &&
				!(player_->GetHotMenu() == Player::HOTMENU::NONE)&&
				map_->GetMapType() == Map::TYPE::TALK &&
				ins.IsTrgMouseLeft() == true)
			{
				hot_ = true;
				// �񋟃t�F�[�Y��
				fase_ = FASE::DRINK;
				// Cup��������Ԃ�
				player_->ChangeHotCup(Player::HOTCUP::NONE);
				// �o�ߎ��Ԃ����Z�b�g
				startTime = GetNowCount();
			}
			else if (player_->GetIceCup() == Player::ICECUP::TAKE &&
				!(player_->GetIceMenu() == Player::ICEMENU::NONE) &&
				map_->GetMapType() == Map::TYPE::TALK &&
				ins.IsTrgMouseLeft() == true)
			{
				ice_ = true;
				// �񋟃t�F�[�Y��
				fase_ = FASE::DRINK;
				// Cup��������Ԃ�
				player_->ChangeIceCup(Player::ICECUP::NONE);
				// �o�ߎ��Ԃ����Z�b�g
				startTime = GetNowCount();
			}
		}
		break;

	case FASE::DRINK:
		for (auto customer : customers_)
		{
			customers_[cnt_]->SetDrink(1);
		}
		// �񋟉�ʂɑJ�ڂ���6�b�o�Ɖ�b��ʂ֑J��
		if (elapsedTime > 6000)
		{
			// ���Ԃ����Z�b�g
			startTime = GetNowCount();

			// �t�F�[�Y�J��
			fase_ = FASE::TALK2;
		}

		break;

	case FASE::TALK2:
		//for (auto customer : customers_)
		//{
		//	customers_[cnt_]->SetDrink(0);
		//}
		message_->Update();

		// �󂯎�������̂ɂ���ă��A�N�V�����ύX����
		//	hotCup_->Update();

		if (hot_ == true)
		{
			for (auto customer : customers_)
			{
				customers_[cnt_]->UpdateHot();
			}
		}
		else if (ice_ == true)
		{
			for (auto customer : customers_)
			{
				customers_[cnt_]->UpdateIce();
			}
		}

		counter_ = 0;

		break;

	default:
		break;
	}

	map_->Update();
	player_->Update();
}

// �`�揈��
void SceneGame::Draw(void)
{
	// �}�b�v�`��
	map_->Draw();

	if (cnt_ == 3)
	{
		return;
	}

	size_t size = customers_.size();

	switch (fase_)
	{
	case FASE::WAIT:
		if (cnt_ == 2)
		{
			return;
		}
		// ���b�Z�[�W�̕`��
		message_->Draw();
		break;

	case FASE::TALK:
		// ���b�Z�[�W�̕`��
		message_->Draw();

		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}
		

		//if (cnt_ == 1)
		//{
		//	hotCup_->Draw();
		//}
		//else if(cnt_ == 2)
		//{
		//	iceCup_->Draw();
		//}

		break;

	case FASE::MAKE:
		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		//if (cnt_ == 1)
		//{
		//	hotCup_->Draw();
		//}
		//else if (cnt_ == 2)
		//{
		//	iceCup_->Draw();
		//}

		break;

	case FASE::DRINK:
		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		if (cnt_ == 0)
		{
			// �񋟂��鎞�ɏo���摜���t�F�[�h�C�����Ȃ���\��
			if (cntA == 0)
			{
				FadeInImage(50, 30, animImgs_[0][0], 0);
			}
			else if (cntA == 1)
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				FadeInImage(300, 30, animImgs_[0][1], 0);
			}
			else if (cntA == 2)
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				DrawGraph(300, 30, animImgs_[0][1], true);
				FadeInImage(550, 30, animImgs_[0][2], 0);
			}
			else
			{
				DrawGraph(50, 30, animImgs_[0][0], true);
				DrawGraph(300, 30, animImgs_[0][1], true);
				DrawGraph(550, 30, animImgs_[0][2], true);
			}
		}
		else 
		{
			// �񋟂��鎞�ɏo���摜���t�F�[�h�C�����Ȃ���\��
			if (cntA == 0)
			{
				FadeInImage(50, 30, animIceImgs_[0][0], 0);
			}
			else if (cntA == 1)
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				FadeInImage(300, 30, animIceImgs_[0][1], 0);
			}
			else if (cntA == 2)
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				DrawGraph(300, 30, animIceImgs_[0][1], true);
				FadeInImage(550, 30, animIceImgs_[0][2], 0);
			}
			else
			{
				DrawGraph(50, 30, animIceImgs_[0][0], true);
				DrawGraph(300, 30, animIceImgs_[0][1], true);
				DrawGraph(550, 30, animIceImgs_[0][2], true);
			}
		}
		break;

	case FASE::TALK2:

		for (auto customer : customers_)
		{
			customers_[cnt_]->Draw();
		}

		// ���b�Z�[�W�̕`��
		message_->Draw();
			
			break;

	default:
		break;
	}

	player_->Draw();
	camera_->Draw();

	DrawRotaGraph(770,
		30,
		1.0f, 0.0f,
		imgsUI_[0][ui_],
		true);

	if (isUI_ == true && page_ == PAGE::PAGE1)
	{
		DrawRotaGraph(400,
			240,
			1.0f, 0.0f,
			imgRecipe_[0][0],
			true);	

		// �A�j���[�V�����X�s�[�h
		int animNum = static_cast<int>(
			static_cast<float>(bookCnt_) * 0.02f)
			% 2;

		DrawRotaGraph(570,
			400,
			1.0f, 0.0f,
			imgNext_[0][animNum],
			true);

	}
	else if (isUI_ == true && page_ == PAGE::PAGE2)
	{
		DrawRotaGraph(400,
			240,
			1.0f, 0.0f,
			imgRecipe_[0][1],
			true);

		// �A�j���[�V�����X�s�[�h
		int animNum = static_cast<int>(
			static_cast<float>(bookCnt_) * 0.02f)
			% 2;

		DrawRotaGraph(570,
			400,
			1.0f, 0.0f,
			imgBacks_[0][animNum],
			true);
	}

	DrawCursor();


	Vector2 cameraPos_ = camera_->GetCameraPos();

}

void SceneGame::DrawCursor(void)
{
	if (MesSwitch() == true)
	{
		if (mpos_.x > 50 && mpos_.x < 380 &&
			mpos_.y >50 && mpos_.y < 250)
		{
			isMessCursor_ = true;
			DrawGraph(mpos_.x, mpos_.y, messagecursorImage_, true);
		}
		else
		{
			DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
		}
	}
	else
	{
		isMessCursor_ = false;
		DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
	}
}

// �������
bool SceneGame::Release(void)
{
	// �T�E���h�n���h���̍폜
	DeleteSoundMem(bgm_);

	// �}�b�v�̉��
	map_->Release();		// �}�b�v���̑f�މ��
	delete map_;			// �C���X�^���X�̍폜
	map_ = nullptr;			// �|�C���^�ϐ���������
	
	message_->Release();	// ���b�Z�[�W���̑f�މ��	
	delete message_;		// �C���X�^���X�̍폜	
	message_ = nullptr;		// �|�C���^�ϐ���������	

	player_->Release();		// �v���C���[���̑f�މ��
	delete player_;			// �C���X�^���X�̍폜
	player_ = nullptr;		// �|�C���^�ϐ���������

	
	DeleteGraph(cursorImage_);
	DeleteGraph(animImgs_[0][0]);

	return true;
}

// �J�����̈ʒu��Ԃ�
Vector2 SceneGame::GetCameraPos(void)
{
	return camera_->GetCameraPos();
}

// ���݂̃t�F�[�Y���擾����
SceneGame::FASE SceneGame::GetFase(void)
{
	return fase_;
}

// �t�F�[�Y��ύX����
void SceneGame::ChangeFase(FASE value)
{
	fase_ = value;
}

// ���݃��b�Z�[�W���\�������ǂ���
bool SceneGame::MesSwitch(void)
{
	return message_->Switch();
}

bool SceneGame::GetIsMesCursor(void)
{
	return isMessCursor_;
}

// �o�ߎ��Ԃ�Ԃ�
int SceneGame::GetTime(void)
{
	elapsedTime = (GetNowCount() - startTime);

	return elapsedTime;
}

void SceneGame::FadeInImage(int x1, int y1, int imageFile, int fadeInSpeed)
{
	fadeInSpeed_ += 3;

	if (fadeInSpeed_ > 255)
	{
		fadeInSpeed_ = 0;

		cntA++;
		DrawGraph(x1, y1, imageFile, true);
	}

	if (cntA == 3)
	{
		return;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInSpeed_);
	DrawGraph(x1, y1, imageFile, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

CustomerBase::CUSTOMER SceneGame::GetCustomer(void)
{
	return customers_[cnt_]->GetCustomer();
}

CustomerBase::REACTION SceneGame::GetReaction(void)
{
	size_t size = customers_.size();
	for (auto customer : customers_)
	{
		return customers_[cnt_]->GetReaction();
	}
}

bool SceneGame::GetMessCursor(void)
{
	return isMessCursor_;
}

void SceneGame::Accele(float speed)
{
	moveSpeedW_ += speed;
	moveSpeedH_ += speed;

	// �E�ړ��̑��x����
	if (moveSpeedW_ > MAX_MOVE_WSPEED)
	{
		moveSpeedW_ = MAX_MOVE_WSPEED;
	}

	// ���ړ��̑��x����
	if (moveSpeedW_ < -MAX_MOVE_WSPEED)
	{
		moveSpeedW_ = -MAX_MOVE_WSPEED;
	}

	// ��ړ��̑��x����
	if (moveSpeedH_ < -MAX_MOVE_HSPEED)
	{
		moveSpeedH_ = -MAX_MOVE_HSPEED;
	}

	// ���ړ��̑��x����
	if (moveSpeedH_ > MAX_MOVE_HSPEED)
	{
		moveSpeedH_ = MAX_MOVE_HSPEED;
	}

}

// ����
void SceneGame::Decelerate(float speed)
{
	// �ړ������F�E
	if (moveSpeedW_ > 0.0f)
	{
		moveSpeedW_ -= speed;
		if (moveSpeedW_ < 0.0f)
		{
			moveSpeedW_ = 0.0f;
		}
	}
	// �ړ������F��
	else if (moveSpeedW_ < 0.0f)
	{
		moveSpeedW_ += speed;
		if (moveSpeedW_ > 0.0f)
		{
			moveSpeedW_ = 0.0f;
		}
	}

	// �ړ������F��
	if(moveSpeedH_ < 0.0f)
	{
		moveSpeedH_ += speed;
		if (moveSpeedH_ > 0.0f)
		{
			moveSpeedH_ = 0.0f;
		}
	}
	// �ړ������F��
	else if (moveSpeedH_ > 0.0f)
	{
		moveSpeedH_ -= speed;
		if (moveSpeedH_ < 0.0f)
		{
			moveSpeedH_ = 0.0f;
		}
	}
}

void SceneGame::Move(int pos)
{
	pos += moveSpeedH_;
}
