//=============================================================================
//
// アイコン処理 [boss1icon.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BOSS1ICON_H_
#define _BOSS1ICON_H_

// マクロ定義
#define TEXTURE_GAME_BOSS1ICON		_T("data/TEXTURE/boss1icon.png")	// サンプル用画像
#define BOSS1ICON_SIZE_X			(100)	// テクスチャサイズ
#define BOSS1ICON_SIZE_Y			(100)	// 同上
#define BOSS1ICON_POS_X				(0)		// ポリゴンの初期位置X(左上)
#define BOSS1ICON_POS_Y				(0)		// 同上
#define BOSS1ICON_MAX				(1)		// 背景の最大数

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

} BOSS1ICON;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss1icon(int type);
void UninitBoss1icon(void);
void UpdateBoss1icon(void);
void DrawBoss1icon(void);
BOSS1ICON *GetBoss1icon(int no);
#endif
