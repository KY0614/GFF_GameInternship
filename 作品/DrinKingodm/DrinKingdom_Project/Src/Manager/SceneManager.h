#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

// 前方宣言
class Fader;
class SceneBase;
class Camera;

class SceneManager
{
public:
	// 列挙型
	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		STORY,
		OPENING,
		GAME,
		GAMEOVER
	};

	// メンバー関数
	bool Init(void);		// 初期化処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理
	bool Release(void);		// 解放処理

	// シーン切り替えを依頼する関数
	void ChangeScene(SCENE_ID nextID, bool isToFade);		// シーン切り替え

	// シングルトン化
	// -------------------

	// インスタンスの生成
	// 外部から静的にインスタンスを生成する
	static void CreateInstance(void);

	// 外部でインスタンスを利用可能とするために
	// インスタンスを返す関数を用意する
	// 参照型にしているがポインタ型でもよい
	static SceneManager& GetInstance(void);

private:
	// メンバー変数
	// ---------------------
	SCENE_ID sceneID_;			// 現在のシーンID
	SCENE_ID waitSceneID_;		// 次に遷移するシーンID

	// シーン遷移中かの判断用フラグ（true:シーン遷移中）
	bool isSceneChanging_;

	// フェード
	Fader* fader_;				// フェードのインスタンス

	// シーン
	SceneBase* scene_;			// シーンインスタンス管理

	// メンバー関数
	// --------------------------
	void DoChangeScene(void);		// シーンを切り替える
	void Fade(void);				// フェードを実施用関数

	// 指定したシーンの解放関数
	void ReleaseScene(SCENE_ID iSceneID);		// シーンの解放処理

	// シングルトン化
	// -------------------
	SceneManager(void);		// コンストラクタ
	~SceneManager(void);	// デストラクタ

	// コピーコンストラクタを利用できなくする
	SceneManager(const SceneManager& ins);

	// インスタンスの破棄
	void Destory(void);

	// 静的なインスタンス格納領域
	static SceneManager* instance_;

	// カメラ
	Camera* camera_;

};