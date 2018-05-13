//=============================================================================
//
// モンスター１1の弾処理 [monster01bullet.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _MONSTER01BULLET_H_
#define _MONSTER01BULLET_


// マクロ定義
#define	NUM_MONSTER01BULLET				(2)		// ポリゴン数

#define TEXTURE_GAME_MONSTER01BULLET		_T("data/TEXTURE/monster01bullet.png")	// 画像
#define TEXTURE_MONSTER01BULLET_SIZE_X	(30)		// テクスチャサイズ
#define TEXTURE_MONSTER01BULLET_SIZE_Y	(30)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_MONSTER01BULLET			(TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET*TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET)	// アニメーションパターン数
#define TIME_ANIMATION_MONSTER01BULLET				(10)	// アニメーションの切り替わるカウント

#define MONSTER01BULLET_MAX							(5)	// バレットの最大数
#define MONSTER01BULLET_SPEED						(2)		// バレットのスピード

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

} MONSTER01BULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMonster01bullet(int type);
void UninitMonster01bullet(void);
void UpdateMonster01bullet(void);
void DrawMonster01bullet(void);
void SetMonster01bullet(D3DXVECTOR3 pos);
MONSTER01BULLET *GetMonster01bullet(int no);
void MoveMonster01bullet(int no);

#endif
