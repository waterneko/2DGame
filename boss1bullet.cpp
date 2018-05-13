//=============================================================================
//
// ボス1の弾処理 [boss1bullet.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "boss1bullet.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言ski
//*****************************************************************************
HRESULT MakeVertexBoss1bullet( int no );
void SetTextureBoss1bullet( int no, int cntPattern );
void SetVertexBoss1bullet( int no );
void MoveBoss1bullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss1bullet = NULL;		// テクスチャへのポリゴン

BOSS1BULLET				boss1bulletWk[BOSS1BULLET_MAX];			// バレット構造体

int						g_nTimer;								// タイマー
bool					g_bEnableTimer;							// タイマー動作ON/OFF
int						g_time = 210;							// タイマーの時間
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss1bullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];		// ボス１のバレットポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスのポインタ
			TEXTURE_GAME_BOSS1BULLET ,				// ファイルの名前
			&g_pD3DTextureBoss1bullet);				// 読み込むメモリのポインタ
		
	}

	// タイマーの初期化
	g_nTimer = g_time;
	g_bEnableTimer = true;

	// バレットの初期化処理
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		boss1bullet->use = false;										// 未使用（発射されていない弾）
		boss1bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		boss1bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		boss1bullet->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		boss1bullet->CountAnim = 0;										// アニメカウントを初期化
		
		boss1bullet->Texture = g_pD3DTextureBoss1bullet;				// テクスチャ情報
		MakeVertexBoss1bullet(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss1bullet(void)
{
	if (g_pD3DTextureBoss1bullet != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBoss1bullet->Release();
		g_pD3DTextureBoss1bullet = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss1bullet(void)
{
	BOSS1BULLET *boss1bullet = boss1bulletWk;				// バレットのポインターを初期化
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			boss1bullet->CountAnim++;
			if ((boss1bullet->CountAnim % TIME_ANIMATION_BOSS1BULLET) == 0)
			{
				// パターンの切り替え
				boss1bullet->PatternAnim = (boss1bullet->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS1BULLET;
				
				// テクスチャ座標を設定
				SetTextureBoss1bullet(i, boss1bullet->PatternAnim);
				
			}

			// 当たらなかったバレットの消す処理
			if (g_bEnableTimer)
			{
				g_nTimer--;
				if (g_nTimer < 0)
				{
					g_nTimer = 0;
					boss1bullet->use = false;
					boss1bullet->pos.x = -100.0f;
					g_nTimer = g_time;
				}
			}
			
			// バレットの移動処理
			if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x == player->pos.x && boss1bullet->pos.y > player->pos.y)
			{
				boss1bullet->pos.y -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x == player->pos.x && boss1bullet->pos.y < player->pos.y)
			{
				boss1bullet->pos.y += BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x > player->pos.x && boss1bullet->pos.y == player->pos.y)
			{
				boss1bullet->pos.x -= BOSS1BULLET_SPEED;
			}
			else if (boss1bullet->pos.x < player->pos.x && boss1bullet->pos.y == player->pos.y)
			{
				boss1bullet->pos.x += BOSS1BULLET_SPEED;
			}

			SetVertexBoss1bullet(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss1bullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = boss1bulletWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, boss1bullet->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS1BULLET, boss1bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoss1bullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexBoss1bullet( no );

	// rhwの設定
	boss1bullet->vertexWk[0].rhw =
	boss1bullet->vertexWk[1].rhw =
	boss1bullet->vertexWk[2].rhw =
	boss1bullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	boss1bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss1bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	boss1bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss1bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET, 0.0f);
	boss1bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET);
	boss1bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBoss1bullet( int no, int cntPattern )
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS1BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS1BULLET;
	
	boss1bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	boss1bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	boss1bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	boss1bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss1bullet( int no )
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	boss1bullet->vertexWk[0].vtx.x = boss1bullet->pos.x - TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[0].vtx.y = boss1bullet->pos.y - TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[0].vtx.z = 0.0f;

	boss1bullet->vertexWk[1].vtx.x = boss1bullet->pos.x + TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[1].vtx.y = boss1bullet->pos.y - TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[1].vtx.z = 0.0f;

	boss1bullet->vertexWk[2].vtx.x = boss1bullet->pos.x - TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[2].vtx.y = boss1bullet->pos.y + TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[2].vtx.z = 0.0f;

	boss1bullet->vertexWk[3].vtx.x = boss1bullet->pos.x + TEXTURE_BOSS1BULLET_SIZE_X;
	boss1bullet->vertexWk[3].vtx.y = boss1bullet->pos.y + TEXTURE_BOSS1BULLET_SIZE_Y;
	boss1bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// スキルの発射設定
//=============================================================================
void SetBoss1bullet(D3DXVECTOR3 pos)
{
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];			// バレットのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == false)			// 未使用状態のバレットを見つける
		{
			boss1bullet->use = true;			// 使用状態へ変更する
			boss1bullet->pos = pos;				// 座標をセット			
			return;								// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
BOSS1BULLET *GetBoss1bullet(int no)
{
	return(&boss1bulletWk[no]);
}
//=============================================================================
// スキルの移動関数
//=============================================================================
void MoveBoss1bullet(int no)
{
	PLAYER *player = GetPlayer(0);
	BOSS1BULLET *boss1bullet = &boss1bulletWk[0];			// バレットのポインターを初期化
	for (int i = 0; i < BOSS1BULLET_MAX;i++, boss1bullet++)
	{
		boss1bullet->pos.x -= player->speedX;
	}

}