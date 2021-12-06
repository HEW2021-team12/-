//=============================================================================
//
// セレクト画面管理 [select_scene.h]
// Author : 歐
//
//=============================================================================
#ifndef SELECT_SCENE_H_
#define SELECT_SCENE_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define			STAGE_1		0
#define			STAGE_4		3
#define			STAGE_NONE	99

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSelect_Scene(void);
void UninitSelect_Scene(void);
void UpdateSelect_Scene(void);
void DrawSelect_Scene(void);
void ControlSelect(void);
void StageSelect(void);

#endif // SELECT_SCENE_H_


