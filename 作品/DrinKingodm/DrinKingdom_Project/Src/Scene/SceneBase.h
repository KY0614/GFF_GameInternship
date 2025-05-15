#pragma once

class SceneBase
{
public:
	SceneBase(void);
	virtual ~SceneBase(void);

	virtual bool Init(void);
	virtual void Update(void);
	virtual void Draw(void);		// �`�揈��
	virtual bool Release(void);		// �������
};