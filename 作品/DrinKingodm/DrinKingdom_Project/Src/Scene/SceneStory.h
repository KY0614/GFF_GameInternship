#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

// �O���錾
class Fader;

class SceneStory :public SceneBase
{
public:
	// �{�^���̃T�C�Y
	static constexpr int SIZE_WIDTH = 120;		// ��
	static constexpr int SIZE_HEIGHT = 70;		// �c

	// �{�^���̈ʒu
	static constexpr int BUTTON_POS_X = 550;	//X���W�͂��낦��̂ňꏏ

	// �^�C�g���{�^���̈ʒu
	static constexpr int TITLEBUTTON_POS_X = 50;
	static constexpr int TITLEBUTTON_POS_Y = 410;

	static constexpr int PLAYBUTTON_POS_X = 220;
	static constexpr int SELECT_IMG_POS_X = 170;

	SceneStory(void);			// �R���X�g���N�^
	~SceneStory(void);			// �f�X�g���N�^

	bool Init(void) override;		// ����������
	void Update(void) override;		// �X�V����	
	void Draw(void) override;		// �`�揈��
	bool Release(void) override;	// �������

private:
	// �����o�[�ϐ�
	//�T�E���h�֘A
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	//�摜�֘A
	int storyImg_;
	int cursorImage_;

	int selectImage_;
	int select_onImage_;

	int title_pushImage_;
	int titleImage_;
	int start_onImage_;
	int start_offImage_;

	// �}�E�X�̈ʒu
	Vector2 mpos_;
	// �I���ʒu���킩��摜�̈ʒu
	Vector2 spos_;

	bool isTitle_;
	bool isPlay_;

	bool isSelect_;
	bool wasSelect_;
};
