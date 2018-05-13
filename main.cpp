//=============================================================================
//
// Main処理 [main.cpp]
// Author : GP11A243 29 潘澤泓
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "icon.h"
#include "enemy.h"
#include "bullet.h"
#include "bulletenemy.h"
#include "bg.h"
#include "title.h"
#include "result.h"
#include "score.h"
#include "sound.h"
#include "gameover.h"
#include "skill.h"
#include "attack.h"
#include "life.h"
#include "mp.h"
#include "monster01.h"
#include "monster01bullet.h"
#include "monster02.h"
#include "portal.h"
#include "boss1.h"
#include "boss1bullet.h"
#include "boss1icon.h"
#include "boss1hp.h"
#include "boss1bg.h"
#include "blackportal.h"
#include "hoshizora.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")			// ウインドウのクラス名
#define WINDOW_NAME			_T("魔法使いの旅")				// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void CheckHit(void);
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

void InitGame(void);

#ifdef _DEBUG
void DrawDebugFont(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// フォントへのポインタ
int						g_nCountFPS;				// FPSカウンタ
#endif

int						g_nStage = 0;				// ステージ番号

LPDIRECTSOUNDBUFFER8	g_pBGM;						// BGM用バッファ

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hWnd, true)))
	{
		return -1;
	}

	//// DirectXの初期化(ウィンドウを作成してから行う)
	//if (FAILED(Init(hWnd, false)))
	//{
	//	return -1;
	//}

	//bool flag = false;//ウィンドウズモード用のフラグ falseフルスクリーンモード

	//if (MessageBox(hWnd, "ウィンドウズモードを起動しますか", "モード確認", MB_YESNO) == IDYES)
	//{
	//	flag = true;//trueはウィンドウズモード
	//}
	//if (FAILED(Init(hWnd, flag)))
	//{
	//	return -1;
	//}


	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPSを測定
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

				Update();			// 更新処理
				Draw();				// 描画処理
				
				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定

	if(bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		//d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.BackBufferFormat           = D3DFMT_X8R8G8B8;					// バックバッファ

		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
									D3DDEVTYPE_HAL,								// ディスプレイタイプ
									hWnd,										// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
									&d3dpp,										// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

	// テクスチャステージ加算合成処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif
	
	// サウンド初期化
	InitSound(hWnd);
	// ロードと再生
	g_pBGM = LoadSound(BGM_00);
	PlaySound(g_pBGM, E_DS8_FLAG_LOOP);

	// プレイヤーの初期化処理
	InitPlayer(0);

	// プレイヤーのアイコン初期化処理
	InitIcon(0);

	// エネミーの初期化処理
	InitEnemy(0);

	// モンスター1の初期化処理
	InitMonster01(0);

	// モンスター１バレットの初期化処理
	InitMonster01bullet(0);

	// モンスター2の初期化処理
	InitMonster02(0);

	// バレットの初期化処理
	InitBullet(0);

	// スキルの初期化処理
	InitSkill(0);

	// アタックの初期化処理
	InitAttack(0);

	// ライフの初期化処理
	InitLife(0);

	// MPの初期化処理
	InitMP(0);

	// エネミーのバレットの初期化処理
	InitBulletenemy(0);

	// BG初期化
	InitBG(0);

	// 魔法陣の初期化処理
	InitPortal(0);

	// ブラック魔法陣の初期化処理
	InitBlackportal(0);

	// ボス１の初期化処理
	InitBoss1(0);

	// ボス１バレットの初期化処理
	InitBoss1bullet(0);

	// ボス１のアイコンの初期化処理
	InitBoss1icon(0);

	// ボス１のHPの初期化処理
	InitBoss1hp(0);

	// ボス１の背景の初期化処理
	InitBOSS1BG(0);
	
	// 星空の初期化処理
	InitHoshizora(0);

	// タイトル初期化
	InitTitle();

	// リザルト初期化
	InitResult();

	// オーバー初期化
	InitGameover();

	// スコア初期化
	InitScore(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 入力処理の終了処理
	UninitInput();

	// プレイヤーの終了処理
	UninitPlayer();

	// プレイヤーのアイコンの終了処理
	UninitIcon();
	
	// エネミーの終了処理
	UninitEnemy();

	// モンスター1の終了処理
	UninitMonster01();

	// モンスター１バレットの終了処理
	UninitMonster01bullet();

	// モンスター2の終了処理
	UninitMonster02();

	// バレットの終了処理
	UninitBullet();

	// エネミーのバレットの終了処理
	UninitBulletenemy();

	// スキルの終了処理
	UninitSkill();

	// アタックの終了処理
	UninitAttack();

	// ライフの終了処理
	UninitLife();

	// MPの終了処理
	UninitMP();

	// BG終了処理
	UninitBG();
	
	// 魔法陣の終了処理
	UninitPortal();

	// ブラック魔法陣の終了処理
	UninitBlackportal();

	// 星空の終了処理
	UninitHoshizora();

	// ボス１の終了処理
	UninitBoss1();

	// ボス１HPの終了処理
	UninitBoss1hp();

	// ボス１バレットの終了処理
	UninitBoss1bullet();

	// ボス１アイコンの終了処理
	UninitBoss1icon();

	// ボス１の背景の終了処理
	UninitBOSS1BG();

	// タイトル終了処理
	UninitTitle();

	// リザルト終了処理
	UninitResult();

	// オーバー終了処理
	UninitGameover();
	
	// スコア終了処理
	UninitScore();

	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}

	// サウンド処理の終了処理
	if (g_pD3D != NULL)
	{
		g_pBGM->Release();
		g_pBGM = NULL;
	}
	UninitSound();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();
	
	// 画面遷移
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();

		if (IsButtonTriggered(0, BUTTON_B))
		{
			SetStage(STAGE_GAME);
		}
		else if (IsButtonTriggered(0, BUTTON_START))
		{
			SetStage(STAGE_GAME);
		}
		break;

	case STAGE_GAME:
		// プレイヤーの更新処理
		UpdatePlayer();

		// プレイヤーのアイコンの更新処理
		UpdateIcon();

		// エネミーの更新処理
		UpdateEnemy();

		// モンスター1の更新処理
		UpdateMonster01();

		// モンスター１バレットの更新処理
		UpdateMonster01bullet();

		// モンスター2の更新処理
		UpdateMonster02();

		// バレットの更新処理
		UpdateBullet();

		// スキルの更新処理
		UpdateSkill();

		// アタックの更新処理
		UpdateAttack();

		// エネミーのバレットの更新処理
		UpdateBulletenemy();

		// 魔法陣の更新処理
		UpdatePortal();


		// ライフの更新処理
		UpdateLife();

		// MPの更新処理
		UpdateMP();

		// BGの更新処理
		UpdateBG();

		// スコアの更新処理
		UpdateScore();
		
		// 当たり判定
		CheckHit();

		if (IsButtonTriggered(0, BUTTON_Y))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}
		break;

	case STAGE_GAME_BOSS1:

		// ボス１の背景の更新処理
		UpdateBOSS1BG();

		// プレイヤーの更新処理
		UpdatePlayer();

		// プレイヤーのアイコンの更新処理
		UpdateIcon();

		// スキルの更新処理
		UpdateSkill();

		// アタックの更新処理
		UpdateAttack();

		// ライフの更新処理
		UpdateLife();

		// MPの更新処理
		UpdateMP();

		// ブラック魔法陣の更新処理
		UpdateBlackportal();

		// ボス１の更新処理
		UpdateBoss1();

		// ボス１HPの更新処理
		UpdateBoss1hp();

		// ボス１の更新処理
		UpdateBoss1bullet();

		// ボス１アイコンの更新処理
		UpdateBoss1icon();

		// スコアの更新処理
		UpdateScore();

		// 星空の更新処理
		UpdateHoshizora();


		// 当たり判定
		CheckHit();

		if (IsButtonTriggered(0, BUTTON_Y))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}

		break;

	case STAGE_GAMEOVER:
		// スコアの更新処理
		UpdateScore();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}
		else if(IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}
		break;
	
	case STAGE_RESULT:
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			InitGame();				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);
		}

		break;

	//case STAGE_GAMEOVER:
	//	UpdateGameover();
	}

	
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// 画面遷移
		switch (g_nStage)
		{
		case STAGE_TITLE:
			DrawTitle();
			break;

		case STAGE_GAME:
		//case STAGE_GAME_END:
			// BGの描画処理
			DrawBG();

			//エネミーの描画処理
			DrawEnemy();

			// モンスター1の描画処理
			DrawMonster01();

			// モンスター１バレットの描画処理
			DrawMonster01bullet();

			// モンスター2の描画処理
			DrawMonster02();

			// プレイヤーの描画処理
			DrawPlayer();

			// プレイヤーのアイコンの描画処理
			DrawIcon();

			// バレットの描画処理
			DrawBullet();

			// エネミーのバレットの描画処理
			DrawBulletenemy();

			// スキルの描画処理
			DrawSkill();

			// アタックの描画処理
			DrawAttack();

			// 魔法陣の描画処理
			DrawPortal();
			
			// ライフの描画処理
			DrawLife();

			// MPの描画処理
			DrawMP();
			
			// スコアの描画処理
			//DrawScore();
			break;

		case STAGE_GAME_BOSS1:
			// ボス１の背景の描画処理
			DrawBOSS1BG();

			// プレイヤーの描画処理
			DrawPlayer();

			// プレイヤーのアイコンの描画処理
			DrawIcon();

			// スキルの描画処理
			DrawSkill();

			// アタックの描画処理
			DrawAttack();

			// ブラック魔法陣の描画処理
			DrawBlackportal();

			// ボス１の描画処理
			DrawBoss1();

			// ボス１バレットの描画処理
			DrawBoss1bullet();

			// ボス１HPの描画処理
			DrawBoss1hp();

			// ボス１アイコンの描画処理
			DrawBoss1icon();

			// ライフの描画処理
			DrawLife();

			// MPの描画処理
			DrawMP();

			// スコアの描画処理
			//DrawScore();

			// 星空の描画処理
			DrawHoshizora();

			break;

		case STAGE_RESULT:
			DrawResult();
			break;

		case STAGE_GAMEOVER:
			DrawGameover();
			break;
		}

