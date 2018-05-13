//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleEnter = NULL;	// テクスチャへのポインタ


VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleEnter[NUM_VERTEX];		// 頂点情報格納ワーク

bool					enteruse;								//使用
int						g_nTimerEnter;							// タイマー
bool					g_bEnableTimerEnter;					// タイマー動作ON/OFF
int						g_timeEnter = 30;						// タイマーの時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE,				// ファイルの名前
								&g_pD3DTextureTitle);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE_LOGO,			// ファイルの名前
								&g_pD3DTextureTitleLogo);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE_ENTER,		// ファイルの名前
								&g_pD3DTextureTitleEnter);	// 読み込むメモリー

	enteruse = true;										// 使用
	g_bEnableTimerEnter = true;								// 使用
	g_nTimerEnter = g_timeEnter;


	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if(g_pD3DTextureTitle != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if(g_pD3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DTextureTitleEnter != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleEnter->Release();
		g_pD3DTextureTitleEnter = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_GAME);
	}
	if (g_bEnableTimerEnter)
	{
		g_nTimerEnter--;
		if (g_nTimerEnter > 0)
		{
			enteruse = true;
		}
		if (g_nTimerEnter < 0)
		{
			enteruse = false;
			if (g_nTimerEnter < -g_timeEnter)
			{
				g_nTimerEnter = g_timeEnter;
			}
		}
	}

	// ゲームパッドでで移動処理
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		SetStage(STAGE_GAME);
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_GAME);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));

	if(enteruse == true)
	{ 
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleEnter);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleEnter, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	//=============================================================================

	// 頂点座標の設定
	g_vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	g_vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitle[0].rhw =
	g_vertexWkTitle[1].rhw =
	g_vertexWkTitle[2].rhw =
	g_vertexWkTitle[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//=============================================================================

	// 頂点座標の設定
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleLogo[0].rhw =
	g_vertexWkTitleLogo[1].rhw =
	g_vertexWkTitleLogo[2].rhw =
	g_vertexWkTitleLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//=============================================================================

	// 頂点座標の設定
	g_vertexWkTitleEnter[0].vtx = D3DXVECTOR3(TITLEENTER_POS_X,  TITLEENTER_POS_Y, 0.0f);
	g_vertexWkTitleEnter[1].vtx = D3DXVECTOR3(TITLEENTER_POS_X + TITLEENTER_SIZE_X, TITLEENTER_POS_Y, 0.0f);
	g_vertexWkTitleEnter[2].vtx = D3DXVECTOR3(TITLEENTER_POS_X,  TITLEENTER_POS_Y + TITLEENTER_SIZE_Y, 0.0f);
	g_vertexWkTitleEnter[3].vtx = D3DXVECTOR3(TITLEENTER_POS_X + TITLEENTER_SIZE_X, TITLEENTER_POS_Y + TITLEENTER_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleEnter[0].rhw =
	g_vertexWkTitleEnter[1].rhw =
	g_vertexWkTitleEnter[2].rhw =
	g_vertexWkTitleEnter[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleEnter[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleEnter[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleEnter[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleEnter[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleEnter[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleEnter[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleEnter[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleEnter[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

