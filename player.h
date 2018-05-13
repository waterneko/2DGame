//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"


// マクロ定義
#define	NUM_PLAYER		(2)					// ポリゴン数

#define TEXTURE_READY_PLAYER	_T("data/TEXTURE/chara02_01idle1.png")	// 画像
#define TEXTURE_STABBING_PLAYER	_T("data/TEXTURE/chara02_08swinging1.png")
#define TEXTURE_RUN_PLAYER		_T("data/TEXTURE/chara02_00run.png")
#define TEXTURE_CHARGE_PLAYER	_T("data/TEXTURE/chara02_10skill.png")

//#define TEXTURE_PLAYER_SIZE_X	(60) // テクスチャサイズ
//#define TEXTURE_PLAYER_SIZE_Y	(80) // 同上

#define TEXTURE_PLAYER_SIZE_X	(60) // テクスチャサイズ
#define TEXTURE_PLAYER_SIZE_Y	(60) // 同上

#define TEXTURE_PATTERN_DIVIDE_X	(4)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(8)	// アニメーションの切り替わるカウント

#define PLAYER_MAX					(1) // プレイヤーの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				hp;							// プレイヤーのhp
	int				mp;							// プレイヤーのmp
	float			speedX;						// プレイヤーのスピード
	float			speedY;						// プレイヤーのスピード
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// プレイヤーの半径
	float			BaseAngle;					// プレイヤーの角度

} PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);


#endif
