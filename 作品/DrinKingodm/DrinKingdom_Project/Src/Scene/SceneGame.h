#pragma once
#include <vector>
#include "SceneBase.h"

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"
#include "../Object/CustomerBase.h"

// �O���錾
class SceneManager;
class Fader;
class Camera;
class Map;
class Player;
class HotCup;
class IceCup;
class Message;
class CustomerBase;

class SceneGame : public SceneBase
{
public:
	// �萔
	static constexpr int UI_SIZE_X = 50;
	static constexpr int UI_SIZE_Y = 50;

	// �J�����֘A
	static constexpr float CAMERA_MAX_WIDTH = 800.0f;	// �J�����̕��̍ő�
	static constexpr float CAMERA_MIN_WIDTH = 0.0f;		// �J�����̕��̍ŏ�
	static constexpr float CAMERA_MAX_HEIGHT = 480.0f;	// �J�����̍����̍ő�
	static constexpr float CAMERA_MIN_HEIGHT = 0.0f;	// �J�����̍����̍ŏ�

	// �ő�ړ����x(�J�����́j
	static constexpr float MAX_MOVE_WSPEED = 15.0f;
	static constexpr float MAX_MOVE_HSPEED = 10.0f;

	// �����x(accelerator)
	static constexpr float MOVE_ACC = 0.25f;

	// ����(decelerate)
	static constexpr float MOVE_DEC = 0.1f;

	static constexpr int ANIM_SIZE_X = 200;
	static constexpr int ANIM_SIZE_Y = 430;

	// �t�F�[�Y
	enum class FASE
	{
		NONE,
		WAIT,	// ���q�҂�
		TALK,	// ���q�Ƙb��
		MAKE,	// ���ݕ������
		DRINK,	// ���ݕ���n��
		TALK2	// �n������̉�b	

	};

	// MODE�͉�ʑJ�ڒ��ɉ����ł��Ȃ��悤�ɂ�����
	enum class MODE
	{
		NONE,
		CHANGE		// ��ʑJ�ڒ�
	};

	enum class PAGE
	{
		NONE,
		PAGE1,
		PAGE2
	};

	SceneGame(void);		// �R���X�g���N�^
	~SceneGame(void);		// �f�X�g���N�^

	bool Init(void);		// ����������
	void Update(void);		// �X�V����	
	void Draw(void);		// �`�揈��
	void DrawCursor(void);
	bool Release(void);		// �������

	// �J�����̈ʒu��Ԃ�
	Vector2 GetCameraPos(void);

	// ��ʑJ�ڎ��̃��[�h
	//void ChangeMode(MODE value);

	// ���݂̃t�F�[�Y��Ԃ�
	FASE GetFase(void);

	// �t�F�[�Y��ύX����
	void ChangeFase(FASE value);

	//���b�Z�[�W���\�������ǂ���
	bool MesSwitch(void);

	bool GetIsMesCursor(void);

	// �o�ߎ��Ԃ�Ԃ�
	int GetTime(void);

	// �t�F�[�h�C�����Ȃ���摜��\��
	void FadeInImage(int x, int y, int imageFile, int fadeInSpeed);

	// �����邨�q���N����Ԃ�
	CustomerBase::CUSTOMER GetCustomer(void);

	// ���q�̔�����Ԃ�
	CustomerBase::REACTION GetReaction(void);

	bool GetMessCursor(void);

	// ���x����
	void Accele(float speed);

	// ��������
	void Decelerate(float speed);

	// �ړ�����
	void Move(int pos);


private:

	// �V�[���}�l�[�W���̃|�C���^�i�[�̈�
	SceneManager* sceneManager_;

	Camera* camera_;

	// �v���C���[
	Player* player_;

	// �q
	HotCup* hotCup_;
	IceCup* iceCup_;

	// �}�b�v
	Map* map_;

	// ���b�Z�[�W
	Message* message_;

	//�q
	std::vector<CustomerBase*> customers_;

	// �}�E�X�摜
	int cursorImage_;
	// �e�L�X�g�{�b�N�X�̒��̃J�[�\���摜
	int messagecursorImage_;

	bool isMessCursor_;

	int imgsUI_[1][2];
	int imgRecipe_[1][2];
	int imgBack_;
	int imgBacks_[1][2];
	int imgNext_[1][2];
	
	int bookCnt_;
	int ui_;
	bool isUI_;
	bool isBack_;

	PAGE page_;

	// �}�E�X�̈ʒu
	Vector2 mpos_;

#pragma region enum class

	// �t�F�[�Y
	FASE fase_;

	// �J�����̃��[�h
	MODE mode_;

#pragma endregion

#pragma region �J�����֘A
	// ��ʂ��J�ڂ���Ƃ��̌���
	AsoUtility::DIR dir_;

	// �J�����̈ʒu
	Vector2 cameraPos_;

	// �J�����̈ړ�
	//void CameraMove(void);


	// �ړ����x
	float moveSpeedH_;	// �c�ړ����x
	float moveSpeedW_;	// ���ړ����x

#pragma endregion

	// �t�F�[�Y�𗬂����߂̃J�E���^�[
	int counter_;

	// �f�o�b�N�p�̐F
	int color;

	//�q�̐�
	int cnt_;

	bool hot_;
	bool ice_;

	// �o�ߎ��ԊǗ��p
	int startTime;
	int elapsedTime;

	// �t�F�[�h�C��������X�s�[�h
	int fadeInSpeed_;

	int cntA;

	int animImgs_[1][3];
	int animIceImgs_[1][3];

	// BGM�p
	int bgm_;

	int openBookSound_;
	int closeBookSound_;
};