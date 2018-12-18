//=============================================================================
//
// タイトル画面処理 [tyutogeme.h]
// Author : GP_11B_341_19 千葉　大樹
//
//=============================================================================
#ifndef _TYUTOGAME_H_
#define _TYUTOGAME_H_
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TYUTOBG		_T("data/TEXTURE/background_3.jpg")			// 読み込むテクスチャファイル名
#define TYUTOBG_POS_X			(0)								// 背景の表示位置
#define TYUTOBG_POS_Y			(0)								// 背景の表示位置
#define TYUTOBG_SIZE_X		(800)								// 背景の幅
#define TYUTOBG_SIZE_Y		(600)								// 背景の高さ

#define	TEXTURE_TYUTOBG2		_T("data/TEXTURE/background_3.jpg")		// 読み込むテクスチャファイル名
#define	TYUTOBG2_POS_X			(0)								// 背景の表示位置
#define	TYUTOBG2_POS_Y			(0)								// 背景の表示位置
#define	TYUTOBG2_SIZE_X		(800)								// 背景の幅
#define	TYUTOBG2_SIZE_Y		(600)								// 背景の高さ

#define	TEXTURE_DESCRIPTION_LOGO	_T("data/TEXTURE/Description2.png")	// 読み込むテクスチャファイル名
#define	DESCRIPTIONLOGO_POS_X	(50)							// タイトルロゴの表示位置
#define	DESCRIPTIONLOGO_POS_Y	(350)							// タイトルロゴの表示位置
#define	DESCRIPTIONLOGO_SIZE_X	(150)						// タイトルロゴの幅
#define	DESCRIPTIONLOGO_SIZE_Y	(100)						// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTyutoGame(HWND hWnd, BOOL bWindow);
void UninitTyutoGame(void);
void UpdateTyutoGame(void);
void DrawTyutoGame(void);

LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス取得関数




#endif
