//=============================================================================
//
// プレイヤー処理 [ENEMYGUAGE.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _ENEMYGUAGE_H_
#define _ENEMYGUAGE_H_
#define	NUM_ENEMYGUAGE		(2)					// ポリゴン数

// マクロ定義


#define TEXTURE_GAME_ENEMYGUAGE	_T("data/TEXTURE/guage01 .png")	// 画像
#define TEXTURE_ENEMYGUAGE_SIZE_X	(100) // テクスチャサイズ
#define TEXTURE_ENEMYGUAGE_SIZE_Y	(20) // 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMYGUAGE			(TEXTURE_PATTERN_DIVIDE_X_ENEMYGUAGE*TEXTURE_PATTERN_DIVIDE_Y_ENEMYGUAGE)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMYGUAGE			(4)	// アニメーションの切り替わるカウント

#define ENEMYGUAGE_MAX					(5) // エネミーゲージの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ゲージ構造体
{

	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	int				HP=200;						// 体力


	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーゲージの半径
	float			BaseAngle;					// エネミーゲージの角度

} ENEMYGUAGE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyGuage(int type);
void UninitEnemyGuage(void);
void UpdateEnemyGuage(void);
void DrawEnemyGuage(void);
ENEMYGUAGE *GetEnemyGuage(int no);


#endif