#pragma once

class SceneBase
{
public:
	SceneBase(void);
	virtual ~SceneBase(void);

	virtual bool Init(void);
	virtual void Update(void);
	virtual void Draw(void);		// 描画処理
	virtual bool Release(void);		// 解放処理
};