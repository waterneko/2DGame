//=============================================================================
//
// アイコン処理 [icon.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "icon.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexIcon(int no);
void SetVertexIcon(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureIcon = NULL;		// テクスチャへのポインタ

ICON					iconWk[ICON_MAX];				// アイコン構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitIcon(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = &iconWk[0];			// アイコンのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_GAME_ICON,		// ファイルの名前
			&g_pD3DTextureIcon);	// 読み込むメモリー
	}


	// アイコンの初期化処理
	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		icon->use = true;										// 使用
		icon->pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);	// 座標データを初期化
		icon->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// 回転データを初期化
		icon->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		icon->CountAnim = 0;									// アニメカウントを初期化

		icon->Texture = g_pD3DTextureIcon;						// テクスチャ情報
		MakeVertexIcon(i);										// 頂点情報の作成

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitIcon(void)
{
	if(g_pD3DTextureIcon != NULL)
	{// テクスチャの開放
		g_pD3DTextureIcon->Release();
		g_pD3DTextureIcon = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateIcon(void)
{
	ICON *icon = &iconWk[0];				// アイコンのポインターを初期化
	PLAYER *player = GetPlayer(0);			// ゲットプレイヤー情報
	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		if (icon->use == true)			// 使用している状態なら更新する
		{
			// 毎フレーム実行する処理

			// プレイヤーの制限処理

				
		}
		
		SetVertexIcon(i);				// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = iconWk;				// アイコンのポインターを初期化
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ICON_MAX; i++, icon++)
	{
		if (icon->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureIcon);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, icon->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexIcon(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ICON *icon = &iconWk[no];			// アイコンのポインターを初期化

	// 頂点座標の設定
	SetVertexIcon(no);

	// 頂点座標の設定
	icon->vertexWk[0].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y, 0.0f);
	icon->vertexWk[1].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y, 0.0f);
	icon->vertexWk[2].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f);
	icon->vertexWk[3].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f);

	// rhwの設定
	icon->vertexWk[0].rhw =
	icon->vertexWk[1].rhw =
	icon->vertexWk[2].rhw =
	icon->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	icon->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	icon->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	icon->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	icon->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	icon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	icon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexIcon(int no)
{
	ICON *icon = &iconWk[no];			// アイコンのポインターを初期化

	// 頂点座標の設定
	icon->vertexWk[0].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y, 0.0f) + icon->pos;
	icon->vertexWk[1].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y, 0.0f) + icon->pos;
	icon->vertexWk[2].vtx = D3DXVECTOR3(ICON_POS_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f) + icon->pos;
	icon->vertexWk[3].vtx = D3DXVECTOR3(ICON_POS_X + ICON_SIZE_X, ICON_POS_Y + ICON_SIZE_Y, 0.0f) + icon->pos;

}

