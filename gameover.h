//=============================================================================
//
// GAMEOVER画面処理 [gameover.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_GAMEOVER		_T("data/TEXTURE/GameOver.png")			// 読み込むテクスチャファイル名
//#define	TEXTURE_RESULT_LOGO	_T("data/TEXTURE/result_logo.png")		// 読み込むテクスチャファイル名
#define	GAMEOVER_POS_X			(0)							// タイトルの表示位置
#define	GAMEOVER_POS_Y			(0)							// タイトルの表示位置
#define	GAMEOVER_SIZE_X			(800)						// タイトルの幅
#define	GAMEOVER_SIZE_Y			(600)						// タイトルの高さ
//#define	RESULTLOGO_POS_X		(160)						// タイトルロゴの表示位置
//#define	RESULTLOGO_POS_Y		(200)						// タイトルロゴの表示位置
//#define	RESULTLOGO_SIZE_X		(480)						// タイトルロゴの幅
//#define	RESULTLOGO_SIZE_Y		(80)						// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGameover(void);
void UninitGameover(void);
void UpdateGameover(void);
void DrawGameover(void);

#endif
