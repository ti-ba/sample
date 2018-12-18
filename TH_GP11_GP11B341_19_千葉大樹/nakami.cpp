//=============================================================================
//
// Main処理 [main.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "enemy2.h"
#include "bullet.h"
#include "bg.h"
#include "enemybullet.h"
#include "guage.h"
#include "enemyguage.h"
#include "score.h"
#include "nakami.h"
#include "gameover.h"
#include "bom.h"
#include "bomguage.h"
#include "sound.h"
#include "boss.h"
#include "effect.h"
#include "effect2.h"
#include "bossguage.h"
#include "bossbullet.h"
#include "enemyguage2.h"
#include "EnemyBullet2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(ptr)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
 LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);

 bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

 void CheckHit(void);
 void InitGame(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

extern int			Score;							// スコア
extern LPDIRECTSOUNDBUFFER8	enemySE;				// SE用バッファ
extern LPDIRECTSOUNDBUFFER8	HitSE;					// SE用バッファ
extern LPDIRECTSOUNDBUFFER8	enemybulletSE;			// SE用バッファ

//=============================================================================
// 更新処理
//=============================================================================
void UpdateNakami(void)
{

		// プレイヤーの更新処理
		UpdatePlayer();

		// エネミーの更新処理
		UpdateEnemy();

		// エネミーの更新処理
		//UpdateEnemy2();

		// バレットの更新処理
		UpdateBullet();

		// ボムの更新処理
		UpdateBom();

		//ボムのゲージ更新処理
		UpdateBomGuage();


		// BGの更新処理
		UpdateBG();

		// 敵の弾の更新処理
		UpdateEnemyBullet();

		//ゲージの更新処理
		UpdateGuage();

		//エネミーゲージの更新処理
		UpdateEnemyGuage();

		// エネミーゲージの更新処理
		UpdateEnemyGuage2();
				
		// エフェクトの更新処理
		UpdateEffect();

		// エフェクト２の更新処理
		UpdateEffect2();

		UpdateEnemyBullet2();


		//当たり判定
		CheckHit();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawNakami(void)
{
			// BGの描画処理
			DrawBG();

			// ゲージの描画処理
			DrawGuage();

			// エネミーゲージの描画処理
			DrawEnemyGuage();

			// エネミーゲージの描画処理
			DrawEnemyGuage2();

			// エネミーの描画処理
			DrawEnemy();

			// エネミーの描画処理
			//DrawEnemy2();

			// プレイヤーの描画処理
			DrawPlayer();

			// バレットの描画処理
			DrawBullet();

			// ボムの描画処理
			DrawBom();

			// ボムのゲージの描画処理
			DrawBomGuage();


			//敵の弾の描画処理
			DrawEnemyBullet();

			// エフェクトの描画処理
			DrawEffect();

			// エフェクト２の描画処理
			DrawEffect2();

			DrawEnemyBullet2();

}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);			//プレイヤーのポインターを初期化						
	ENEMY *enemy = GetEnemy(0);				// エネミーのポインターを初期化
	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	GUAGE *guage = GetGuage(0);				// ゲージのポインターを初期化
	ENEMYBULLET *enemybullet = GetEnemyBullet(0);	//エネミーバレットのポインターを初期化
	BOM *bom = GetBom(0);					// ボムのポインターを初期化
	ENEMYGUAGE *enemyguage = GetEnemyGuage(0);		//敵のゲージのポインターを初期化
	EFFECT2 *effect2 = GetEffect2(0);		// エフェクトのポインターを初期化
	BOSS *boss = GetBoss(0);				// ボスのポインターを初期化
	ENEMY2 *enemy2 = GetEnemy2(0);
	ENEMYGUAGE2*Enemyguage2 = GetEnemyGuage2(0);
	/* 弾と敵(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;
		

		for (int j = 0; j < ENEMY_MAX; j++, enemy++ ,enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				bullet->use = false;		// 弾の消滅処理を行い
				enemyguage->Radius -= 100 / 3;		// ゲージ減少
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					enemy->use = false;		// 敵は倒される
					SetEffect(enemy->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				}
			}
		}
	}

	/* 弾と敵2(BC)*/
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;


		for (int j = 0; j < ENEMY2_MAX; j++, enemy2++, Enemyguage2++)
		{
			if (enemy2->use == false) continue;

			if (CheckHitBC(bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY2_SIZE_X) == true)
			{
				bullet->use = false;		// 弾の消滅処理を行い
				Enemyguage2->Radius -= 100 / 3;		// ゲージ減少
				if (Enemyguage2->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					enemy2->use = false;		// 敵は倒される
					SetEffect(enemy2->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				}
			}
		}
	}

	// ボムと敵
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;

		enemyguage = GetEnemyGuage(0);		//敵のゲージのポインターを初期化
		enemy = GetEnemy(0);				//敵のポインターを初期化

		for (int j = 0; j < ENEMY_MAX; j++, enemy++ ,enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(bom->pos, enemy->pos, TEXTURE_BOM_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				bom->use = false;			// 弾の消滅処理を行い
				enemyguage->Radius -= 100 / 1;		// ゲージ減少
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					enemy->use = false;		// 敵は倒される
					SetEffect2(enemy->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
			}
		}
	}

	//エフェクト２と敵
	for (int i = 0; i < EFFECT2_MAX; i++, effect2++)
	{

		if (effect2->use == false) continue;

		enemyguage = GetEnemyGuage(0);		//敵のゲージのポインターを初期化
		enemy = GetEnemy(0);

		for (int j = 0; j < ENEMY_MAX; j++, enemy++, enemyguage++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(effect2->pos, enemy->pos, TEXTURE_EFFECT2_SIZE_X, TEXTURE_ENEMY_SIZE_X) == true)
			{
				effect2->use = false;		// 弾の消滅処理を行い
				enemyguage->Radius -= 100 / 1;		// ゲージ減少
				if (enemyguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					enemy->use = false;		// 敵は倒される
					SetEffect2(enemy->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				}
			}
		}
	}


	//敵が全滅したら画面遷移
	enemy = GetEnemy(0);	//エネミーのポインターの初期化
	int enemycnt = 0;		//敵を数える

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			enemycnt++;
		}
	}

	// 数えた結果敵が全滅？
	if (enemycnt == 0)
	{
		boss = GetBoss(0);	//ボスのポインターの初期化
		boss->use = true;
		SetStage(STAGE_BOSS);
	}


	

	//自分と敵の弾(BC)
