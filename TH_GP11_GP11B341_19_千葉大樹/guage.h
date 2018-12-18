//=============================================================================
//
// プレイヤー処理 [GUAGE.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_GUAGE		(2)					// ポリゴン数

#define TEXTURE_GAME_GUAGE	_T("data/TEXTURE/guage00.png")	// 画像
#define TEXTURE_GUAGE_SIZE_X	(100) // テクスチャサイズ
#define TEXTURE_GUAGE_SIZE_Y	(20) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_GUAGE	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_GUAGE	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_GUAGE			(TEXTURE_PATTERN_DIVIDE_X_GUAGE*TEXTURE_PATTERN_DIVIDE_Y_GUAGE)	// アニメーションパターン数
#define TIME_ANIMATION_GUAGE				(4)	// アニメーションの切り替わるカウント

#define GUAGE_MAX					(1) // ゲージの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ゲージ構造体
{
	
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	int				HP;

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// ゲージの半径
	float			BaseAngle;					// ゲージの角度

} GUAGE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGuage(int type);
void UninitGuage(void);
void UpdateGuage(void);
void DrawGuage(void);
GUAGE *GetGuage(int no);


#endif