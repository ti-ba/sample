//=============================================================================
//
// 敵処理 [boss.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "boss.h"
#include "input.h"
#include "bossbullet.h"
#include "bossguage.h"
#include "sound.h"
#include "player.h"
#include "bg.h"
#include "guage.h"
#include "bullet.h"
#include "bom.h"
#include "effect2.h"
#include "score.h"
#include "nakami.h"
#include "bomguage.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakevertexBoss(int no);
void SetTextureBoss(int no, int cntPattern);
void SetVertexBoss(int no);

extern void CheckHit(void);
extern bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBoss = NULL;		// テクスチャへのポリゴン

BOSS					bossWk[BOSS_MAX];			// エネミー構造体
LPDIRECTSOUNDBUFFER8	bossSE;						// SE用バッファ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = bossWk;				// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_BOSS,				// ファイルの名前
			&D3DTextureBoss);				// 読み込むメモリのポインタ
		bossSE = LoadSound(HIT_00);
	}

	// ボスの初期化処理
	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		boss->use = false;										// 使用
		boss->pos = D3DXVECTOR3(300.0f, 70.0f, 0.0f);			// 座標データを初期化
		boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		boss->bulletTime = 0;									//弾発射時間の初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y);
		boss->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		boss->BaseAngle = atan2f(TEXTURE_BOSS_SIZE_Y, TEXTURE_BOSS_SIZE_X);	// エネミーの角度を初期化

		boss->Texture = D3DTextureBoss;							// テクスチャ情報
		MakevertexBoss(i);										// 頂点情報の作成

	}


	return S_OK;
}

////=============================================================================
//// 終了処理
////=============================================================================
//void UninitBoss(void)
//{
//
//
//
//	 //ボスの終了処理
//	UninitBoss();
//
//	//UninitBossguage();
//
//
//
//	//ボスの弾終了処理
//	UninitBossBullet();
//
//
//
//
//}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss(void)
{
	BOSS *boss = bossWk;				// エネミーのポインターを初期化
	D3DXVECTOR3 pos = boss->pos;



	// ボスのゲージ更新処理
	UpdateBossguage();
	
	// ボスの更新処理
	UpdateBoss(); 




	// ボスの弾更新処理
	UpdateBossBullet();



	//当たり判定
	//CheckHit_Boss();


	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == false)			// 使用している状態なら更新する
		{
			boss->fire++;
			if (boss->fire == 40)
				{
					pos.y -= TEXTURE_BOSS_SIZE_Y;
					SetBossBullet(pos);
					boss->fire = 0;
				}
			
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = bossWk;				// エネミーのポインターを初期化




	// ボスの描画処理
	DrawBoss();


	DrawBossguage();



	//ボスの弾
	DrawBossBullet();


	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, boss->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS, boss->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakevertexBoss(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexBoss(no);

	// rhwの設定
	boss->vertexWk[0].rhw =


	boss->vertexWk[1].rhw =
	boss->vertexWk[2].rhw =
	boss->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);

	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss(int no, int cntPattern)
{
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS;

	boss->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	boss->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	boss->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	boss->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss(int no)
{
	BOSS *boss = &bossWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	boss->vertexWk[0].vtx.x = boss->pos.x - cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[0].vtx.z = 0.0f;

	boss->vertexWk[1].vtx.x = boss->pos.x + cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.y = boss->pos.y - sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.z = 0.0f;

	boss->vertexWk[2].vtx.x = boss->pos.x - cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.y = boss->pos.y + sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.z = 0.0f;

	boss->vertexWk[3].vtx.x = boss->pos.x + cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.y = boss->pos.y + sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// エネミー取得関数
//=============================================================================
BOSS *GetBoss(int no)
{
	return(&bossWk[no]);
}


