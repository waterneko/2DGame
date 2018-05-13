//=============================================================================
//
// 星空処理 [hoshizora.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _HOSHIZORA_H_
#define _HOSHIZORA_H_


// マクロ定義
#define	NUM_HOSHIZORA				(2)			// ポリゴン数

#define TEXTURE_GAME_HOSHIZORA		_T("data/TEXTURE/hoshihikari.png")	// 画像
#define TEXTURE_HOSHIZORA_SIZE_X	(800)		// テクスチャサイズ
#define TEXTURE_HOSHIZORA_SIZE_Y	(600)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA	(20)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_HOSHIZORA			(TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA*TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA)	// アニメーションパターン数
#define TIME_ANIMATION_HOSHIZORA			(5)	// アニメーションの切り替わるカウント

#define HOSHIZORA_MAX						(1)			// バレットの最大数


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

} HOSHIZORA;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHoshizora(int type);
void UninitHoshizora(void);
void UpdateHoshizora(void);
void DrawHoshizora(void);
void SetHoshizora(D3DXVECTOR3 pos);
HOSHIZORA *GetHoshizora(int no);

#endif
