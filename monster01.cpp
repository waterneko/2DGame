//=============================================================================
//
// 敵処理 [monster01.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMonster01( int no );
void SetTextureMonster01( int no, int cntPattern );
void SetVertexMonster01( int no );
void MoveMonster01(int no);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01[2] = { NULL };		// テクスチャへのポリゴン

MONSTER01				monster01Wk[MONSTER01_MAX];			// エネミー構造体

int						g_nTimerMon1;								// タイマー
int						g_nTimerMon1Move;							// タイマー
int						g_nTimerMon1Move01;							// タイマー
int						g_nTimerMon1Move02;							// タイマー
int						g_nTimerMon1Move03;							// タイマー
int						g_nTimerMon1Bullet;							// タイマー
bool					g_bEnableTimerMon1;							// タイマー動作ON/OFF
int						g_timeMon1 = 30;							// タイマーの時間
int						g_timeMon1Move = 700;						// タイマーの時間
int						g_timeMon1Move01 = 600;						// タイマーの時間
int						g_timeMon1Move02 = 400;						// タイマーの時間
int						g_timeMon1Move03 = 300;						// タイマーの時間
int						g_timeMon1Bullet = 30;						// タイマーの時間
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMonster01(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = monster01Wk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MONSTER01,				// ファイルの名前
			&g_pD3DTextureMonster01[0]);		// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_MONSTER01DIE,				// ファイルの名前
			&g_pD3DTextureMonster01[1]);		// 読み込むメモリのポインタ
	}

	// タイマーの初期化
	g_nTimerMon1 = g_timeMon1;
	g_nTimerMon1Move = g_timeMon1Move;
	g_nTimerMon1Move01 = g_timeMon1Move01;
	g_nTimerMon1Move02 = g_timeMon1Move02;
	g_nTimerMon1Move03 = g_timeMon1Move03;
	g_nTimerMon1Bullet = g_timeMon1Bullet;
	g_bEnableTimerMon1 = true;


	// エネミーの初期化処理
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		monster01->use = true;										// 使用
		monster01->pos = D3DXVECTOR3(450+i*80.0f,350.0+i*50.0f, 0.0f);	// 座標データを初期化
		monster01->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		monster01->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		monster01->CountAnim = 0;									// アニメカウントを初期化
		monster01->hp = 100;										// エネミーのHP

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y);
		monster01->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		monster01->BaseAngle = atan2f(TEXTURE_MONSTER01_SIZE_Y, TEXTURE_MONSTER01_SIZE_X);	// エネミーの角度を初期化

		monster01->Texture = g_pD3DTextureMonster01[0];				// テクスチャ情報
		MakeVertexMonster01(i);										// 頂点情報の作成
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMonster01(void)
{
	if (g_pD3DTextureMonster01[0] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster01[0]->Release();
		g_pD3DTextureMonster01[0] = NULL;
	}
	if (g_pD3DTextureMonster01[1] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster01[1]->Release();
		g_pD3DTextureMonster01[1] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonster01(void)
{
	MONSTER01 *monster01 = monster01Wk;				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->use == true)			// 使用している状態なら更新する
		{
			monster01->CountAnim++;
			if ((monster01->CountAnim % TIME_ANIMATION_MONSTER01) == 0)
			{
				// パターンの切り替え
				monster01->PatternAnim = (monster01->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01;

				// テクスチャ座標を設定
				SetTextureMonster01(i, monster01->PatternAnim);			}
			
			//敵の移動
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1Move --;
				g_nTimerMon1Move01--;
				g_nTimerMon1Move02--;
				if (g_nTimerMon1Move > 0)
				{
					monster01Wk[0].pos.y += 0.3f;
				}
				if (g_nTimerMon1Move01 > 0)
				{
					monster01Wk[1].pos.y += 0.3f;
				}
				if (g_nTimerMon1Move02 > 0)
				{
					monster01Wk[2].pos.y += 0.3f;
				}

				if (g_nTimerMon1Move < 0 )
				{
					monster01Wk[0].pos.y -= 0.3f;
					if (g_nTimerMon1Move < -g_timeMon1Move)
					{
						g_nTimerMon1Move = g_timeMon1Move;
					}
				}
				if (g_nTimerMon1Move01 < 0)
				{
					monster01Wk[1].pos.y -= 0.3f;

					if (g_nTimerMon1Move01 < -g_timeMon1Move01)
					{
						g_nTimerMon1Move01 = g_timeMon1Move01;
					}
				}
				if (g_nTimerMon1Move02 < 0)
				{
					monster01Wk[2].pos.y -= 0.3f;

					if (g_nTimerMon1Move02 < -g_timeMon1Move02)
					{
						g_nTimerMon1Move02 = g_timeMon1Move02;
					}
				}
			}

			 //弾発射
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1Bullet--;
				if (g_nTimerMon1Bullet < 0)
				{
					D3DXVECTOR3 pos = monster01->pos;
					pos.x -= TEXTURE_MONSTER01BULLET_SIZE_Y;
					SetMonster01bullet(pos);
					g_nTimerMon1Bullet = g_timeMon1Bullet;
				}
			}

			SetVertexMonster01(i);	// 移動後の座標で頂点を設定

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMonster01(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = monster01Wk;				// エネミーのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, monster01->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01, monster01->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMonster01( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01 *monster01 = &monster01Wk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexMonster01( no );

	// rhwの設定
	monster01->vertexWk[0].rhw =
	monster01->vertexWk[1].rhw =
	monster01->vertexWk[2].rhw =
	monster01->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	monster01->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	monster01->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01, 0.0f);
	monster01->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01);
	monster01->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMonster01( int no, int cntPattern )
{
	MONSTER01 *monster01 = &monster01Wk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01;
	
	monster01->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMonster01( int no )
{
	MONSTER01 *monster01 = &monster01Wk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	monster01->vertexWk[0].vtx.x = monster01->pos.x - cosf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[0].vtx.y = monster01->pos.y - sinf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[0].vtx.z = 0.0f;

	monster01->vertexWk[1].vtx.x = monster01->pos.x + cosf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[1].vtx.y = monster01->pos.y - sinf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[1].vtx.z = 0.0f;

	monster01->vertexWk[2].vtx.x = monster01->pos.x - cosf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[2].vtx.y = monster01->pos.y + sinf(monster01->BaseAngle - monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[2].vtx.z = 0.0f;

	monster01->vertexWk[3].vtx.x = monster01->pos.x + cosf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[3].vtx.y = monster01->pos.y + sinf(monster01->BaseAngle + monster01->rot.z) * monster01->Radius;
	monster01->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
MONSTER01 *GetMonster01(int no)
{
	return(&monster01Wk[no]);
}

//=============================================================================
// モンスター1移動関数
//=============================================================================
void MoveMonster01(int no)
{
	MONSTER01 *monster01 = &monster01Wk[no];			// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		monster01->pos.x -= player->speedX;
	}

}

//=============================================================================
//モンスター1の死亡動画
//=============================================================================
void SetMonster01die(void)
{
	MONSTER01 *monster01 = monster01Wk;			// エネミーのポインターを初期化

	for (int i = 0; i < MONSTER01_MAX; i++, monster01++)
	{
		if (monster01->hp <= 0)
		{
			monster01->Texture = g_pD3DTextureMonster01[1];
			if (g_bEnableTimerMon1)
			{
				g_nTimerMon1--;
				if (g_nTimerMon1 < 0)
				{
					g_nTimerMon1 = 0;
					monster01->use = false;
					g_nTimerMon1 = g_timeMon1;
				}
			}
		}
	}
}

