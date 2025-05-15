#include <DxLib.h>
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Application.h"

// �t���X�N���[���ƃE�B���h�E��F11�Ő؂�ւ����悤�ɂ�����

// �V���O���g����
// ----------------
// instance_�̏�����
Application* Application::instance_ = nullptr;

// �f�t�H���g�R���X�g���N�^
Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	screen_ = false;
	currentTime = 0;
	lastFrameTime = 0;
	frameCnt = 0;
	updateFrameRateTime = 0;
	frameRate = 0.0f;
	isDone_ = false;
}

// �f�X�g���N�^
Application::~Application(void)
{
}


// ����������
bool Application::Init(void)
{
	// �V�X�e������
	// -------------
	SetWindowText("DrinKingdom");		// �Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);				// �Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);					// �Q�[���E�B���h�E�̕\�����@�ifalse:�t���X�N���[��)
	isInitFail_ = true;
	if (DxLib_Init() == -1)					// DX���C�u�����̏���������
	{
		OutputDebugString("DXLib�̏��������s");
		return false;							// DX���C�u�����̏��������s�̂��߃V�X�e���I��
	}
	// �����̏����l��ݒ肷��
	SRand(100);		// �����̈�艻

	// �C���X�^���X�𐶐�����
	// ---------------------------
	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	
	// �V�[���}�l�[�W��(�V���O���g���j
	SceneManager::CreateInstance();

	currentTime = 0;
	lastFrameTime = 0;

	frameCnt = 0;

	updateFrameRateTime = 0;

	frameRate = 0.0f;

	isDone_ = false;

	return true;
}

void Application::Update(void)
{

}

// �Q�[�����[�v����
void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	// �Q�[�����[�v
	// ------------------
	while (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0 || isDone_ == false))
	{
		Sleep(1);		// �V�X�e���ɏ�����Ԃ�

		// ���݂̎������擾
		currentTime = GetNowCount();

		// ���߂̎������A�O��̃t���[�������
		// 1/60�b�o�߂��Ă����珈�������s����
		if (currentTime - lastFrameTime >= FRAME_RATE)
		{
			// �t���[�����s���̎��Ԃ��X�V
			lastFrameTime = currentTime;

			// �t���[�����J�E���g
			frameCnt++;

			// �G�X�P�[�v�������ꂽ��Q�[���I��
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || isDone_ == true)
			{
				return;
			}

			// �t���[�����[�g�v�Z
			CalcFrameRate();



			// �Q�[���̃��C������
			// ------------------
			Update();
			inputManager.Update();
			sceneManager.Update();

			// �`�揈��
			// ------------------
			SetDrawScreen(DX_SCREEN_BACK);		// �`�悷���ʂ𗠂̉�ʂɐݒ�
			ClearDrawScreen();					// �`�悷���ʂ̓��e������

			sceneManager.Draw();

			ScreenFlip();						// ���̉�ʂ�\�̉�ʂɏu�ԃR�s�[
		}
	}
}

// �������
bool Application::Release(void)
{
	// �Ǘ��}�l�[�W���[�̉������
	// �V�[���Ǘ��p
	SceneManager::GetInstance().Release();

	// �V���O���g����
	// ------------------------
	Destory();

	// �V�X�e���I������
	// ----------------------
	DxLib_End();			// DX���C�u�����̏I������


	return true;			// �Q�[���̏I��
}	

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

void Application::Screen(void)
{

}

// �V���O���g����
// -----------------

// �C���X�^���X�̐���
// �O������ÓI�ɃC���X�^���X�𐶐�����
void Application::CreateInstance(void)
{
	// instance_ �� nullptr �̏ꍇ�́A���������ꂽ�̂���������Ă��Ȃ��̂ŁA�����������s��
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}

	instance_->Init();
}

// �O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂�
// �C���X�^���X��Ԃ��֐���p�ӂ���
// �Q�ƌ^�ɂ��Ă��邪�|�C���^�^�ł��悢
Application& Application::GetInstance(void)
{
	return *instance_;
}

// �C���X�^���X�̔j��
void Application::Destory(void)
{
	delete instance_;		// �C���X�^���X���폜
	instance_ = nullptr;	// �C���X�^���X�i�[�̈��������
}

void Application::CalcFrameRate(void)
{
	int nDifTime = currentTime - updateFrameRateTime;

	if (nDifTime > 1000)
	{
		float fFrameCnt = (float)(frameCnt * 1000);

		frameRate = fFrameCnt / nDifTime;

		frameCnt = 0;

		updateFrameRateTime = currentTime;
	}
}

void Application::SetIsDone(bool value)
{
	isDone_ = value;
}