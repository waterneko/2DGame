//=============================================================================
//
// MP処理 [mp.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "mp.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMP( int no );
void SetTextureMP( int no, int cntPattern );
void SetVertexMP( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMP = NULL;		// テクスチャへのポリゴン

MP						mpWk[MP_MAX];				// MP構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMP(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = &mpWk[0];		// MPのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_MP,				// ファイルの名前
			&g_pD3DTextureMP);				// 読み込むメモリのポインタ
		
	}
	
	PLAYER *player = GetPlayer(0);		//プレイヤーの情報ゲット

	// ライフの初期化処理
	for (int i = 0; i < player->mp / 100; i++, mp++)
	{
		mp->use = true;											// 使用
		mp->pos = D3DXVECTOR3(100.0f + i* 30.0f, 55.0f, 0.0f);	// 座標データを初期化
		mp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		mp->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		mp->CountAnim = 0;										// アニメカウントを初期化
		
		mp->Texture = g_pD3DTextureMP;							// テクスチャ情報
		MakeVertexMP(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMP(void)
{
	if (g_pD3DTextureMP != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMP->Release();
		g_pD3DTextureMP = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMP(void)
{
	MP *mp = mpWk;						// MPのポインターを初期化
	PLAYER *player = GetPlayer(0);		// プレイヤーの情報ゲット
	
	for (int i = 0; i < player->mp / 100; i++, mp++)
	{
		if (mp->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			mp->CountAnim++;
			if ((mp->CountAnim % TIME_ANIMATION_MP) == 0)
			{
				// パターンの切り替え
				mp->PatternAnim = (mp->PatternAnim + 1) % ANIM_PATTERN_NUM_MP;

				// テクスチャ座標を設定
				SetTextureMP(i, mp->PatternAnim);
				}

			}
			
			SetVertexMP(i);				// 移動後の座標で頂点を設定
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = mpWk;				// ライフのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーの情報ゲット

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < player->mp / 100; i++, mp++)
	{
		if (mp->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, mp->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MP, mp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMP( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MP *mp = &mpWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	SetVertexMP( no );

	// rhwの設定
	mp->vertexWk[0].rhw =
	mp->vertexWk[1].rhw =
	mp->vertexWk[2].rhw =
	mp->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	mp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	mp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	mp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	mp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MP, 0.0f);
	mp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MP);
	mp->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MP, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MP);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMP( int no, int cntPattern )
{
	MP *mp = &mpWk[no];			// ライフのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MP;
	
	mp->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	mp->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	mp->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	mp->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMP( int no )
{
	MP *mp = &mpWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	mp->vertexWk[0].vtx.x = mp->pos.x - TEXTURE_MP_SIZE_X;
	mp->vertexWk[0].vtx.y = mp->pos.y - TEXTURE_MP_SIZE_Y;
	mp->vertexWk[0].vtx.z = 0.0f;

	mp->vertexWk[1].vtx.x = mp->pos.x + TEXTURE_MP_SIZE_X;
	mp->vertexWk[1].vtx.y = mp->pos.y - TEXTURE_MP_SIZE_Y;
	mp->vertexWk[1].vtx.z = 0.0f;

	mp->vertexWk[2].vtx.x = mp->pos.x - TEXTURE_MP_SIZE_X;
	mp->vertexWk[2].vtx.y = mp->pos.y + TEXTURE_MP_SIZE_Y;
	mp->vertexWk[2].vtx.z = 0.0f;

	mp->vertexWk[3].vtx.x = mp->pos.x + TEXTURE_MP_SIZE_X;
	mp->vertexWk[3].vtx.y = mp->pos.y + TEXTURE_MP_SIZE_Y;
	mp->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ライフ取得関数
//=============================================================================
MP *GetMP(int no)
{
	return(&mpWk[no]);
}

