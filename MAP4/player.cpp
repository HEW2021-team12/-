/*==============================================================================

   頂点管理 [player.cpp]
	Author :	歐　改造 古市
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"
#include "map.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLAYER_POS_X		(13)
#define	PLAYER_POS_Y		(16)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_PlayerTexture = 0;
PLAYER		g_Player;
float		control_timer;
float		gravity_timer;
float		vertigo_timer;
bool		button_bool;
float		button_timer;

float		g_DrawGrav = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	g_PlayerTexture = LoadTexture("data/TEXTURE/player.png");

	g_Player.pos.x = (CHIP_SIZE / 2) + CHIP_SIZE * PLAYER_POS_X;
	g_Player.pos.y = (CHIP_SIZE / 2) + CHIP_SIZE * PLAYER_POS_Y;
	g_Player.size.x = PLAYER_SIZE;
	g_Player.size.y = PLAYER_SIZE;
	g_Player.vel.x = 0.0f;
	g_Player.vel.y = 0.0f;

	g_Player.u = 0.0f;
	g_Player.v = 0.0f;
	g_Player.uh = 0.0f;
	g_Player.vh = 0.0f;

	g_Player.rot = 0.0f;
	g_Player.rot_vel = 0.1f;
	control_timer = 0.0f;
	gravity_timer = 0.0f;
	g_Player.vertigo_isUse = false;
	vertigo_timer = 0.0f;
	g_Player.difference.x = 0.0f;
	g_Player.difference.y = 0.0f;
	button_timer = 0.0f;
	button_bool = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.rot <= -2.0f || g_Player.rot >= 3.0f)
	{
		g_Player.vertigo_isUse = true;
	}

	if (g_Player.vertigo_isUse == false)
	{
		ZeroGravity();
		ControlPlayer();
		FramePlayer();
	}

	if (g_Player.vertigo_isUse == true)
	{
		vertigo_timer ++;
	}

	if (vertigo_timer >= 100.0f)
	{
		g_Player.vertigo_isUse = false;
		g_Player.rot = 0.0f;
		vertigo_timer = 0.0f;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	DrawSpriteColorRotate(g_PlayerTexture,
		SCREEN_WIDTH / 2 + g_Player.difference.x,
		SCREEN_HEIGHT / 2 + g_Player.difference.y + g_DrawGrav,
		g_Player.size.x, g_Player.size.y,
		g_Player.u, g_Player.v,
		g_Player.uh, g_Player.vh,
		col, g_Player.rot);
}

void ControlPlayer(void)
{
	if(!Keyboard_IsKeyDown(KK_LEFT) 
		&& !(GetThumbLeftX(0) < -INPUT_ZONE) && 
		!Keyboard_IsKeyDown(KK_RIGHT) 
		&& !(GetThumbLeftX(0) > INPUT_ZONE) &&
		!Keyboard_IsKeyDown(KK_UP) 
		&& !(GetThumbLeftY(0) > INPUT_ZONE) && 
		!Keyboard_IsKeyDown(KK_DOWN)
		&& !(GetThumbLeftY(0) < -INPUT_ZONE))
	{
		button_bool = true;
	}
	
	if (button_bool)
	{
		button_timer += 1.0f;
	}
	else 
	{
		button_timer = 0.0f;
	}

	g_Player.pos.x += g_Player.vel.x;
	g_Player.pos.y += g_Player.vel.y;

	// 横の移動量の方が大きいとき
	if (fabsf(g_Player.vel.x) > fabsf(g_Player.vel.y))
	{
		// 左に行くとき
		if (g_Player.vel.x < 0)
		{
			g_Player.u = 0.0f;
			g_Player.v = 0.5f;
			g_Player.uh = 0.5f;
			g_Player.vh = 0.5f;
		}
		else // 右に行くとき
		{
			g_Player.u = 0.5f;
			g_Player.v = 0.5f;
			g_Player.uh = 0.5f;
			g_Player.vh = 0.5f;
		}
	}
	else // 縦の移動量の方が大きい or 同じとき
	{
		// 上に行くとき
		if (g_Player.vel.y < 0)
		{
			g_Player.u = 0.5f;
			g_Player.v = 0.0f;
			g_Player.uh = 0.5f;
			g_Player.vh = 0.5f;
		}
		else // 下に行くとき
		{
			g_Player.u = 0.0f;
			g_Player.v = 0.0f;
			g_Player.uh = 0.5f;
			g_Player.vh = 0.5f;
		}
	}

	// X軸の当たり判定
	if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + g_Player.vel.x, g_Player.pos.y))
		== 1)
	{
		g_Player.pos.x -= g_Player.vel.x;
	}

	// Y軸の当たり判定
	if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + g_Player.vel.y))
		== 1)
	{
		g_Player.pos.y -= g_Player.vel.y;
	}

	//左(移動)
	if (Keyboard_IsKeyDown(KK_LEFT) // キーボード
		|| GetThumbLeftX(0) < -INPUT_ZONE) // パッド
	{
		button_bool = false;
		g_Player.vel.x -= PLAYER_ACCELE;

		// X速度の上限値
		if (g_Player.vel.x < -PLAYER_MAX_SPD)
		{
			g_Player.vel.x = -PLAYER_MAX_SPD;
		}

		control_timer++;
		if (control_timer >= 20.0f)
		{
			g_Player.rot -= g_Player.rot_vel;
			control_timer = 0.0f;
		}
	}

	//右(移動)
	if (Keyboard_IsKeyDown(KK_RIGHT) // キーボード
		|| GetThumbLeftX(0) > INPUT_ZONE) // パッド
	{
		button_bool = false;
		g_Player.vel.x += PLAYER_ACCELE;

		// X速度の上限値
		if (g_Player.vel.x > PLAYER_MAX_SPD)
		{
			g_Player.vel.x = PLAYER_MAX_SPD;
		}
		control_timer++;
		if (control_timer >= 20.0f)
		{
			g_Player.rot += g_Player.rot_vel;
			control_timer = 0.0f;
		}
	}

	//上(移動)
	if (Keyboard_IsKeyDown(KK_UP) // キーボード
		|| GetThumbLeftY(0) > INPUT_ZONE) // パッド
	{
		button_bool = false;
		g_Player.vel.y -= PLAYER_ACCELE;

		// y速度の上限値
		if (g_Player.vel.y < -PLAYER_MAX_SPD)
		{
			g_Player.vel.y= -PLAYER_MAX_SPD;
		}

	}
	
	//下(移動)
	if (Keyboard_IsKeyDown(KK_DOWN) // キーボード
		|| GetThumbLeftY(0) < -INPUT_ZONE) // パッド
	{
		button_bool = false;
		g_Player.vel.y += PLAYER_ACCELE;

		// y速度の上限値
		if (g_Player.vel.y > PLAYER_MAX_SPD)
		{
			g_Player.vel.y = PLAYER_MAX_SPD;
		}
	}

	//左回転
	if (Keyboard_IsKeyDown(KK_Q)
		|| GetLeftTrigger(0) > TRIGER_ZONE)
	{
		g_Player.rot -= 0.01f;
	}

	//右回転
	if (Keyboard_IsKeyDown(KK_E)
		|| GetRightTrigger(0) > TRIGER_ZONE)
	{
		g_Player.rot += 0.01f;
	}

	if (button_timer >= SLIDE_TIME)
	{
		g_Player.vel.x = PLAYER_MIN_SPD;
		g_Player.vel.y = PLAYER_MIN_SPD;
		button_timer = 0.0f;
	}
}

void ZeroGravity(void)
{
	if (gravity_timer < 20.0f)
	{
		g_DrawGrav -= GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 20.0f && gravity_timer < 40.0f)
	{
		g_DrawGrav += GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 40.0f && gravity_timer < 60.0f)
	{
		g_DrawGrav += GRAVITY_VEL;
		gravity_timer++;
	}
	if (gravity_timer >= 60.0f && gravity_timer < 80.0f)
	{
		g_DrawGrav -= GRAVITY_VEL;
		gravity_timer++;
	}

	if (gravity_timer >= 80.0f)
	{
		gravity_timer = 0.0f;
	}
}

void FramePlayer(void)
{
	//左(枠)
	if (g_Player.pos.x <= 0.0f + (g_Player.size.x / 2))
	{
		g_Player.pos.x = 0.0f + (g_Player.size.x / 2);
	}
	//右(枠)
	if (g_Player.pos.x >= (MAP_X * 60.0f) - (g_Player.size.x / 2))
	{
		g_Player.pos.x = (MAP_X * 60.0f) - (g_Player.size.x / 2);
	}

	//上(枠)
	if (g_Player.pos.y <= 0.0f + (g_Player.size.y / 2))
	{
		g_Player.pos.y = 0.0f + (g_Player.size.y / 2);
	}
	//下(枠)
	if (g_Player.pos.y >= (MAP_Y * 60.0f) - (g_Player.size.y / 2))
	{
		g_Player.pos.y = (MAP_Y * 60.0f) - (g_Player.size.y / 2);
	}
}

PLAYER* GetPlayer(void)
{
	return &g_Player;
}

D3DXVECTOR2 GetPlayerPosition(void)
{
	return g_Player.pos;
}