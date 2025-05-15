#pragma once

#include "../Common/Vector2.h"
#include "../Common/Geometry.h"
#include "../Utility/AsoUtility.h"

class Map;
class SceneGame;

class Player
{
public:
	
	static constexpr int POINT_SIZE_X = 54;
	static constexpr int POINT_SIZE_Y = 54;

	static constexpr int PUSHKEY_SIZE_X = 76;
	static constexpr int PUSHKEY_SIZE_Y = 69;

	static constexpr int PUSHKEY_MAX_NUM = 2;

#pragma region FILTER�֘A
	// filter�֘A
	// filter�̃T�C�Y
	static constexpr int FSIZE_X = 42;
	static constexpr int FSIZE_Y = 113;
	// beans�̃T�C�Y
	static constexpr int BSIZE_X = 39;
	static constexpr int BSIZE_Y = 6;

	// filter�̏����ʒu
	static constexpr int FILTER_POS_X = 1431;
	static constexpr int FILTER_POS_Y = 585;
	
	// grinder�̉��̈ʒu
	static constexpr int FILTER_GPOS_X = 1125;
	static constexpr int FILTER_GPOS_Y = 670;
	
	// tamper�ׂ̗̈ʒu
	static constexpr int FILTER_TPOS_X = 1511;
	static constexpr int FILTER_TPOS_Y = 741;

	// �}�V���ɃZ�b�g����ʒu
	static constexpr int FILTER_CPOS_X = 927;
	static constexpr int FILTER_CPOS_Y = 642;

	// �Z�b�g���m�肳���鎞�ɑ��₷�l
	static constexpr int SET_POS = 7;

	// filter�摜�̏�Ԃ̐�
	static constexpr int FILTER_NUM = 4;	// �����I�ɂT���炢�ق���
									// (����,�I����,take��,in��,�J�X���j

	// filter�̏��
	enum class FILTER
	{
		NONE,			// 0
		SELECT,			// 1
		TAKE,			// 2
		SELECT_G,		// 3
		SET_G,			// 4  
		SELECT_T,		// 5
		SET_T,			// 6
		SELECT_M,		// 7
		SET_M,			// 8
		DUST
	};

#pragma endregion

#pragma region TAMPER�֘A
	// tamper�֘A
	// tamper�̃T�C�Y
	static constexpr int TSIZE_X = 39;
	static constexpr int TSIZE_Y = 52;

	// tamper�̏����ʒu
	static constexpr int TAMPER_POS_X = 1570;
	static constexpr int TAMPER_POS_Y = 719;
	// tamper��filter�㕔�̈ʒu
	static constexpr int TAMPER_FPOS_X = 1510;
	static constexpr int TAMPER_FPOS_Y = 680;	// 700

	// Stamp����Ƃ��̃Q�[�W�̍ő�l
	static constexpr int MAX_COUNT = 40;

	// tamper�摜�̏�Ԃ̐�
	static constexpr int TAMPER_NUM = 2;	

	// tamper�̏��
	enum class TAMPER
	{
		NONE,
		SELECT,
		TAKE,
		SET_F,
		STAMP,
		FINISH
	};

#pragma endregion

#pragma region GRINDER�֘A
	// grinder�֘A
	// grinder�̃T�C�Y
	static constexpr int GSIZE_X = 85;
	static constexpr int GSIZE_Y = 245;
	// grinder�̏����ʒu
	static constexpr int GRINDER_POS_X = 1125/*1177*/;
	static constexpr int GRINDER_POS_Y = 629;

	static constexpr int GRINDER_NUM = 2;

	// grinder�̏��
	enum class GRINDER
	{
		NONE,
		SELECT,
		TAKE,
		SET_G,
		INCOFFEE,
		SET_C
	};

#pragma endregion

#pragma region CUP�֘A

	// �摜�T�C�Y
	static constexpr int CUP_SIZE_X = 65;
	static constexpr int CUP_SIZE_Y = 64;

	static constexpr int ICECUP_SIZE_X = 51;
	static constexpr int ICECUP_SIZE_Y = 66;

	// �����ʒu
	// HotCup
	static constexpr int HOTCUP_POS_X = 850/*1293*/;
	static constexpr int HOTCUP_POS_Y = 928/*718*/;

	// IceCup
	static constexpr int ICECUP_POS_X = 925/*1293*/;
	static constexpr int ICECUP_POS_Y = 928/*718*/;

	static constexpr int CENTER_POS_X = 933;
	static constexpr int CENTER_POS_Y = 679;

	static constexpr int LEFT_POS_X = 856;
	static constexpr int LEFT_POS_Y = 679;

