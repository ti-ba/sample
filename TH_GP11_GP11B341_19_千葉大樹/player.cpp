//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "bom.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// テクスチャへのポリゴン

PLAYER					playerWk[PLAYER_MAX];			// プレイヤー構造体

LPDIRECTSOUNDBUFFER8	HitSE;							// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_PLAYER,				// ファイルの名前
			&D3DTexturePlayer);					// 読み込むメモリのポインタ

		HitSE = LoadSound(HIT_00);

	}

	// プレイヤーの初期化処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;									// 使用
		player->pos = D3DXVECTOR3(200.0f+200.0f, 300.0f, 0.0f);	// 座標データを初期化
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
		player->PatternAnim = rand() % ANIM_PATTERN_NUM;	// アニメパターン番号をランダムで初期化
		player->CountAnim = 0;								// アニメカウントを初期化
		player->firecount = 0;
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		player->Radius = D3DXVec2Length(&temp);				// プレイヤーの半径を初期化
		player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// プレイヤーの角度を初期化
		player->Texture = D3DTexturePlayer;					// テクスチャ情報
		MakeVertexPlayer(i);								// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (D3DTexturePlayer != NULL)
	{	// テクスチャの開放
		D3DTexturePlayer->Release();
		D3DTexturePlayer = NULL;
	}

	if (HitSE != NULL)
	{	// テクスチャの開放
		HitSE->Release();
		HitSE = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	D3DXVECTOR3 pos = player->pos;
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// 使用している状態なら更新する
		{
			if (GetKeyboardPress(DIK_DOWN))
			{
				player->pos.y += 8.0f;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				player->pos.y -= 8.0f;
			}

			if (GetKeyboardPress(DIK_RIGHT))
			{
				player->pos.x += 8.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				player->pos.x -= 8.0f;
			}

			// 回転
			if (GetKeyboardPress(DIK_R))
			{
				player->rot.z += 0.1f;
			}

			// 拡大縮小
			if (GetKeyboardPress(DIK_F))
			{
				player->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player->Radius += 1.0f;
			}


			// ゲームパッドで移動処理
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				player->pos.y += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				player->pos.y -= 2.0f;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->pos.x += 2.0f;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				player->pos.x -= 2.0f;
			}

			// 移動後の座標で頂点を設定
			SetVertexPlayer(i);

			// 弾発射
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
			}

			if (GetKeyboardPress(DIK_SPACE))
			{
				player-> firecount++;
				if (player->firecount == 8)
				{
					pos.y -= TEXTURE_PLAYER_SIZE_Y;
					SetBullet(pos);
					player->firecount = 0;
				}
			}
			else if(IsButtonRepeat(0, BUTTON_B))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
				player->firecount = 0;
			}

			if (GetKeyboardTrigger(DIK_V))
			{	
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBom(pos);
			}
			else if (IsButtonRepeat(0, BUTTON_C))
			{
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBom(pos);
			}

			if (GetKeyboardRelease(DIK_SPACE))
			{
				player->firecount = 0;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[0];

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			Device->SetTexture(0, player->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &playerWk[no];

	// 頂点座標の設定
	SetVertexPlayer(no);

	// rhwの設定
	player->vertexWk[0].rhw = 1.0f;
	player->vertexWk[1].rhw = 1.0f;
	player->vertexWk[2].rhw = 1.0f;
	player->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );

	player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];
	
	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	
	player->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	player->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	player->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	player->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// 頂点座標の設定
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

