/*==============================================================================

   マップ管理[map.h]
														 Author :	歐 改造 古市
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef MAP_H_
#define MAP_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//↓は絶対にいじらないこと！
#define VIEW_SCREEN_WIDTH	(16.0f)		// 表示範囲(横)
#define VIEW_SCREEN_HEIGHT	(9.0f)		// 表示範囲(縦)

#define CHIP_SIZE			(60.0f)		// マスの大きさ

// α版マップ
#define MAP_X				(27)		// マップの横のマス数
#define MAP_Y				(22)		// マップの縦のマス数

// それ以降のマップ
#define MAP2_X				()			// 2マップ目
#define MAP2_Y				()			// 2マップ目

#define MAP3_X				()			// 3マップ目
#define MAP3_Y				()			// 3マップ目

#define MAP4_X				()			// 4マップ目
#define MAP4_Y				()			// 4マップ目

#define MAP5_X				()			// 5マップ目
#define MAP5_Y				()			// 5マップ目

//マップ構造体
typedef struct
{
	float		u = 0.0f;
	float		v = 0.0f;
	float		uh = 0.0f;
	float		vh = 0.0f;
}MAP;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMap	(void);
void UninitMap	(void);
void UpdateMap	(void);
void DrawMap	(void);
void ChangeUv   (void);

int GetMapEnter(D3DXVECTOR2 pos);
int GetMap(int x, int y);

#endif //MAP_H_