	static constexpr int HOTCUP_NUM = 4;
	static constexpr int ICECUP_NUM = 7;

	enum class HOTCUP
	{
		NONE,
		SELECT,
		TAKE,
		MACHINE_CENTER,		//
		MACHINE_LEFT,		//
		SET_CENTER,				//
		SET_LEFT,				//
		FINISH
	};

	enum class ICECUP
	{
		NONE,
		SELECT,
		TAKE,
		ICEDISPENSER,
		SET_ICE,
		MACHINE_CENTER,		//
		MACHINE_LEFT,		//
		SET_CENTER,				//
		SET_LEFT,				//
		FINISH
	};

#pragma endregion

#pragma region MILK & PITCHER
	// �T�C�Y
	static constexpr int PITCHER_SIZE_X = 80;
	static constexpr int PITCHER_SIZE_Y = 62;	
	
	static constexpr int REIZOU_SIZE_X = 159;
	static constexpr int REIZOU_SIZE_Y = 179;

	// �����ʒu
	static constexpr int PITCHER_POS_X = ICECUP_POS_X + PITCHER_SIZE_X;
	static constexpr int PITCHER_POS_Y = ICECUP_POS_Y + 2;

	static constexpr int PITCHER_DESKPOS_X = 1359;
	static constexpr int PITCHER_DESKPOS_Y = 720;

	// ��Ԃ̎��
	static constexpr int PITCHER_NUM = 5;
	static constexpr int MILK_NUM = 2;

	// �s�b�`���[�̏��
	enum class PITCHER
	{
		NONE,			// 
		SELECT,			// �I��ł�����
		TAKE,			// �����Ă�����
		SELECT_DESK,
		SET_DESK,
		SELECT_M,		// �}�V����I��ł�����
		SET_M,			// �}�V���ɃZ�b�g���Ă�����
		READY_POUR,		// �J�b�v�㕔�Œ������������Ă�����
		POUR			// �J�b�v�ɒ����ł�����
	};

	// �����̏��
	enum class MILK
	{
		NONE,			//
		SELECT,			// �I��ł�����
		TAKE,			// �����Ă�����
		READY_POUR,		// �s�b�`���[�㕔�Œ������������Ă�����
		POUR			// �s�b�`���[�ɒ����ł�����
	};

	// �①�ɂ̏��
	enum class REIZOU
	{
		NONE,			//
		SELECT			// �I��ł�����
	};
#pragma endregion


	// ��������́i�z�b�g���j���[�j
	enum class HOTMENU
	{
		NONE,		// ����Ă��Ȃ��i�ł��Ă��Ȃ��j
		ESPRESSO,	// �G�X�v���b�\
		AMERICANO,	// �A�����J�\�m
		LATTE,		// ���e
		MOCA,		// ���J
		MACCHIATO	// �}�L�A�[�g
	};

	// ��������́i�A�C�X���j���[�j
	enum class ICEMENU
	{
		NONE,		// ����Ă��Ȃ��i�ł��Ă��Ȃ��j
		ESPRESSO,	// �G�X�v���b�\
		AMERICANO,	// �A�����J�\�m
		LATTE,		// ���e
		MOCA,		// ���J
		MACCHIATO	// �}�L�A�[�g
	};

	// �}�E�X�̃J�[�\���摜�̃T�C�Y
	static constexpr int CURSOR_SIZE_X = 20;
	static constexpr int CURSOR_SIZE_Y = 22;

	Player(Map& map);			// �R���X�g���N�^
	~Player(void);				// �f�X�g���N�^

	bool Init(SceneGame* parent);		// ����������

	void Update(void);			// �X�V����	
	void UpdateTalk(void);		// TALK
	void UpdateMake(void);		// MAKE	
	void UpdateDrink(void);		// DRINK
	void UpdateTalk2(void);		// TALK2

	void Draw(void);			// �`�揈��
	void DrawWait(void);
	void DrawTalk(void);
	void DrawMake(void);
	void DrawDrink(void);
	void DrawTalk2(void);

	bool Release(void);		// �������

