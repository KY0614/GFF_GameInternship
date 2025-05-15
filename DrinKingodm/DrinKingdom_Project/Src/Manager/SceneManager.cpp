#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "InputManager.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/SceneStory.h"
#include "../Scene/SceneOpening.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneGameOver.h"
#include "SceneManager.h"

// �V���O���g����
// ----------------
// instance_�̏�����
SceneManager* SceneManager::instance_ = nullptr;

// �f�t�H���g�R���X�g���N�^
SceneManager::SceneManager(void)
{
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::NONE;

	isSceneChanging_ = false;

	fader_ = nullptr;
	camera_ = nullptr;
	scene_ = nullptr;

}

// �f�X�g���N�^
SceneManager::~SceneManager(void)
{

}


// ����������
bool SceneManager::Init(void)
{
	// �t�F�[�h
	fader_ = new Fader();
	fader_->Init();

	// �V�[���̐�������
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;
	DoChangeScene();
	
	// �^�C�g�����t�F�[�h�C���ŕ\������
	fader_->SetFade(Fader::STATE::FADE_IN);
	isSceneChanging_ = true;

	// �C���X�^���X�𐶐�����
	// ---------------------------

	//SetBackgroundColor(0, 130, 130);

	return true;
}

// �X�V����
void SceneManager::Update(void)
{
	if (scene_ == nullptr)
	{
		return;
	}

	// �t�F�[�h�������t�F�[�h���s���Ă��Ȃ��ꍇ�����͂Ȃɂ�����Ȃ�
	fader_->Update();
	
	if (isSceneChanging_ == true)
	{
		// �t�F�[�h��
		Fade();
	}
	else	// �t�F�[�h�I��
	{
		// �e�V�[���̍X�V����
		scene_->Update();
	}

}

// �`�揈��
void SceneManager::Draw(void)
{
	scene_->Draw();

	// �t�F�[�h
	fader_->Draw();
}

// �������
bool SceneManager::Release(void)
{
	//  /�V�[���̉������
	ReleaseScene(sceneID_);

	// �t�F�[�h�̉��
	delete fader_;
	fader_ = new Fader();

	// �V���O���g����
	// -------------------
	Destory();

	return true;
}

// �V�[���؂�ւ����˗�����֐�
void SceneManager::ChangeScene(SCENE_ID nextID,bool isToFade)
{
	// �t�F�[�h�������I����ɃV�[����J�ڂ���ꍇ������ׁA
	// �J�ڐ�V�[��ID�������o�[�ϐ��ɕێ�����
	waitSceneID_ = nextID;

	if (isToFade)
	{
		// �t�F�[�h�����{���A�V�[���J�ڂ���
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else
	{
		// �t�F�[�h�����{�����ɃV�[���J�ڂ���
		DoChangeScene();
	}
}

// �V�[����؂�ւ���
void SceneManager::DoChangeScene(void)
{
	// ����(sceneID_)�̃V�[�������
	ReleaseScene(sceneID_);

	// ���Ɉړ�����V�[��(waitSceneId_)�������Ă���
	sceneID_ = waitSceneID_;

	switch (sceneID_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		break;

	case SCENE_ID::STORY:
		scene_ = new SceneStory();
		break;

	case SCENE_ID::OPENING:
		scene_ = new SceneOpening();
		break;

	case SCENE_ID::GAME:
		scene_ = new SceneGame();
		break;

	case SCENE_ID::GAMEOVER:
		scene_ = new SceneGameOver();
		break;

	default:
		break;
	}
	scene_->Init();

	// �V�[���̑J�ڂ��I�������̂Ŏ��̃V�[�����N���A����
	waitSceneID_ = SCENE_ID::NONE;

}

// �t�F�[�h�����{�p�֐�
void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();

	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd() == true)
		{
			// �V�[���؂�ւ�
			DoChangeScene();

			// �t�F�[�h�Ŗ��邭���Ă���
			fader_->SetFade(Fader::STATE::FADE_IN);

		}
		break;

	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd() == true)
		{
			// �t�F�[�h���I������
			fader_->SetFade(Fader::STATE::NONE);

			// �V�[���؂�ւ��̏I��
			isSceneChanging_ = false;
		}
		break;
	}
}

// �w�肵���V�[���̉������
void SceneManager::ReleaseScene(SCENE_ID iSceneID)
{
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}

// �V���O���g����
// -----------------

// �C���X�^���X�̐���
// �O������ÓI�ɃC���X�^���X�𐶐�����
void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

// �O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂�
// �C���X�^���X��Ԃ��֐���p�ӂ���
// �Q�ƌ^�ɂ��Ă��邪�|�C���^�^�ł��悢
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

// �C���X�^���X�̔j��
void SceneManager::Destory(void)
{
	delete instance_;		// �C���X�^���X���폜
	instance_ = nullptr;	// �C���X�^���X�i�[�̈��������
}
