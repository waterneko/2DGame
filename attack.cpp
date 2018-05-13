//=============================================================================
//
// Attack処理 [Attack.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "attack.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexAttack( int no );
void SetTextureAttack( int no, int cntPattern );
void SetVertexAttack( int no );
void MoveAttack(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureAttack = NULL;		// テクスチャへのポリゴン

ATTACK					attackWk[ATTACK_MAX];			// アタック構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitAttack(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = &attackWk[0];		// アタックのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ATTACK,			// ファイルの名前
			&g_pD3DTextureAttack);			// 読み込むメモリのポインタ
		
	}

	// ライフの初期化処理
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		attack->use = false;										// 未使用
		attack->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				// 座標データを初期化
		attack->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		attack->PatternAnim = 0;									// アニメパターン番号初期化
		attack->CountAnim = 0;										// アニメカウントを初期化
		
		attack->Texture = g_pD3DTextureAttack;						// テクスチャ情報
		MakeVertexAttack(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAttack(void)
{
	if (g_pD3DTextureAttack != NULL)
	{	// テクスチャの開放
		g_pD3DTextureAttack->Release();
		g_pD3DTextureAttack = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAttack(void)
{
	ATTACK *attack = attackWk;				// アタックのポインターを初期化
	
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			attack->CountAnim++;
			if ((attack->CountAnim % TIME_ANIMATION_ATTACK) == 0)
			{
				// パターンの切り替え
				attack->PatternAnim = (attack->PatternAnim + 1) % ANIM_PATTERN_NUM_ATTACK;

				// もし一回パターンの切り替えが終わったら、消えます
				if (attack->PatternAnim >= 9)
				{
					attack->use = false;
					attack->pos.x = -100.0f;
				}

				// テクスチャ座標を設定
				SetTextureAttack(i, attack->PatternAnim);
				
			}

		}

		SetVertexAttack(i);				// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = attackWk;				// アタックのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, attack->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ATTACK, attack->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexAttack( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ATTACK *attack = &attackWk[no];			// アタックのポインターを初期化

	// 頂点座標の設定
	SetVertexAttack( no );

	// rhwの設定
	attack->vertexWk[0].rhw =
	attack->vertexWk[1].rhw =
	attack->vertexWk[2].rhw =
	attack->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	attack->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	attack->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	attack->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	attack->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ATTACK, 0.0f);
	attack->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ATTACK);
	attack->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ATTACK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ATTACK);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureAttack( int no, int cntPattern )
{
	ATTACK *attack = &attackWk[no];			// アタックのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ATTACK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ATTACK;
	
	attack->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	attack->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	attack->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	attack->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexAttack( int no )
{
	ATTACK *attack = &attackWk[no];			// アタックのポインターを初期化

	// 頂点座標の設定
	attack->vertexWk[0].vtx.x = attack->pos.x - TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[0].vtx.y = attack->pos.y - TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[0].vtx.z = 0.0f;

	attack->vertexWk[1].vtx.x = attack->pos.x + TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[1].vtx.y = attack->pos.y - TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[1].vtx.z = 0.0f;

	attack->vertexWk[2].vtx.x = attack->pos.x - TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[2].vtx.y = attack->pos.y + TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[2].vtx.z = 0.0f;

	attack->vertexWk[3].vtx.x = attack->pos.x + TEXTURE_ATTACK_SIZE_X;
	attack->vertexWk[3].vtx.y = attack->pos.y + TEXTURE_ATTACK_SIZE_Y;
	attack->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// スキルの発射設定
//=============================================================================
void SetAttack(D3DXVECTOR3 pos)
{
	ATTACK *attack = &attackWk[0];			// アタックのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false)			// 未使用状態のバレットを見つける
		{
			attack->use = true;				// 使用状態へ変更する
			attack->pos = pos;				// 座標をセット			
			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// アタック取得関数
//=============================================================================
ATTACK *GetAttack(int no)
{
	return(&attackWk[no]);
}

//=============================================================================
// アタック移動関数
//=============================================================================
void MoveAttack(int no)
{
	PLAYER *player = GetPlayer(0);
	ATTACK *attack = &attackWk[no];
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		attack->pos.x -= player->speedX;
	}
}