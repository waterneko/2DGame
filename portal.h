//=============================================================================
//
// portal処理 [portal.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _PORTAL_H_
#define _PORTAL_H_


// マクロ定義
#define	NUM_PORTAL				(2)			// ポリゴン数

#define TEXTURE_GAME_PORTAL		_T("data/TEXTURE/shoukan_effect.png")	// 画像
#define TEXTURE_PORTAL_SIZE_X	(80)		// テクスチャサイズ
#define TEXTURE_PORTAL_SIZE_Y	(80)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_PORTAL	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PORTAL	(7)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PORTAL			(TEXTURE_PATTERN_DIVIDE_X_PORTAL*TEXTURE_PATTERN_DIVIDE_Y_PORTAL)	// アニメーションパターン数
#define TIME_ANIMATION_PORTAL			(15)	// アニメーションの切り替わるカウント

#define PORTAL_MAX						(1)			// バレットの最大数


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

} PORTAL;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPortal(int type);
void UninitPortal(void);
void UpdatePortal(void);
void DrawPortal(void);
PORTAL *GetPortal(int no);
void MovePortal(int no);

#endif
