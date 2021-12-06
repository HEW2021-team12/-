/*==============================================================================

	キー入力の記録制御 [keylogger.h]
														 Author : Youhei Sato
														 Date   : 2020/7/29
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

// キーロガーキー列挙型
typedef enum KeyloggerKey_tag
{
	KL_FRONT, 
	KL_BACK,
	KL_LEFT,
	KL_RIGHT,
	KL_DOWN,
	KL_UP,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_TURN_UP,
	KL_TURN_DOWN,
	KL_ALT,
	KL_ATTACK,
	KL_DEBUG,
	KL_MAX
}KeyloggerKey;

// キーロガーモジュールの初期化
void Keylogger_Initialize(void);

// キーロガーモジュールの終了処理
void Keylogger_Finalize(void);

// キーロガーモジュールの更新
void Keylogger_Update(void);

// キー入力状態の取得
//
// 引数:
//
// 戻り値:押されていたらtrue
//
bool Keylogger_Press(KeyloggerKey kl);

// キー入力状態の取得（押した瞬間）
//
// 引数:
//
// 戻り値:押した瞬間だったらtrue
//
bool Keylogger_Trigger(KeyloggerKey kl);

// キー入力状態の取得（離した瞬間）
//
// 引数:
//
// 戻り値:離した瞬間だったらtrue
//
bool Keylogger_Release(KeyloggerKey kl);


void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void keylogger_RecordLoad(void);
void keylogger_RecordPlay(void);
bool keylogger_IsRecordPlay(void);

#endif // KEYLOGGER_H