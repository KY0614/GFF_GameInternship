// ---------------------------------------
// �Q�[������	 :DrinKingdom(��)
// ����			 :2316032	�P���h�q
// ---------------------------------------

#include <DxLib.h>		// DX���C�u�������g�p����
#include "Application.h"

// WinMain�֐�
// -----------------
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR IpCmdLine, int nCmdShow)
{
	Application::CreateInstance();

	Application::GetInstance().Run();

	Application::GetInstance().Release();

	return 0;				// �V�X�e���̏I������
}