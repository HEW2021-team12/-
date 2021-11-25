//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "player.h"
#include "map.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROT_SPD				(0.05f)
#define ENEMY_SPD			(2.0f)
#define ENEMY_SIZE			(55.0f)
#define MOVE_TIMER			(50)
#define SERCH_RANGE			(250.0f)
#define FIND_SPD			(2.0f)

#define SEARCH_TIMER		(CHIP_SIZE / ENEMY_SPD)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_EnemyTexture = 0;
static ENEMY g_Enemy;							  // エネミー構造体
static float MAPleft, MAPright, MAPtop, MAPunder; // エネミーの行動範囲
static int g_Enemy_Timer;
static int g_Search_Timer;
int move;
D3DXVECTOR2 g_NotMove;
D3DXVECTOR2 g_Move;
bool g_MoveCntX, g_MoveCntY;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	g_EnemyTexture = LoadTexture("data/TEXTURE/enemy.png");

	MAPleft = SCREEN_WIDTH / 2;
	MAPright = SCREEN_WIDTH / 2;

	MAPtop = SCREEN_HEIGHT / 2;
	MAPunder = SCREEN_HEIGHT / 2;

	// エネミー構造体の初期化
	g_Enemy.use   = true;
	g_Enemy.w     = ENEMY_SIZE;
	g_Enemy.h     = ENEMY_SIZE;
	g_Enemy.pos   = D3DXVECTOR2(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 150.0f);
	g_Enemy.vel   = D3DXVECTOR2(ENEMY_SPD,ENEMY_SPD);

	g_Enemy_Timer = 0;
	g_Search_Timer = 0;

	// エネミーUV
	g_Enemy.u = 0.0f;
	g_Enemy.v = 0.0f;
	g_Enemy.uh = 0.0f;
	g_Enemy.vh = 0.0f;
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{

	if (g_Enemy.use == true)
	{
		// 追跡判定
		if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
		{// 見つけた(範囲内に入った)

			// 旧版サーチ
			{
			//現在位置
			D3DXVECTOR2 position = g_Enemy.pos;

			//目標地点
			D3DXVECTOR2 destination = GetPlayerPosition();

			//成分
			D3DXVECTOR2 components;

			//大きさ
			float magnitude;

			//方向（単位ベクトル）
			D3DXVECTOR2 direction;

			//成分計算
			components.x = destination.x - position.x;
			components.y = destination.y - position.y;

			//大きさ計算
			magnitude = (float)sqrt(components.x * components.x + components.y * components.y);

			//方向計算（正規化）
			direction.x = components.x / magnitude;
			direction.y = components.y / magnitude;

			// 横の移動量の方が大きいとき
			if (fabsf(direction.x) > fabsf(direction.y))
			{
				// 左に行くとき
				if (direction.x < 0)
				{
					g_Enemy.u = 1.0f;
					g_Enemy.v = 0.0f;
					g_Enemy.uh = -0.5f;
					g_Enemy.vh = 0.5f;
				}
				else // 右に行くとき
				{
					g_Enemy.u = 0.5f;
					g_Enemy.v = 0.0f;
					g_Enemy.uh = 0.5f;
					g_Enemy.vh = 0.5f;
				}
			}
			else // 縦の移動量の方が大きい or 同じとき
			{
				// 上に行くとき
				if (direction.y < 0)
				{
					g_Enemy.u = 0.5f;
					g_Enemy.v = 0.5f;
					g_Enemy.uh = 0.5f;
					g_Enemy.vh = 0.5f;
				}
				else // 下に行くとき
				{
					g_Enemy.u = 0.0f;
					g_Enemy.v = 0.5f;
					g_Enemy.uh = 0.5f;
					g_Enemy.vh = 0.5f;
				}
			}

			//移動後の位置を計算
			g_Enemy.pos.x += direction.x * FIND_SPD;
			if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + direction.x * FIND_SPD, g_Enemy.pos.y),
				D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
				== 1)
			{
				g_Enemy.pos.x -= direction.x * FIND_SPD;
				g_NotMove.x += fabsf(direction.x);

				if (!g_MoveCntX)
				{
					// 一定時間動けない（障害物に引っかかる）
					if (g_NotMove.x > CHIP_SIZE)
					{
						g_MoveCntX = true;
						g_NotMove.x = 0.0f;
					}
				}
			}

			g_Enemy.pos.y += direction.y * FIND_SPD;
			if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + direction.y * FIND_SPD),
				D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
				== 1)
			{
				g_Enemy.pos.y -= direction.y * FIND_SPD;
				g_NotMove.y += fabsf(direction.y);

				if (!g_MoveCntY)
				{
					// 一定時間動けない（障害物に引っかかる）
					if (g_NotMove.y > CHIP_SIZE)
					{
						g_MoveCntY = true;
						g_NotMove.y = 0.0f;
					}
				}

			}

			// 一定時間動けない（障害物に引っかかる）
			if (g_MoveCntX)
			{
				g_Move.y += ENEMY_SPD;

				g_Enemy.pos.y += ENEMY_SPD;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + ENEMY_SPD),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.y -= ENEMY_SPD;
				}

				// STOP_CNT分移動したら
				if (g_Move.y > CHIP_SIZE * 3 / 2)
				{
					g_MoveCntX = false;
					g_Move.y = 0.0f;
				}
			}
			if (g_MoveCntY)
			{
				g_Move.x += ENEMY_SPD;

				g_Enemy.pos.x += ENEMY_SPD;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + ENEMY_SPD, g_Enemy.pos.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.x -= ENEMY_SPD;
				}

				// STOP_CNT分移動したら
				if (g_Move.x > CHIP_SIZE * 3 / 2)
				{
					g_MoveCntY = false;
					g_Move.x = 0.0f;
				}
			}

			}
			
		}
		// 見つけていない
		else 
		{
			g_Enemy_Timer++;

			if (g_Enemy_Timer > MOVE_TIMER)
			{
				move = rand() % 5;
				g_Enemy_Timer = 0;
				srand((unsigned)time(NULL));
			}

			// エネミー移動
			// 1:上　2:下　3:右　4:左　0:なし(待機)
			if (move == 1) // 上
			{
				g_Enemy.pos.y -= g_Enemy.vel.y;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y - g_Enemy.vel.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.y += g_Enemy.vel.y;
				}
				g_Enemy.u = 0.5f;
				g_Enemy.v = 0.5f;
				g_Enemy.uh = 0.5f;
				g_Enemy.vh = 0.5f;
			}

			if (move == 2) // 下
			{
				g_Enemy.pos.y += g_Enemy.vel.y;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x, g_Enemy.pos.y + g_Enemy.vel.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.y -= g_Enemy.vel.y;
				}
				g_Enemy.u = 0.0f;
				g_Enemy.v = 0.5f;
				g_Enemy.uh = 0.5f;
				g_Enemy.vh = 0.5f;
			}

			if (move == 3) // 右
			{
				g_Enemy.pos.x += g_Enemy.vel.x;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x + g_Enemy.vel.x, g_Enemy.pos.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.x -= g_Enemy.vel.x;
				}
				g_Enemy.u = 0.5f;
				g_Enemy.v = 0.0f;
				g_Enemy.uh = 0.5f;
				g_Enemy.vh = 0.5f;
			}

			if (move == 4) // 左
			{
				g_Enemy.pos.x -= g_Enemy.vel.x;
				if (GetMapEnter(D3DXVECTOR2(g_Enemy.pos.x - g_Enemy.vel.x, g_Enemy.pos.y),
					D3DXVECTOR2(g_Enemy.w, g_Enemy.h))
					== 1)
				{
					g_Enemy.pos.x += g_Enemy.vel.x;
				}
				g_Enemy.u = 1.0f;
				g_Enemy.v = 0.0f;
				g_Enemy.uh = -0.5f;
				g_Enemy.vh = 0.5f;
			}

			if (move == 0) // 待機
			{
				g_Enemy.u = 0.0f;
				g_Enemy.v = 0.0f;
				g_Enemy.uh = 0.5f;
				g_Enemy.vh = 0.5f;
			}

		}
		
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	if (g_Enemy.use == true)
	{
		PLAYER* player = GetPlayer();

		// 画面内に入っているか
		if (fabsf(g_Enemy.pos.x - player->pos.x) < (VIEW_SCREEN_WIDTH * CHIP_SIZE) &&
			fabsf(g_Enemy.pos.y - player->pos.y) < (VIEW_SCREEN_HEIGHT * CHIP_SIZE))
		{
			//エネミーの位置やテクスチャー座標を反映
			float px = SCREEN_WIDTH / 2 + player->difference.x + (g_Enemy.pos.x - player->pos.x);	// エネミーの表示位置X
			float py = SCREEN_HEIGHT / 2 + player->difference.y + (g_Enemy.pos.y - player->pos.y);	// エネミーの表示位置Y
			float pw = g_Enemy.w;		// エネミーの表示幅
			float ph = g_Enemy.h;		// エネミーの表示高さ
			D3DXCOLOR col;

			if (SerchPlayer(GetPlayerPosition(), g_Enemy.pos))
			{
				col = D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColor(g_EnemyTexture, px, py, pw, ph,
				g_Enemy.u, g_Enemy.v,
				g_Enemy.uh, g_Enemy.vh,
				col);
		}

		
	}
}

//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy;
}


//=============================================================================
// 敵の発生処理
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos)
{
	// もし未使用のデータを探す
	if (g_Enemy.use == false)		// 未使用状態の敵データを見つける
	{
		g_Enemy.use = true;			// 使用状態へ変更する
		g_Enemy.pos = pos;			// 座標をセット
		return;						// 敵をセットできたので終了する
	}
	
}

bool SerchPlayer(D3DXVECTOR2 Playerpos, D3DXVECTOR2 Enemypos)
{
	D3DXVECTOR2 maxRange, minRange;

	minRange.x = Enemypos.x - SERCH_RANGE;
	minRange.y = Enemypos.y - SERCH_RANGE;
	maxRange.x = Enemypos.x + SERCH_RANGE;
	maxRange.y = Enemypos.y + SERCH_RANGE;

	//X軸の判定
	if (minRange.x < Playerpos.x &&
		maxRange.x > Playerpos.x)
	{
		//Y軸の判定
		if (minRange.y < Playerpos.y &&
			maxRange.y > Playerpos.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}