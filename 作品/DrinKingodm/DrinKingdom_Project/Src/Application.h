#pragma once
#include <string>

class SceneManager;

class Application
{
public:
	// �E�B���h�E�T�C�Y (����)
	static constexpr int SCREEN_SIZE_X = 800;

	// �E�B���h�E�T�C�Y (�c��)
	static constexpr int SCREEN_SIZE_Y = 480;

	// �t���[�����[�g (60FPS�ɐݒ�)
	static constexpr float FRAME_RATE = (1000 / 60);
	
	bool Init(void);		// ����������
	void Update(void);		// �X�V����
	void Run(void);			// �Q�[�����[�v����
	bool Release(void);		// �������

	// �����������^���s�̔���
	bool IsInitFail(void) const;

	// ��������^���s�̔���
	bool IsReleaseFail(void) const;

	void Screen(void);

	// �V���O���g����
	// -------------------

	// �C���X�^���X�̐���
	// �O������ÓI�ɃC���X�^���X�𐶐�����
	static void CreateInstance(void);

	// �O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂�
	// �C���X�^���X��Ԃ��֐���p�ӂ���
	// �Q�ƌ^�ɂ��Ă��邪�|�C���^�^�ł��悢
	static Application& GetInstance(void);

	void SetIsDone(bool value);

private:
	// �����o�[�ϐ�

	// �V���O���g����
	// -------------------
	Application(void);		// �R���X�g���N�^
	~Application(void);	// �f�X�g���N�^

	// �R�s�[�R���X�g���N�^�𗘗p�ł��Ȃ�����
	Application(const Application& ins);

	// �C���X�^���X�̔j��
	void Destory(void);

	// �ÓI�ȃC���X�^���X�i�[�̈�
	static Application* instance_;

	bool isInitFail_;       // ���������s�t���O
	bool isReleaseFail_;    // ������s�t���O
	bool isDone_;           // �Q�[���I���t���O
	bool screen_;           // �X�N���[���̏��

	int currentTime;        // ���݂̎��� (�~���b)
	int lastFrameTime;      // �O��t���[���̎��� (�~���b)

	int frameCnt;           // �t���[���J�E���^�[
	int updateFrameRateTime;// �t���[�����[�g�v�Z�p�̎��� (�~���b)

	float frameRate;        // �t���[�����[�g�l (FPS)


	void CalcFrameRate(void);// �t���[�����[�g�v�Z����
};