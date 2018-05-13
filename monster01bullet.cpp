//=============================================================================
//
// モンスター１の弾処理 [monster01bullet.cpp]
// Author :GP11A243 29 潘澤泓 
//
//=============================================================================
#include "main.h"
#include "monster01bullet.h"
#include "sound.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言ski
//*****************************************************************************
HRESULT MakeVertexMonster01bullet( int no );
void SetTextureMonster01bullet( int no, int cntPattern );
void SetVertexMonster01bullet( int no );
void MoveMonster01bullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMonster01bullet = NULL;			// テクスチャへのポリゴン

MONSTER01BULLET			monster01bulletWk[MONSTER01BULLET_MAX];			// バレット構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMonster01bullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];		// バレットポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,				// デバイスのポインタ
			TEXTURE_GAME_MONSTER01BULLET ,				// ファイルの名前
			&g_pD3DTextureMonster01bullet);				// 読み込むメモリのポインタ
		
	}

	// タイマーの初期化


	// バレットの初期化処理
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		monster01bullet->use = false;										// 未使用（発射されていない弾）
		monster01bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// 座標データを初期化
		monster01bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		monster01bullet->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		monster01bullet->CountAnim = 0;										// アニメカウントを初期化
		
		monster01bullet->Texture = g_pD3DTextureMonster01bullet;			// テクスチャ情報
		MakeVertexMonster01bullet(i);										// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMonster01bullet(void)
{
	if (g_pD3DTextureMonster01bullet != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMonster01bullet->Release();
		g_pD3DTextureMonster01bullet = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonster01bullet(void)
{
	MONSTER01BULLET *monster01bullet = monster01bulletWk;				// バレットのポインターを初期化
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			monster01bullet->CountAnim++;
			if ((monster01bullet->CountAnim % TIME_ANIMATION_MONSTER01BULLET) == 0)
			{
				// パターンの切り替え
				monster01bullet->PatternAnim = (monster01bullet->PatternAnim + 1) % ANIM_PATTERN_NUM_MONSTER01BULLET;
				
				// テクスチャ座標を設定
				SetTextureMonster01bullet(i, monster01bullet->PatternAnim);
				
			}
			// バレットの移動処理
			monster01bullet->pos.x -= MONSTER01BULLET_SPEED;

			// 当たらなかったバレットの消す処理

			
			// バレットの移動処理

			// 画面外まで進んだ？
			if (monster01bullet->pos.x < -TEXTURE_MONSTER01BULLET_SIZE_X)	// 自分の大きさを考慮して画面外か判定している
			{
				monster01bullet->use = false;
				monster01bullet->pos.x = -100.0f;
			}

			SetVertexMonster01bullet(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMonster01bullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = monster01bulletWk;				// バレットのポインターを初期化

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, monster01bullet->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MONSTER01BULLET, monster01bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMonster01bullet( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	SetVertexMonster01bullet( no );

	// rhwの設定
	monster01bullet->vertexWk[0].rhw =
	monster01bullet->vertexWk[1].rhw =
	monster01bullet->vertexWk[2].rhw =
	monster01bullet->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	monster01bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	monster01bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	monster01bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	monster01bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET, 0.0f);
	monster01bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET);
	monster01bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET);


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureMonster01bullet( int no, int cntPattern )
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// バレットのポインターを初期化

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_MONSTER01BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_MONSTER01BULLET;
	
	monster01bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	monster01bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	monster01bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	monster01bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMonster01bullet( int no )
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[no];			// バレットのポインターを初期化

	// 頂点座標の設定
	monster01bullet->vertexWk[0].vtx.x = monster01bullet->pos.x - TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[0].vtx.y = monster01bullet->pos.y - TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[0].vtx.z = 0.0f;

	monster01bullet->vertexWk[1].vtx.x = monster01bullet->pos.x + TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[1].vtx.y = monster01bullet->pos.y - TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[1].vtx.z = 0.0f;

	monster01bullet->vertexWk[2].vtx.x = monster01bullet->pos.x - TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[2].vtx.y = monster01bullet->pos.y + TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[2].vtx.z = 0.0f;

	monster01bullet->vertexWk[3].vtx.x = monster01bullet->pos.x + TEXTURE_MONSTER01BULLET_SIZE_X;
	monster01bullet->vertexWk[3].vtx.y = monster01bullet->pos.y + TEXTURE_MONSTER01BULLET_SIZE_Y;
	monster01bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// スキルの発射設定
//=============================================================================
void SetMonster01bullet(D3DXVECTOR3 pos)
{
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];			// バレットのポインターを初期化

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == false)			// 未使用状態のバレットを見つける
		{
			monster01bullet->use = true;			// 使用状態へ変更する
			monster01bullet->pos = pos;				// 座標をセット			
			return;									// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// 取得関数
//=============================================================================
MONSTER01BULLET *GetMonster01bullet(int no)
{
	return(&monster01bulletWk[no]);
}
//=============================================================================
// スキルの移動関数
//=============================================================================
void MoveMonster01bullet(int no)
{
	PLAYER *player = GetPlayer(0);
	MONSTER01BULLET *monster01bullet = &monster01bulletWk[0];			// バレットのポインターを初期化
	for (int i = 0; i < MONSTER01BULLET_MAX;i++, monster01bullet++)
	{
		monster01bullet->pos.x -= player->speedX;
	}

}