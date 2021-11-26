/*==============================================================================

	ガスゲージ管理 [gas_gauge.h]
	Author :	歐　
	Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef GAS_GAUGE_H_
#define GAS_GAUGE_H_

#include "main.h"
#include "renderer.h"

#endif//GAS_GAUGE_H_

//ガスゲージ構造体
typedef struct
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float gauge_u;
	float gauge_v;
	float gauge_uh;
	float gauge_vh;
}GAS_GAUGE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGasGauge(void);
void UninitGasGauge(void);
void UpdateGasGauge(void);
void DrawGasGauge(void);