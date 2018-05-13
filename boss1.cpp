//=============================================================================
//
// 敵処理 [boss1.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "boss1.h"
#include "input.h"
#include "player.h"
#include "boss1bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBoss1( int no );
void SetTextureBoss1( int no, int cntPattern );
void SetVertexBoss1( int no );
void MoveBoss1(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1 = NULL;		// テクスチャへのポリゴン

BOSS1					boss1Wk[BOSS1_MAX];				// ボス１構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss1(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = boss1Wk;					// ボス１のポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BOSS1,				// ファイルの名前
			&g_pD3DTextureBoss1);			// 読み込むメモリのポインタ
	}

	// ボス１の初期化処理
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		boss1->use = false;										// 不使用
		boss1->pos = D3DXVECTOR3(600.0f, 300.0f, 0.0f);			// 座標データを初期化
		boss1->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		boss1->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		boss1->CountAnim = 0;									// アニメカウントを初期化
		boss1->hp = 100000;										// ボス１のHP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS1_SIZE_X, TEXTURE_BOSS1_SIZE_Y);
		boss1->Radius = D3DXVec2Length(&temp);					// ボス１の半径を初期化
		boss1->BaseAngle = atan2f(TEXTURE_BOSS1_SIZE_Y, TEXTURE_BOSS1_SIZE_X);	// ボス１の角度を初期化

		boss1->Texture = g_pD3DTextureBoss1;					// テクスチャ情報
		MakeVertexBoss1(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss1(void)
{
	if (g_pD3DTextureBoss1 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBoss1->Release();
		g_pD3DTextureBoss1 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss1(void)
{
	BOSS1 *boss1 = boss1Wk;				// ボス１のポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		if (boss1->use == true)			// 使用している状態なら更新する
		{
			boss1->CountAnim++;
			if ((boss1->CountAnim % TIME_ANIMATION_BOSS1) == 0)
			{
				// パターンの切り替え
				boss1->PatternAnim = (boss1->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1;

				// テクスチャ座標を設定
				SetTextureBoss1(i, boss1->PatternAnim);			}
			
			// ボス１の弾発射
			if (boss1->pos.x - player->pos.x < 500)
			{
				D3DXVECTOR3 pos = boss1->pos;
				pos.x = boss1->pos.x + 50.0f;
				pos.y = boss1->pos.y - 50.0f;
				SetBoss1bullet(pos);
			}
			//敵の移動
			SetVertexBoss1(i);	// 移動後の座標で頂点を設定

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = boss1Wk;				// ボス１のポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		if (boss1->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, boss1->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1, boss1->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss1( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1 *boss1 = &boss1Wk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexBoss1( no );

	// rhwの設定
	boss1->vertexWk[0].rhw =
	boss1->vertexWk[1].rhw =
	boss1->vertexWk[2].rhw =
	boss1->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss1->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss1->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1, 0.0f);
	boss1->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1);
	boss1->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss1( int no, int cntPattern )
{
	BOSS1 *boss1 = &boss1Wk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1;
	
	boss1->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss1( int no )
{
	BOSS1 *boss1 = &boss1Wk[no];			// ボス１のポインターを初期化
	
	// 頂点座標の設定
	boss1->vertexWk[0].vtx.x = boss1->pos.x - cosf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[0].vtx.y = boss1->pos.y - sinf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[0].vtx.z = 0.0f;

	boss1->vertexWk[1].vtx.x = boss1->pos.x + cosf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[1].vtx.y = boss1->pos.y - sinf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[1].vtx.z = 0.0f;

	boss1->vertexWk[2].vtx.x = boss1->pos.x - cosf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[2].vtx.y = boss1->pos.y + sinf(boss1->BaseAngle - boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[2].vtx.z = 0.0f;

	boss1->vertexWk[3].vtx.x = boss1->pos.x + cosf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[3].vtx.y = boss1->pos.y + sinf(boss1->BaseAngle + boss1->rot.z) * boss1->Radius;
	boss1->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ボス１取得関数
//=============================================================================
BOSS1 *GetBoss1(int no)
{
	return(&boss1Wk[no]);
}

//=============================================================================
// ボス１移動関数
//=============================================================================
void MoveBoss1(int no)
{
	BOSS1 *boss1 = &boss1Wk[no];			// ボス１のポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < BOSS1_MAX; i++, boss1++)
	{
		boss1->pos.x -= player->speedX;
	}

}