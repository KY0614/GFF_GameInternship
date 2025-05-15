// #pragma once
#include "./CustomerBase.h"

class SceneGame;
class Camera;
class Player;

class IceCup : public CustomerBase
{
public:
	IceCup(Player* player, Camera* camera);
	~IceCup(void);

	void Update(void) override;
	void UpdateHot(void) override;
	void UpdateIce(void) override;

	void Draw(void) override;


	// �p�����[�^�ݒ�
	void SetParam(void) override;

protected:
	Camera* camera_;

	// �v���C���[�̃|�C���^
	Player* player_;

};

