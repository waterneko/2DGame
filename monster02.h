//=============================================================================
//
// 敵処理 [monster02.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _MONSTER02_H_
#define _MONSTER02_H_


// マクロ定義
#define	NUM_MONSTER02			(2)			// ポリゴン数

#define TEXTURE_GAME_MONSTER02		_T("data/TEXTURE/monster02.png")	// 画像
#define TEXTURE_GAME_MONSTER02DIE	_T("data/TEXTURE/monster02die.png")	// 画像
#define TEXTURE_MONSTER02_SIZE_X	(60)		// テクスチャサイズ
#define TEXTURE_MONSTER02_SIZE_Y	(70)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_MONSTER02	(4)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_MONSTER02	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_MONSTER02			(TEXTURE_PATTERN_DIVIDE_X_MONSTER02*TEXTURE_PATTERN_DIVIDE_Y_MONSTER02)	// アニメーションパターン数
#define TIME_ANIMATION_MONSTER02			(15)	// アニメーションの切り替わるカウント

#define MONSTER02_MAX						(1) // 敵の最大数
#define MONSTER02_SPEED						(1)	// バレットのスピード
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

} MONSTER02;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMonster02(int type);
void UninitMonster02(void);
void UpdateMonster02(void);
void DrawMonster02(void);
MONSTER02 *GetMonster02(int no);
void MoveMonster02(int no);
void SetMonster02die(void);
#endif
