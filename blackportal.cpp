//=============================================================================
//
// blackportal処理 [blackportal.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "blackportal.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBlackportal( int no );
void SetTextureBlackportal( int no, int cntPattern );
void SetVertexBlackportal( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBlackportal = NULL;		// テクスチャへのポリゴン

BLACKPORTAL				blackportalWk[BLACKPORTAL_MAX];			// 暗闇ポータル構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBlackportal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = &blackportalWk[0];		// ポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスのポインタ
			TEXTURE_GAME_BLACKPORTAL,				// ファイルの名前
			&g_pD3DTextureBlackportal);				// 読み込むメモリのポインタ
		
	}

	// バレットの初期化処理
	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		blackportal->use = false;										// 未使用
		blackportal->pos = D3DXVECTOR3(400.0f, 450.0f, 0.0f);			// 座標データを初期化
		blackportal->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		blackportal->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		blackportal->CountAnim = 0;										// アニメカウントを初期化
		
		blackportal->Texture = g_pD3DTextureBlackportal;				// テクスチャ情報
		MakeVertexBlackportal(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlackportal(void)
{
	if (g_pD3DTextureBlackportal != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBlackportal->Release();
		g_pD3DTextureBlackportal = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlackportal(void)
{
	BLACKPORTAL *blackportal = blackportalWk;				// バレットのポインターを初期化
	
	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		if (blackportal->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			blackportal->CountAnim++;
			if ((blackportal->CountAnim % TIME_ANIMATION_BLACKPORTAL) == 0)
			{
				// パターンの切り替え
				blackportal->PatternAnim = (blackportal->PatternAnim + 1) % ANIM_PATTERN_NUM_BLACKPORTAL;
				
				// テクスチャ座標を設定
				SetTextureBlackportal(i, blackportal->PatternAnim);
				

			}
			
			SetVertexBlackportal(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlackportal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = blackportalWk;				// ポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BLACKPORTAL_MAX; i++, blackportal++)
	{
		if (blackportal->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, blackportal->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BLACKPORTAL, blackportal->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBlackportal( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BLACKPORTAL *blackportal = &blackportalWk[no];			// ポインターを初期化

	// 頂点座標の設定
	SetVertexBlackportal( no );

	// rhwの設定
	blackportal->vertexWk[0].rhw =
	blackportal->vertexWk[1].rhw =
	blackportal->vertexWk[2].rhw =
	blackportal->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	blackportal->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	blackportal->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	blackportal->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	blackportal->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL, 0.0f);
	blackportal->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL);
	blackportal->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBlackportal( int no, int cntPattern )
{
	BLACKPORTAL *blackportal = &blackportalWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BLACKPORTAL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BLACKPORTAL;
	
	blackportal->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	blackportal->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	blackportal->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	blackportal->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBlackportal( int no )
{
	BLACKPORTAL *blackportal = &blackportalWk[no];			// ポインターを初期化

	// 頂点座標の設定
	blackportal->vertexWk[0].vtx.x = blackportal->pos.x - TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[0].vtx.y = blackportal->pos.y - TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[0].vtx.z = 0.0f;

	blackportal->vertexWk[1].vtx.x = blackportal->pos.x + TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[1].vtx.y = blackportal->pos.y - TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[1].vtx.z = 0.0f;

	blackportal->vertexWk[2].vtx.x = blackportal->pos.x - TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[2].vtx.y = blackportal->pos.y + TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[2].vtx.z = 0.0f;

	blackportal->vertexWk[3].vtx.x = blackportal->pos.x + TEXTURE_BLACKPORTAL_SIZE_X;
	blackportal->vertexWk[3].vtx.y = blackportal->pos.y + TEXTURE_BLACKPORTAL_SIZE_Y;
	blackportal->vertexWk[3].vtx.z = 0.0f;
}



//=============================================================================
// エネミー取得関数
//=============================================================================
BLACKPORTAL *GetBlackportal(int no)
{
	return(&blackportalWk[no]);
}
