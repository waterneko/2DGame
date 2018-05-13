//=============================================================================
//
// 背景処理 [bg.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// マクロ定義
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/mori.png")	// サンプル用画像
#define BG00_SIZE_X			(1920)	// テクスチャサイズ
#define BG00_SIZE_Y			(1080)	// 同上
#define BG00_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define BG00_POS_Y			(0)		// 同上
#define BG_MAX				(1)		// 背景の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// BG構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} BG;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBG(int no);
#endif