	void SetPointPos(Vector2 pos,AsoUtility::DIR dir);
	void IsPoint(bool value) { isPoint_ = value; }
	void MovePoint(void);

#pragma region FILTER�֘A�̊֐�
	// filter�֘A�̊֐�------------------------------------------------------------------------------
	void ChangeFilter(FILTER value) { filter_ = value; }	// FILTER�̃��[�h��ς���
	FILTER GetFilter(void) { return filter_; }				// FITLER�̌��݂̃��[�h���擾����
	void SetFilterPos(Vector2 value) { filterPos_ = value; }	// FILTER�̍��W��ݒ肷��
	void StampFilter(bool value) { beansStamp_ = value; }		// FILTER�̒���STAMP������
	void BeansFilter(bool value) { beansIn_ = value; }		// FILTER�̒���BEANS�����邩�ǂ���
	void BeansState(bool In, bool Stamp, bool Brew, bool Dust);		// FILTER�̒���Beans�̏�Ԃ�ύX
	bool GetBeansIn(void) { return beansIn_; }				// beansIn�̏�Ԃ��擾����
	bool GetBeansStamp(void) { return beansStamp_; }			// beansStamp�̏�Ԃ��擾����
	bool GetBeansBrew(void) { return beansBrew_; }			// beansBrew�̏�Ԃ��擾����
	void DustBeans(void);				// beans�̕ϐ�������������
#pragma endregion

	//�A�C�e�����������Ă��邩�ǂ���----------------------------------------------------------------------
	bool IsHolding(void);				// �v���C���[����ɉ��������Ă��邩(true:�����Ă���)
	bool IsSetMachineCenter(void);		// �}�V�������ɉ����Z�b�g����Ă��邩
	bool IsSetMachineLeft(void);		// �}�V�������ɉ����Z�b�g����Ă��邩

	// tamper�֘A�̊֐�--------------------------------------------------------------------------------
	void ChangeTamper(TAMPER value) { tamper_ = value; }	// TAMPER�̃��[�h��ς���
	TAMPER GetTamper(void) { return tamper_; }				// TAMPER�̌��݂̃��[�h���擾����
	void SetTamperPos(Vector2 value) { tamperPos_ = value; }	// TAMPER�̍��W��ݒ肷��

	// cup�֘A�̊֐�--------------------------------------------------------------------------------
	void ChangeHotCup(HOTCUP value) { cup_ = value; }	// HOTCUP�̃��[�h��ς���
	HOTCUP GetHotCup(void) { return cup_; }

	void ChangeIceCup(ICECUP value) { iceCup_ = value; }	// ICECUP�̃��[�h��ς���
	ICECUP GetIceCup(void){ return iceCup_; }

	// �����ƃs�b�`���[�֘A�̊֐�--------------------------------------------------------------------
	void ChangePitcher(PITCHER value) { pitcher_ = value; }	// PITCHER�̃��[�h��ς���
	PITCHER GetPitcher(void){ return pitcher_; }

	void ChangeMilk(MILK value) { milk_ = value; }	// PITCHER�̃��[�h��ς���
	MILK GetMilk(void) { return milk_; }

	// ���j���[�֘A�̊֐�----------------------------------------------------------------------------
	HOTMENU GetHotMenu(void) { return hotMenu_; }				// �z�b�g���j���[�𓾂�
	ICEMENU GetIceMenu(void) { return iceMenu_; }				// �A�C�X���j���[�𓾂�
	void ResetHotMenu(void) { hotMenu_ = HOTMENU::NONE; }				// hotMenu_�����Z�b�g(NONE)�ɂ���
	void ResetIceMenu(void) { iceMenu_ = ICEMENU::NONE; }				// hotMenu_�����Z�b�g(NONE)�ɂ���

	void MoveCaution(void);

	void SetColor(int value){ color_ = value; }

	// �����o�������֘A--------------------------------------------------------------

	int SignVal(float value);

	bool IsHit(const Rect& rcA, const Rect& rcB);

	// ���֘A -----------------------------------------------------------------------
	void PlaySounds(int SoundName, int Vol);	// �ǂݍ��񂾉����Đ�����p

private:
	Map& map_;

	Vector2 mpos_;

	SceneGame* sceneGame_;

	// ���������֘A�̕ϐ�-----------------
	// ���̉摜
	int imgsPoint_[1][static_cast<int>(AsoUtility::DIR::MAX)];
	// �J�[�\�����L�[�������摜
	int imgsPushKey_[2][PUSHKEY_MAX_NUM];

	AsoUtility::DIR dir_;

	Vector2 pointPos_;
	Vector2 pointMove_;
	Vector2 pushPos_;

	bool isPoint_;
	bool isPushKey_;

	int pointDirection_;

	int pushKey_;	// 0:down , 1:up

	int cntAnim_;
	float speedAnim_;

	// ------------------------------------

	// �J�[�\���摜
	int cursorImage_;
	// �e�L�X�g�{�b�N�X�̒��̃J�[�\���摜
	int messagecursorImage_;

#pragma region filter�֘A
	// fitler�摜
	int imgsfilter_[2][FILTER_NUM];
	// beans�P�̉摜
	int imgbeans_;
	// �R�[�q�[�����̂Ă�悤�ɏo��x���摜
	int imgdust_;

