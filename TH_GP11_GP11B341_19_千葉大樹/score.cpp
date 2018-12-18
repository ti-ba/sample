//=============================================================================
//
// スコア処理 [score.cpp]
//  GP_11B_341_19 千葉　大樹
//
//=============================================================================
#include "main.h"
#include "score.h"
#include <stdio.h>
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureScore = NULL;			// テクスチャへのポリゴン
LPDIRECT3DTEXTURE9		D3DTextureScoreLogo = NULL;		// テクスチャへのポリゴン

VERTEX_2D				vertexWkScore[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				vertexWkScoreLogo[SCORE_LOGO_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

D3DXVECTOR3				posScore;						// ポリゴンの移動量
int						Score;							// スコア

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,		// デバイスへのポインタ
			TEXTURE_GAME_SCORE,					// ファイルの名前
			&D3DTextureScore);					// 読み込むメモリー


		
		D3DXCreateTextureFromFile(Device,		// デバイスのポインタ
			TEXTURE_GAME_SCORE_LOGO,			// ファイルの名前
			&D3DTextureScoreLogo);				// 読み込むメモリのポインタ
	}

	posScore = D3DXVECTOR3((float)SCORE_LOGO_POS_X, (float)SCORE_LOGO_POS_Y, 0.0f);
	Score = 0;

	// 頂点情報の作成
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if( D3DTextureScore != NULL )
	{	// テクスチャの開放
		D3DTextureScore->Release();
		D3DTextureScore = NULL;
	}

	if (D3DTextureScore != NULL)
	{	// テクスチャの開放
		D3DTextureScoreLogo->Release();
		D3DTextureScoreLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_CUREA);
	}
	// 毎フレーム実行される処理を記述する
	
	SetTextureScore();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	int i;

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture( 0, D3DTextureScore );

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkScore, sizeof(VERTEX_2D));

	// スコア
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		int date = Score;
		int num = date % 10;
		// 頂点フォーマットの設定
		Device->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		Device->SetTexture(0, D3DTextureScoreLogo);

		// ポリゴンの描画
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkScoreLogo[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float habaX = 16.0f;	// 数字の横幅
	
							// 頂点座標の設定
	vertexWkScore[0].vtx = D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y, 0.0f);
	vertexWkScore[1].vtx = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
	vertexWkScore[2].vtx = D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
	vertexWkScore[3].vtx = D3DXVECTOR3(SCORE_POS_X + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkScore[0].rhw =
		vertexWkScore[1].rhw =
		vertexWkScore[2].rhw =
		vertexWkScore[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkScore[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkScore[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkScore[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkScore[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkScore[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkScore[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 桁数分処理する
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		// 頂点座標の設定
		vertexWkScoreLogo[i][0].vtx.x = -habaX * i + posScore.x;
		vertexWkScoreLogo[i][0].vtx.y = posScore.y;
		vertexWkScoreLogo[i][0].vtx.z = 0.0f;
		vertexWkScoreLogo[i][1].vtx.x = -habaX * i + posScore.x + TEXTURE_SCORE_LOGO_SIZE_X;
		vertexWkScoreLogo[i][1].vtx.y = posScore.y;
		vertexWkScoreLogo[i][1].vtx.z = 0.0f;
		vertexWkScoreLogo[i][2].vtx.x = -habaX * i + posScore.x;
		vertexWkScoreLogo[i][2].vtx.y = posScore.y + TEXTURE_SCORE_LOGO_SIZE_Y;
		vertexWkScoreLogo[i][2].vtx.z = 0.0f;
		vertexWkScoreLogo[i][3].vtx.x = -habaX * i + posScore.x + TEXTURE_SCORE_LOGO_SIZE_X;
		vertexWkScoreLogo[i][3].vtx.y = posScore.y + TEXTURE_SCORE_LOGO_SIZE_Y;
		vertexWkScoreLogo[i][3].vtx.z = 0.0f;

		// rhwの設定
		vertexWkScoreLogo[i][0].rhw =
		vertexWkScoreLogo[i][1].rhw =
		vertexWkScoreLogo[i][2].rhw =
		vertexWkScoreLogo[i][3].rhw = 1.0f;

		// 反射光の設定
		vertexWkScoreLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkScoreLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		vertexWkScoreLogo[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		vertexWkScoreLogo[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		vertexWkScoreLogo[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		vertexWkScoreLogo[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureScore(void)
{
	int i;
	int number = Score;
	
	for( i = 0; i < SCORE_LOGO_DIGIT; i++ )
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		vertexWkScoreLogo[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		vertexWkScoreLogo[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		vertexWkScoreLogo[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		vertexWkScoreLogo[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void AddScore( int add )
{
	Score += add;

	if(Score > SCORE_LOGO_MAX )
	{
		Score = SCORE_LOGO_MAX;
	}
	else if( Score < 0 )
	{
		Score = 0;
	}

}
