#include <DxLib.h>
#include <string.h>
#include "../Manager/InputManager.h"
#include "../Scene/SceneGame.h"
#include "../Object/CustomerBase.h"
#include "Message.h"

Message::Message(void)
{
	currentCursor = 0;
	currentLineCursor = 0;
	timeCnt_ = 0;
	messCount_ = 0;
	isMessage_ = false;
	isWrite_ = false;
}

Message::~Message(void)
{
}

bool Message::Init(SceneGame* parent)
{
	sceneGame_ = parent;

	imgMessageBox_ = LoadGraph("Data/GameScene/message.png");
	if (imgMessageBox_ == -1)
	{
		OutputDebugString("message.png�摜��������Ȃ�");
		return false;
	}
	
	imgMessageBox2_ = LoadGraph("Data/GameScene/message2.png");
	if (imgMessageBox2_ == -1)
	{
		OutputDebugString("message2.png�摜��������Ȃ�");
		return false;
	}
	
	imgMessageBox3_ = LoadGraph("Data/GameScene/message3.png");
	if (imgMessageBox3_ == -1)
	{
		OutputDebugString("message3.png�摜��������Ȃ�");
		return false;
	}

	// �X�y�[�X�L�[�����摜�̓ǂݍ���
	int ret;
	ret = LoadDivGraph(
		"Data/Push Space.png",
		1 * MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		MAX_ANIM_NUM,
		SPACE_SIZE_X,
		SPACE_SIZE_Y,
		&(imgsSpace_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("Push Space.png�摜��������Ȃ�");
		return false;
	}

	waitSound_ = LoadSoundMem("Data/Sound/HotCup_talk.mp3");
	iceSound_ = LoadSoundMem("Data/Sound/IceCup_talk.mp3");
	hotSound_ = LoadSoundMem("Data/Sound/wait.mp3");

	// �ǂ݂��񂾉��̉��ʂ𒲐�
	ChangeVolumeSoundMem(WAIT_SOUND_VOLUME, waitSound_);
	ChangeVolumeSoundMem(ICE_SOUND_VOLUME, iceSound_);
	ChangeVolumeSoundMem(HOT_SOUND_VOLUME, hotSound_);


	SetFontSize(FONT_SIZE);

	messCount_ = -1;
	isMessage_ = false;
	isWrite_ = false;

	cntAnim_ = 0;
	speedAnim_ = 0.05f;

	return true;
}

void Message::Update(void)
{
	auto& ins = InputManager::GetInstance();

	timeCnt_++;
	cntAnim_++;

	if (sceneGame_->GetFase() == SceneGame::FASE::WAIT)
	{
		UpdateWait();
	}
	else if (sceneGame_->GetFase() == SceneGame::FASE::TALK)
	{
		UpdateTalk();
	}
	else if(sceneGame_->GetFase() == SceneGame::FASE::TALK2)
	{
		UpdateTalk2();
	}

}

void Message::UpdateWait(void)
{
	auto& ins = InputManager::GetInstance();

	// �o�ߎ���
	int time = sceneGame_->GetTime();

	isWrite_ = true;

	// �ŏ��͏������̕������Z�b�g
	// �Q��ڈȍ~�͓��X�҂����Z�b�g
	if (messCount_ == -1)
	{
		sound_ = waitSound_;

		SetMessage("������......");

		messCount_ = 1;
	}
	else if ((messCount_ == 0))
	{
		sound_ = waitSound_;

		SetMessage("���X�҂�......");
		messCount_++;
	}
	else if ((messCount_ > 0) && time > 3000 )
	{
		SetMessage("");
		sceneGame_->ChangeFase(SceneGame::FASE::TALK);
		isMessage_ = false;
		messCount_++;	// 2
	}
}

void Message::UpdateTalk(void)
{
	auto& ins = InputManager::GetInstance();
	int time = sceneGame_->GetTime();

	CustomerBase::CUSTOMER customer = sceneGame_->GetCustomer();

	bool messCursor = sceneGame_->GetMessCursor();

	switch (customer)
	{
	case CustomerBase::CUSTOMER::NONE:
		break;

	case CustomerBase::CUSTOMER::HOTCUP:
		sound_ = hotSound_;

		// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
		// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
		if (((messCount_ > 1) && (messCount_ < 3))		// 1 < messCount_ < 3
			&& time > MESSAGE_DELAY_TIME)
		{
			SetMessage("...�ǂ���");
			messCount_++;	// 3
		}
		else if (((messCount_ > 2) && (messCount_ < 4)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
			(messCursor == true && ins.IsTrgMouseLeft() == true)
			))
		{
			SetMessage("������̂��X�ɂ͉�������܂����H");

			messCount_++;	// 4
		}
		else if (((messCount_ > 3) && (messCount_ < 5)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage(".....�Ƃ����Ă��A���̓R�[�q�[�������߂Ȃ���ł����ǂˁB");
			messCount_++;	// 5
		}
		else if (((messCount_ > 4) && (messCount_ < 6)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("�Ȃ�ׂ��ꂢ�R�[�q�[�ŉ��������̂����肢���܂��B");
			messCount_++;	// �U
		}
		else if (((messCount_ > 5) && (messCount_ < 7)) && !(isWrite_) &&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("");
			sceneGame_->ChangeFase(SceneGame::FASE::MAKE);
			isMessage_ = false;
			isWrite_ = true;
			messCount_++;	// 7
		}
		break;
	
	case CustomerBase::CUSTOMER::ICECUP:
		sound_ = iceSound_;

		// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
		// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
		if (((messCount_ > 1) && (messCount_ < 3)) 
			&& time > MESSAGE_DELAY_TIME)
		{
			SetMessage("����ɂ��́I�I�V�����Ȃ��X�ˁI");
			messCount_++;	// 3
		}
		else if (((messCount_ > 2) && (messCount_ < 4)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("���̂��X�͉�������́H");

			messCount_++;	// 4
		}
		else if (((messCount_ > 3) && (messCount_ < 5)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("(...���Ȃ��̓��j���[�������Ȃ��珤�i���Љ�Ă���...�j");
			messCount_++;	// 5
		}
		else if (((messCount_ > 4) && (messCount_ < 6)) 
			&& !(isWrite_)
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("...���`��ǂ���悭�킩��Ȃ���I�₽�����̂�������Ȃ�ł�������I");
			messCount_++;	// �U
		}
		else if (((messCount_ > 5) && (messCount_ < 7)) 
			&& !(isWrite_) 
			&&
			((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
				(messCursor == true && ins.IsTrgMouseLeft() == true)
				))
		{
			SetMessage("");
			sceneGame_->ChangeFase(SceneGame::FASE::MAKE);
			isMessage_ = false;
			isWrite_ = true;
			messCount_++;	// 7
		}
		break;
	
	default:
		break;
	}

 }

void Message::UpdateTalk2(void)
{
	auto& ins = InputManager::GetInstance();
	int time = sceneGame_->GetTime();

	CustomerBase::CUSTOMER customer = sceneGame_->GetCustomer();
	CustomerBase::REACTION reaction = sceneGame_->GetReaction();

	bool messCursor = sceneGame_->GetMessCursor();

	switch (customer)
	{
	case CustomerBase::CUSTOMER::NONE:
		break;

	case CustomerBase::CUSTOMER::HOTCUP:
		// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
		// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
		switch (reaction)
		{
		case CustomerBase::REACTION::HAPPY:
			// ��]�ʂ�̏��i��n�����Ƃ�
			if (((messCount_ > 6) && (messCount_ < 8))		// 1 < messCount_ < 3
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("���肪�Ƃ��������܂��B");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("�ƂĂ��r�^�[�ŔZ���ł��ˁB���̍D���ȃR�[�q�[�ł��B");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("�ƂĂ��������������ł��B�����A��Ă܂����܂��ˁB����ł́B");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::NORMAL:
			// ��]�ʂ�̏��i�ɋ߂����̂�n�����Ƃ�
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("���肪�Ƃ��������܂��B");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("���܂ŐF��ȃR�[�q�[������ł��܂������ǁA�����̃R�[�q�[�������Ȃ��ł��ˁB");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("�܂����݂����Ȃ����瑫���^�т܂��ˁB");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::BAD:
			// ��]�������i�ƑS���Ⴄ���̂�n�����Ƃ�
			if (((messCount_ > 6) && (messCount_ < 8))		// 1 < messCount_ < 3
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage(".....");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("...�����̂��X�̃R�[�q�[�͂���Ȋ����Ȃ�ł��ˁB");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("����...���̌��ɂ͍���Ȃ���������܂���...���̃R�[�q�[���C�ɓ���l������ł��傤�B");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11)) && !(isWrite_) &&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}

			break;

		default:
			break;
		}

		break;

	case CustomerBase::CUSTOMER::ICECUP:
		switch (reaction)
		{
		case CustomerBase::REACTION::HAPPY:
			// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
			// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("���肪�ƁI");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("�߂���������������I����ς�₽�����ݕ��͂����ς肷��ˁI");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("����Ȃɂ������X������Ȃ�Ēm��Ȃ������c�B���Z�������A��Ă܂�����ˁI");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::NORMAL:
			// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
			// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("���肪�Ƃ��I");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("���\��߂̃R�[�q�[�������Ă�񂾂ˁB�ł�����������I");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("���x�͋ꖡ���T���ڂ��Ɗ������ȁ`�B�܂�����ˁI");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		case CustomerBase::REACTION::BAD:
			// �ŏ��̃��b�Z�[�W�͎��Ԍo�߂ŕ\�������
			// ���b�Z�[�W���Ō�܂ŕ\�����ꂽ�Ƃ��ɃX�y�[�X�C�[�����Ŏ��̃��b�Z�[�W���Z�b�g����
			if (((messCount_ > 6) && (messCount_ < 8))
				&& time > MESSAGE_SWITCH_TIME)
			{
				SetMessage("���肪�Ƃ�");
				messCount_++;	// 3
			}
			else if (((messCount_ > 7) && (messCount_ < 9))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("���ɂ͂������...�₽�����̂��ǂ��������Ȃ�...");

				messCount_++;	// 4
			}
			else if (((messCount_ > 8) && (messCount_ < 10))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("���͗₽�����ݕ�������̂����҂��Ƃ���");
				messCount_++;	// 5
			}
			else if (((messCount_ > 9) && (messCount_ < 11))
				&& !(isWrite_)
				&&
				((ins.IsTrgDown(KEY_INPUT_SPACE)) ||
					(messCursor == true && ins.IsTrgMouseLeft() == true)
					))
			{
				SetMessage("");
				sceneGame_->ChangeFase(SceneGame::FASE::NONE);
				isMessage_ = false;
				isWrite_ = true;
				messCount_ = 0;
			}
			break;

		default:
			break;
		}


		break;

	default:
		break;
	}

}

void Message::Draw(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 cameraPos = sceneGame_->GetCameraPos();

	// ������1�������Z�b�g����ĂȂ������烁�b�Z�[�W�{�b�N�X��\�����Ȃ�
	if (strnlen_s(message_, MAX_LENGTH * MAX_LINE) <= 0)
	{
		return;
	}
	
	int animNum = static_cast<int>(
		static_cast<float>(cntAnim_) * speedAnim_)
		% MAX_ANIM_NUM;

	DrawGraph(25, 25, imgMessageBox_, true);
	DrawGraph(300, 260, imgMessageBox2_, true);
	DrawGraph(370, 310, imgMessageBox3_, true);

	if (isWrite_ == false)
	{
		DrawRotaGraph(300,
			200,
			0.5f, 0.0f,
			imgsSpace_[0][animNum],
			true);
	}

	DrawMessage();
}

void Message::DrawTalk(void)
{

}

void Message::DrawTalk2(void)
{

}

// ���b�Z�[�W�̕`��
void Message::DrawMessage(void)
{
	auto& ins = InputManager::GetInstance();

	isMessage_ = true;


	if (timeCnt_ == 4)
	{
		// 1�b�Ԃ��������̏���
		if (message_[currentCursor] != '\0')
		{
			currentCursor++;
			isWrite_ = true;
			PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
		}	
		else
		{
			isWrite_ = false;
		}

		
		// MESSAGE_MAX_LENGTH�܂ŕ�����`�悵����i�K��؂�ւ���
		if (currentCursor % MAX_LENGTH == 0)
		{
			if (message_[currentCursor] != '\0')
			{
				currentLineCursor++;
			}
			else
			{
				isWrite_ = false;
			}
		}

		if (message_[currentCursor] == '\0')
		{
			StopSoundMem(sound_);
		}
		timeCnt_ = 0;
	}

	// ���b�Z�[�W�`��
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (i == currentLineCursor)
		{
			// �T�E���h�m�x�����b�Z�[�W���ɕ\��
			WriteSubstring(message_, i * MAX_LENGTH,
				currentCursor - MAX_LENGTH * i,
				MESSAGE_POS_X , MESSAGE_POS_Y + FONT_SIZE * i ,
				0xffffff, i);
			break;
		}
		else
		{
			// ���b�Z�[�W�����̂܂ܕ\��
 			WriteSubstring(message_, i * MAX_LENGTH,
				MAX_LENGTH, MESSAGE_POS_X,
				MESSAGE_POS_Y + FONT_SIZE * i,
				0xffffff, i);

			StopSoundMem(sound_);
		}
	}
}

bool Message::Release(void)
{
	return true;
}

// code�����{��ł��邩���肷��
// �߂�l���P�F���{��@�O�F���{��ł͂Ȃ�
int Message::isJapaneseCharacter(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) ||
		(code >= 0xE0 && code <= 0xFC))
	{
		return 1;
	}
	return 0;
}

// message�Ŏw�肵�����͂�start�̈ʒu����len�������\������
// �����񍶑��̍��W��(posX,posY)�A�����̐F��color�Ƃ���
void Message::WriteSubstring(char* message, int start, int len, 
	int posX, int posY, int color, int bufferLine)
{
	int i;
	// ������
	int maxLen = strlen(message);

	// start�̈ʒu��ύX����	
	// start�̈ʒu�܂łɓ��{�ꂪ�o�Ă��Ă�����A1�𑫂��Ă���
	for (i = 0; i < start && message[i] != '\0';)
	{
		if (isJapaneseCharacter(message[i]))
		{
			// ���{��̏ꍇ2�o�C�g���i�߂�
			i += 2;

			// start��1�o�C�g������
			start++;
		}
		else
		{
			// ���p�����̏ꍇ�A�P�o�C�g���i�߂�
			i++;
		}
	}

	// start�̈ʒu���\���������ő啶�������傫���ꍇ
	if (start >= maxLen)
	{
		return;
	}

	// �w�肵���ʒu����len�������\������
	for (i = 0; i < len && message[start + i] != '\0';)
	{
		if (isJapaneseCharacter(message[start + i]))
		{
			// ���{��̏ꍇ�A2������buffer�ɃZ�b�g����
			messageBuffer[bufferLine][ i ] = message[start + i];
			messageBuffer[bufferLine][i + 1] = message[start + i + 1];
			// len�͓��{��Ȃ̂ŁA�P�o�C�g���ǉ�����
			len++;
			// 2�o�C�g���i�߂�
			i += 2;
		}
		else
		{
			// ���p����1������\��
			// printf("%c", message[start + i]);
			messageBuffer[bufferLine][i] = message[start + i];
			// 1�o�C�g���i�߂�
			i++;
		}
	}
	messageBuffer[bufferLine][i] = '\0';

	// ���b�Z�[�W�`��
	DrawString(posX, posY, messageBuffer[bufferLine], color);
}

void Message::SetMessage(const char* message)
{
	// �J�[�\���̏�����
	currentCursor = 0;
	currentLineCursor = 0;
	timeCnt_ = 0;

	// ���b�Z�[�W���R�s�[
	strncpy_s(message_, message, MAX_LENGTH * MAX_LINE);
}

bool Message::Switch(void)
{
	return isMessage_;
}