//=============================================================================
//
// バレット処理 [bom.cpp]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "bom.h"
#include "sound.h"
#include "bomguage.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBom(int no);
void SetTextureBom(int no, int cntPattern);
void SetVertexBom(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBom = NULL;		// テクスチャへのポリゴン

BOM						bomWk[BOM_MAX];				// バレット構造体
LPDIRECTSOUNDBUFFER8	bomSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBom(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = &bomWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_GAME_BOM,			// ファイルの名前
			&D3DTextureBom);			// 読み込むメモリのポインタ

		bomSE = LoadSound(BOMB_00);

	}

	//  ボムの初期化処理
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		bom->use = false;									// 未使用（発射されていない弾）
		bom->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);		// 座標データを初期化
		bom->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		bom->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		bom->CountAnim = 0;									// アニメカウントを初期化

		bom->Texture = D3DTextureBom;						// テクスチャ情報
		MakeVertexBom(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBom(void)
{
	if (D3DTextureBom != NULL)
	{	// テクスチャの開放
		D3DTextureBom->Release();
		D3DTextureBom = NULL;
	}

	if (bomSE != NULL)
	{	// テクスチャの開放
		bomSE->Release();
		bomSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBom(void)
{
	BOM *bom = bomWk;				// バレットのポインターを初期化
	BOMGUAGE *bomguage = GetBomGuage(0);
	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == true)			// 使用している状態なら更新する
		{
			// バレットの移動処理
			bom->pos.y -= BOM_SPEED;
			//bomguage->Radius -= 100 / 5;			//ゲージの減少

			// 画面外まで進んだ？
			if (bom->pos.y < -TEXTURE_BOM_SIZE_Y)	// 自分の大きさを考慮して画面外か判定している
			{
				bom->use = false;
				bom->pos.x = -100.0f;
			}

			SetVertexBom(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBom(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = bomWk;				// バレットのポインターを初期化

											// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOM_MAX; i++, bom++)
	{
		if (bom->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			Device->SetTexture(0, bom->Texture);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOM, bom->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBom(int no)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BOM *bom = &bomWk[no];			// バレットのポインターを初期化
										
	SetVertexBom(no);				// 頂点座標の設定

	// rhwの設定
	bom->vertexWk[0].rhw =
	bom->vertexWk[1].rhw =
	bom->vertexWk[2].rhw =
	bom->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bom->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bom->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bom->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bom->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM, 0.0f);
	bom->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM);
	bom->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM);

	bom->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bom->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bom->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bom->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBom(int no, int cntPattern)
{
	BOM *bom = &bomWk[no];			// バレットのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOM;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOM;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOM;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOM;

	bom->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bom->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bom->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bom->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBom(int no)
{
	BOM *bom = &bomWk[no];			// バレットのポインターを初期化

											// 頂点座標の設定
	bom->vertexWk[0].vtx.x = bom->pos.x - TEXTURE_BOM_SIZE_X;
	bom->vertexWk[0].vtx.y = bom->pos.y - TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[0].vtx.z = 0.0f;
	
	bom->vertexWk[1].vtx.x = bom->pos.x + TEXTURE_BOM_SIZE_X;
	bom->vertexWk[1].vtx.y = bom->pos.y - TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[1].vtx.z = 0.0f;
	
	bom->vertexWk[2].vtx.x = bom->pos.x - TEXTURE_BOM_SIZE_X;
	bom->vertexWk[2].vtx.y = bom->pos.y + TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[2].vtx.z = 0.0f;
	
	bom->vertexWk[3].vtx.x = bom->pos.x + TEXTURE_BOM_SIZE_X;
	bom->vertexWk[3].vtx.y = bom->pos.y + TEXTURE_BOM_SIZE_Y;
	bom->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ボムの発射設定
//=============================================================================
void SetBom(D3DXVECTOR3 pos)
{
	BOM *bom = &bomWk[0];			// バレットのポインターを初期化

	for (int i = 0; i < BOM_MAX; i++, bom++)	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	{
		if (bom->use == false)				// 未使用状態のバレットを見つける
		{
			bom->use = true;				// 使用状態へ変更する
			bom->pos = pos;					// 座標をセット

											
			PlaySound(bomSE, E_DS8_FLAG_NONE);	// 発射音再生

			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// ボム取得関数
//=============================================================================
BOM *GetBom(int no)
{
	return(&bomWk[no]);
}

