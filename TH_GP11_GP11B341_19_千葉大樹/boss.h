//=============================================================================
//
// 敵処理 [boss.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_


// マクロ定義
#define	NUM_BOSS				(2)			// ポリゴン数

#define TEXTURE_GAME_BOSS		_T("data/TEXTURE/boss.jpg")	// 画像
#define TEXTURE_BOSS_SIZE_X	(100)		// テクスチャサイズ
#define TEXTURE_BOSS_SIZE_Y	(70)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSS	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSS			(TEXTURE_PATTERN_DIVIDE_X_BOSS*TEXTURE_PATTERN_DIVIDE_Y_BOSS)	// アニメーションパターン数
#define TIME_ANIMATION_BOSS				(5)	// アニメーションの切り替わるカウント

#define BOSS_MAX						(1) // 敵の最大数




//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

	int				bulletTime;					// 弾発射間隔
	int				Startweit;					// 登場時間
	int				fire;
} BOSS;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss(int type);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
BOSS *GetBoss(int no);


#endif

