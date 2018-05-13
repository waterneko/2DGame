//=============================================================================
//
// MP処理 [mp.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _MP_H_
#define _MP_H_


// マクロ定義
#define	NUM_MP				(2)			// ポリゴン数

#define TEXTURE_GAME_MP		_T("data/TEXTURE/mp.png")	// 画像
#define TEXTURE_MP_SIZE_X		(30)		// テクスチャサイズ
#define TEXTURE_MP_SIZE_Y		(30)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_MP	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MP	(6)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_MP			(TEXTURE_PATTERN_DIVIDE_X_MP*TEXTURE_PATTERN_DIVIDE_Y_MP)	// アニメーションパターン数
#define TIME_ANIMATION_MP			(10)	// アニメーションの切り替わるカウント

#define MP_MAX						(99)	// MPの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// MP構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} MP;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMP(int type);
void UninitMP(void);
void UpdateMP(void);
void DrawMP(void);
MP *GetMP(int no);


#endif
