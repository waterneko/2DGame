//=============================================================================
//
// portal処理 [portal.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "portal.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPortal( int no );
void SetTexturePortal( int no, int cntPattern );
void SetVertexPortal( int no );
void MovePortal(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePortal = NULL;		// テクスチャへのポリゴン

PORTAL					portalWk[PORTAL_MAX];			// バレット構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPortal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = &portalWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_PORTAL,				// ファイルの名前
			&g_pD3DTexturePortal);			// 読み込むメモリのポインタ
		
	}

	// バレットの初期化処理
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		portal->use = true;											// 使用
		portal->pos = D3DXVECTOR3(1850.0f + i*1800, 500.0f, 0.0f);	// 座標データを初期化
		portal->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		portal->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		portal->CountAnim = 0;										// アニメカウントを初期化
		
		portal->Texture = g_pD3DTexturePortal;						// テクスチャ情報
		MakeVertexPortal(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPortal(void)
{
	if (g_pD3DTexturePortal != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePortal->Release();
		g_pD3DTexturePortal = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePortal(void)
{
	PORTAL *portal = portalWk;				// バレットのポインターを初期化
	
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			portal->CountAnim++;
			if ((portal->CountAnim % TIME_ANIMATION_PORTAL) == 0)
			{
				// パターンの切り替え
				portal->PatternAnim = (portal->PatternAnim + 1) % ANIM_PATTERN_NUM_PORTAL;
				
				// テクスチャ座標を設定
				SetTexturePortal(i, portal->PatternAnim);
				

			}
			
			SetVertexPortal(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPortal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = portalWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, portal->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PORTAL, portal->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPortal( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PORTAL *portal = &portalWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexPortal( no );

	// rhwの設定
	portal->vertexWk[0].rhw =
	portal->vertexWk[1].rhw =
	portal->vertexWk[2].rhw =
	portal->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	portal->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	portal->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	portal->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	portal->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PORTAL ,0.0f);
	portal->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PORTAL);
	portal->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_PORTAL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PORTAL);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePortal( int no, int cntPattern )
{
	PORTAL *portal = &portalWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PORTAL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PORTAL;
	
	portal->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	portal->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	portal->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	portal->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPortal( int no )
{
	PORTAL *portal = &portalWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	portal->vertexWk[0].vtx.x = portal->pos.x - TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[0].vtx.y = portal->pos.y - TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[0].vtx.z = 0.0f;

	portal->vertexWk[1].vtx.x = portal->pos.x + TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[1].vtx.y = portal->pos.y - TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[1].vtx.z = 0.0f;

	portal->vertexWk[2].vtx.x = portal->pos.x - TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[2].vtx.y = portal->pos.y + TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[2].vtx.z = 0.0f;

	portal->vertexWk[3].vtx.x = portal->pos.x + TEXTURE_PORTAL_SIZE_X;
	portal->vertexWk[3].vtx.y = portal->pos.y + TEXTURE_PORTAL_SIZE_Y;
	portal->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// エネミー取得関数
//=============================================================================
PORTAL *GetPortal(int no)
{
	return(&portalWk[no]);
}
//=============================================================================
// スキルの移動関数
//=============================================================================
void MovePortal(int no)
{
	PLAYER *player = GetPlayer(0);
	PORTAL *portal = &portalWk[0];			// バレットのポインターを初期化
	for (int i = 0; i < PORTAL_MAX;i++,portal++)
	{
		portal->pos.x -= player->speedX;
	}

}