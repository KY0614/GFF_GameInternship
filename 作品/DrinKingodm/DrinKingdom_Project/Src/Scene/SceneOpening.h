#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

// �O���錾
class Fader;

class SceneOpening :public SceneBase
{
public:
	//�X�y�[�X�L�[�����摜�T�C�Y
	static constexpr int SPACE_SIZE_WIDTH = 89;
	static constexpr int SPACE_SIZE_HEIGHT = 56;

	//�X�y�[�X�L�[�����摜���W
	static constexpr int SPACE_IMAGE_POS_X = 700;
	static constexpr int SPACE_IMAGE_POS_Y = 400;

	//�ő�A�j���[�V������
	static constexpr int MAX_ANIM_NUM = 2;

	//�ő�ҋ@����
	static constexpr int WAIT_INTERVAL = 5000;

	SceneOpening(void);			// �R���X�g���N�^
	~SceneOpening(void);		// �f�X�g���N�^

	bool Init(void) override;		// ����������
	void Update(void) override;		// �X�V����	
	void Draw(void) override;		// �`�揈��
	bool Release(void) override;	// �������

private:
	// �����o�[�ϐ�
	// �摜�֘A
	int operateImg_;
	int imgsSpace_[1][MAX_ANIM_NUM];

	// ���֘A
	int bgm_;

	//�@�A�j���[�V�����֘A
	int cntAnim_;
	float speedAnim_;

	//�^�C�}�[�֘A
	int startTime;
	int elapsedTime;

};