#ifdef _DEBUG
		// デバッグ表示
		DrawDebugFont();
#endif
		
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// デバッグ表示処理
//=============================================================================
void DrawDebugFont(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	PLAYER *player = GetPlayer(0);
	BG *bg = GetBG(0);
	MONSTER01 *monster01 = GetMonster01(0);
	ATTACK *attack = GetAttack(0);
	BOSS1 *boss1 = GetBoss1(0);
	 //テキスト描画
	//sprintf(str, _T("FPS:%d"), g_nCountFPS);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 20;
	//sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 40;
	//sprintf(str, "BOSS HP:%d", boss1->hp);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 60;
	//sprintf(str, "BG0X:%f", bg[0].pos.x);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//rect.top = 80;
	//sprintf(str, "MP:%d", player->mp);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage( int stage )
{
	//if( state < 0 || state >= STATE_MAX ) return;

	g_nStage = stage;
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer(0);						// プレイヤーのポインターを初期化
	ENEMY *enemy = GetEnemy(0);							// エネミーのポインターを初期化
	BULLET *bullet = GetBullet(0);						// バレットのポインターを初期化
	BULLETENEMY *bulletenemy = GetBulletenemy(0);		// エネミーのバレットのポインターを初期化
	MONSTER01 *monster01 = GetMonster01(0);				// モンスター1のポインター初期化
	MONSTER02 *monster02 = GetMonster02(0);				// モンスター2のポインター初期化
	ATTACK *attack = GetAttack(0);						// アタックスキルのポインター初期化
	SKILL *skill = GetSkill(0);							// スキルのポインターを初期化
	BOSS1BULLET *boss1bullet = GetBoss1bullet(0);		// ボス１の弾ポインターを初期化
	BOSS1 *boss1 = GetBoss1(0);							// ボス１のポインターを初期化
	BOSS1ICON *boss1icon = GetBoss1icon(0);				// ボス１のアイコンを初期化
	BOSS1HP *boss1hp = GetBoss1hp(0);					// ボス１HPを初期化
	MONSTER01BULLET *monster01bullet = GetMonster01bullet(0);
	PORTAL *portal = GetPortal(0);						// ポータルのポインターを初期化
	BLACKPORTAL *blackportal = GetBlackportal(0);		// ブラック魔法陣のポインターを初期化
	int cnt = 0;										// 敵の数を数える

	// 敵と操作キャラ(BB)
	player = GetPlayer(0);								// プレイヤーのポインターを初期化
	for( int i = 0; i < MONSTER01_MAX; i++, monster01++ )
	{
		if(monster01->use == false )	continue;

		if( CheckHitBB( GetPlayer(0)->pos, monster01->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X,TEXTURE_MONSTER01_SIZE_Y) ) )
		{

			// 操作キャラクターは死に

			// 敵キャラクターは倒される
			monster01->use = false;

			// HP減少処理
			player->hp -= 1;

		}
	}

	// モンスター2と操作キャラ(BB)
	monster02 = GetMonster02(0);			// モンスターのポインターを初期化
	for (int i = 0; i < MONSTER02_MAX; i++, monster01++)
	{
		if (monster02->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, monster02->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
		{
			// HP減少処理
			player->hp -= 1;

			// モンスターが死ぬ
			monster02->use = false;

		}
	}

	// プレイヤーとポータル(BB)
	portal = GetPortal(0);						// ポータルのポインターを初期化
	for (int i = 0; i < PORTAL_MAX; i++, portal++)
	{
		if (portal->use == false)	continue;

		if (CheckHitBB(GetPlayer(0)->pos, portal->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_PORTAL_SIZE_X, TEXTURE_PORTAL_SIZE_Y)))
		{
			InitPlayer(3);			// プレイヤーの座標を初期化
			SetStage(STAGE_GAME_BOSS1);
			blackportal->use = true;
		}
	}


	// アタックスキルとモンスター1(BB)
	monster01 = GetMonster01(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
		{
			if (monster01->use == false) continue;

			if (CheckHitBB(attack->pos, monster01->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y)))
			{
				// 敵のHP減る
				monster01->hp -= 1;		

				// MPの回復
				player->mp += 1;

				// スコア計算
				AddScore(100);
			}
		}
	}

	// スキルとモンスター1(BB)
	skill = GetSkill(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
		{
			if (monster01->use == false) continue;

			if (CheckHitBB(skill->pos, monster01->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER01_SIZE_X, TEXTURE_MONSTER01_SIZE_Y)))
			{
				// 敵のHP減る
				monster01->hp -= 10;

				// スコア計算
				AddScore(100);
			}
		}
	}

	// アタックスキルとモンスター2(BB)
	monster02 = GetMonster02(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
		{
			if (monster02->use == false) continue;

			if (CheckHitBB(attack->pos, monster02->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
			{
				// 敵のHP減る
				monster02->hp -= 1;

				// MPの回復
				player->mp += 1;

				// スコア計算
				AddScore(100);
			}
		}
	}

	// スキルとモンスター2(BB)
	skill = GetSkill(0);
	monster02 = GetMonster02(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
		{
			if (monster02->use == false) continue;

			if (CheckHitBB(skill->pos, monster02->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_MONSTER02_SIZE_X, TEXTURE_MONSTER02_SIZE_Y)))
			{
				// 敵のHP減る
				monster02->hp -= 10;

				// スコア計算
				AddScore(100);
			}
		}
	}

	// アタックとエネミー(BB)
	enemy = GetEnemy(0);
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBB(attack->pos, enemy->pos, D3DXVECTOR2(TEXTURE_ATTACK_SIZE_X, TEXTURE_ATTACK_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
			{
				// 敵のHP減る
				enemy->hp -= 10;

				// MPの回復
				player->mp += 1;

				// スコア計算
				AddScore(100);
			}
		}
	}

	// スキルとエネミ－(BB)
	skill = GetSkill(0);
	enemy = GetEnemy(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBB(skill->pos, enemy->pos, D3DXVECTOR2(TEXTURE_SKILL_SIZE_X, TEXTURE_SKILL_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
			{
				// 敵のHP減る
				enemy->hp -= 200;

				// スコア計算
				AddScore(100);
			}
		}
	}



	// スキルとボス1(BC)
	boss1 = GetBoss1(0);
	skill = GetSkill(0);
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (skill->use == false) continue;

		for (int j = 0; j < BOSS1_MAX; j++, boss1++)
		{
			if (boss1->use == false) continue;

			if (CheckHitBC(skill->pos, boss1->pos, TEXTURE_SKILL_SIZE_X, TEXTURE_BOSS1_SIZE_X))
			{
				// HPの減少
				boss1->hp -= 200;

				// スコア計算
				AddScore(10);
			}
		}
	}

	// アタックとボス１(BB)
	attack = GetAttack(0);
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < BOSS1_MAX; j++, boss1++)
		{
			if (boss1->use == false) continue;
			
			if (CheckHitBC(attack->pos, boss1->pos,TEXTURE_ATTACK_SIZE_X,TEXTURE_BOSS1_SIZE_X))
			{
				// HPの減少
				boss1->hp -= 10;

				// MPの回復
				player->mp += 1;

				// スコア計算
				AddScore(1);
			}
		}
	}






	// 敵と敵(BB)
	enemy = GetEnemy(0);									// エネミーのポインターを初期化
	for (int i = 0; i < ENEMY_MAX - 1; i++, enemy++)
	{
		if (enemy->use == false)	continue;

		if (CheckHitBB(GetEnemy(i)->pos, GetEnemy(i+1)->pos, D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
		{
			enemy->pos.x = enemy->pos.x +10.0f;
		}
	}


	// 弾と敵(BC)
	enemy = GetEnemy(0);					// エネミーのポインターを初期化
	for( int i = 0; i < BULLET_MAX; i++, bullet++ )
	{
		if( bullet->use == false ) continue;

		for( int j = 0; j < ENEMY_MAX; j++, enemy++ )
		{
			if( enemy->use == false ) continue;

			if( CheckHitBC( bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X ) )
			{
				bullet->use = false;	// 弾の消滅処理を行い
				enemy->hp -= 1;			// HPの減少
				if (enemy->hp == 0)
				{
					enemy->use = false;		// 敵は倒される
				}

				// スコア計算
				AddScore(100);
			}
		}
	}


	// ボスの弾とプレイヤー(BC)
	boss1bullet = GetBoss1bullet(0);		// ボス１の弾ポインターを初期化
	for (int i = 0; i < BOSS1BULLET_MAX; i++, boss1bullet++)
	{
		if (boss1bullet->use == false) continue;

		if (CheckHitBB(boss1bullet->pos, player->pos, D3DXVECTOR2(TEXTURE_BOSS1BULLET_SIZE_X, TEXTURE_BOSS1BULLET_SIZE_Y), D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			player->hp -= 2;				//HPの減少
			boss1bullet->use = false;		//弾の消滅処理を行い
		}
	}


	// 自分と敵の弾(BC)
	player = GetPlayer(0);			// プレイヤーのポインターを初期化
	for (int i = 0; i < BULLETENEMY_MAX; i++, bulletenemy++)
	{
		if (bulletenemy->use == false) continue;

		if (CheckHitBB(bulletenemy->pos, player->pos, D3DXVECTOR2(TEXTURE_BULLETENEMY_SIZE_X, TEXTURE_BULLETENEMY_SIZE_Y),D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			bulletenemy->use = false;	// 弾の消滅処理を行い
			bulletenemy->pos.x = enemy->pos.x;
			player->hp -= 1;			//hpを減る

		}

	}

	// 自分とモンスター１バレット(BB)
	monster01bullet = GetMonster01bullet(0);		// モンスター１バレットのポインターを初期化
	for (int i = 0; i < MONSTER01BULLET_MAX; i++, monster01bullet++)
	{
		if (monster01bullet->use == false) continue;

		if (CheckHitBB(monster01bullet->pos, player->pos, D3DXVECTOR2(TEXTURE_MONSTER01BULLET_SIZE_X, TEXTURE_MONSTER01BULLET_SIZE_Y), D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y)))
		{
			monster01bullet->use = false;	// 弾の消滅処理を行い
			monster01bullet->pos.x = -100.0f;
			player->hp -= 1;			//hpを減る

		}

	}


	// アタックとブラック魔法陣(BC)
	blackportal = GetBlackportal(0);		// ブラック魔法陣のポインターを初期化
	attack = GetAttack(0);					// アタックのポインターを初期化
	boss1hp = GetBoss1hp(0);				// ボス１HPの初期化
	for (int i = 0; i < ATTACK_MAX; i++, attack++)
	{
		if (attack->use == false) continue;

		for (int j = 0; j < BLACKPORTAL_MAX; j++, blackportal++)
		{
			if (blackportal->use == false) continue;

			if (CheckHitBC(attack->pos, blackportal->pos, TEXTURE_ATTACK_SIZE_X,TEXTURE_BLACKPORTAL_SIZE_X))
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

				SetHoshizora(pos);

				boss1icon->use = true;
				for (int i = 0; i < BOSS1HP_MAX; i++,boss1hp++)
				{
					boss1hp->use = true;
				}
				blackportal->use = false;

				// スコア計算
				AddScore(1);
			}
		}
	}





	// プレイヤーのHP処理
	player = GetPlayer(0);					// プレイヤーのポインターを初期化

	if (player->hp <= 0)
	{
		player->use = false;				// プレイヤーは死んだ
	}

	// モンスター１のHP処理
	monster01 = GetMonster01(0);			// モンスターのポインターを初期化

	for (int j = 0; j < MONSTER01_MAX; j++, monster01++)
	{
		if (monster01->use == false) continue;

		if (monster01->hp <= 0)
		{
			SetMonster01die();
			//monster01->use = false;
		}
	}

	// モンスター2のHP処理
	monster02 = GetMonster02(0);			// モンスターのポインターを初期化

	for (int j = 0; j < MONSTER02_MAX; j++, monster02++)
	{
		if (monster02->use == false) continue;

		if (monster02->hp <= 0)
		{
			//monster02->use = false;
			SetMonster02die();
		}
	}

	// エネミーのHP処理
	enemy = GetEnemy(0);			// エネミーのポインターを初期化

	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	{
		if (enemy->use == false) continue;

		if (enemy->hp <= 0)
		{
			SetEnemydie();
		}
	}

	// 敵が全滅したら画面遷移
	//enemy = GetEnemy(0);					// エネミーのポインターを初期化
	//for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	//{
	//	if (enemy->use == true)
	//	{
	//		cnt++;
	//	}
	//}

	//// 数えた結果敵が全滅？
	//if (cnt == 0)
	//{
	//	SetStage(STAGE_RESULT);
	//}
	
	// プレイヤーが死んだら画面遷移
	player = GetPlayer(0);
	if (player->use == false)
	{
		SetStage(STAGE_GAMEOVER);
	}
	

	// ボス１を倒したら？
	if (boss1->hp < 0)
	{
		SetStage(STAGE_RESULT);

	}
	
}


//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBB( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2 )
{
	size1 /= 2.0f;	// 半サイズにする
	size2 /= 2.0f;	// 同上

	if( ((pos2.x + size2.x) > (pos1.x - size1.x)) && ((pos1.x + size1.x) > (pos2.x - size2.x)) &&
		((pos2.y + size2.y) > (pos1.y - size1.y)) && ((pos1.y + size1.y) > (pos2.y - size2.y)) )
	{
		return true;
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBC( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2 )
{
	
	D3DXVECTOR3 temp = pos1 - pos2;
	float len = D3DXVec3LengthSq(&temp);

	if (len <= ((size1 + size2) * (size1 + size2)))
	{
		return true;
	}

	return false;
}


//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
void InitGame(void)
{
	InitPlayer(1);			// プレイヤーの再初期化
	InitEnemy(1);			// エネミーの再初期化
	InitBullet(1);			// バレットの再初期化
	InitBulletenemy(1);		// エネミーのバレットの再初期化
	InitPortal(1);			// 魔法陣の再初期化
	InitSkill(1);			// スキルの再初期化
	InitLife(1);			// ライフの再初期化
	InitMP(1);				// MPの再初期化
	InitAttack(1);			// アタックの再初期化
	InitBoss1(1);			// ボス１の再初期化
	InitBoss1bullet(1);		// ボス１弾の再初期化
	InitBoss1hp(1);			// ボス１HPの再初期化
	InitBoss1icon(1);		// ボス１アイコンの再初期化
	InitMonster01(1);		// モンスターの再初期化
	InitMonster01bullet(1);	// モンスター1のバレット再初期化
	InitMonster02(1);		// モンスターの再初期化


	InitScore(1);		// スコアの再初期化
	InitBG(1);			// BGの再初期化
	InitBOSS1BG(1);		// ボス１の背景の再初期化
}

