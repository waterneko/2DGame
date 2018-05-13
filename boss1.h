//=============================================================================
//
// 敵処理 [boss1.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _BOSS1_H_
#define _BOSS1_H_


// マクロ定義
#define	NUM_BOSS1			(2)			// ポリゴン数

#define TEXTURE_GAME_BOSS1		_T("data/TEXTURE/dragon.png")	// 画像
#define TEXTURE_BOSS1_SIZE_X	(400)		// テクスチャサイズ
#define TEXTURE_BOSS1_SIZE_Y	(300)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_BOSS1	(4)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BOSS1	(1)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BOSS1			(TEXTURE_PATTERN_DIVIDE_X_BOSS1*TEXTURE_PATTERN_DIVIDE_Y_BOSS1)	// アニメーションパターン数
#define TIME_ANIMATION_BOSS1			(15)	// アニメーションの切り替わるカウント

#define BOSS1_MAX						(1) // 敵の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				hp;							// エネミーのHP
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} BOSS1;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss1(int type);
void UninitBoss1(void);
void UpdateBoss1(void);
void DrawBoss1(void);
BOSS1 *GetBoss1(int no);
void MoveBoss1(int no);

#endif
