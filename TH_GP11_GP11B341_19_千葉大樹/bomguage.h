//=============================================================================
//
// プレイヤー処理 [bomguage.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _BOMUAGE_H
#define _BOMUAGE_H

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_BOMGUAGE		(2)					// ポリゴン数

#define TEXTURE_GAME_BOMGUAGE	_T("data/TEXTURE/guage00.png")	// 画像
#define TEXTURE_BOMGUAGE_SIZE_X	(200/2) // テクスチャサイズ
#define TEXTURE_BOMGUAGE_SIZE_Y	(50/2) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOMGUAGE	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOMGUAGE	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOMGUAGE			(TEXTURE_PATTERN_DIVIDE_X_BOMGUAGE*TEXTURE_PATTERN_DIVIDE_Y_BOMGUAGE)	// アニメーションパターン数
#define TIME_ANIMATION_BOMGUAGE				(4)	// アニメーションの切り替わるカウント

#define BOMGUAGE_MAX					(1) // ゲージの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ゲージ構造体
{

	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// ゲージの半径
	float			BaseAngle;					// ゲージの角度

} BOMGUAGE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBomGuage(int type);
void UninitBomGuage(void);
void UpdateBomGuage(void);
void DrawBomGuage(void);
BOMGUAGE *GetBomGuage(int no);


#endif