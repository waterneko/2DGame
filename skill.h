//=============================================================================
//
// スキル処理 [skill.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _SKILL_H_
#define _SKILL_H_


// マクロ定義
#define	NUM_SKILL				(2)			// ポリゴン数

#define TEXTURE_GAME_SKILL		_T("data/TEXTURE/pipo-btleffect161.png")	// 画像
#define TEXTURE_SKILL_SIZE_X	(100)		// テクスチャサイズ
#define TEXTURE_SKILL_SIZE_Y	(100)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_SKILL	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_SKILL	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_SKILL			(TEXTURE_PATTERN_DIVIDE_X_SKILL*TEXTURE_PATTERN_DIVIDE_Y_SKILL)	// アニメーションパターン数
#define TIME_ANIMATION_SKILL			(6)	// アニメーションの切り替わるカウント

#define SKILL_MAX						(1)			// バレットの最大数


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

} SKILL;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSkill(int type);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos);
SKILL *GetSkill(int no);
void MoveSkill(int no);

#endif
