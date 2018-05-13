//=============================================================================
//
// 星空処理 [hoshizora.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "hoshizora.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "boss1.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexHoshizora( int no );
void SetTextureHoshizora( int no, int cntPattern );
void SetVertexHoshizora( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureHoshizora = NULL;		// テクスチャへのポリゴン

HOSHIZORA				hoshizoraWk[HOSHIZORA_MAX];			// 星空構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHoshizora(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = &hoshizoraWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_HOSHIZORA,				// ファイルの名前
			&g_pD3DTextureHoshizora);			// 読み込むメモリのポインタ
		
	}

	// バレットの初期化処理
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		hoshizora->use = false;										// 未使用
		hoshizora->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		hoshizora->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		hoshizora->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		hoshizora->CountAnim = 0;									// アニメカウントを初期化
		
		hoshizora->Texture = g_pD3DTextureHoshizora;				// テクスチャ情報
		MakeVertexHoshizora(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHoshizora(void)
{
	if (g_pD3DTextureHoshizora != NULL)
	{	// テクスチャの開放
		g_pD3DTextureHoshizora->Release();
		g_pD3DTextureHoshizora = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHoshizora(void)
{
	HOSHIZORA *hoshizora = hoshizoraWk;				// バレットのポインターを初期化
	BOSS1 *boss1 = GetBoss1(0);						// ボス１の情報をゲット
	
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			hoshizora->CountAnim++;
			if ((hoshizora->CountAnim % TIME_ANIMATION_HOSHIZORA) == 0)
			{
				// パターンの切り替え
				hoshizora->PatternAnim = (hoshizora->PatternAnim + 1) % ANIM_PATTERN_NUM_HOSHIZORA;
				
				// もし一回パターンの切り替えが終わったら、消えます
				if (hoshizora->PatternAnim >= 19)
				{
					hoshizora->use = false;
					hoshizora->pos.x = -100.0f;
					boss1->use = true;			// ボス１の使用状態を使用に変更
				}
				// テクスチャ座標を設定
				SetTextureHoshizora(i, hoshizora->PatternAnim);
				

			}
			
			SetVertexHoshizora(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHoshizora(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = hoshizoraWk;				// ポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, hoshizora->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HOSHIZORA, hoshizora->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexHoshizora( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexHoshizora( no );

	// rhwの設定
	hoshizora->vertexWk[0].rhw =
	hoshizora->vertexWk[1].rhw =
	hoshizora->vertexWk[2].rhw =
	hoshizora->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	hoshizora->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hoshizora->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	hoshizora->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	hoshizora->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA, 0.0f);
	hoshizora->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA);
	hoshizora->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureHoshizora( int no, int cntPattern )
{
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HOSHIZORA;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOSHIZORA;
	
	hoshizora->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	hoshizora->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	hoshizora->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	hoshizora->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexHoshizora( int no )
{
	HOSHIZORA *hoshizora = &hoshizoraWk[no];			// ポインターを初期化

	// 頂点座標の設定
	hoshizora->vertexWk[0].vtx.x = hoshizora->pos.x - TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[0].vtx.y = hoshizora->pos.y - TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[0].vtx.z = 0.0f;

	hoshizora->vertexWk[1].vtx.x = hoshizora->pos.x + TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[1].vtx.y = hoshizora->pos.y - TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[1].vtx.z = 0.0f;

	hoshizora->vertexWk[2].vtx.x = hoshizora->pos.x - TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[2].vtx.y = hoshizora->pos.y + TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[2].vtx.z = 0.0f;

	hoshizora->vertexWk[3].vtx.x = hoshizora->pos.x + TEXTURE_HOSHIZORA_SIZE_X;
	hoshizora->vertexWk[3].vtx.y = hoshizora->pos.y + TEXTURE_HOSHIZORA_SIZE_Y;
	hoshizora->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// スキルの発射設定
//=============================================================================
void SetHoshizora(D3DXVECTOR3 pos)
{
	HOSHIZORA *hoshizora = &hoshizoraWk[0];			// バレットのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < HOSHIZORA_MAX; i++, hoshizora++)
	{
		if (hoshizora->use == false)			// 未使用状態の星空を見つける
		{
			hoshizora->use = true;				// 使用状態へ変更する
			hoshizora->pos = pos;				// 座標をセット			
			return;								// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
HOSHIZORA *GetHoshizora(int no)
{
	return(&hoshizoraWk[no]);
}
