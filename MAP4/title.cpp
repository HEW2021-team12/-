//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_TextureNo_2 = 0;	
static int	g_BGMNo = 0;		// BGM識別子
float		transparency;
float		transparency_timer;

// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/title.png");
	g_TextureNo_2 = LoadTexture("data/TEXTURE/game_start.png");
	g_BGMNo = LoadSound("data/BGM/title.wav");
	PlaySound(g_BGMNo, 255);
	transparency = 1.0f;
	transparency_timer = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	transparency_timer++;
	while (transparency_timer >= 20.0f)
	{
		if (transparency == 1.0f)
		{
			transparency = 0.5f;
			transparency_timer = 0.0f;
			break;
		}

		if (transparency == 0.5f)
		{
			transparency = 1.0f;
			transparency_timer = 0.0f;
			break;
		}
	}
	if (Keyboard_IsKeyDown(KK_ENTER) ||
		IsButtonTriggered(0, XINPUT_GAMEPAD_B)
		&& GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_SELECT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, transparency);
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureNo_2, SCREEN_WIDTH / 2+ 20.0f, SCREEN_HEIGHT / 2 + 200.0f, 500.0f, 100.0f, 0.0f, 0.13f, 1.0f, 0.067f, col);

}

