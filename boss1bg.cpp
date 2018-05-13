//=============================================================================
//
// 背景処理 [boss1bg.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "boss1bg.h"
#include "input.h"
#include "player.h"
#include "portal.h"
#include "boss1.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBOSS1BG(int no);
void SetVertexBOSS1BG(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBOSS1BG = NULL;		// テクスチャへのポインタ

BOSS1BG					boss1bgWk[BOSS1BG_MAX];				// BG構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBOSS1BG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = &boss1bgWk[0];			// BGのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_GAME_BOSS1BG,							// ファイルの名前
			&g_pD3DTextureBOSS1BG);							// 読み込むメモリー
	}


	// BGの初期化処理
	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		boss1bg->use = true;										// 使用
		boss1bg->pos = D3DXVECTOR3(0.0f + i*1920.0f,0.0f, 0.0f);	// 座標データを初期化
		boss1bg->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// 回転データを初期化
		boss1bg->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		boss1bg->CountAnim = 0;										// アニメカウントを初期化

		boss1bg->Texture = g_pD3DTextureBOSS1BG;					// テクスチャ情報
		MakeVertexBOSS1BG(i);										// 頂点情報の作成

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBOSS1BG(void)
{
	if(g_pD3DTextureBOSS1BG != NULL)
	{// テクスチャの開放
		g_pD3DTextureBOSS1BG->Release();
		g_pD3DTextureBOSS1BG = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBOSS1BG(void)
{
	BOSS1BG *boss1bg = &boss1bgWk[0];			// BGのポインターを初期化
	PLAYER *player = GetPlayer(0);				// ゲットプレイヤー情報

	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		if (boss1bg->use == true)			// 使用している状態なら更新する
		{
			// 毎フレーム実行する処理

			// プレイヤーの制限処理
			if (player->pos.y < 150.0f)
			{
				player->pos.y = 150.0f;
			}

		}
		
		SetVertexBOSS1BG(i);				// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBOSS1BG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = boss1bgWk;				// BGのポインターを初期化
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1BG_MAX; i++, boss1bg++)
	{
		if (boss1bg->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureBOSS1BG);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, boss1bg->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBOSS1BG(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BG *boss1bg = &boss1bgWk[no];			// BGのポインターを初期化

	// 頂点座標の設定
	SetVertexBOSS1BG(no);

	// 頂点座標の設定
	boss1bg->vertexWk[0].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y, 0.0f);
	boss1bg->vertexWk[1].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y, 0.0f);
	boss1bg->vertexWk[2].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f);
	boss1bg->vertexWk[3].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f);

	// rhwの設定
	boss1bg->vertexWk[0].rhw =
	boss1bg->vertexWk[1].rhw =
	boss1bg->vertexWk[2].rhw =
	boss1bg->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss1bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss1bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss1bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss1bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBOSS1BG(int no)
{
	BOSS1BG *boss1bg = &boss1bgWk[no];			// BGのポインターを初期化

	// 頂点座標の設定
	boss1bg->vertexWk[0].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[1].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[2].vtx = D3DXVECTOR3(BOSS1BG_POS_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f) + boss1bg->pos;
	boss1bg->vertexWk[3].vtx = D3DXVECTOR3(BOSS1BG_POS_X + BOSS1BG_SIZE_X, BOSS1BG_POS_Y + BOSS1BG_SIZE_Y, 0.0f) + boss1bg->pos;

}

//=============================================================================
// BG取得関数
//=============================================================================
BOSS1BG *GetBOSS1BG(int no)
{
	return(&boss1bgWk[no]);
}