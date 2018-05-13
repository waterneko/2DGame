//=============================================================================
//
// HP処理 [boss1hp.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "boss1hp.h"
#include "boss1.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBoss1hp( int no );
void SetTextureBoss1hp( int no, int cntPattern );
void SetVertexBoss1hp( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1hp = NULL;		// テクスチャへのポリゴン

BOSS1HP					boss1hpWk[BOSS1HP_MAX];				// HP構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss1hp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = &boss1hpWk[0];		// HPのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BOSS1HP,				// ファイルの名前
			&g_pD3DTextureBoss1hp);				// 読み込むメモリのポインタ
		
	}
	
	BOSS1 *boss1 = GetBoss1(0);		// ボス１の情報ゲット

	// ライフの初期化処理
	for (int i = 0; i < boss1->hp / 500 ; i++, boss1hp++)
	{
		boss1hp->use = false;											// 未使用
		boss1hp->pos = D3DXVECTOR3(700.0f - i* 1.0f, 60.0f, 0.0f);		// 座標データを初期化
		boss1hp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		boss1hp->PatternAnim = 0;										// アニメパターン番号をランダムで初期化
		boss1hp->CountAnim = 0;											// アニメカウントを初期化
		
		boss1hp->Texture = g_pD3DTextureBoss1hp;						// テクスチャ情報
		MakeVertexBoss1hp(i);											// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss1hp(void)
{
	if (g_pD3DTextureBoss1hp != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBoss1hp->Release();
		g_pD3DTextureBoss1hp = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss1hp(void)
{
	BOSS1HP *boss1hp = boss1hpWk;						// HPのポインターを初期化
	BOSS1 *boss1 = GetBoss1(0);							// ボス１の情報ゲット
	
	for (int i = 0; i < boss1->hp / 500; i++, boss1hp++)
	{
		if (boss1hp->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			boss1hp->CountAnim++;
			if ((boss1hp->CountAnim % TIME_ANIMATION_BOSS1HP) == 0)
			{
				// パターンの切り替え
				boss1hp->PatternAnim = (boss1hp->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1HP;

				// テクスチャ座標を設定
				SetTextureBoss1hp(i, boss1hp->PatternAnim);
				}

			}
			
			SetVertexBoss1hp(i);			// 移動後の座標で頂点を設定
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss1hp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = boss1hpWk;				// ライフのポインターを初期化
	BOSS1 *boss1 = GetBoss1(0);					// プレイヤーの情報ゲット

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < boss1->hp / 500; i++, boss1hp++)
	{
		if (boss1hp->use == true)				// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, boss1hp->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1HP, boss1hp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss1hp( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1HP *boss1hp = &boss1hpWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	SetVertexBoss1hp( no );

	// rhwの設定
	boss1hp->vertexWk[0].rhw =
	boss1hp->vertexWk[1].rhw =
	boss1hp->vertexWk[2].rhw =
	boss1hp->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss1hp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1hp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定(図
	boss1hp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1hp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP, 0.0f);
	boss1hp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP);
	boss1hp->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1HP, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss1hp( int no, int cntPattern )
{
	BOSS1HP *boss1hp = &boss1hpWk[no];			// ライフのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1HP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1HP;
	
	boss1hp->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1hp->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1hp->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1hp->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定(框
//=============================================================================
void SetVertexBoss1hp( int no )
{
	BOSS1HP *boss1hp = &boss1hpWk[no];			// HPのポインターを初期化

	// 頂点座標の設定
	boss1hp->vertexWk[0].vtx.x = boss1hp->pos.x - TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[0].vtx.y = boss1hp->pos.y - TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[0].vtx.z = 0.0f;

	boss1hp->vertexWk[1].vtx.x = boss1hp->pos.x + TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[1].vtx.y = boss1hp->pos.y - TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[1].vtx.z = 0.0f;

	boss1hp->vertexWk[2].vtx.x = boss1hp->pos.x - TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[2].vtx.y = boss1hp->pos.y + TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[2].vtx.z = 0.0f;

	boss1hp->vertexWk[3].vtx.x = boss1hp->pos.x + TEXTURE_BOSS1HP_SIZE_X;
	boss1hp->vertexWk[3].vtx.y = boss1hp->pos.y + TEXTURE_BOSS1HP_SIZE_Y;
	boss1hp->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ライフ取得関数
//=============================================================================
BOSS1HP *GetBoss1hp(int no)
{
	return(&boss1hpWk[no]);
}

