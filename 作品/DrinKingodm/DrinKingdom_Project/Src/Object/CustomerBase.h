#pragma once
#include <DxLib.h>

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneGame;

class CustomerBase
{
public:
	// �摜�T�C�Y
	static constexpr int SIZE_X = 214/*320*/;	
	static constexpr int SIZE_Y = 380;

	static constexpr int ICESIZE_X = 204;
	static constexpr int ICESIZE_Y = 400;

	static constexpr int POS_X = 1300;
	static constexpr int POS_Y = 202;

	// �A�j���[�V������
	static constexpr int NUM_ANIM = 7;

	// ���q�̏���
	enum class CUSTOMER
	{
		NONE,
		HOTCUP,	  // 1�l��
		ICECUP,	  // 2�l��
		THREE	  // 3�l��
	};

	// �q�̔����i����v�f�j
	enum class REACTION
	{
		NONE,	 // �܂��󂯎���Ă��Ȃ�
		HAPPY,	 // ��]����ʂ�̏��i
		NORMAL,	 // ��]�������̂Ə����Ⴄ����
		BAD		 // �S���Ⴄ����
	};

	enum class WINK
	{
		NONE,
		ONCE,
		TWICE
	};

	CustomerBase(void);
	virtual ~CustomerBase(void);

	bool Init(SceneGame*scenegame);		// ����������

	virtual void Update(void);			// �X�V����	

	virtual void UpdateTalk(void);		// �X�V����	
	virtual void UpdateHot(void);
	virtual void UpdateIce(void);

	virtual void UpdateMake(void);		// �X�V����	
	virtual void UpdateDrink(void);		// �X�V����	
	virtual void UpdateTalk2(void);		// �X�V����	


	virtual void Draw(void);			// �`�揈��
	bool Release(void);					// �������

	virtual void SetParam(void) = 0;	// �ŗL�̋@�\��ݒ肷��֐�

	void Wink(void);

	CUSTOMER GetCustomer(void);			// customer_�̏�Ԃ𓾂�
	REACTION GetReaction(void);			// �q���ǂ̔��������Ă��邩

	void SetDrink(int value);

protected:

	// �摜�t�@�C����
	std::string imgFileName;

	// �\�����W
	Vector2 pos_;

	// �T�C�Y
	Vector2 size_;

	// 
	int numY;

	int drink_;

	// ���q�̏���
	CUSTOMER customer_;

	// ���q�̔���
	REACTION reaction_;

	// ------------------------------------------

	// �V�[���Q�[���̃|�C���^�i�[�̈�
	SceneGame* sceneGame_;

	int image_;
	int imgs_[5][NUM_ANIM];

	// ����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����J�E���^
	int cntAnim_;

	// �A�j���[�V�������x
	float speedAnim_;

	int animNum_;
	bool increasing;

	float time;


	int blink_;

	WINK wink_;
	int rand_;
	bool winkRand_;
};

