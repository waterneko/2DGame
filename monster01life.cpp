//=============================================================================
//
// ライフ処理 [monster01life.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "monster01.h"
#include "monster01life.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMonster01life( int no );
void SetTextureMonster01life( int no, int cntPattern );
void SetVertexMonster01life( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01life = NULL;				// テクスチャへのポリゴン

MONSTER01LIFE			monster01lifeWk[MONSTER01LIFE_MAX];				// ライフ構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMonster01life(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = &monster01lifeWk[0];		// ライフのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスのポインタ
			TEXTURE_GAME_MONSTER01LIFE,				// ファイルの名前
			&g_pD3DTextureMonster01life);			// 読み込むメモリのポインタ
		
	}
	

	// ライフの初期化処理
	for (int i = 0; i < MONSTER01LIFE_MAX; i++, monster01life++)
	{
		monster01life->use = true;										// 未使用（発射されていない弾）
		monster01life->pos = D3DXVECTOR3(25.0f + i* 30.0f, 25.0f, 0.0f);// 座標データを初期化
		monster01life->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		monster01life->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		monster01life->CountAnim = 0;									// アニメカウントを初期化
		
		monster01life->Texture = g_pD3DTextureMonster01life;			// テクスチャ情報
		MakeVertexMonster01life(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMonster01life(void)
{
	if (g_pD3DTextureMonster01life != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster01life->Release();
		g_pD3DTextureMonster01life = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonster01life(void)
{
	MONSTER01LIFE *monster01life = monster01lifeWk;				// ライフのポインターを初期化
	MONSTER01 *monster01 = GetMonster01(0);						// モンスター１の情報ゲット
	
	for (int i = 0; i < monster01->hp; i++, monster01life++)
	{
		if (monster01life->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			monster01life->CountAnim++;
			if ((monster01->CountAnim % TIME_ANIMATION_MONSTER01LIFE) == 0)
			{
				// パターンの切り替え
				monster01life->PatternAnim = (monster01life->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01LIFE;

				// テクスチャ座標を設定
				SetTextureMonster01life(i, monster01life->PatternAnim);
				}

			}
			
			SetVertexMonster01life(i);				// 移動後の座標で頂点を設定
		}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMonster01life(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = monster01lifeWk;				// ライフのポインターを初期化
	MONSTER01 *monster01 = GetMonster01(0);						// モンスター１の情報ゲット
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < monster01->hp; i++, monster01life++)
	{
		if (monster01life->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, monster01life->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01LIFE, monster01life->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMonster01life( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	SetVertexMonster01life( no );

	// rhwの設定
	monster01life->vertexWk[0].rhw =
	monster01life->vertexWk[1].rhw =
	monster01life->vertexWk[2].rhw =
	monster01life->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	monster01life->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01life->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	monster01life->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01life->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE, 0.0f);
	monster01life->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE);
	monster01life->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMonster01life( int no, int cntPattern )
{
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ライフのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01LIFE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01LIFE;
	
	monster01life->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01life->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01life->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01life->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMonster01life( int no )
{
	MONSTER01LIFE *monster01life = &monster01lifeWk[no];			// ライフのポインターを初期化

	// 頂点座標の設定
	monster01life->vertexWk[0].vtx.x = monster01life->pos.x - TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[0].vtx.y = monster01life->pos.y - TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[0].vtx.z = 0.0f;

	monster01life->vertexWk[1].vtx.x = monster01life->pos.x + TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[1].vtx.y = monster01life->pos.y - TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[1].vtx.z = 0.0f;

	monster01life->vertexWk[2].vtx.x = monster01life->pos.x - TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[2].vtx.y = monster01life->pos.y + TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[2].vtx.z = 0.0f;

	monster01life->vertexWk[3].vtx.x = monster01life->pos.x + TEXTURE_MONSTER01LIFE_SIZE_X;
	monster01life->vertexWk[3].vtx.y = monster01life->pos.y + TEXTURE_MONSTER01LIFE_SIZE_Y;
	monster01life->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ライフ取得関数
//=============================================================================
MONSTER01LIFE *GetMonster01life(int no)
{
	return(&monster01lifeWk[no]);
}

