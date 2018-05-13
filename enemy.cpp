//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "bulletenemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy[2] = {};		// テクスチャへのポリゴン

ENEMY					enemyWk[ENEMY_MAX];				// エネミー構造体

int						g_nTimerEnemy;								// タイマー
int						g_nTimerEnemyM;								// タイマー
bool					g_bEnableTimerEnemy;						// タイマー動作ON/OFF
int						g_timeEnemy = 30;							// タイマーの時間
int						g_timeEnemyM = 300;							// タイマーの時間
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMY,				// ファイルの名前
			&g_pD3DTextureEnemy[0]);		// 読み込むメモリのポインタ
											// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ENEMYDIE,			// ファイルの名前
			&g_pD3DTextureEnemy[1]);		// 読み込むメモリのポインタ
	}

	// エネミーの初期化処理
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// 使用
		enemy->pos = D3DXVECTOR3(1800.0f, 600.0f, 0.0f);		// 座標データを初期化
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		enemy->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemy->CountAnim = 0;									// アニメカウントを初期化
		enemy->hp = 2000;										// エネミーのHP
		
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// エネミーの角度を初期化

		enemy->Texture = g_pD3DTextureEnemy[0];					// テクスチャ情報
		MakeVertexEnemy(i);										// 頂点情報の作成
	}

	g_bEnableTimerEnemy = true;
	g_nTimerEnemy = g_timeEnemy;
	g_nTimerEnemyM = g_timeEnemyM;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy[0] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy[0]->Release();
		g_pD3DTextureEnemy[0] = NULL;
	}
	if (g_pD3DTextureEnemy[1] != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEnemy[1]->Release();
		g_pD3DTextureEnemy[1] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// 使用している状態なら更新する
		{
			enemy->CountAnim++;
			if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// パターンの切り替え
				enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

				// テクスチャ座標を設定
				SetTextureEnemy(i, enemy->PatternAnim);			}
			
			//敵の移動
			if (g_bEnableTimerEnemy)
			{
				g_nTimerEnemyM--;
				if (g_nTimerEnemyM > 0)
				{
					enemy->pos.y -= 2.0f;
				}
				if (g_nTimerEnemyM < 0)
				{
					enemy->pos.y += 2.0f;
					if (g_nTimerEnemyM < -g_timeEnemyM)
					{
						g_nTimerEnemyM = g_timeEnemyM;
					}
				}
			}


			// 弾発射
			if(enemy->use ==true)
			{ 
			D3DXVECTOR3 pos = enemy->pos;
			pos.x = enemy->pos.x;
			SetBulletenemy(pos);
			
			}

			SetVertexEnemy(i);	// 移動後の座標で頂点を設定

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;				// エネミーのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, enemy->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化

	// 頂点座標の設定
	SetVertexEnemy( no );

	// rhwの設定
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	//enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy( int no, int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化
	
	// 頂点座標の設定
	enemy->vertexWk[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

//=============================================================================
// 移動関数
//=============================================================================
void MoveEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];			// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->pos.x -= player->speedX;
	}

}

//=============================================================================
//死亡動画
//=============================================================================
void SetEnemydie(void)
{
	ENEMY *enemy = enemyWk;			// エネミーのポインターを初期化

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->hp <= 0)
		{
			enemy->Texture = g_pD3DTextureEnemy[1];
			if (g_bEnableTimerEnemy)
			{
				g_nTimerEnemy--;
				if (g_nTimerEnemy < 0)
				{
					g_nTimerEnemy = 0;
					enemy->use = false;
					g_nTimerEnemy = g_timeEnemy;
				}
			}
		}
	}
}