#include <DxLib.h>
#include <sstream>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "AsoUtility.h"


// ������̕���
std::vector <std::string>
	AsoUtility::Split(std::string& line, char delimiter)
{
	// ���I�z��̖߂�l�i�[�̈�m��
	std::vector<std::string> result;

	// �����񑀍�p�̃N���X�ɒu��������
	std::istringstream lineStream(line);

	// 1�f�[�^�̊i�[�̈�
	std::string field;

	// stream�����ɓǂݍ��݁Agetline���g����
	// ��R�����Ŏw�肵���f���~�^�L���܂ł̃f�[�^��
	// ��Q�����̕ϐ��Ɋi�[����
	while (getline(lineStream, field, delimiter)) 
	{
		// ���I�z��Ɏ擾�����f�[�^��ǉ�����
		result.push_back(field);
	}

	return result;
}

// �l�̌ܓ��ifloat)
int AsoUtility::Round(float value)
{
	return static_cast<int>(roundf (value));
}


// �I�[�o�[���[�h�֐�
// �����Ɩ߂�l��ύX���Ă���֐�
Vector2 AsoUtility::Round(Vector2F value)
{
	Vector2 ret;

	ret.x = static_cast<int>(roundf(value.x));
	ret.y = static_cast<int>(roundf(value.y));

	return ret;
}