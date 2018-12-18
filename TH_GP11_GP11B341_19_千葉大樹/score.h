//=============================================================================
//
// スコア処理 [score.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// マクロ定義
#define	TEXTURE_GAME_SCORE		_T("data/TEXTURE/bg002.jpg")		// 読み込むテクスチャファイル名
#define TEXTURE_GAME_SCORE_LOGO	_T("data/TEXTURE/number16x32.png")		// サンプル用画像
#define SCORE_POS_X			(0)					// タイトルの表示位置
#define SCORE_POS_Y			(0)					// タイトルの表示位置
#define SCORE_SIZE_X		(800)				// タイトルの幅
#define SCORE_SIZE_Y		(600)				// タイトルの高さ
#define TEXTURE_SCORE_LOGO_SIZE_X	(20)		// テクスチャサイズ
#define TEXTURE_SCORE_LOGO_SIZE_Y	(64)		// 同上
#define SCORE_LOGO_POS_X			(350)		// ポリゴンの初期位置X
#define SCORE_LOGO_POS_Y			(230)		// 同上
#define SCORE_LOGO_MAX			(99999)			// スコアの最大値
#define SCORE_LOGO_DIGIT			(5)			// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );

#endif
