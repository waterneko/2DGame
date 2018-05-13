//=============================================================================
//
// attack処理 [attack.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _ATTACK_H_
#define _ATTACK_H_


// マクロ定義
#define	NUM_ATTACK				(2)			// ポリゴン数

#define TEXTURE_GAME_ATTACK		_T("data/TEXTURE/pipo-btleffect159.png")	// 画像
#define TEXTURE_ATTACK_SIZE_X		(50)		// テクスチャサイズ
#define TEXTURE_ATTACK_SIZE_Y		(50)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ATTACK	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ATTACK	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ATTACK			(TEXTURE_PATTERN_DIVIDE_X_ATTACK*TEXTURE_PATTERN_DIVIDE_Y_ATTACK)	// アニメーションパターン数
#define TIME_ANIMATION_ATTACK			(8)	// アニメーションの切り替わるカウント

#define ATTACK_MAX						(1)	// アタックの最大数


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

} ATTACK;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitAttack(int type);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);
ATTACK *GetAttack(int no);
void SetAttack(D3DXVECTOR3 pos);
void MoveAttack(int no);

#endif
