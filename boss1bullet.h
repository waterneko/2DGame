//=============================================================================
//
// ボス1の弾処理 [boss1bulletl.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BOSS1BULLET_H_
#define _BOSS1BULLET_


// マクロ定義
#define	NUM_BOSS1BULLET				(2)		// ポリゴン数

#define TEXTURE_GAME_BOSS1BULLET		_T("data/TEXTURE/boss1bullet.png")	// 画像
#define TEXTURE_BOSS1BULLET_SIZE_X	(50)		// テクスチャサイズ
#define TEXTURE_BOSS1BULLET_SIZE_Y	(50)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET	(5)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSS1BULLET			(TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET*TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET)	// アニメーションパターン数
#define TIME_ANIMATION_BOSS1BULLET				(8)	// アニメーションの切り替わるカウント

#define BOSS1BULLET_MAX							(1)	// バレットの最大数
#define BOSS1BULLET_SPEED						(2)	// バレットのスピード

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

} BOSS1BULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss1bullet(int type);
void UninitBoss1bullet(void);
void UpdateBoss1bullet(void);
void DrawBoss1bullet(void);
void SetBoss1bullet(D3DXVECTOR3 pos);
BOSS1BULLET *GetBoss1bullet(int no);
void MoveBoss1bullet(int no);

#endif
