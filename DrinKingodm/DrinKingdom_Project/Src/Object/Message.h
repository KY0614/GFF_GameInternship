#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class Message
{
public:


	// �t�H���g�T�C�Y 
	static constexpr int FONT_SIZE = 20;

	// ���b�Z�[�W�̍ő啶���� 
	static constexpr int MAX_LENGTH = 13;

	// ���b�Z�[�W�̍ő�s��
	static constexpr int MAX_LINE = 10;

	// ���b�Z�[�W�`��ʒu (X���W)
	static constexpr int MESSAGE_POS_X = 60;
	// ���b�Z�[�W�`��ʒu (Y���W)
	static constexpr int MESSAGE_POS_Y = 60;

	// �X�y�[�X�A�j���[�V�����̉���
	static constexpr int SPACE_SIZE_X = 89;

	// �X�y�[�X�A�j���[�V�����̏c�� 
	static constexpr int SPACE_SIZE_Y = 56;

	// �A�j���[�V�����t���[����
	static constexpr int MAX_ANIM_NUM = 2;

	// ���z�e�L�X�g�o�b�t�@�̉��T�C�Y�c�T�C�Y
	static constexpr int STRBUF_WIDTH = 24;
	static constexpr int STRBUF_HEIGHT = 20;

	// ���b�Z�[�W�̋󔒕\������ (�~���b)
	static constexpr int MESSAGE_DELAY_TIME = 3500;

	// ���b�Z�[�W�؂�ւ����� (��: 1000ms)
	static constexpr int MESSAGE_SWITCH_TIME = 1000;

	// �T�E���h�{�����[�� (�W���ݒ�)
	static constexpr int WAIT_SOUND_VOLUME = 130;
	static constexpr int ICE_SOUND_VOLUME = 120;
	static constexpr int HOT_SOUND_VOLUME = 200;


	Message(void);			// �R���X�g���N�^
	~Message(void);			// �f�X�g���N�^

	bool Init(SceneGame* parent);	// ����������

	void Update(void);			// �X�V����	

	void UpdateWait(void);		// Wait�t�F�[�Y�̍X�V����	
	void UpdateTalk(void);		// Talk�t�F�[�Y�̍X�V����	
	void UpdateTalk2(void);		// Talk2�t�F�[�Y�̍X�V����	

	void Draw(void);			// �`�揈��
	void DrawTalk(void);		// �`�揈��
	void DrawTalk2(void);		// �`�揈��

	void DrawMessage(void);	// ���b�Z�[�W�`��

	bool Release(void);		// �������

	// ���{�ꂩ�ǂ�������
	int isJapaneseCharacter(unsigned char code);

	// message�Ŏw�肵�����͂�start�̈ʒu����len�������\������
	void WriteSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine);

	// �`�悵�������b�Z�[�W���Z�b�g����
	void SetMessage(const char* message);

	// ���b�Z�[�W�{�b�N�X�̏�Ԃ�Ԃ�
	bool Switch(void);

private:

	int imgMessageBox_;
	int imgMessageBox2_;
	int imgMessageBox3_;

	char message_[MAX_LENGTH * MAX_LINE] = "";

	char messageBuffer[MAX_LINE][MAX_LENGTH];

	int currentCursor;		// ���������ڂ�
	int currentLineCursor;	// �����s�ڂ̕�����

	int timeCnt_;				// �b���Ǘ��p

	SceneGame* sceneGame_;

	int imgsSpace_[1][MAX_ANIM_NUM];
	int cntAnim_;
	float speedAnim_;

	int messCount_;

	// �����b�Z�[�W�ƃ��b�Z�[�W�{�b�N�X���\�������ǂ���
	bool isMessage_;

	// �����b�Z�[�W��`�撆�i�Ō�܂ŕ\������ĂȂ��j���ǂ���
	bool isWrite_;

	int hotSound_;
	int iceSound_;
	int waitSound_;
	int sound_;
};

