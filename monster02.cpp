//=============================================================================
//
// 敵処理 [monster02.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "monster02.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMonster02( int no );
void SetTextureMonster02( int no, int cntPattern );
void SetVertexMonster02( int no );
void MoveMonster02(int no);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster02[2] = { NULL };		// テクスチャへのポリゴン

MONSTER02				monster02Wk[MONSTER02_MAX];					// エネミー構造体

int						g_nTimerMon2;								// タイマー
int						g_nTimerMon2Move;							// タイマー
bool					g_bEnableTimerMon2;							// タイマー動作ON/OFF
int						g_timeMon2 = 30;							// タイマーの時間
int						g_timeMon2Move = 300;						// タイマーの時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMonster02(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = monster02Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MONSTER02,				// ファイルの名前
			&g_pD3DTextureMonster02[0]);		// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MONSTER02DIE,				// ファイルの名前
			&g_pD3DTextureMonster02[1]);		// 読み込むメモリのポインタ
	}

	// タイマーの初期化
	g_nTimerMon2 = g_timeMon2;
	g_nTimerMon2Move = g_timeMon2Move;
	g_bEnableTimerMon2 = true;


	// エネミーの初期化処理
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		monster02->use = true;										// 使用
		monster02Wk[0].pos = D3DXVECTOR3(1300.0f, 350.0f, 0.0f);	// 座標データを初期化
		monster02Wk[1].pos = D3DXVECTOR3(1300.0f, 450.0f, 0.0f); 	// 座標データを初期化
		monster02->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		monster02->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		monster02->CountAnim = 0;									// アニメカウントを初期化
		monster02->hp = 200;										// エネミーのHP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y);
		monster02->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		monster02->BaseAngle = atan2f(TEXTURE_MONSTER02_SIZE_Y, TEXTURE_MONSTER02_SIZE_X);	// エネミーの角度を初期化

		monster02->Texture = g_pD3DTextureMonster02[0];				// テクスチャ情報
		MakeVertexMonster02(i);										// 頂点情報の作成
	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMonster02(void)
{
	if (g_pD3DTextureMonster02[0] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster02[0]->Release();
		g_pD3DTextureMonster02[0] = NULL;
	}
	if (g_pD3DTextureMonster02[1] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster02[1]->Release();
		g_pD3DTextureMonster02[1] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonster02(void)
{
	MONSTER02 *monster02 = monster02Wk;				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->use == true)			// 使用している状態なら更新する
		{
			monster02->CountAnim++;
			if ((monster02->CountAnim % TIME_ANIMATION_MONSTER02) == 0)
			{
				// パターンの切り替え
				monster02->PatternAnim = (monster02->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER02;

				// テクスチャ座標を設定
				SetTextureMonster02(i, monster02->PatternAnim);			}
			
			if (monster02->pos.x - player->pos.x < 600)
			{
				monster02->pos.x -= MONSTER02_SPEED;

				if (monster02->pos.x - player->pos.x < 100)
				{

					if (monster02->pos.x > player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x > player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x == player->pos.x && monster02->pos.y > player->pos.y)
					{
						monster02->pos.y -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x == player->pos.x && monster02->pos.y < player->pos.y)
					{
						monster02->pos.y += MONSTER02_SPEED;
					}
					else if (monster02->pos.x > player->pos.x && monster02->pos.y == player->pos.y)
					{
						monster02->pos.x -= MONSTER02_SPEED;
					}
					else if (monster02->pos.x < player->pos.x && monster02->pos.y == player->pos.y)
					{
						monster02->pos.x += MONSTER02_SPEED;
					}
				}
			}

			SetVertexMonster02(i);	// 移動後の座標で頂点を設定

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMonster02(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = monster02Wk;				// エネミーのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, monster02->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER02, monster02->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMonster02( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER02 *monster02 = &monster02Wk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexMonster02( no );

	// rhwの設定
	monster02->vertexWk[0].rhw =
	monster02->vertexWk[1].rhw =
	monster02->vertexWk[2].rhw =
	monster02->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	monster02->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster02->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	monster02->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster02->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER02, 0.0f);
	monster02->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER02);
	monster02->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER02, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER02);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMonster02( int no, int cntPattern )
{
	MONSTER02 *monster02 = &monster02Wk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER02;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER02;
	
	monster02->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster02->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster02->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster02->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMonster02( int no )
{
	MONSTER02 *monster02 = &monster02Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	monster02->vertexWk[0].vtx.x = monster02->pos.x - cosf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[0].vtx.y = monster02->pos.y - sinf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[0].vtx.z = 0.0f;

	monster02->vertexWk[1].vtx.x = monster02->pos.x + cosf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[1].vtx.y = monster02->pos.y - sinf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[1].vtx.z = 0.0f;

	monster02->vertexWk[2].vtx.x = monster02->pos.x - cosf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[2].vtx.y = monster02->pos.y + sinf(monster02->BaseAngle - monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[2].vtx.z = 0.0f;

	monster02->vertexWk[3].vtx.x = monster02->pos.x + cosf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[3].vtx.y = monster02->pos.y + sinf(monster02->BaseAngle + monster02->rot.z) * monster02->Radius;
	monster02->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
MONSTER02 *GetMonster02(int no)
{
	return(&monster02Wk[no]);
}

//=============================================================================
// モンスター2移動関数
//=============================================================================
void MoveMonster02(int no)
{
	MONSTER02 *monster02 = &monster02Wk[no];			// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		monster02->pos.x -= player->speedX;
	}

}

//=============================================================================
//モンスター2の死亡動画
//=============================================================================
void SetMonster02die(void)
{
	MONSTER02 *monster02 = monster02Wk;			// エネミーのポインターを初期化

	for (int i = 0; i < MONSTER02_MAX; i++, monster02++)
	{
		if (monster02->hp <= 0)
		{
			monster02->Texture = g_pD3DTextureMonster02[1];
			if (g_bEnableTimerMon2)
			{
				g_nTimerMon2--;
				if (g_nTimerMon2 < 0)
				{
					g_nTimerMon2 = 0;
					monster02->use = false;
					g_nTimerMon2 = g_timeMon2;
				}
			}
		}
	}
}

