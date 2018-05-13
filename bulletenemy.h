//=============================================================================
//
// バレット処理 [bulletenemy.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BULLETENEMY_H_
#define _BULLETENEMY_H_


// マクロ定義
#define	NUM_BULLETENEMY				(2)			// ポリゴン数

#define TEXTURE_GAME_BULLETENEMY	_T("data/TEXTURE/promin_pipo004_.png")	// 画像
#define TEXTURE_BULLETENEMY_SIZE_X	(100)								// テクスチャサイズ
#define TEXTURE_BULLETENEMY_SIZE_Y	(100)								// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY	(3)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BULLETENEMY			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// アニメーションパターン数
#define TIME_ANIMATION_BULLETENEMY				(30)	// アニメーションの切り替わるカウント

#define BULLETENEMY_MAX						(ENEMY_MAX * 2) // バレットの最大数

#define BULLETENEMY_SPEED					(5.0f)		// バレットの移動スピード


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

} BULLETENEMY;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBulletenemy(int type);
void UninitBulletenemy(void);
void UpdateBulletenemy(void);
void DrawBulletenemy(void);
void SetBulletenemy(D3DXVECTOR3 pos);
BULLETENEMY *GetBulletenemy(int no);


#endif
