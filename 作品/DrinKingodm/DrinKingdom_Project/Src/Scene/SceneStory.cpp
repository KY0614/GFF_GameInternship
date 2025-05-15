#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "SceneStory.h"

// �f�t�H���g�R���X�g���N�^
SceneStory::SceneStory(void)
{
	bgm_ = -1;
	buttonSelectSound_ = -1;
	buttonPushSound_ = -1;

	storyImg_ = -1;
	cursorImage_ = -1;

	selectImage_ = -1;
	select_onImage_ = -1;

	title_pushImage_ = -1;
	titleImage_ = -1;
	start_onImage_ = -1;
	start_offImage_ = -1;

	mpos_ = { 0,0 };
	spos_ = { 0,0 };

	isTitle_ = false;
	isPlay_ = false;
	isSelect_ = false;
	wasSelect_ = false;
}

// �f�X�g���N�^
SceneStory::~SceneStory(void)
{

}


// ����������
bool SceneStory::Init(void)
{
	bgm_ = LoadSoundMem("Data/Story.mp3");
	buttonSelectSound_ = LoadSoundMem("Data/Sound//Title_button.mp3");
	buttonPushSound_ = LoadSoundMem("Data/Sound//Title_button_push.mp3");
	// �ǂ݂��񂾉����Đ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(140, bgm_);
	ChangeVolumeSoundMem(230, buttonSelectSound_);
	ChangeVolumeSoundMem(180, buttonPushSound_);

	storyImg_ = LoadGraph("Data/Opening/story.png");
	if (storyImg_ == -1)
	{
		OutputDebugString("story.png�摜��������Ȃ�");
		return false;
	}

	cursorImage_ = LoadGraph("Data/cursor.png");
	if (cursorImage_ == -1)
	{
		OutputDebugString("cursor.png�摜��������Ȃ�");
		return false;
	}

	start_onImage_ = LoadGraph("Data/Title/Start_on.png");
	if (start_onImage_ == -1)
	{
		OutputDebugString("Start_on.png�摜��������Ȃ�");
		return false;
	}

	start_offImage_ = LoadGraph("Data/Title/Start_off.png");
	if (start_offImage_ == -1)
	{
		OutputDebugString("Start_off.png�摜��������Ȃ�");
		return false;
	}


	titleImage_ = LoadGraph("Data/GameOver/Title.png");
	title_pushImage_ = LoadGraph("Data/GameOver/Title_push.png");
	if (titleImage_ == -1)
	{
		OutputDebugString("Thank.png�摜��������Ȃ�");
		return false;
	}
	if (title_pushImage_ == -1)
	{
		OutputDebugString("Thank.png�摜��������Ȃ�");
		return false;
	}

	selectImage_ = LoadGraph("Data/Title/select.png");
	if (selectImage_ == -1)
	{
		OutputDebugString("select.png�摜��������Ȃ�");
		return false;
	}

	select_onImage_ = LoadGraph("Data/Title/select_on.png");
	if (select_onImage_ == -1)
	{
		OutputDebugString("select_on.png�摜��������Ȃ�");
		return false;
	}

	mpos_ = { 0,0 };

	spos_ = { 0, TITLEBUTTON_POS_Y };

	isTitle_ = false;
	isPlay_ = false;
	isSelect_ = false;

	return true;
}

// �X�V����
void SceneStory::Update(void)
{
	auto& ins = InputManager::GetInstance();

	SetMouseDispFlag(false);

	ins.GetMouse();
	mpos_ = ins.GetMousePos();

	isTitle_ = false;
	isPlay_ = false;

	//�{�^�������őI�����鏈��
	if (ins.IsTrgDown(KEY_INPUT_RIGHT)
		|| ins.IsTrgDown(KEY_INPUT_D))
	{
		spos_.x = SELECT_IMG_POS_X;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}
	else if (ins.IsTrgDown(KEY_INPUT_LEFT)
		|| ins.IsTrgDown(KEY_INPUT_A))
	{
		spos_.x = 0;
		PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
	}

	if (spos_.x == 0)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			isTitle_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::TITLE,
				true
			);
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			isPlay_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::OPENING,
				true
			);
		}
	}

	// �}�E�X�J�[�\���ƃ{�^���̋�`����
	if (
		mpos_.x > TITLEBUTTON_POS_X &&
		mpos_.x < TITLEBUTTON_POS_X + SIZE_WIDTH &&
		mpos_.y > TITLEBUTTON_POS_Y &&
		mpos_.y < TITLEBUTTON_POS_Y + SIZE_HEIGHT
		)
	{
		isSelect_ = true;
		spos_.x = 0;
		if (!wasSelect_)
		{
			PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
		}
		if (ins.IsTrgMouseLeft() == true)
		{
			isTitle_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::TITLE,
				true
			);
		}
	}
	else if (
		mpos_.x > PLAYBUTTON_POS_X &&
		mpos_.x < PLAYBUTTON_POS_X + SIZE_WIDTH &&
		mpos_.y > TITLEBUTTON_POS_Y &&
		mpos_.y < TITLEBUTTON_POS_Y + SIZE_WIDTH
		)
	{
		isSelect_ = true;
		spos_.x = SELECT_IMG_POS_X;
		if (!wasSelect_)
		{
			PlaySoundMem(buttonSelectSound_, DX_PLAYTYPE_BACK);
		}
		if (ins.IsTrgMouseLeft() == true)
		{
			isPlay_ = true;
			PlaySoundMem(buttonPushSound_, DX_PLAYTYPE_BACK);
			SceneManager::GetInstance().ChangeScene(
				SceneManager::SCENE_ID::OPENING,
				true
			);
		}
	}
	else
	{
		isSelect_ = false;
	}

	wasSelect_ = isSelect_;
}

// �`�揈��
void SceneStory::Draw(void)
{
	DrawGraph(0, 0, storyImg_, true);

	DrawGraph(spos_.x, spos_.y, selectImage_, true);

	if (!isTitle_)
	{
		DrawGraph(TITLEBUTTON_POS_X, TITLEBUTTON_POS_Y, titleImage_, true);	// �^�C�g����
	}
	else
	{
		DrawGraph(TITLEBUTTON_POS_X, TITLEBUTTON_POS_Y, title_pushImage_, true);	// �^�C�g����
		DrawGraph(0, TITLEBUTTON_POS_Y, select_onImage_, true);
	}

	if (!isPlay_)
	{
		DrawGraph(PLAYBUTTON_POS_X, TITLEBUTTON_POS_Y, start_offImage_, true);
	}
	else
	{
		DrawGraph(PLAYBUTTON_POS_X, TITLEBUTTON_POS_Y, start_onImage_, true);
		DrawGraph(SELECT_IMG_POS_X, TITLEBUTTON_POS_Y, select_onImage_, true);
	}

	DrawGraph(mpos_.x, mpos_.y, cursorImage_, true);
}

// �������
bool SceneStory::Release(void)
{
	DeleteGraph(title_pushImage_);
	DeleteGraph(titleImage_);
	DeleteGraph(start_offImage_);
	DeleteGraph(start_onImage_);
	DeleteGraph(selectImage_);
	DeleteGraph(select_onImage_);
	DeleteGraph(cursorImage_);
	DeleteGraph(storyImg_);

	// �T�E���h�n���h���̍폜
	DeleteSoundMem(bgm_);
	DeleteSoundMem(buttonSelectSound_);
	DeleteSoundMem(buttonPushSound_);

	return true;
}