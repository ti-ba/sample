//=============================================================================
//
// エネミーバレット処理 [enemybullet.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _ENEMYBULLET2_H_
#define _ENEMYBULLET2_H_


// マクロ定義
#define	NUM_ENEMYBULLET2				(2)			// ポリゴン数			

#define TEXTURE_GAME_ENEMYBULLET2		_T("data/TEXTURE/enemybullet02 .png")	// 画像
#define TEXTURE_ENEMYBULLET2_SIZE_X	(30)		// テクスチャサイズ
#define TEXTURE_ENEMYBULLET2_SIZE_Y	(30)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMYBULLET2			(TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET2*TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET2)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMYBULLET2			(4)	// アニメーションの切り替わるカウント

#define ENEMYBULLET2_MAX						(600) // バレットの最大数

#define ENEMYBULLET2_SPEED			(7.0f)		// バレットの移動スピード



//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				Radius;						// 半径
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} ENEMYBULLET2;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyBullet2(int type);
void UninitEnemyBullet2(void);
void UpdateEnemyBullet2(void);
void DrawEnemyBullet2(void);
void SetEnemyBullet2(D3DXVECTOR3 pos);
ENEMYBULLET2 *GetEnemyBullet2(int no);


#endif
