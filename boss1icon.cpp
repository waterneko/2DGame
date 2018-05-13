//=============================================================================
//
// アイコン処理 [boss1icon.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "boss1icon.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBoss1icon(int no);
void SetVertexBoss1icon(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1icon = NULL;	// テクスチャへのポインタ

BOSS1ICON				boss1iconWk[BOSS1ICON_MAX];		// アイコン構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss1icon(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = &boss1iconWk[0];			// アイコンのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_GAME_BOSS1ICON,		// ファイルの名前
			&g_pD3DTextureBoss1icon);	// 読み込むメモリー
	}


	// アイコンの初期化処理
	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		boss1icon->use = false;										// 未使用
		boss1icon->pos = D3DXVECTOR3(700.0f,0.0f, 0.0f);			// 座標データを初期化
		boss1icon->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// 回転データを初期化
		boss1icon->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		boss1icon->CountAnim = 0;									// アニメカウントを初期化

		boss1icon->Texture = g_pD3DTextureBoss1icon;				// テクスチャ情報
		MakeVertexBoss1icon(i);										// 頂点情報の作成

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss1icon(void)
{
	if(g_pD3DTextureBoss1icon != NULL)
	{// テクスチャの開放
		g_pD3DTextureBoss1icon->Release();
		g_pD3DTextureBoss1icon = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss1icon(void)
{
	BOSS1ICON *boss1icon = &boss1iconWk[0];				// アイコンのポインターを初期化
	PLAYER *player = GetPlayer(0);						// ゲットプレイヤー情報
	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		if (boss1icon->use == true)			// 使用している状態なら更新する
		{
			// 毎フレーム実行する処理

			// プレイヤーの制限処理

				
		}
		
		SetVertexBoss1icon(i);				// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss1icon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = boss1iconWk;				// アイコンのポインターを初期化
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1ICON_MAX; i++, boss1icon++)
	{
		if (boss1icon->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureBoss1icon);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, boss1icon->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss1icon(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1ICON *boss1icon = &boss1iconWk[no];			// アイコンのポインターを初期化

	// 頂点座標の設定
	SetVertexBoss1icon(no);

	// 頂点座標の設定
	boss1icon->vertexWk[0].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y, 0.0f);
	boss1icon->vertexWk[1].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y, 0.0f);
	boss1icon->vertexWk[2].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f);
	boss1icon->vertexWk[3].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f);

	// rhwの設定
	boss1icon->vertexWk[0].rhw =
	boss1icon->vertexWk[1].rhw =
	boss1icon->vertexWk[2].rhw =
	boss1icon->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss1icon->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1icon->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss1icon->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1icon->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss1icon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss1icon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss1icon(int no)
{
	BOSS1ICON *boss1icon = &boss1iconWk[no];			// アイコンのポインターを初期化

	// 頂点座標の設定
	boss1icon->vertexWk[0].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[1].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[2].vtx = D3DXVECTOR3(BOSS1ICON_POS_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f) + boss1icon->pos;
	boss1icon->vertexWk[3].vtx = D3DXVECTOR3(BOSS1ICON_POS_X + BOSS1ICON_SIZE_X, BOSS1ICON_POS_Y + BOSS1ICON_SIZE_Y, 0.0f) + boss1icon->pos;

}

//=============================================================================
// 取得関数
//=============================================================================
BOSS1ICON *GetBoss1icon(int no)
{
	return(&boss1iconWk[no]);
}
