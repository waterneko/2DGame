//=============================================================================
//
// アイコン処理 [icon.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

// マクロ定義
#define TEXTURE_GAME_ICON		_T("data/TEXTURE/chara.png")	// サンプル用画像
#define ICON_SIZE_X			(80)	// テクスチャサイズ
#define ICON_SIZE_Y			(80)	// 同上
#define ICON_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define ICON_POS_Y			(0)		// 同上
#define ICON_MAX				(1)		// 背景の最大数

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

} ICON;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitIcon(int type);
void UninitIcon(void);
void UpdateIcon(void);
void DrawIcon(void);
#endif
