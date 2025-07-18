#pragma once
#include "SceneBase.h"
#include"../Common/Fader.h"
#include"../Object/Character/PlayerManager.h"
#include<vector>
#include<memory>

class Grid;
class PlayerManager;
class PlayerBase;
class Enemy;
class EnemyManager;
class StageManager;
class SkyDome;
class LevelScreenManager;
class UnitPositionLoad;
class ChickenManager;
class FazeResult;
class InformFaze;
class PlayerUI;


class GameScene : public SceneBase
{
public:
	//デバッグ用
	//#define _DEBUG_COL	//テスト用の敵とプレイヤーを一体ずつ生成（この行をコメントアウトすると消える）

	//定数
	static constexpr int PHASE_TIME = 180;	//フェーズ切り替えの時間（仮）

	static constexpr int LAST_FAZE = 3;

	//ヒットエフェクトサイズ
	static constexpr float HIT_EFFECT_SIZE = 20.0f;
	//バフアローのヒットエフェクトサイズ
	static constexpr float BUFF_ARROW_EFFECT_SIZE = 40.0f;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	//ステージ
	std::unique_ptr<StageManager> stage_;

	//スカイドーム
	std::unique_ptr<SkyDome> sky_;

	//フェーダー
	std::unique_ptr<Fader>fader_;
	bool isFadeInFinish_;

	//ゲームシーンのフェーズ遷移中判定
	bool isPhaseChanging_;
	int phaseCnt_;


	//フェーズリザルト
	std::unique_ptr<FazeResult>fazeResult_;
	//リザルト中か
	bool isFazeRezult_;

	//プレイヤー
	std::unique_ptr<PlayerManager>playerMng_;
	std::unique_ptr<PlayerUI> uis_[PlayerManager::PLAYER_NUM];

	//敵
	std::unique_ptr<EnemyManager>enmMng_;

	//フェーズ数カウント
	int fazeCnt_;

	//フェーズ数通知関連
	bool isInformFaze_;		//通知中かのtrue/false
	std::unique_ptr<InformFaze>inform_;

	//チキン
	std::unique_ptr<ChickenManager> chicken_;

	std::unique_ptr<LevelScreenManager> level_;

	std::unique_ptr<UnitPositionLoad> unitLoad_;

	void SoundInit(void);	//音関連初期化

#pragma region 当たり判定
	//当たり判定All
	void Collision(void);
	//敵関連の当たり判定
	void CollisionEnemy(void);
	//プレイヤー関連の当たり判定
	void CollisionPlayer(void);
	//ニワトリあたり判定
	void CollisionChicken(void);

	//遠距離関係の当たり判定
	void CollisionPlayerArrow(int _p1Num);	
	//アーチャー用の攻撃ターゲット取得可能
	void CollisionPlayerSerch(int _p1Num);	
#pragma endregion

	//フェード
	void Fade(void);

	//フェーズ遷移
	void ChangePhase(void);
	//フェーズ更新(完全暗転中)
	void UpdatePhase(void);
	//フェーズ描画
	void DrawPhase(void);

	//強化要素反映
	void LevelUpReflection();

	//リザルト
	void FazeResultUpdate(void);
	//フェーズ数を知らせる
	void InformFazeNum(void);

	void SetIsInform(const bool _flag);	//フェーズ数表示するかどうかのフラグ

	//ゲームオーバー判定
	bool IsGameOver(void);
};

