#pragma once
#include <DxLib.h>

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Map;
class Player;
class SceneGame;

class Camera
{
public:
	// �萔

	// ���֘A
	static constexpr int ARROW_SIZE_X = 77;       // ���摜�̉���
	static constexpr int ARROW_SIZE_Y = 46;       // ���摜�̏c��
	static constexpr int AD_SIZE_X = 48;          // ���E���̉���
	static constexpr int AD_SIZE_Y = 77;          // ���E���̏c��

	// �J�����ړ��֘A
	static constexpr float CAMERA_MOVE_SPEED_W = 15.0f; // ���ړ����x
	static constexpr float CAMERA_MOVE_SPEED_H = 10.0f; // �c�ړ����x
	static constexpr float CAMERA_MAX_WIDTH = 800.0f;   // �J����X�ő�
	static constexpr float CAMERA_MIN_WIDTH = 0.0f;     // �J����X�ŏ�
	static constexpr float CAMERA_MAX_HEIGHT = 480.0f;  // �J����Y�ő�

	// �A�j���[�V�����֘A
	static constexpr int ANIMATION_INIT_COUNT = 0;      // �A�j���[�V���������J�E���g
	static constexpr float ANIMATION_SPEED = 0.7f;      // �A�j���[�V�������x
	static constexpr int ARROW_MOVE_MIN = -2;           // ���ړ��ŏ��l
	static constexpr int ARROW_MOVE_MAX = 0;            // ���ړ��ő�l

	// UI���W�֘A
	static constexpr int ARROW_W_POS_X = 1200;          // W���X
	static constexpr int ARROW_W_POS_Y = 480 + ARROW_SIZE_Y / 2 + 8; // W���Y
	static constexpr int ARROW_S_POS_X = 1200;          // S���X
	static constexpr int ARROW_S_POS_Y = 450;           // S���Y
	static constexpr int ARROW_A_POS_X = 800 + AD_SIZE_X / 2 + 8;     // A���X
	static constexpr int ARROW_A_POS_Y = 780;           // A���Y
	static constexpr int ARROW_D_POS_X = 800 - AD_SIZE_X / 2 - 8;     // D���X
	static constexpr int ARROW_D_POS_Y = 780;           // D���Y

	// ���̏��
	// ON�F�}�E�X�J�[�\�������ɍ����Ă���
	enum class W_TOGGLE
	{
		OFF,
		ON
	};

	enum class S_TOGGLE
	{
		OFF,
		ON
	};

	enum class A_TOGGLE
	{
		OFF,
		ON
	};

	enum class D_TOGGLE
	{
		OFF,
		ON
	};

	// �J�������[�h
	// MODE�͉�ʑJ�ڒ��ɉ����ł��Ȃ��悤�ɂ�����
	enum class MODE
	{
		NONE,
		CHANGE		// ��ʑJ�ڒ�
	};

	// �R���X�g���N�^
	Camera(Map* map, Player* player);
	// �f�X�g���N�^
	~Camera(void);

	// ��������(��{�I�ɍŏ��̂P�񂾂�����)
	bool Init(SceneGame* parent);

	// �X�V����(���t���[�����s)
	void Update(void);

	// �`�揈��(���t���[�����s)
	void Draw(void);

	// �������(��{�I�ɍŌ�̂P�񂾂�����)
	void Release(void);

	// �J�����̈ʒu��Ԃ�
	Vector2 GetCameraPos(void);

	// ��ʑJ�ڎ��̃��[�h
	void ChangeMode(MODE value);

	void MoveArrow(void);

private:
	SceneGame* sceneGame_;       // �e�V�[���ւ̃|�C���^
	Map* map_;                   // �}�b�v�I�u�W�F�N�g�ւ̃|�C���^
	Player* player_;             // �v���C���[�I�u�W�F�N�g�ւ̃|�C���^

	Vector2 mpos_;               // �}�E�X�̌��݈ʒu
	int cnt_;                   // �A�j���[�V�����p�J�E���^
	float speedAnim_;           // �A�j���[�V�������x

	int imgsW_[1][2];           // W���摜�̃n���h���z��
	int imgsS_[1][2];           // S���摜�̃n���h���z��
	int imgsA_[1][2];           // A���摜�̃n���h���z��
	int imgsD_[1][2];           // D���摜�̃n���h���z��

	W_TOGGLE toggleW_;          // W���g�O�����
	S_TOGGLE toggleS_;          // S���g�O�����
	A_TOGGLE toggleA_;          // A���g�O�����
	D_TOGGLE toggleD_;          // D���g�O�����

	Vector2 arrowWPos_;         // W���̍��W
	Vector2 arrowSPos_;         // S���̍��W
	Vector2 arrowAPos_;         // A���̍��W
	Vector2 arrowDPos_;         // D���̍��W

	Vector2 arrowMove_;         // ���̃A�j���[�V�����ړ���

	int directionY;             // ���ړ�����Y
	int directionX;             // ���ړ�����X

	MODE mode_;                 // �J�����̓��샂�[�h
	AsoUtility::DIR dir_;       // �J�����̈ړ�����

	Vector2 cameraPos_;         // �J�����̌��ݍ��W

	float moveSpeedH_;          // �c�����̃J�����ړ����x
	float moveSpeedW_;          // �������̃J�����ړ����x

	// �J�����̈ړ�
	void CameraMove(void);
};