;	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		
		if (enemybullet->use == false) continue;
		{
			//guage = GetGuage(0);		// プレイヤーのゲージのポインターを初期化
			player = GetPlayer(0);		// プレイヤーのポインターを初期化
			for (int j = 0; j < PLAYER_MAX; j++, player++, guage++)
			{
				if (player->use == false) continue;

				if (CheckHitBC(enemybullet->pos, player->pos, TEXTURE_ENEMYBULLET_SIZE_X, TEXTURE_PLAYER_SIZE_X) == true)
				{
					enemybullet->use = false;	// 弾の消滅処理を行い
					guage->Radius -= 100 / 9;			//ゲージの減少
					if (guage->Radius <= 0)
					{
						PlaySound(HitSE, E_DS8_FLAG_NONE);	// 被弾した音再生
						player->use = false;	// プレイヤーは倒される
						InitGame();				// ゲームの再初期化処理
						SetStage(STAGE_GAME_OVER);	//画面遷移
					}
					else
					{
						PlaySound(HitSE, E_DS8_FLAG_NONE);	// 被弾した音再生
					}
				}
			}
		}
	}

}


void CheckHit_Boss(void)
{
	PLAYER *player = GetPlayer(0);			//プレイヤーのポインターを初期化						
	BULLET *bullet = GetBullet(0);			// バレットのポインターを初期化
	GUAGE *guage = GetGuage(0);				// ゲージのポインターを初期化
	BOM *bom = GetBom(0);					// ボムのポインターを初期化
	EFFECT2 *effect2 = GetEffect2(0);		// エフェクトのポインターを初期化
	BOSS *boss = GetBoss(0);				// ボスのポインターを初期化
	BOSSGUAGE *bossguage = GetBossguage(0); // ボスゲージのポインターを初期化
	BOSSBULLET *bossbullet = GetBossBullet(0);


	// ボスと弾(BC)
	bullet = GetBullet(0);
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false) continue;
		bossguage = GetBossguage(0);		//敵のゲージのポインターを初期化
		boss = GetBoss(0);

		for (int j = 0; j < BOSS_MAX; j++, boss++, bossguage++)
		{
			if (boss->use == false) continue;

			if (CheckHitBC(bullet->pos, boss->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_BOSS_SIZE_X) == true)
			{
				bullet->use = false;		// 弾の消滅処理を行い
				bossguage->Radius -= 100 / 20;		// ゲージ減少
				if (bossguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					boss->use = false;		// 敵は倒される
					SetEffect2(boss->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
				else
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
				}
			}
		}
	}

	//ボムとボス(BC)
	bom = GetBom(0);					// ボムのポインターを初期化
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == false) continue;
		bossguage = GetBossguage(0);		//敵のゲージのポインターを初期化
		boss = GetBoss(0);


		for (int j = 0; j < BOSS_MAX; j++, boss++, bossguage++)
		{
			if (boss->use == false) continue;

			if (CheckHitBC(bom->pos, boss->pos, TEXTURE_BOM_SIZE_X, TEXTURE_BOSS_SIZE_X) == true)
			{
				bom->use = false;			// 弾の消滅処理を行い
				bossguage->Radius -= 100 / 10;		// ゲージ減少
				if (bossguage->Radius <= 0)
				{
					PlaySound(enemySE, E_DS8_FLAG_NONE);	// 当たったときの音再生
					boss->use = false;		// 敵は倒される
					SetEffect2(boss->pos);	// 爆破
					AddScore(100);			// スコア計算
				}
			}
		}
	}

	//敵が全滅したら画面遷移
	boss = GetBoss(0);	//ボスのポインターの初期化
	int bosscnt = 0;		//敵を数える
	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == true)
		{
			bosscnt++;
		}
	}

	// 数えた結果敵が全滅？
	if (bosscnt == 0)
	{
		InitGame();		// ゲームの再初期化処理
		SetStage(STAGE_SCORE);
	}

	//自分とボスの弾(BC)
	for (int i = 0; i < BOSSBULLET_MAX; i++, bossbullet++)
	{

		if (bossbullet->use == false) continue;

		guage = GetGuage(0);		// プレイヤーのゲージのポインターを初期化
		player = GetPlayer(0);		// プレイヤーのポインターを初期化
		for (int j = 0; j < PLAYER_MAX; j++, player++, guage++)
		{
			if (player->use == false) continue;

			if (CheckHitBC(bossbullet->pos, player->pos, TEXTURE_BOSSBULLET_SIZE_X, TEXTURE_PLAYER_SIZE_X) == true)
			{
				bossbullet->use = false;	// 弾の消滅処理を行い
				guage->Radius -= 100 / 9;			//ゲージの減少
				if (guage->Radius <= 0)
				{
					PlaySound(HitSE, E_DS8_FLAG_NONE);	// 被弾した音再生
					player->use = false;	// プレイヤーは倒される
					InitGame();				// ゲームの再初期化処理
					SetStage(STAGE_GAME_OVER);	//画面遷移
				}
				else
				{
					PlaySound(HitSE, E_DS8_FLAG_NONE);	// 被弾した音再生
				}
			}
		}
	}

}


//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
	bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
	{
		if ((size1 + size2) * (size1 + size2) >
			(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y))
		{
			return true;
		}

		return false;
	}

//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
	void InitGame(void)
	{
		InitPlayer(1);		// プレイヤーの再初期化
		//InitGuage(1);		// ゲージの再初期化
		InitEnemy(1);		// エネミーの再初期化
		InitBullet(1);		// バレットの再初期化
		InitBG(1);			// BGの再初期化
		InitEnemyBullet(1);	// エネミーバレットの再初期化
		//InitEnemyGuage(1);	// エネミーゲージの再初期化
		InitEffect(1);		// エフェクト再初期化
		InitEffect2(1);		// エフェクト２再初期化
		InitBoss(1);		// ボス再初期化
		InitBossBullet(1);	// ボスバレット再初期化
		//InitBossguage(1);
	}