	int imgfiltermat_;

	// �����]�����邽�߂̕ϐ�
	int direction;

	int flyPos_;

	// filter��beans�������Ă��邩�ǂ���(true;�����Ă���j
	bool beansIn_;

	// filter�̏�ɂ���beans�����������ǂ����itrue:�������j
	bool beansStamp_;

	// filter�ɓ����Ă���beans�🹂ꂽ���ǂ���(true�F���ꂽ�j
	bool beansBrew_;

	// filter�ɓ����Ă��韹�ꂽ���beans���̂Ă����ǂ���
	bool beansDust_;

	// filter�̏ꏊ
	Vector2 filterPos_;

	// filter�̏��
	FILTER filter_;

#pragma endregion

#pragma region grinder��ice dispenser�֘A

	int imgsgrinder_[1][2];

	Vector2 grinderPos_;

	int imgIceDispenser_;

#pragma endregion


#pragma region tamper�֘A
	// tamper�摜
	int imgstamper_[2][TAMPER_NUM];

	// tamper�̏ꏊ
	Vector2 tamperPos_;

	TAMPER tamper_;

	int pushCnt_;


#pragma endregion

#pragma region cup�֘A
	// cup�摜
	int imgsHotCup_[1][HOTCUP_NUM];
	int imgsIceCup_[1][ICECUP_NUM];

	int imgEspresso_;
	int imgAmericano_;
	int imgLatte_;	
	
	int imgIce_Espresso_;
	int imgIce_Americano_;
	int imgIce_Latte_;

	// �J�b�v�����ʒu�������摜
	int imgHotCupSet_;
	int imgIceCupSet_;

	// cup�̏ꏊ
	Vector2 cupPos_;

	// cup�̏��
	HOTCUP cup_;

	// icecup�̏��
	ICECUP iceCup_;

	bool isIce_;

#pragma endregion

#pragma region Milk�֘A

	int imgsPitcher_[1][PITCHER_NUM];
	int imgsReizou_[1][MILK_NUM];
	int imgMilk_;
	int imgMachineMilk_;
	int imgPitcherSet_;

	PITCHER pitcher_;
	MILK milk_;
	REIZOU reizou_;

	Vector2 pitcherPos_;
	Vector2 milkPos_;

	bool isMilk_;
	bool isFormer_;

#pragma endregion

	HOTMENU hotMenu_;
	ICEMENU iceMenu_;

	int imgsButton_[1][3];

	Vector2 cpos;
	int colorg;
	int colore;
	int colora;
	int colori;
	int colorm;

	int color_;

	Vector2 boxPos_;

	// �T�E���h�p--------------------------------------------------------------------------
	// �ϐ�

	// filter�p
	int filterTakeSound_;			// filter�������̉�	
	int filterSetMatSound_;			// mat�ɃZ�b�g����Ƃ��̉�
	int filterSetSound_;			// �}�V�[���ɃZ�b�g����Ƃ��̉�
	int filterSetOutSound_;			// �}�V�[������O���Ƃ��̉�
	int beansDustSound_;			// �{�b�N�X�Ɏ̂Ă�Ƃ��̉�

	// tamper�p
	int tamperPullupSound_;			// tamper�������グ�����̉�
	int tamperSetSound_;			// tamper�������グ�����̉�

	// cup�p
	int CupTakeSound_;				// Cup�������̉�
	int CupSetSound_;				// Cup���}�V�[���ɃZ�b�g����Ƃ��̉�
	int CupIceInSound_;				// Cup�ɕX�🹂��Ƃ��̉�
	int CupPourIceSound_;			// Cup�ɃA�C�X�R�[�q�[�🹂��Ƃ��̉�
	int CupPourHotSound_;			// Cup�Ƀz�b�g�R�[�q�[�🹂��Ƃ��̉�

	// grinder�p
	int grinderButton_;				// grinder�̃{�^�����������Ƃ��̉�

	// milk�p
	int pourMilkSound_;

	// pitcher�p
	int pitcherSound_;
	int setPitcherSound_;
	
	// �①�ɗp
	int reizouOpenSound_;
	int reizouCloseSound_;

	bool isPlaySound_;				// �������Đ������ǂ���

	int soundMem_;

	// �T�E���h�p�֐�
	bool LoadSounds(void);			// �ǂݍ��ݗp

	void CheckSounds(void);			// ���݉����Đ������ǂ������f����p

};

