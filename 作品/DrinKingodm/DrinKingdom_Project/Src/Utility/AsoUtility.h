#pragma once

#include<string>
#include <vector>

class Vector2;
class Vector2F;

class AsoUtility
{
public:
	// �񋓌^
	// ����
	enum class DIR
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
	
	// ������̕���
	static std::vector <std::string> 
		Split(std::string& line, char delimiter);

	// �l�̌ܓ��ifloat)
	static int Round(float value);

	// �I�[�o�[���[�h�֐�
	static Vector2 Round(Vector2F value);

};