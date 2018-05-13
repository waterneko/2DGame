//=============================================================================
//
// スキル処理 [skill.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "skill.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSkill( int no );
void SetTextureSkill( int no, int cntPattern );
void SetVertexSkill( int no );
void MoveSkill(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSkill = NULL;		// テクスチャへのポリゴン

SKILL					skillWk[SKILL_MAX];			// バレット構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkill(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = &skillWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_SKILL,				// ファイルの名前
			&g_pD3DTextureSkill);			// 読み込むメモリのポインタ
		
	}

	// バレットの初期化処理
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		skill->use = false;										// 未使用（発射されていない弾）
		skill->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		skill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		skill->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		skill->CountAnim = 0;									// アニメカウントを初期化
		
		skill->Texture = g_pD3DTextureSkill;					// テクスチャ情報
		MakeVertexSkill(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkill(void)
{
	if (g_pD3DTextureSkill != NULL)
	{	// テクスチャの開放
		g_pD3DTextureSkill->Release();
		g_pD3DTextureSkill = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkill(void)
{
	SKILL *skill = skillWk;				// バレットのポインターを初期化
	
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			skill->CountAnim++;
			if ((skill->CountAnim % TIME_ANIMATION_SKILL) == 0)
			{
				// パターンの切り替え
				skill->PatternAnim = (skill->PatternAnim + 1) % ANIM_PATTERN_NUM_SKILL;
				
				// もし一回パターンの切り替えが終わったら、消えます
				if (skill->PatternAnim >= 9)
				{
					skill->use = false;
					skill->pos.x = -100.0f;
				}
				// テクスチャ座標を設定
				SetTextureSkill(i, skill->PatternAnim);
				

			}
			
			SetVertexSkill(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = skillWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, skill->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SKILL, skill->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSkill( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKILL *skill = &skillWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexSkill( no );

	// rhwの設定
	skill->vertexWk[0].rhw =
	skill->vertexWk[1].rhw =
	skill->vertexWk[2].rhw =
	skill->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	skill->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	skill->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	skill->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	skill->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_SKILL, 0.0f);
	skill->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SKILL);
	skill->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_SKILL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_SKILL);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureSkill( int no, int cntPattern )
{
	SKILL *skill = &skillWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SKILL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SKILL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SKILL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SKILL;
	
	skill->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	skill->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	skill->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	skill->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSkill( int no )
{
	SKILL *skill = &skillWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	skill->vertexWk[0].vtx.x = skill->pos.x - TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[0].vtx.y = skill->pos.y - TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[0].vtx.z = 0.0f;

	skill->vertexWk[1].vtx.x = skill->pos.x + TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[1].vtx.y = skill->pos.y - TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[1].vtx.z = 0.0f;

	skill->vertexWk[2].vtx.x = skill->pos.x - TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[2].vtx.y = skill->pos.y + TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[2].vtx.z = 0.0f;

	skill->vertexWk[3].vtx.x = skill->pos.x + TEXTURE_SKILL_SIZE_X;
	skill->vertexWk[3].vtx.y = skill->pos.y + TEXTURE_SKILL_SIZE_Y;
	skill->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// スキルの発射設定
//=============================================================================
void SetSkill(D3DXVECTOR3 pos)
{
	SKILL *skill = &skillWk[0];			// バレットのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false)			// 未使用状態のバレットを見つける
		{
			skill->use = true;				// 使用状態へ変更する
			skill->pos = pos;				// 座標をセット			
			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
SKILL *GetSkill(int no)
{
	return(&skillWk[no]);
}
//=============================================================================
// スキルの移動関数
//=============================================================================
void MoveSkill(int no)
{
	PLAYER *player = GetPlayer(0);
	SKILL *skill = &skillWk[0];			// バレットのポインターを初期化
	for (int i = 0; i < SKILL_MAX;i++,skill++)
	{
		skill->pos.x -= player->speedX;
	}

}