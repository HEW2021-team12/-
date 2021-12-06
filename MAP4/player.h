/*==============================================================================

   頂点管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SIZE			(50.0f)
#define PLAYER_ACCELE		(0.1f)
#define	PLAYER_MIN_SPD		(0.0f)
#define PLAYER_MAX_SPD		(3.0f)
#define SLIDE_TIME			(65.0f)

#define GRAVITY_VEL			(0.5f)


// プレイヤー構造体
struct PLAYER
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 vel;
	float		rot;
	float		rot_vel;
	bool		vertigo_isUse;
	float					u;
	float					v;
	float					uh;
	float					vh;

	// マップ用
	D3DXVECTOR2 difference;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void ControlPlayer(void);
void FramePlayer(void);
void ZeroGravity(void);

PLAYER* GetPlayer(void);
D3DXVECTOR2 GetPlayerPosition(void);