//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX		(1)			// エネミーのMax人数

// エネミー構造体
struct ENEMY
{
	bool					use;		// true:使っている  false:未使用
	float					w, h;		// 幅と高さ
	D3DXVECTOR2				pos;		// ポリゴンの座標
	D3DXVECTOR2				vel;		// 移動量
	float					u;
	float					v;
	float					uh;
	float					vh;
};


// AIの移動の状態
enum MOVE_STATE
{
	MOVE_NONE = 0 , // 動かさない
	MOVE_UP,		// 上方向へ
	MOVE_DOWN,		// 下方向へ
	MOVE_RIGHT,		// 右方向へ
	MOVE_LEFT,		// 左方向へ
	
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
void SetEnemy(D3DXVECTOR2 pos);
bool SerchPlayer(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos);
