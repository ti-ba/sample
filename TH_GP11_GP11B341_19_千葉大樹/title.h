//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/background_3.jpg")			// 読み込むテクスチャファイル名
#define	TITLE_POS_X			(0)								// タイトルの表示位置
#define	TITLE_POS_Y			(0)								// タイトルの表示位置
#define	TITLE_SIZE_X		(800)							// タイトルの幅
#define	TITLE_SIZE_Y		(600)							// タイトルの高さ

#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/shooting-3.png")		// 読み込むテクスチャファイル名
#define	TITLELOGO_POS_X		(80)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(150)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(100)							// タイトルロゴの高さ

#define	TEXTURE_TITLE2		_T("data/TEXTURE/background_3.jpg")			// 読み込むテクスチャファイル名
#define	TITLE2_POS_X			(0)								// タイトルの表示位置
#define	TITLE2_POS_Y			(0)								// タイトルの表示位置
#define	TITLE2_SIZE_X		(800)							// タイトルの幅
#define	TITLE2_SIZE_Y		(600)							// タイトルの高さ

#define	TEXTURE_PUSH_LOGO	_T("data/TEXTURE/push2.png")		// 読み込むテクスチャファイル名
#define	PUSHLOGO_POS_X		(230)							// タイトルロゴの表示位置
#define	PUSHLOGO_POS_Y		(270)							// タイトルロゴの表示位置
#define	PUSHLOGO_SIZE_X	(200)							// タイトルロゴの幅
#define	PUSHLOGO_SIZE_Y	(200)							// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
