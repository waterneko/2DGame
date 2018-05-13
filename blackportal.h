//=============================================================================
//
// blackportal処理 [blackportal.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BLACKPORTAL_H_
#define _BLACKPORTAL_H_


// マクロ定義
#define	NUM_BLACKPORTAL				(2)			// ポリゴン数

#define TEXTURE_GAME_BLACKPORTAL	_T("data/TEXTURE/pipo-mapeffect015_480.png")	// 画像
#define TEXTURE_BLACKPORTAL_SIZE_X	(80)									// テクスチャサイズ
#define TEXTURE_BLACKPORTAL_SIZE_Y	(80)									// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BLACKPORTAL			(TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL*TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL)	// アニメーションパターン数
#define TIME_ANIMATION_BLACKPORTAL				(15)// アニメーションの切り替わるカウント

#define BLACKPORTAL_MAX							(1)			// バレットの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

} BLACKPORTAL;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBlackportal(int type);
void UninitBlackportal(void);
void UpdateBlackportal(void);
void DrawBlackportal(void);
BLACKPORTAL *GetBlackportal(int no);

#endif
