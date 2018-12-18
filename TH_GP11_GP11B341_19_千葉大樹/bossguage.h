//=============================================================================
//
// プレイヤー処理 [BOSSGUAGE.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _BOSSGUAGE_H_
#define _BOSSGUAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_BOSSGUAGE		(2)					// ポリゴン数

#define TEXTURE_GAME_BOSSGUAGE	_T("data/TEXTURE/guage00.png")	// 画像
#define TEXTURE_BOSSGUAGE_SIZE_X	(100) // テクスチャサイズ
#define TEXTURE_BOSSGUAGE_SIZE_Y	(20) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSSGUAGE	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSSGUAGE	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSSGUAGE			(TEXTURE_PATTERN_DIVIDE_X_BOSSGUAGE*TEXTURE_PATTERN_DIVIDE_Y_BOSSGUAGE)	// アニメーションパターン数
#define TIME_ANIMATION_BOSSGUAGE			(4)	// アニメーションの切り替わるカウント

#define BOSSGUAGE_MAX					(1) // ゲージの最大数


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

} BOSSGUAGE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBossguage(int type);
void UninitBossguage(void);
void UpdateBossguage(void);
void DrawBossguage(void);
BOSSGUAGE *GetBossguage(int no);


#endif
