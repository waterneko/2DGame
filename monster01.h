//=============================================================================
//
// 敵処理 [monster01.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _MONSTER01_H_
#define _MONSTER01_H_


// マクロ定義
#define	NUM_MONSTER01			(2)			// ポリゴン数

#define TEXTURE_GAME_MONSTER01		_T("data/TEXTURE/monster01.png")	// 画像
#define TEXTURE_GAME_MONSTER01DIE	_T("data/TEXTURE/monster01die.png")	// 画像
#define TEXTURE_MONSTER01_SIZE_X	(50)		// テクスチャサイズ
#define TEXTURE_MONSTER01_SIZE_Y	(50)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER01	(4)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER01	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_MONSTER01			(TEXTURE_PATTERN_DIVIDE_X_MONSTER01*TEXTURE_PATTERN_DIVIDE_Y_MONSTER01)	// アニメーションパターン数
#define TIME_ANIMATION_MONSTER01			(15)	// アニメーションの切り替わるカウント

#define MONSTER01_MAX						(4) // 敵の最大数

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

} MONSTER01;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMonster01(int type);
void UninitMonster01(void);
void UpdateMonster01(void);
void DrawMonster01(void);
MONSTER01 *GetMonster01(int no);
void MoveMonster01(int no);
void SetMonster01die(void);
#endif
