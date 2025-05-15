// #pragma once


#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "SceneBase.h"

class SceneTitle :public SceneBase
{
public:
	// �萔�̒�`
	// �{�^���̃T�C�Y
	static constexpr int SIZE_WIDTH = 120;		// ��
	static constexpr int SIZE_HEIGHT = 70;		// �c

	// �{�^���̈ʒu
	static constexpr int BUTTON_POS_X = 550;	//X���W�͂��낦��̂ňꏏ

	// start�{�^���̈ʒu
	static constexpr int START_POS_Y = 250;		//Y���W	

	// story�{�^���̈ʒu
	static constexpr int STORY_BUTTON_Y = 350;

	// Title���S�摜�̃T�C�Y
	static constexpr int TITLE_SIZE_WIDTH = 402;
	static constexpr int TITLE_SIZE_HEIGHT = 480;
	//���S�摜�̍��W
	static constexpr int TITLE_IMAGE_X = 610;
	static constexpr int TITLE_IMAGE_Y = 120;

	// ��摜�̃T�C�Y
	static constexpr int FACE_SIZE_WIDTH = 473;
	static constexpr int FACE_SIZE_HEIGHT = 480;

	//�A�j���[�V�����֘A
	static constexpr int FACE_ANIM_NUM = 7;	

	//�����֘A
	static constexpr int BLINK_RANDOM_THRESHOLD_NONE = 90;
	static constexpr int BLINK_RANDOM_THRESHOLD_ONCE = 50;
	static constexpr int BLINK_ONCE_ANIM_NUM = 5;
	static constexpr int BLINK_TWICE_ANIM_NUM = 4;
	static constexpr int BLINK_TWICE_IMAGE_NUM = 6;

	// �񋓌^
	// �{�^���̑I�����
	enum class SELECT
	{
		START,	// ���I��
		SECRET,	// �I��
		MAX
	};

	enum class BUTTON
	{
		OFF,
		ON
	};

	enum class BLINK
	{
		NONE,
		ONCE,
		TWICE
	};

	SceneTitle(void);			// �R���X�g���N�^
	~SceneTitle(void);			// �f�X�g���N�^

	bool Init(void) override;		// ����������
	void Update(void) override;		// �X�V����	
	void Draw(void) override;		// �`�揈��
	bool Release(void) override;	// �������

private:
	//�����o�[�ϐ�

	//BGM��SE
	int bgm_;
	int buttonSelectSound_;
	int buttonPushSound_;

	//�摜���i�[����ϐ�-----------------------
	int titleImage_;
	int backImage_;

	int crownImage_;
	int faceImgs_[1][FACE_ANIM_NUM];
	int bodyImage_;

	int selectImage_;
	int select_onImage_;
	int start_onImage_;
	int start_offImage_;
	int story_onImage_;
	int story_offImage_;

	int cursorImage_;

	// -----------------------------------

	bool isSelect_;
	bool wasSelect_;

	// �I����̈ʒu
	Vector2 pos_;

	// �}�E�X�̈ʒu
	Vector2 mpos_;

	//�㉺�ɓ������摜�p���W�ƈړ���
	Vector2 crownPos_;	//�������W
	Vector2 crownMove_;	//�����ړ���
	Vector2 facePos_;	//����W
	Vector2 faceMove_;	//��ړ���

	int animNum_;
	int blink_;

	BLINK blinkNum_;
	int blinkPersent_;
	bool isBlink_;

	int crownDirection;
	int faceDirection;

	// �I�����
	SELECT select_;

	//�{�^���̏��
	BUTTON button_;

	int cntAnim_;
	int cntMove_;
	float moveDelay_;
	float speedAnim_;

	//�^�C�}�[�֘A
	int startTime;		//�J�n����
	int elapsedTime;	//�o�ߎ���

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