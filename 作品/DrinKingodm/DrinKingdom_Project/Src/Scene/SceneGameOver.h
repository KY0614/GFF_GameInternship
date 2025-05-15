// #pragma once

#include "SceneBase.h"
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class SceneGameOver :public SceneBase
{
public:

	//�摜�֘A

	//��摜�̃T�C�Y
	static constexpr int FACE_SIZE_WIDTH = 473;
	static constexpr int FACE_SIZE_HEIGHT = 480;

	static constexpr int ANIM_NUM = 4;
	static constexpr int FACEANIM_NUM = 7;

	// �{�^���֘A
	static constexpr int BUTTON_SIZE_WIDTH = 120;	// �{�^���̕�
	static constexpr int BUTTON_SIZE_HEIGHT = 70;	// �{�^���̍���
	static constexpr int BUTTON_POS_X = 140;		// �{�^����X���W
	static constexpr int TITLE_POS_Y = 300;			// �^�C�g���{�^����Y���W
	static constexpr int EXIT_POS_Y = 400;			// �I���{�^����Y���W
	static constexpr int SELECT_POS_X = 90;		// �I�����Ă���摜��X���W

	// �r�̓����֘A
	static constexpr float ARM_ANGLE_MAX = 0.6f;     // �r�̉�]�ő�p�x
	static constexpr float ARM_ANGLE_MIN = -0.1f;    // �r�̉�]�ŏ��p�x
	static constexpr float ARM_ANGLE_SPEED = 0.01f;  // �r�̉�]���x

	// ���ʊ֘A
	static constexpr int BGM_VOLUME = 140;            // BGM�̉���
	static constexpr int BUTTON_SELECT_VOLUME = 230;   // �{�^���I�����̉���
	static constexpr int BUTTON_PUSH_VOLUME = 180;     // �{�^���������̉���

	//����t�Ƃ܂΂����֘A
	static constexpr int BLINK_RANDOM_THRESHOLD_NONE = 90;
	static constexpr int BLINK_RANDOM_THRESHOLD_ONCE = 50;
	static constexpr int BLINK_ONCE_ANIM_NUM = 5;
	static constexpr int BLINK_TWICE_ANIM_NUM = 4;
	static constexpr int BLINK_TWICE_IMAGE_NUM = 6;

	enum class BLINK
	{
		NONE,
		ONCE,
		TWICE
	};

	SceneGameOver(void);			// �R���X�g���N�^
	 ~SceneGameOver(void);			// �f�X�g���N�^

	bool Init(void) override;		// ����������
	void Update(void) override;		// �X�V����	
	void Draw(void) override;		// �`�揈��
	bool Release(void) override;	// �������

private:
	// �����o�[�ϐ�

	// BGM
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	// �摜
	int backImage_;
	int thankImage_;
	int playImage_;

	int title_pushImage_;
	int titleImage_;
	int exitImage_;
	int exit_pushImage_;

	int selectImage_;
	int select_onImage_;

	int crownImage_;
	int faceImage_;
	int faceImgs_[1][FACEANIM_NUM];
	int bodyImage_;
	int armImage_;

	int cursorImage_;

	bool isTitle_;
	bool isExit_;

	// �}�E�X�̈ʒu
	Vector2 mpos_;

	Vector2 spos_;

	Vector2 crownPos_;
	Vector2 crownMove_;

	Vector2 facePos_;
	Vector2 faceMove_;

	int crownDirection;
	int faceDirection;
	int armDirection;

	int cntAnim_;
	int cntMove_;
	float moveDelay_;
	float speedAnim_;

	float moveArm_;
	float armAngle_;	
	float moveHand_;

	int animNum_;
	int blink_;

	BLINK blinkNum_;
	int blinkPersent_;
	bool isBlink_;

	int startTime;
	int elapsedTime;

	int cnt_;

	/// <summary>
	/// �����摜�𓮂�������
	/// </summary>
	/// <param name="">�㉺�ɓ���������</param>
	void MoveCrown(void);

	/// <summary>
	/// ��摜�𓮂�������
	/// </summary>
	/// <param name="">�㉺�ɓ���������</param>
	void MoveFace(void);

	/// <summary>
	/// �r�𓮂�������
	/// </summary>
	/// <param name="">�r����]������</param>
	void MoveArm(void);

	/// <summary>
	/// �܂΂����p�̏���
	/// </summary>
	/// <param name="">�u�����Ă��ȂƂ��̓����_���ł�����</param>
	void Blink(void);

	/// <summary>
	/// �o�ߎ��Ԃ�Ԃ�
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	int GetTime(void);
};