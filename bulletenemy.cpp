//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bulletenemy.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBulletenemy( int no );
void SetTextureBulletenemy( int no, int cntPattern );
void SetVertexBulletenemy( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBulletenemy = NULL;		// テクスチャへのポリゴン

BULLETENEMY					bulletenemyWk[BULLETENEMY_MAX];			// バレット構造体

LPDIRECTSOUNDBUFFER8	g_eSE;						// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBulletenemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = &bulletenemyWk[0];		// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_GAME_BULLETENEMY,			// ファイルの名前
			&g_pD3DTextureBulletenemy);			// 読み込むメモリのポインタ
		
		g_eSE = LoadSound(SE_00);

	}

	// バレットの初期化処理
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		bulletenemy->use = false;										// 未使用（発射されていない弾）
		bulletenemy->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		bulletenemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		bulletenemy->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		bulletenemy->CountAnim = 0;										// アニメカウントを初期化
		
		bulletenemy->Texture = g_pD3DTextureBulletenemy;				// テクスチャ情報
		MakeVertexBulletenemy(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBulletenemy(void)
{
	if (g_pD3DTextureBulletenemy != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBulletenemy->Release();
		g_pD3DTextureBulletenemy = NULL;
	}

	if (g_eSE != NULL)
	{	// テクスチャの開放
		g_eSE->Release();
		g_eSE = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBulletenemy(void)
{
	BULLETENEMY *bulletenemy = bulletenemyWk;				// バレットのポインターを初期化
	ENEMY *enemy = GetEnemy(0);								// エネミーのポインターを初期化
	enemy = GetEnemy(0);
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
			if (bulletenemy->use == true)			// 使用している状態なら更新する
			{
				bulletenemy->CountAnim++;
				if ((bulletenemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
				{
					// パターンの切り替え
					bulletenemy->PatternAnim = (bulletenemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

					// テクスチャ座標を設定
					SetTextureBulletenemy(i, bulletenemy->PatternAnim);
				}

				// バレットの移動処理
				bulletenemy->pos.x -= BULLETENEMY_SPEED;
			

				// 画面外まで進んだ？
				if(bulletenemy->pos.x < 0)	// 画面外判定
				{
				bulletenemy->use = false;
				bulletenemy->pos.x = enemy->pos.x;
				}
			
				SetVertexBulletenemy(i);				// 移動後の座標で頂点を設定
			}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBulletenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = bulletenemyWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bulletenemy->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLETENEMY, bulletenemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBulletenemy( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexBulletenemy( no );

	// rhwの設定
	bulletenemy->vertexWk[0].rhw =
	bulletenemy->vertexWk[1].rhw =
	bulletenemy->vertexWk[2].rhw =
	bulletenemy->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bulletenemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletenemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bulletenemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bulletenemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY, 0.0f);
	bulletenemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY);
	bulletenemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY);

	//bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBulletenemy( int no, int cntPattern )
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLETENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLETENEMY;
	
	bulletenemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bulletenemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bulletenemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bulletenemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

	//bulletenemy->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	//bulletenemy->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	//bulletenemy->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	//bulletenemy->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBulletenemy( int no )
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	bulletenemy->vertexWk[0].vtx.x = bulletenemy->pos.x - TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[0].vtx.y = bulletenemy->pos.y - TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[0].vtx.z = 0.0f;

	bulletenemy->vertexWk[1].vtx.x = bulletenemy->pos.x + TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[1].vtx.y = bulletenemy->pos.y - TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[1].vtx.z = 0.0f;

	bulletenemy->vertexWk[2].vtx.x = bulletenemy->pos.x - TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[2].vtx.y = bulletenemy->pos.y + TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[2].vtx.z = 0.0f;

	bulletenemy->vertexWk[3].vtx.x = bulletenemy->pos.x + TEXTURE_BULLETENEMY_SIZE_X;
	bulletenemy->vertexWk[3].vtx.y = bulletenemy->pos.y + TEXTURE_BULLETENEMY_SIZE_Y;
	bulletenemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBulletenemy(D3DXVECTOR3 pos)
{
	BULLETENEMY *bulletenemy = &bulletenemyWk[0];			// バレットのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == false)			// 未使用状態のバレットを見つける
		{
			bulletenemy->use = true;				// 使用状態へ変更する
			bulletenemy->pos = pos;				// 座標をセット
			
			// 発射音再生
			PlaySound(g_eSE, E_DS8_FLAG_NONE);

			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
BULLETENEMY *GetBulletenemy(int no)
{
	return(&bulletenemyWk[no]);
}

