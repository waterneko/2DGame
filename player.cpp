//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
//#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "skill.h"
#include "attack.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer[4] = {};	// テクスチャへのポリゴン
// 0:普通の状態
// 1:攻撃
// 2:走る


PLAYER					playerWk[PLAYER_MAX];			// プレイヤー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスのポインタ
			TEXTURE_READY_PLAYER,							// ファイルの名前
			&g_pD3DTexturePlayer[0]);						// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_STABBING_PLAYER,						// ファイルの名前
			&g_pD3DTexturePlayer[1]);						// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_RUN_PLAYER,								// ファイルの名前
			&g_pD3DTexturePlayer[2]);						// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_CHARGE_PLAYER,								// ファイルの名前
			&g_pD3DTexturePlayer[3]);						// 読み込むメモリー

															// プレイヤーの初期化処理
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			player->use = true;											// 使用
			player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// 座標データを初期化	
			player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			player->PatternAnim = rand() % ANIM_PATTERN_NUM;			// アニメパターン番号をランダムで初期化
			player->CountAnim = 0;										// アニメカウントを初期化
			player->hp = 5;												// プレイヤーのhpを初期化
			player->mp = 500;											// プレイヤーのmpを初期化
			player->speedX = 1.5f;										// プレイヤーのスピードを初期化
			player->speedY = 1.0f;										// プレイヤーのスピードを初期化

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
			player->Radius = D3DXVec2Length(&temp);										// プレイヤーの半径を初期化
			player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// プレイヤーの角度を初期化

			player->Texture = g_pD3DTexturePlayer[0];									// テクスチャ情報
			MakeVertexPlayer(i);														// 頂点情報の作成
		}
	}

	if (type == 3)
	{
		player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// 座標データを初期化	
	}

	if (type == 1)
	{
		// プレイヤーの初期化処理
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			player->use = true;											// 使用
			player->pos = D3DXVECTOR3(50.0f, 440.0f, 0.0f);				// 座標データを初期化	
			player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			player->PatternAnim = rand() % ANIM_PATTERN_NUM;			// アニメパターン番号をランダムで初期化
			player->CountAnim = 0;										// アニメカウントを初期化
			player->hp = 5;												// プレイヤーのhpを初期化
			player->mp = 500;											// プレイヤーのmpを初期化
			player->speedX = 1.5f;										// プレイヤーのスピードを初期化
			player->speedY = 1.0f;										// プレイヤーのスピードを初期化

			D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
			player->Radius = D3DXVec2Length(&temp);										// プレイヤーの半径を初期化
			player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// プレイヤーの角度を初期化

			player->Texture = g_pD3DTexturePlayer[0];									// テクスチャ情報
			MakeVertexPlayer(i);														// 頂点情報の作成
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer[0] != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer[0]->Release();
		g_pD3DTexturePlayer[0] = NULL;
	}
	if (g_pD3DTexturePlayer[1] != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer[1]->Release();
		g_pD3DTexturePlayer[1] = NULL;
	}
	if (g_pD3DTexturePlayer[2] != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer[2]->Release();
		g_pD3DTexturePlayer[2] = NULL;
	}
	if (g_pD3DTexturePlayer[3] != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer[3]->Release();
		g_pD3DTexturePlayer[3] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];							// プレイヤーのポインターを初期化
	SKILL *skill = GetSkill(0);								// スキルのポインターを初期化


	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			player->CountAnim++;
			if ((player->CountAnim % TIME_ANIMATION) == 0)
			{				
				// パターンの切り替え
				player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTexturePlayer(i, player->PatternAnim);
			}


			// キーボード入力で移動(ひとまず全プレイヤーを同じキーで動かしちゃう)
			else
			{
				player->Texture = g_pD3DTexturePlayer[0];
			}
			if (GetKeyboardPress(DIK_S))
			{// キャラの下の移動
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y += player->speedY;
			}
			else if (GetKeyboardPress(DIK_W))
			{// キャラの上の移動
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y -= player->speedY;
			}
			if (GetKeyboardPress(DIK_D))
			{// キャラの左の移動
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x += player->speedX;
			}
			else if (GetKeyboardPress(DIK_A))
			{// キャラの右の移動
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x -= player->speedX;
			}

			// プレイヤーのMPの最大値
			if (player->mp > 500)
			{
				player->mp = 500;
			}

			//プレイヤーのHPの最大値
			if (player->hp > 5)
			{
				player->hp = 5;
			}

			//// ゲームパッドでで移動処理
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y += player->speedY;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.y -= player->speedY;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x += player->speedX;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				player->Texture = g_pD3DTexturePlayer[2];
				player->pos.x -= player->speedX;
			}


			// 弾発射
			//if (GetKeyboardTrigger(DIK_SPACE))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}
			//else if (IsButtonTriggered(0, BUTTON_B))
			//{
			//	D3DXVECTOR3 pos = player->pos;
			//	pos.y -= TEXTURE_PLAYER_SIZE_Y;
			//	SetBullet(pos);
			//}

			if ((GetKeyboardPress(DIK_K))|| (IsButtonPressed(0, BUTTON_B)))
			{// 普通の攻撃
				player->Texture = g_pD3DTexturePlayer[1];
				D3DXVECTOR3 pos = player->pos;
				pos.x += TEXTURE_PLAYER_SIZE_X + 50.0f;
				if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(0, BUTTON_LEFT)))
				{
					pos.x -= TEXTURE_PLAYER_SIZE_X + 150.0f;
					//player->pos.x += player->speedX;
				}
				SetAttack(pos);
			}
			if ((GetKeyboardTrigger(DIK_O)) || (IsButtonTriggered(0, BUTTON_A)))
			{// スキルの使用
				if (player->mp - 100 >= 0)
				{// MPの減少
					player->mp -= 100;
					player->Texture = g_pD3DTexturePlayer[3];
					D3DXVECTOR3 pos = player->pos;
					pos.x += TEXTURE_PLAYER_SIZE_X + 50.0f;
					if ((GetKeyboardPress(DIK_D)) || (IsButtonPressed(0, BUTTON_RIGHT)))
					{
						pos.x += TEXTURE_PLAYER_SIZE_X - 50.0f;
						//player->pos.x -= player->speedX;
					}
					else if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(0, BUTTON_LEFT)))
					{
						pos.x -= TEXTURE_PLAYER_SIZE_X + 150.0f;
						//player->pos.x += player->speedX;
					}
					SetSkill(pos);
				}
			}

			// プレイヤーが外に出たら？
			if (player->pos.x > SCREEN_WIDTH)
			{
				player->pos.x -= 10.0f;
			}
			//else if(player->pos.y < 300)
			//{
			//	player->pos.y = 300.0f;
			//}
			else if (player->pos.y > SCREEN_HEIGHT)
			{
				player->pos.y -= 10.0f;
			}
			else if(player->pos.x < 0)
			{
				player->pos.x += 10.0f;
			}
			else if (player->pos.y < 0)
			{
				player->pos.y += 10.0f;
			}

			// 移動後の座標で頂点を設定
			SetVertexPlayer(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	//// αテストを有効に
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, player->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}

	//// αテストを無効に
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// 頂点座標の設定
	SetVertexPlayer(no);

	// rhwの設定
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int no, int cntPattern)
{
	PLAYER *player = &playerWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	if (GetKeyboardPress(DIK_A)|| IsButtonPressed(0, BUTTON_LEFT))
	{
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else if (GetKeyboardPress(DIK_D)|| IsButtonPressed(0, BUTTON_RIGHT))
	{
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else
	{
		player->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		player->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		player->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		player->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// 頂点座標の設定
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

