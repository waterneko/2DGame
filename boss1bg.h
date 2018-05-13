//=============================================================================
//
// 背景処理 [boss1bg.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BOSS1BG_H_
#define _BOSS1BG_H_

// マクロ定義
#define TEXTURE_GAME_BOSS1BG	_T("data/TEXTURE/pipo-battlebg001.jpg")	// サンプル用画像
#define BOSS1BG_SIZE_X			(800)	// テクスチャサイズ
#define BOSS1BG_SIZE_Y			(600)	// 同上
#define BOSS1BG_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define BOSS1BG_POS_Y			(0)		// 同上
#define BOSS1BG_MAX				(1)		// 背景の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// BOSS1BG構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} BOSS1BG;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBOSS1BG(int type);
void UninitBOSS1BG(void);
void UpdateBOSS1BG(void);
void DrawBOSS1BG(void);
BOSS1BG *GetBOSS1BG(int no);
#endif
