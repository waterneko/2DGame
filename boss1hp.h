//=============================================================================
//
// HP処理 [boss1hp.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BOSS1HP_H_
#define _BOSS1HP_H_


// マクロ定義
#define	NUM_BOSS1HP				(2)			// ポリゴン数

#define TEXTURE_GAME_BOSS1HP		_T("data/TEXTURE/bosshp.png")	// 画像
#define TEXTURE_BOSS1HP_SIZE_X		(1)		// テクスチャサイズ
#define TEXTURE_BOSS1HP_SIZE_Y		(15)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1HP	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSS1HP			(TEXTURE_PATTERN_DIVIDE_X_BOSS1HP*TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP)	// アニメーションパターン数
#define TIME_ANIMATION_BOSS1HP				(10)	// アニメーションの切り替わるカウント

#define BOSS1HP_MAX							(200)	// HPの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// HP構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} BOSS1HP;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss1hp(int type);
void UninitBoss1hp(void);
void UpdateBoss1hp(void);
void DrawBoss1hp(void);
BOSS1HP *GetBoss1hp(int no);


#endif
