#pragma once
#include "../Object/CustomerBase.h"

class SceneGame;
class Camera;
class Player;

class HotCup : public CustomerBase
{
public:

	HotCup(Player* player,Camera*camera);
	~HotCup(void);

	void Update(void) override;
	void UpdateHot(void) override;
	void UpdateIce(void) override;

	void Draw(void) override;

	// �p�����[�^�ݒ�
	void SetParam(void) override;

protected:
	// �V�[���Q�[���̃|�C���^�i�[�̈�
	SceneGame* sceneGame_;

	Camera* camera_;

	// �v���C���[�̃|�C���^
	Player* player_;

};

