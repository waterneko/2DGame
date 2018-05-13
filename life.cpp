//=============================================================================
//
// ライフ処理 [life.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "life.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLife( int no );
void SetTextureLife( int no, int cntPattern );
void SetVertexLife( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLife = NULL;		// テクスチャへのポリゴン

LIFE					lifeWk[LIFE_MAX];				// ライフ構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLife(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = &lifeWk[0];		// ライフのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_LIFE,				// ファイルの名前
			&g_pD3DTextureLife);			// 読み込むメモリのポインタ
		
	}
	
	PLAYER *player = GetPlayer(0);		//プレイヤーの情報ゲット

	// ライフの初期化処理
	for (int i = 0; i < player->hp; i++, life++)
	{
		life->use = true;										// 使用
		life->pos = D3DXVECTOR3(100.0f + i* 30.0f, 25.0f, 0.0f);// 座標データを初期化
		life->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		life->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		life->CountAnim = 0;									// アニメカウントを初期化
		
		life->Texture = g_pD3DTextureLife;					// テクスチャ情報
		MakeVertexLife(i);									// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	if (g_pD3DTextureLife != NULL)
	{	// テクスチャの開放
		g_pD3DTextureLife->Release();
		g_pD3DTextureLife = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
	LIFE *life = lifeWk;				// ライフのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーの情報ゲット
	
	for (int i = 0; i < player->hp; i++, life++)
	{
		if (life->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			life->CountAnim++;
			if ((life->CountAnim % TIME_ANIMATION_LIFE) == 0)
			{
				// パターンの切り替え
				life->PatternAnim = (life->PatternAnim + 1) % ANIM_PATTERN_NUM_LIFE;

				// テクスチャ座標を設定
				SetTextureLife(i, life->PatternAnim);
				}

			}
			
			SetVertexLife(i);				// 移動後の座標で頂点を設定
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = lifeWk;				// ライフのポインターを初期化
	PLAYER *player = GetPlayer(0);		//プレイヤーの情報ゲット

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < player->hp; i++, life++)
	{
		if (life->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, life->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_LIFE, life->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLife( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LIFE *life = &lifeWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	SetVertexLife( no );

	// rhwの設定
	life->vertexWk[0].rhw =
	life->vertexWk[1].rhw =
	life->vertexWk[2].rhw =
	life->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	life->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	life->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	life->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	life->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_LIFE, 0.0f);
	life->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LIFE);
	life->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_LIFE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_LIFE);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureLife( int no, int cntPattern )
{
	LIFE *life = &lifeWk[no];			// ライフのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_LIFE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_LIFE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_LIFE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_LIFE;
	
	life->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	life->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	life->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	life->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexLife( int no )
{
	LIFE *life = &lifeWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	life->vertexWk[0].vtx.x = life->pos.x - TEXTURE_LIFE_SIZE_X;
	life->vertexWk[0].vtx.y = life->pos.y - TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[0].vtx.z = 0.0f;

	life->vertexWk[1].vtx.x = life->pos.x + TEXTURE_LIFE_SIZE_X;
	life->vertexWk[1].vtx.y = life->pos.y - TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[1].vtx.z = 0.0f;

	life->vertexWk[2].vtx.x = life->pos.x - TEXTURE_LIFE_SIZE_X;
	life->vertexWk[2].vtx.y = life->pos.y + TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[2].vtx.z = 0.0f;

	life->vertexWk[3].vtx.x = life->pos.x + TEXTURE_LIFE_SIZE_X;
	life->vertexWk[3].vtx.y = life->pos.y + TEXTURE_LIFE_SIZE_Y;
	life->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ライフ取得関数
//=============================================================================
LIFE *GetLife(int no)
{
	return(&lifeWk[no]);
}

