//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/bg_ZT004.jpg")			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/logo.png")					// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_ENTER	_T("data/TEXTURE/enter.png")				// 読み込むテクスチャファイル名
#define	TITLE_POS_X			(0)								// タイトルの表示位置
#define	TITLE_POS_Y			(0)								// タイトルの表示位置
#define	TITLE_SIZE_X		(800)							// タイトルの幅
#define	TITLE_SIZE_Y		(600)							// タイトルの高さ
#define	TITLELOGO_POS_X		(150)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(100)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(500)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(100)							// タイトルロゴの高さ
#define	TITLEENTER_SIZE_X	(200)							// タイトルロゴの幅
#define	TITLEENTER_SIZE_Y	(40)							// タイトルロゴの高さ
#define	TITLEENTER_POS_X	(300)							// タイトルロゴの表示位置
#define	TITLEENTER_POS_Y	(500)							// タイトルロゴの表示位置

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
