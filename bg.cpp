//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "monster02.h"
#include "enemy.h"
#include "attack.h"
#include "skill.h"
#include "portal.h"
#include "boss1.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBG(int no);
void SetVertexBG(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBG = NULL;		// テクスチャへのポインタ
//VERTEX_2D				g_vertexWkBG[NUM_VERTEX];	// 頂点情報格納ワーク

BG						bgWk[BG_MAX];				// BG構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = &bgWk[0];			// BGのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_GAME_BG00,		// ファイルの名前
			&g_pD3DTextureBG);		// 読み込むメモリー
	}


	// BGの初期化処理
	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		bg->use = true;										// 未使用（発射されていない弾）
		bg->pos = D3DXVECTOR3(0.0f + i*1920.0f,0.0f, 0.0f);	// 座標データを初期化
		bg->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);				// 回転データを初期化
		bg->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		bg->CountAnim = 0;									// アニメカウントを初期化

		bg->Texture = g_pD3DTextureBG;						// テクスチャ情報
		MakeVertexBG(i);									// 頂点情報の作成

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	if(g_pD3DTextureBG != NULL)
	{// テクスチャの開放
		g_pD3DTextureBG->Release();
		g_pD3DTextureBG = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{
	BG *bg = &bgWk[0];					// BGのポインターを初期化
	PLAYER *player = GetPlayer(0);		// ゲットプレイヤー情報
	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		if (bg->use == true)			// 使用している状態なら更新する
		{
			// 毎フレーム実行する処理

			// プレイヤーの制限処理
			if(player->pos.y < 300)
			{
				player->pos.y = 300.0f;
			}

			// スクロール処理
			if (bgWk[0].pos.x > -(BG00_SIZE_X * BG_MAX - SCREEN_WIDTH))
			if (GetPlayer(0)->pos.x + GetPlayer(0)->speedX > SCREEN_CENTER_X)
			{
				GetPlayer(0)->pos.x = SCREEN_CENTER_X;
				if (GetKeyboardPress(DIK_D)|| IsButtonPressed(0, BUTTON_RIGHT))
				{
					if (bgWk[0].pos.x > -(BG00_SIZE_X * BG_MAX - SCREEN_WIDTH))
					{
						bg->pos.x -= GetPlayer(0)->speedX;
						MoveMonster01(0);
						MoveAttack(0);
						MoveSkill(0);
						MovePortal(0);
						MoveMonster01bullet(0);
						MoveMonster02(0);
						MoveEnemy(0);
						//MoveBoss1(0);
					}
					if (GetKeyboardPress(DIK_O))
					{
						//bg->pos.x += GetPlayer(0)->speedX;
					}
				}
			}


		}
		
		SetVertexBG(i);				// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = bgWk;				// BGのポインターを初期化
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG_MAX; i++, bg++)
	{
		if (bg->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureBG);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bg->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBG(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *bg = &bgWk[no];			// BGのポインターを初期化

	// 頂点座標の設定
	SetVertexBG(no);

	// 頂点座標の設定
	bg->vertexWk[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	bg->vertexWk[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	bg->vertexWk[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	bg->vertexWk[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhwの設定
	bg->vertexWk[0].rhw =
	bg->vertexWk[1].rhw =
	bg->vertexWk[2].rhw =
	bg->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBG(int no)
{
	BG *bg = &bgWk[no];			// BGのポインターを初期化

	// 頂点座標の設定
	bg->vertexWk[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f) + bg->pos;
	bg->vertexWk[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + bg->pos;
	bg->vertexWk[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + bg->pos;
	bg->vertexWk[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + bg->pos;

}

//=============================================================================
// BG取得関数
//=============================================================================
BG *GetBG(int no)
{
	return(&bgWk[no]);
}