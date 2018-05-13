//=============================================================================
//
// life処理 [life.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_


// マクロ定義
#define	NUM_LIFE				(2)			// ポリゴン数

#define TEXTURE_GAME_LIFE		_T("data/TEXTURE/life1.png")	// 画像
#define TEXTURE_LIFE_SIZE_X		(15)		// テクスチャサイズ
#define TEXTURE_LIFE_SIZE_Y		(15)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_LIFE	(3)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_LIFE	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_LIFE			(TEXTURE_PATTERN_DIVIDE_X_LIFE*TEXTURE_PATTERN_DIVIDE_Y_LIFE)	// アニメーションパターン数
#define TIME_ANIMATION_LIFE				(10)	// アニメーションの切り替わるカウント

#define LIFE_MAX						(8)			// ライフの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// ライフ構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} LIFE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLife(int type);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
LIFE *GetLife(int no);


#endif
