//=============================================================================
//
// GAMEOVER画面処理 [gameover.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "gameover.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGameover(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGameover = NULL;		// テクスチャへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkGameover[NUM_VERTEX];			// 頂点情報格納ワーク
//VERTEX_2D				g_vertexWkResultLogo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_GAMEOVER,				// ファイルの名前
								&g_pD3DTextureGameover);		// 読み込むメモリー

	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//							TEXTURE_RESULT_LOGO,		// ファイルの名前
	//							&g_pD3DTextureResultLogo);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexGameover();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameover(void)
{
	if(g_pD3DTextureGameover != NULL)
	{// テクスチャの開放
		g_pD3DTextureGameover->Release();
		g_pD3DTextureGameover = NULL;
	}

	//if(g_pD3DTextureResultLogo != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureResultLogo->Release();
	//	g_pD3DTextureResultLogo = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameover(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage( STAGE_TITLE );
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureGameover);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkGameover, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureResultLogo);

	//// ポリゴンの描画
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGameover(void)
{	
	// 頂点座標の設定
	g_vertexWkGameover[0].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	g_vertexWkGameover[1].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	g_vertexWkGameover[2].vtx = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	g_vertexWkGameover[3].vtx = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkGameover[0].rhw =
	g_vertexWkGameover[1].rhw =
	g_vertexWkGameover[2].rhw =
	g_vertexWkGameover[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkGameover[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkGameover[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkGameover[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkGameover[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkGameover[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkGameover[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// 頂点座標の設定
	//g_vertexWkResultLogo[0].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y, 0.0f);
	//g_vertexWkResultLogo[1].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y, 0.0f);
	//g_vertexWkResultLogo[2].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);
	//g_vertexWkResultLogo[3].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);

	//// テクスチャのパースペクティブコレクト用
	//g_vertexWkResultLogo[0].rhw =
	//g_vertexWkResultLogo[1].rhw =
	//g_vertexWkResultLogo[2].rhw =
	//g_vertexWkResultLogo[3].rhw = 1.0f;

	//// 反射光の設定
	//g_vertexWkResultLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_vertexWkResultLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// テクスチャ座標の設定
	//g_vertexWkResultLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//g_vertexWkResultLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//g_vertexWkResultLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//g_vertexWkResultLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

