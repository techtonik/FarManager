/*
keyboard.cpp

�������, ������� ��������� � ���������

*/

/* Revision: 1.80 18.09.2002 $ */

/*
Modify:
  18.09.2002 VVM
    + SheckForEscSilent() - ��������� �� ESC ���� ������ �������� ������������
    + CinfirmAbortOp()    - �������� � ������������ ������������� ����������
    ! �������������� CheckForEsc() ������ ������� �� ���� ���� �������
  16.09.2002 SVS
    - "��� ���������� ������ � ��������� ����� ��� ���� ����������� ��
       ��������� - ���������, ������?"
  21.08.2002 SVS
    ! WaitKey ������ ���������� ��� ������� �������
  19.08.2002 SVS
    + ��� SKV "����� KEY_CTRL ���� ����� IsShiftKey" :)
      (��� ���������� � "BugZ#579 - ����������� ���������")
  17.08.2002 SVS
    - ������ � Alt-Digit + NumLock=On ��� ���������.
    - � ������ ������� �� Gray-Del ������ �������� � ������� Del, ����������
      �� ��������� NumLock (��� ���������� NumLock ������� '.', �� �� �
      ������ ����).
    - �������-�� ������ ������ �����������, ����������� ����� - ������
      �������� ����������� Shift � ������� ��� ������� ��������� �����������
      ������... � �.�. � NT... - ��.. "��� ������ ������ �������, ������" ;-)
  23.07.2002 SKV
    + ����� KEY_ALT ���� ����� IsShiftKey :)
  30.05.2002 SVS
    ! ��������������� ���� ��� USE_WFUNC_IN - ���� ������ ������������
      (���� �� ���������� :-))
  24.05.2002 SVS
    ! ��������� Numpad.
    ! ���������� ��������, ����� ��� ������ ������� � �������������
      �������� ���������� ������� � KEY_EVENT ��� ��������������� �������
      ��������� (�� ���� Autowrap � ��� �������� - �������� �� ������
      ���������)
  16.05.2002 SVS
    - ����� � ����� (����.����). ����������� �� ������ ������
      (����� � �� �������, �.�. �� LeftAlt �� ���� ��������� �������)
    ! USE_WFUNC -> USE_WFUNC_IN, �.�. ��� ������ ������ �������
      �.�. ����� �� ����� - ��� ����, � ��� ���� - ������ ������!
      ���� � ������� ����� ����� ����, �� ����� ������ ������.
  15.05.2002 SVS
    ! ��������� � WriteInput (�������� ��� Key > 255 :-)
    + � ����������� ����... ������� Ctrl-keys �... ���� ���� ����� ������ ��
      ����������, ����� ������ � ������� VK_F16
  14.05.2002 VVM
    - ���� ������ ������ ����, �� ���������� ��� ������� EventType;
  05.04.2002 SVS
    + Prev?ButtonPressed
  01.04.2002 SVS
    ! ������ KEY_FOCUS_CHANGED ������� KEY_KILLFOCUS � KEY_GOTFOCUS.
  19.03.2002 SVS
    - BugZ#364 - alt+break
  12.03.2002 VVM
    + ����������� ������� AbortMessage()
  20.02.2002 OT
    - BugZ#314 - Shift-Enter �� ����� ������ ���� ��������� ����
  14.02.2002 VVM
    ! UpdateIfChanged ��������� �� ������� Force, � �������� �� UIC_*
  05.02.2002 SVS
    ! ��������������� ���� - ��� �������
    + SpecKeyName - �������� ������ ��� ������� (SysLog)
  04.02.2002 SVS
    + IsNavKey(), IsShiftKey()
  29.01.2002 SVS
    - ���� �������� ���������� ��������� ��������� ������� (��������,
      ������ �������� ������������)
  10.01.2002 SVS
    ! ����� ������� Opt.HotkeyRules ��� Alt-�����
  27.12.2001 KM
    ! ������� KeyText � KeyToText (��� � ���� ������), � ��������� ������
      � ������ ������� ����������� �����!
  26.12.2001 SVS
    ! ��� �������� ���� "�� ������"... ������ ������������!
  25.12.2001 SVS
    ! � ������ WaitInMainLoop=1 Alt-������ � Alt-Shift-������ ����������� ���
      ���� (����� ��������� ������� FastFind). � ��������� ������� - �����
      ���.�������� ���� �������.
    ! ������� �����������
  21.12.2001 SVS
    + DOUBLE_CLICK as Macro
  08.12.2001 SVS
    - ���� � KeyNameToKey() - ��������, ��� "ShiftFooBar" ������ KEY_SHIFT,
      ������� ����� ��������� Pos � Len, �.�. � ���������� �������� ������
      ���� Pos == Len
  26.11.2001 SVS
    + MouseEventFlags, PreMouseEventFlags - ���� ������� ����
  20.11.2001 SVS
    ! � ��������� FOCUS_EVENT ������� ����� ��������� LButtonPressed,
      RButtonPressed � MButtonPressed
  15.11.2001 SVS
    - BugZ#66 - ����� ��������� ������ ����� �������� AltF9
      ������� ������� Sleep(1) ����������� �� ����...
  24.10.2001 SVS
    ! CheckForEsc() - ������� Esc � ������� ����������� ������� ������ Yes
      ���� - ���������� Alt-F9 � ����������.
  21.10.2001 SVS
    + PrevScrX,PrevScrY - ���������� ������� ������� (��� ����������������
      ��������)
  15.10.2001 SVS
    + _KEYMACRO()
  11.10.2001 SVS
    - BugZ#79. ����������� �������������� ���� ������ � ���� (��� ������� �
      ��������� �������� ������)
  20.09.2001 SVS
    - ���� � Alt-�������� �������.
    ! �������� � InputRecordToKey "const"
  18.09.2001 SVS
    ! �������� ������� "...������ ���� ��� ������� ��������� �����������..."
  14.09.2001 SVS
    - ���� � TranslateKeyToVK() - ������� ������������� ���� ��� Shift-������
    ! ������ ���� ��� ������� ��������� ����������� ��������� INPUT_RECORD
      � ������� GetInputRecord()
  30.08.2001 IS
    ! ��� �������������� �������� ���� �������� ����� ���� ��� ��, ��� � ���
      ������� �� F10 � �������, ������ �� ����������� ������������� ��������,
      ���� ��� ��������.
  24.07.2001 SVS
    ! ���� ���� KEY_CTRLALTSHIFTRELEASE, �� ����� ������ (!)
  23.07.2001 SVS
    - �� �������� ���������� Alt (�� ��������, � ������) sp_
      (�� ��������� ����� ������������� ��� ������� Alt)
  01.07.2001 KM
    - ��� ���������� Shift-Enter � ������� ����������
      ������� Shift ����� ���������� ������.
  28.06.2001 SVS
    - ��� Win9x ��� ������� NumLock � ������ ��������� ������
      �������� � ������� ���������� �����������.
  25.06.2001 IS
    ! ��������� const
  23.06.2001 OT
    - far -r
  21.06.2001 SVS
    ! ������� ������� WriteSequenceInput() �� �������������
  14.06.2001 OT
    ! "����" ;-)
  08.06.2001 SVS
    ! ����������� �������� (����) � ����������� ���� ��� ������� ���������
      PE ����������!
    ! ENABLE_MOUSE_INPUT -> ENABLE_WINDOW_INPUT � ������ ER ;-)
  06.06.2001 SVS
    ! ��������� � ������� WriteInput - ������ wVirtualScanCode
      ��������� �������������.
    ! W-������� ����� ���� ������ � ������ USE_WFUNC
  06.06.2001 SVS
    ! ��������� � ������� TranslateKeyToVK - ������ wVirtualScanCode
      ��������� �������������.
  23.05.2001 SVS
    ! ������ �� Alt+Shift+�����
  17.05.2001 OT
    + ��� ��������� ������� ������� ������� KEY_CONSOLE_BUFFER_RESIZE.
  07.05.2001 SVS
    ! SysLog(); -> _D(SysLog());
  07.05.2001 SVS
    - ��� ������� ������ Alt-Shift-'-' �� �������� ����� ������, ������������
      � '_', � �������� � '-'. ������ �������� ���������.
  06.05.2001 DJ
    ! �������� #include
  06.05.2001 ��
    ! �������������� Window � Frame :)
  05.05.2001 DJ
    + �������� NWZ
  29.04.2001 ��
    + ��������� NWZ �� ����������
  28.04.2001 vvm
    + KEY_FOCUS_CHANGED ��� ���������� �������.
  27.04.2001 SVS
    + ���������:
       "MsWheelDown" ��� KEY_MSWHEEL_DOWN �
       "MsWheelUp" ��� KEY_MSWHEEL_UP
      � ������ FKeys1[]
    ! �� ���� ������ �������� ������� ��� ��������� ������, ��-�� ����
      ������ ���� ������������ � �������� ����� ����� "ShiftMsWheelUp"
  26.04.2001 VVM
    - ������� ����� MouseWheeled
    + ��������� ���������� KEY_MSWHEEL_XXXX
  24.04.2001 SVS
    + MouseWheeled - ������� ����, ��� ��������� ������.
  16.04.2001 VVM
    + ��������� � ������ ����������� �� PgUp/PgDn
    + Opt.MouseWheelDelta - ������ �������� ��� ���������. ������� ��� �������� UP/DOWN
  13.04.2001 VVM
    + ��������� �������� ����� ��� 2000.
  12.03.2001 SVS
    ! � ��������� ���������� ��������� - ��������...
  07.03.2001 SVS
    ! ��������� ��������� - ����� ���� � ��������� (��� �������� �� ����� ����
      � �� ��� ����� �������� - ���� �� ����, �� Shift-F4 Shift-Enter, ��
      �������� Shift - �������� ��������� :-)
  28.02.2001 IS
    ! "CtrlObject->CmdLine." -> "CtrlObject->CmdLine->"
  25.02.2001 SVS
    ! ��������� ��� Alt-Shift-...
  09.02.2001 IS
    + ������������� ������� Esc � CheckForEsc (�����������)
  06.02.2001 SVS
    - ���... :-)
      ���������� � ������� "�����������" Divide & Multiple �� �������� �����.
  05.02.2001 SVS
    - ����� ��� �������... :-( ��� ������������ � Upper.
  01.02.2001 SVS
    - ���� - ������� ������������ ��� ������� :-(
  01.02.2001 SVS
    - �������� �������������� ������ � VK_* � ������� TranslateKeyToVK()
      ��-�� ���� �� ����������� ENTER, etc � ��������.
    - �� �������������� ���������� Alt-Shift-* � Alt-Shift-? ��� �������
      ������ � �������.
  28.01.2001 SVS
    ! ����� ���... WriteInput (� ������ ������ �� VK_F16)
  24.01.2001 SVS
    ! ������ ���� ���������� WriteInput
  23.01.2001 SVS
    ! CalcKeyCode - �������������� �������� - �������� �� �������.
    ! ���������� ������� �������� ��� �������� "�� ������������ �������"
  21.01.2001 SVS
    ! ��������� � WriteInput!
    ! WriteInput ������ ���������� ��������� � ���� FALASE/TRUE.
    + WriteSequenceInput
  17.01.2001 SVS
    + Opt.ShiftsKeyRules - ������� �� ���� ������ ��������� ����������
      Alt-����� ��� ����������� �������
  09.01.2001 SVS
    ! ������ ������ ���� ������ Alt-Number-�����
  05.01.2001 SVS
    - � ����� CalcKeyCode - �� ������� Alt-Ins
  05.01.2001 SVS
    - ���� � "�����������" ������ :-(
  04.01.2001 SVS
    + ��������� ���������� ������������� ������...
    + TranslateKeyToVK
  26.12.2000 SVS
    + ����� KeyMacroToText() (������� ���������� � macro.cpp)
  22.12.2000 SVS
    + ��������� � �������� ���������������� ������, ����� ���� ����� �����
      ����� ��������� �������������������� �������� :-)
*/

#include "headers.hpp"
#pragma hdrstop

#include "keys.hpp"
#include "farqueue.hpp"
#include "global.hpp"
#include "fn.hpp"
#include "plugin.hpp"
#include "lang.hpp"
#include "ctrlobj.hpp"
#include "filepanels.hpp"
#include "panel.hpp"
#include "cmdline.hpp"
#include "grabber.hpp"
#include "manager.hpp"
#include "scrbuf.hpp"
#include "savescr.hpp"

static unsigned int AltValue=0;
static int ReturnAltValue,KeyCodeForALT_LastPressed=0;
static int ShiftPressedLast=FALSE,AltPressedLast=FALSE,CtrlPressedLast=FALSE;
static int RightAltPressedLast=FALSE,RightCtrlPressedLast=FALSE;
#if defined(MOUSEKEY)
static int PrePreMouseEventFlags;
#endif
static BOOL IsKeyCASPressed=FALSE; // CtrlAltShift - ������ ��� ���?
static clock_t PressedLastTime,KeyPressedLastTime;
static int ShiftState=0;

/* ----------------------------------------------------------------- */
static struct TTable_KeyToVK{
  int Key;
  int VK;
} Table_KeyToVK[]={
//   {KEY_PGUP,          VK_PRIOR},
//   {KEY_PGDN,          VK_NEXT},
//   {KEY_END,           VK_END},
//   {KEY_HOME,          VK_HOME},
//   {KEY_LEFT,          VK_LEFT},
//   {KEY_UP,            VK_UP},
//   {KEY_RIGHT,         VK_RIGHT},
//   {KEY_DOWN,          VK_DOWN},
//   {KEY_INS,           VK_INSERT},
//   {KEY_DEL,           VK_DELETE},
//   {KEY_LWIN,          VK_LWIN},
//   {KEY_RWIN,          VK_RWIN},
//   {KEY_APPS,          VK_APPS},
//   {KEY_MULTIPLY,      VK_MULTIPLY},
//   {KEY_ADD,           VK_ADD},
//   {KEY_SUBTRACT,      VK_SUBTRACT},
//   {KEY_DIVIDE,        VK_DIVIDE},
//   {KEY_F1,            VK_F1},
//   {KEY_F2,            VK_F2},
//   {KEY_F3,            VK_F3},
//   {KEY_F4,            VK_F4},
//   {KEY_F5,            VK_F5},
//   {KEY_F6,            VK_F6},
//   {KEY_F7,            VK_F7},
//   {KEY_F8,            VK_F8},
//   {KEY_F9,            VK_F9},
//   {KEY_F10,           VK_F10},
//   {KEY_F11,           VK_F11},
//   {KEY_F12,           VK_F12},
   {KEY_BREAK,         VK_CANCEL},
   {KEY_BS,            VK_BACK},
   {KEY_TAB,           VK_TAB},
   {KEY_ENTER,         VK_RETURN},
   {KEY_ESC,           VK_ESCAPE},
   {KEY_SPACE,         VK_SPACE},
   {KEY_NUMPAD5,       VK_CLEAR},
};


struct TFKey3{
  DWORD Key;
  int   Len;
  char *Name;
};

static struct TFKey3 FKeys1[]={
  { KEY_CTRLALTSHIFTRELEASE, 19, "CtrlAltShiftRelease"},
  { KEY_CTRLALTSHIFTPRESS,   17, "CtrlAltShiftPress"},
#if defined(MOUSEKEY)
  { KEY_MSLDBLCLICK,         11, "MsLDblClick"},
  { KEY_MSRDBLCLICK,         11, "MsRDblClick"},
#endif
  { KEY_MSWHEEL_DOWN,        11, "MsWheelDown"},
  { KEY_MSWHEEL_UP,           9, "MsWheelUp"},
  { KEY_BACKSLASH,            9, "BackSlash"},
  { KEY_SUBTRACT,             8, "Subtract"},
  { KEY_MULTIPLY,             8, "Multiply"},
  { KEY_DIVIDE,               6, "Divide"},
  { KEY_BREAK,                5, "Break"},
  { KEY_CLEAR,                5, "Clear"},
  //{ KEY_NUMPAD5,              5, "Clear"},
  { KEY_RIGHT,                5, "Right"},
  { KEY_ENTER,                5, "Enter"},
  { KEY_SPACE,                5, "Space"},
  { KEY_PGUP,                 4, "PgUp"},
  { KEY_HOME,                 4, "Home"},
  { KEY_LEFT,                 4, "Left"},
  { KEY_DOWN,                 4, "Down"},
  { KEY_PGDN,                 4, "PgDn"},
  { KEY_APPS,                 4, "Apps"},
  { KEY_LWIN,                 4 ,"LWin"},
  { KEY_NUMPAD0,              4 ,"Num0"},
  { KEY_NUMPAD1,              4 ,"Num1"},
  { KEY_NUMPAD2,              4 ,"Num2"},
  { KEY_NUMPAD3,              4 ,"Num3"},
  { KEY_NUMPAD4,              4 ,"Num4"},
  { KEY_NUMPAD5,              4, "Num5"},
  { KEY_NUMPAD6,              4 ,"Num6"},
  { KEY_NUMPAD7,              4 ,"Num7"},
  { KEY_NUMPAD8,              4 ,"Num8"},
  { KEY_NUMPAD9,              4 ,"Num9"},
  { KEY_RWIN,                 4 ,"RWin"},
  { KEY_END,                  3, "End"},
  { KEY_INS,                  3, "Ins"},
  { KEY_DEL,                  3, "Del"},
  { KEY_ADD,                  3, "Add"},
  { KEY_F10,                  3, "F10"},
  { KEY_F11,                  3, "F11"},
  { KEY_F12,                  3, "F12"},
  { KEY_TAB,                  3, "Tab"},
  { KEY_ESC,                  3, "Esc"},
  { KEY_F1,                   2, "F1"},
  { KEY_F2,                   2, "F2"},
  { KEY_F3,                   2, "F3"},
  { KEY_F4,                   2, "F4"},
  { KEY_F5,                   2, "F5"},
  { KEY_F6,                   2, "F6"},
  { KEY_F7,                   2, "F7"},
  { KEY_F8,                   2, "F8"},
  { KEY_F9,                   2, "F9"},
  { KEY_UP,                   2, "Up"},
  { KEY_BS,                   2, "BS"},
  { KEY_BRACKET,              1, "["},
  { KEY_BACKBRACKET,          1, "]"},
  { KEY_COMMA,                1, ","},
  { KEY_QUOTE,                1, "\""},
  { KEY_COLON,                1, ":"},
  { KEY_DOT,                  1, "."},
  { KEY_SLASH,                1, "/"},
};

static struct TFKey3 ModifKeyName[]={
  { KEY_CTRL   ,4 ,"Ctrl"},
  { KEY_RCTRL  ,5 ,"RCtrl"},
  { KEY_ALT    ,3 ,"Alt"},
  { KEY_RALT   ,4 ,"RAlt"},
  { KEY_SHIFT  ,5 ,"Shift"},
//  { KEY_LCTRL  ,5 ,"LCtrl"},
//  { KEY_LALT   ,4 ,"LAlt"},
//  { KEY_LSHIFT ,6 ,"LShift"},
//  { KEY_RSHIFT ,6 ,"RShift"},
};

#if defined(SYSLOG)
static struct TFKey3 SpecKeyName[]={
  { KEY_CONSOLE_BUFFER_RESIZE,19, "ConsoleBufferResize"},
  { KEY_LOCKSCREEN           ,10, "LockScreen"},
  { KEY_KILLFOCUS             ,9, "KillFocus"},
  { KEY_GOTFOCUS              ,8, "GotFocus"},
  { KEY_DRAGCOPY             , 8, "DragCopy"},
  { KEY_DRAGMOVE             , 8, "DragMove"},
  { KEY_NONE                 , 4, "None"},
  { KEY_IDLE                 , 4, "Idle"},
};
#endif

/* ----------------------------------------------------------------- */

/* tran 31.08.2000 $
  FarInputRecordToKey */
int WINAPI InputRecordToKey(const INPUT_RECORD *r)
{
  if(r)
  {
    INPUT_RECORD Rec=*r; // ����!, �.�. ������ CalcKeyCode
                         //   ��������� INPUT_RECORD ��������������!
    return CalcKeyCode(&Rec,TRUE);
  }
  return KEY_NONE;
}
/* tran 31.08.2000 $ */


int IsMouseButtonPressed()
{
  INPUT_RECORD rec;
  if (PeekInputRecord(&rec))
    GetInputRecord(&rec);
  Sleep(20);
  if (LButtonPressed)
    return(1);
  if (RButtonPressed)
    return(2);
  /* $ 23.08.2000 SVS
     + ������������� - ��� ������� ������� ����
  */
  if(MButtonPressed)
    return(3);
  /* SVS $ */
  return(0);
}

int GetInputRecord(INPUT_RECORD *rec)
{
  static int LastEventIdle=FALSE;
  DWORD ReadCount;
  DWORD LoopCount=0,CalcKey;
  DWORD ReadKey=0;
  int NotMacros=FALSE;

  if (CtrlObject!=NULL)
  {
     _KEYMACRO(CleverSysLog SL("GetInputRecord()"));
    int VirtKey,ControlState;
    int MacroKey=CtrlObject->Macro.GetKey();
    if (MacroKey)
    {
      ScrBuf.Flush();
      TranslateKeyToVK(MacroKey,VirtKey,ControlState,rec);
      rec->EventType=0;
      _KEYMACRO(SysLog("MacroKey1 =%s",_FARKEY_ToName(MacroKey)));
//      memset(rec,0,sizeof(*rec));
      return(MacroKey);
    }
    if (CtrlObject->Cp()&&CtrlObject->Cp()->ActivePanel&&!CmdMode)
      CtrlObject->Macro.RunStartMacro();
    MacroKey=CtrlObject->Macro.GetKey();
    if (MacroKey)
    {
      ScrBuf.Flush();
      TranslateKeyToVK(MacroKey,VirtKey,ControlState,rec);
      rec->EventType=0;
      _KEYMACRO(SysLog("MacroKey2 =%s",_FARKEY_ToName(MacroKey)));
//      memset(rec,0,sizeof(*rec));
      return(MacroKey);
    }
  }

  if(KeyQueue && KeyQueue->Peek())
  {
    CalcKey=KeyQueue->Get();
    NotMacros=CalcKey&0x80000000?1:0;
    CalcKey&=~0x80000000;
    if (!NotMacros)
    {
      if (CtrlObject!=NULL && CtrlObject->Macro.ProcessKey(CalcKey))
        CalcKey=KEY_NONE;
    }
    return(CalcKey);
  }

  int EnableShowTime=Opt.Clock && (WaitInMainLoop || CtrlObject!=NULL &&
                     CtrlObject->Macro.GetMode()==MACRO_SEARCH);

  if (EnableShowTime)
    ShowTime(1);

  ScrBuf.Flush();

  if (!LastEventIdle)
    StartIdleTime=clock();
  LastEventIdle=FALSE;
  SetFarConsoleMode();
  while (1)
  {
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
      PeekConsoleInputW(hConInp,rec,1,&ReadCount);
    else
      PeekConsoleInputA(hConInp,rec,1,&ReadCount);
#else
    PeekConsoleInput(hConInp,rec,1,&ReadCount);
#endif
    /* $ 26.04.2001 VVM
       ! ����� ������� �������� */
    if (ReadCount!=0)
    {
      // � ������ ���� ����� ��� �������� � ������������ ���������� ��������� ;-(
      // ��� ����� ����� ������ � ������� ���������� ����� - ��������� �� �������� - � ��� ��������
      // ... ����� ��������� � ������� ��������� ����� ������������
      if(rec->EventType==KEY_EVENT && IsProcessAssignMacroKey)
      {
        if(rec->Event.KeyEvent.wVirtualKeyCode == VK_SHIFT)
        {
          if(rec->Event.KeyEvent.dwControlKeyState&ENHANCED_KEY)
          {
            /*
            Left Right ��������� ����������� �������
            MustDie:
            Dn, 1, Vk=0x0025, Scan=0x004B Ctrl=0x00000120 (casa - cEcN)
            Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000130 (caSa - cEcN)
                          ^^                          ^            ^ !!! ��� ����� � �������� ;-)
            Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000120 (casa - cEcN)
            Up, 1, Vk=0x0025, Scan=0x004B Ctrl=0x00000120 (casa - cEcN)
            Dn, 1, Vk=0x0027, Scan=0x004D Ctrl=0x00000120 (casa - cEcN)
            Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000130 (caSa - cEcN)
            Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000120 (casa - cEcN)
            Up, 1, Vk=0x0027, Scan=0x004D Ctrl=0x00000120 (casa - cEcN)
            --------------------------------------------------------------
            NT:
            Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
            Dn, 1, Vk=0x0025, Scan=0x004B Ctrl=0x00000130 (caSa - cEcN)
            Up, 1, Vk=0x0025, Scan=0x004B Ctrl=0x00000130 (caSa - cEcN)
            Dn, 1, Vk=0x0027, Scan=0x004D Ctrl=0x00000130 (caSa - cEcN)
            Up, 1, Vk=0x0027, Scan=0x004D Ctrl=0x00000130 (caSa - cEcN)
            Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000020 (casa - cecN)
            */
            INPUT_RECORD pinp;
            DWORD nread;
            ReadConsoleInput(hConInp, &pinp, 1, &nread);
            continue;
          }

          /* ��������� �����, �.�.
          NumLock=ON Shift-Numpad1
             Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
             Dn, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
             Up, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
          >>>Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
             Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000020 (casa - cecN)
          ����� ��������� ������ ����
          */
          if(rec->Event.KeyEvent.bKeyDown)
          {
            if(!ShiftState)
              ShiftState=TRUE;
            else // ����� ������ �� �������... ���� ����� ������ ����
            {
              INPUT_RECORD pinp;
              DWORD nread;
              ReadConsoleInput(hConInp, &pinp, 1, &nread);
              continue;
            }
          }
          else if(!rec->Event.KeyEvent.bKeyDown)
            ShiftState=FALSE;
        }

        if((rec->Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED) == 0 && ShiftState)
          rec->Event.KeyEvent.dwControlKeyState|=SHIFT_PRESSED;
      }

#if 0
      if(rec->EventType==KEY_EVENT)
      {
        // ����� ���������� ���������� ������ �������
        DWORD ReadCount2;
        GetNumberOfConsoleInputEvents(hConInp,&ReadCount2);
        // ���� �� ���������� �����, �� ���������� ��� �� ������� KEY_EVENT
        if(ReadCount2 > 1)
        {
          INPUT_RECORD *TmpRec=(INPUT_RECORD*)malloc(sizeof(INPUT_RECORD)*ReadCount2);
          if(TmpRec)
          {
            DWORD ReadCount3;
            INPUT_RECORD TmpRec2;
            int I;

            #if defined(USE_WFUNC_IN)
            if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
              PeekConsoleInputW(hConInp,TmpRec,ReadCount2,&ReadCount3);
            else
              PeekConsoleInputA(hConInp,TmpRec,ReadCount2,&ReadCount3);
            #else
            PeekConsoleInput(hConInp,TmpRec,ReadCount2,&ReadCount3);
            #endif
            for(I=0; I < ReadCount2; ++I)
            {
              if(TmpRec[I].EventType!=KEY_EVENT)
                break;

              // ������� �� �������
              #if defined(USE_WFUNC_IN)
              if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
                ReadConsoleInputW(hConInp,&TmpRec2,1,&ReadCount3);
              else
                ReadConsoleInputA(hConInp,&TmpRec2,1,&ReadCount3);
              #else
              ReadConsoleInput(hConInp,&TmpRec2,1,&ReadCount3);
              #endif

              if(TmpRec[I].Event.KeyEvent.bKeyDown==1)
              {
                if (TmpRec[I].Event.KeyEvent.uChar.AsciiChar != 0)
                  WriteInput(TmpRec[I].Event.KeyEvent.uChar.AsciiChar,0);
              }
              else if(TmpRec[I].Event.KeyEvent.wVirtualKeyCode==0x12)
              {
                if (TmpRec[I].Event.KeyEvent.uChar.AsciiChar != 0)
                  WriteInput(TmpRec[I].Event.KeyEvent.uChar.AsciiChar,0);
              }
            }
            // ��������� ������
            free(TmpRec);
            return KEY_NONE;
          }
        }
      }
#endif

      _SVS(if(rec->EventType==KEY_EVENT))
        _SVS(SysLog("-- %s",_INPUT_RECORD_Dump(rec)));
#if defined(USE_WFUNC_IN)
      WCHAR UnicodeChar=rec->Event.KeyEvent.uChar.UnicodeChar;
      if((UnicodeChar&0xFF00) && WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
        //_SVS(if(rec->EventType==KEY_EVENT)SysLog(">GetInputRecord= %s",_INPUT_RECORD_Dump(rec)));
        rec->Event.KeyEvent.uChar.UnicodeChar=0;
        UnicodeToAscii(&UnicodeChar,&rec->Event.KeyEvent.uChar.AsciiChar,sizeof(WCHAR));
        CharToOemBuff(&rec->Event.KeyEvent.uChar.AsciiChar,&rec->Event.KeyEvent.uChar.AsciiChar,1);
        //_SVS(if(rec->EventType==KEY_EVENT)SysLog("<GetInputRecord= %s",_INPUT_RECORD_Dump(rec)));
      }
#endif
      break;
    }
    /* VVM $ */

    ScrBuf.Flush();

    Sleep(15);
    // ��������� �������� �������� ������������ ����
    if(Opt.Mouse) // � ����� �� ��� �������???
      SetFarConsoleMode();

    if (CloseFAR)
    {
//      CloseFAR=FALSE;
      /* $ 30.08.2001 IS
         ��� �������������� �������� ���� �������� ����� ���� ��� ��, ��� � ���
         ������� �� F10 � �������, ������ �� ����������� ������������� ��������,
         ���� ��� ��������.
      */
      if(!Opt.CloseConsoleRule)
        FrameManager->IsAnyFrameModified(TRUE);
      else
        FrameManager->ExitMainLoop(FALSE);
      return KEY_NONE;
      /* IS $ */
    }

    if ((LoopCount & 15)==0)
    {
      clock_t CurTime=clock();
      clock_t TimeAfterExec=CurTime-StartExecTime;
      if (EnableShowTime)
        ShowTime(0);
      if (WaitInMainLoop)
      {
        if (Opt.InactivityExit && Opt.InactivityExitTime>0 &&
            CurTime-StartIdleTime>Opt.InactivityExitTime*60000 &&
            FrameManager->GetFrameCount()==1)
        {
          FrameManager->ExitMainLoop(FALSE);
          return(KEY_NONE);
        }
        if ((LoopCount & 63)==0)
        {
          static int Reenter=0;
          if (!Reenter)
          {
            Reenter++;
            int X,Y;
            GetRealCursorPos(X,Y);
            if (X==0 && Y==ScrY && CtrlObject->CmdLine->IsVisible())
            {
              while (1)
              {
                INPUT_RECORD tmprec;
                int Key=GetInputRecord(&tmprec);
                if ((DWORD)Key==KEY_NONE || (DWORD)Key!=KEY_SHIFT && tmprec.Event.KeyEvent.bKeyDown)
                  break;
              }
              CtrlObject->Cp()->SetScreenPosition();
              ScrBuf.ResetShadow();
              ScrBuf.Flush();
            }
            Reenter--;
          }
          static int UpdateReenter=0;
          if (!UpdateReenter && CurTime-KeyPressedLastTime>700)
          {
            UpdateReenter=TRUE;
            CtrlObject->Cp()->LeftPanel->UpdateIfChanged(UIC_UPDATE_NORMAL);
            CtrlObject->Cp()->RightPanel->UpdateIfChanged(UIC_UPDATE_NORMAL);
            UpdateReenter=FALSE;
          }
        }
      }
      if (StartExecTime!=0 && TimeAfterExec>2000)
      {
        StartExecTime=0;
        if (!IsWindowed() && !Opt.Mouse)
        {
          SetConsoleMode(hConInp,ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT);
          SetConsoleMode(hConInp,ENABLE_WINDOW_INPUT);
        }
        SetFarTitle(NULL);//LastFarTitle);
      }
      if (Opt.ScreenSaver && Opt.ScreenSaverTime>0 &&
          CurTime-StartIdleTime>Opt.ScreenSaverTime*60000)
        if (!ScreenSaver(WaitInMainLoop))
          return(KEY_NONE);
      if (!WaitInMainLoop && LoopCount==64)
      {
        LastEventIdle=TRUE;
        memset(rec,0,sizeof(*rec));
        rec->EventType=KEY_EVENT;
        return(KEY_IDLE);
      }
    }
    LoopCount++;
  } // while (1)

  clock_t CurClock=clock();

  if (rec->EventType==FOCUS_EVENT)
  {
    /* $ 28.04.2001 VVM
      + �� ������ ���������� ���� ����� ������, �� � ��������� ������ */
    ShiftPressed=ShiftPressedLast=FALSE;
    CtrlPressed=CtrlPressedLast=RightCtrlPressedLast=FALSE;
    AltPressed=AltPressedLast=RightAltPressedLast=FALSE;
    LButtonPressed=RButtonPressed=MButtonPressed=FALSE;
    ShiftState=FALSE;
    PressedLastTime=0;
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
      ReadConsoleInputW(hConInp,rec,1,&ReadCount);
      WCHAR UnicodeChar=rec->Event.KeyEvent.uChar.UnicodeChar;
      if((UnicodeChar&0xFF00))
      {
        rec->Event.KeyEvent.uChar.UnicodeChar=0;
        UnicodeToAscii(&UnicodeChar,&rec->Event.KeyEvent.uChar.AsciiChar,sizeof(WCHAR));
        CharToOemBuff(&rec->Event.KeyEvent.uChar.AsciiChar,&rec->Event.KeyEvent.uChar.AsciiChar,1);
      }
    }
    else
      ReadConsoleInputA(hConInp,rec,1,&ReadCount);
#else
    ReadConsoleInput(hConInp,rec,1,&ReadCount);
#endif
    CalcKey=rec->Event.FocusEvent.bSetFocus?KEY_GOTFOCUS:KEY_KILLFOCUS;
    memset(rec,0,sizeof(*rec)); // ����� � ProcessEditorInput ����� ���� �������� - ������ ����� ����������
    rec->EventType=KEY_EVENT;
    return CalcKey;
    /* VVM $ */
  }

  if (rec->EventType==KEY_EVENT)
  {
    /* ��������� �����, �.�.
    NumLock=ON Shift-Numpad1
       Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
       Dn, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
       Up, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
    >>>Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
       Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000020 (casa - cecN)
    ����� ��������� ������ ����
    */
/*
    if(rec->Event.KeyEvent.wVirtualKeyCode == VK_SHIFT)
    {
      if(rec->Event.KeyEvent.bKeyDown)
      {
        if(!ShiftState)
          ShiftState=TRUE;
        else // ����� ������ �� �������... ���� ����� ������ ����
        {
          INPUT_RECORD pinp;
          DWORD nread;
          ReadConsoleInput(hConInp, &pinp, 1, &nread);
          return KEY_NONE;
        }
      }
      else if(!rec->Event.KeyEvent.bKeyDown)
        ShiftState=FALSE;
    }

    if((rec->Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED) == 0 && ShiftState)
      rec->Event.KeyEvent.dwControlKeyState|=SHIFT_PRESSED;
*/
    //_SVS(if(rec->EventType==KEY_EVENT)SysLog("%s",_INPUT_RECORD_Dump(rec)));

    DWORD CtrlState=rec->Event.KeyEvent.dwControlKeyState;

    /* $ 28.06.2001 SVS
       ��� Win9x ��� ������� NumLock � ������ ��������� ������
       �������� � ������� ���������� �����������.
    */
    if(CtrlObject && CtrlObject->Macro.IsRecording())
    {
      static WORD PrevVKKeyCode=0; // NumLock+Cursor
      WORD PrevVKKeyCode2=PrevVKKeyCode;
      PrevVKKeyCode=rec->Event.KeyEvent.wVirtualKeyCode;

      if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS &&
        (CtrlState&NUMLOCK_ON))
      {
        if((PrevVKKeyCode2 >= 0x21 && PrevVKKeyCode2 <= 0x28 ||
            PrevVKKeyCode2 >= 0x2D && PrevVKKeyCode2 <= 0x2E) &&
           PrevVKKeyCode == VK_SHIFT && rec->Event.KeyEvent.bKeyDown
           ||
           (PrevVKKeyCode >= 0x21 && PrevVKKeyCode <= 0x28 ||
            PrevVKKeyCode >= 0x2D && PrevVKKeyCode <= 0x2E) &&
           PrevVKKeyCode2 == VK_SHIFT && !rec->Event.KeyEvent.bKeyDown
          )
        {
          if(PrevVKKeyCode2 != VK_SHIFT)
          {
            INPUT_RECORD pinp;
            DWORD nread;
            // ������ �� �������...
            ReadConsoleInput(hConInp, &pinp, 1, &nread);
            return KEY_NONE;
          }
        }
      }
      /* 1.07.2001 KM
        ��� ���������� Shift-Enter � ������� ����������
        ������� Shift ����� ���������� ������.
      */
      if((PrevVKKeyCode2==VK_SHIFT && PrevVKKeyCode==VK_RETURN &&
          rec->Event.KeyEvent.bKeyDown) ||
          (PrevVKKeyCode2==VK_RETURN && PrevVKKeyCode==VK_SHIFT &&
          !rec->Event.KeyEvent.bKeyDown))
      {
        if(PrevVKKeyCode2 != VK_SHIFT)
        {
          INPUT_RECORD pinp;
          DWORD nread;
          // ������ �� �������...
          ReadConsoleInput(hConInp, &pinp, 1, &nread);
          return KEY_NONE;
        }
      }
      /* KM $ */
    }
    /* SVS $ */

    if (AltPressed && (CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED))==0)
      DetectWindowedMode();
    CtrlPressed=(CtrlState & (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED));
    AltPressed=(CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED));
    ShiftPressed=(CtrlState & SHIFT_PRESSED);
    KeyPressedLastTime=CurClock;
    /* $ 24.08.2000 SVS
       + ���������� �� ������� KEY_CTRLALTSHIFTRELEASE
    */
    if(IsKeyCASPressed && (!CtrlPressed || !AltPressed || !ShiftPressed))
    {
      IsKeyCASPressed=FALSE;
      return(KEY_CTRLALTSHIFTRELEASE);
    }
    /* SVS $ */
  }

  ReturnAltValue=FALSE;
  CalcKey=CalcKeyCode(rec,TRUE,&NotMacros);
//_SVS(SysLog("1) CalcKey=%s",_FARKEY_ToName(CalcKey)));
  if (ReturnAltValue && !NotMacros)
  {
    if (CtrlObject!=NULL && CtrlObject->Macro.ProcessKey(CalcKey))
      CalcKey=KEY_NONE;
    return(CalcKey);
  }
  int GrayKey=(CalcKey==KEY_ADD || CalcKey==KEY_SUBTRACT || CalcKey==KEY_MULTIPLY);
  if ((CalcKey>=' ' && CalcKey<256 || CalcKey==KEY_BS || GrayKey) &&
      CalcKey!=KEY_DEL && WinVer.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
  {
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
      ReadConsoleW(hConInp,&ReadKey,1,&ReadCount,NULL);
      WCHAR UnicodeChar=ReadKey;
      if((UnicodeChar&0xFF00))
      {
        UnicodeToAscii(&UnicodeChar,(char*)&ReadKey,sizeof(WCHAR));
        CharToOemBuff((char*)&ReadKey,(char*)&ReadKey,1);
      }
    }
    else
      ReadConsoleA(hConInp,&ReadKey,1,&ReadCount,NULL);
#else
    ReadConsole(hConInp,&ReadKey,1,&ReadCount,NULL);
#endif
    if (ReadKey==13 && CalcKey!=KEY_ENTER)
    {
#if defined(USE_WFUNC_IN)
      if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
        ReadConsoleW(hConInp,&ReadKey,1,&ReadCount,NULL);
        WCHAR UnicodeChar=ReadKey;
        if((UnicodeChar&0xFF00))
        {
          ReadKey=0;
          UnicodeToAscii(&UnicodeChar,(char*)&ReadKey,sizeof(WCHAR));
          CharToOemBuff((char*)&ReadKey,(char*)&ReadKey,1);
        }
      }
      else
        ReadConsoleA(hConInp,&ReadKey,1,&ReadCount,NULL);
#else
      ReadConsole(hConInp,&ReadKey,1,&ReadCount,NULL);
#endif
    }
    rec->Event.KeyEvent.uChar.AsciiChar=(char) ReadKey;
  }
  else
  {
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
      ReadConsoleInputW(hConInp,rec,1,&ReadCount);
      WCHAR UnicodeChar=rec->Event.KeyEvent.uChar.UnicodeChar;
      if((UnicodeChar&0xFF00))
      {
        rec->Event.KeyEvent.uChar.UnicodeChar=0;
        UnicodeToAscii(&UnicodeChar,&rec->Event.KeyEvent.uChar.AsciiChar,sizeof(WCHAR));
        CharToOemBuff(&rec->Event.KeyEvent.uChar.AsciiChar,&rec->Event.KeyEvent.uChar.AsciiChar,1);
      }
    }
    else
      ReadConsoleInputA(hConInp,rec,1,&ReadCount);
#else
    ReadConsoleInput(hConInp,rec,1,&ReadCount);

    // ��� ����� ����� ������ � ������� ���������� ����� - ��������� �� �������� - � ��� ��������
    // ... ����� ��������� � ������� ��������� ����� ������������
    /* ��������� �����, �.�.
    NumLock=ON Shift-Numpad1
       Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
       Dn, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
       Up, 1, Vk=0x0023, Scan=0x004F Ctrl=0x00000020 (casa - cecN)
    >>>Dn, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000030 (caSa - cecN)
       Up, 1, Vk=0x0010, Scan=0x002A Ctrl=0x00000020 (casa - cecN)
    ����� ��������� ������ ����
    */
    if(rec->Event.KeyEvent.wVirtualKeyCode == VK_SHIFT &&
       rec->EventType==KEY_EVENT &&
       IsProcessAssignMacroKey)
    {
      if(rec->Event.KeyEvent.bKeyDown)
      {
        if(!ShiftState)
          ShiftState=TRUE;
      }
      else if(!rec->Event.KeyEvent.bKeyDown)
        ShiftState=FALSE;
    }
#endif
  }


  if (EnableShowTime)
    ShowTime(1);

  /*& 17.05.2001 OT ��������� ������ �������, ������� �������*/
  if (rec->EventType==WINDOW_BUFFER_SIZE_EVENT)
  {
    int PScrX=ScrX;
    int PScrY=ScrY;
    //_SVS(SysLog(1,"GetInputRecord(WINDOW_BUFFER_SIZE_EVENT)"));
    Sleep(1);
    GetVideoMode(CurScreenBufferInfo);
    if (PScrX+1 == CurScreenBufferInfo.dwSize.X &&
        PScrY+1 == CurScreenBufferInfo.dwSize.Y)
    {
      //_SVS(SysLog(-1,"GetInputRecord(WINDOW_BUFFER_SIZE_EVENT); return KEY_NONE"));
      return KEY_NONE;
    }
    else
    {
      PrevScrX=PScrX;
      PrevScrY=PScrY;
      //_SVS(SysLog(-1,"GetInputRecord(WINDOW_BUFFER_SIZE_EVENT); return KEY_CONSOLE_BUFFER_RESIZE"));
      Sleep(1);
      return(KEY_CONSOLE_BUFFER_RESIZE);
    }
  }
  /* 17.05.2001 $ */

  if (rec->EventType==KEY_EVENT)
  {
    DWORD CtrlState=rec->Event.KeyEvent.dwControlKeyState;
    DWORD KeyCode=rec->Event.KeyEvent.wVirtualKeyCode;
    CtrlPressed=(CtrlState & (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED));
    AltPressed=(CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED));

    // ��� NumPad!
    if((CalcKey&(KEY_CTRL|KEY_SHIFT|KEY_ALT|KEY_RCTRL|KEY_RALT)) == KEY_SHIFT &&
       (CalcKey&KEY_MASKF) >= KEY_NUMPAD0 && (CalcKey&KEY_MASKF) <= KEY_NUMPAD9)
      ShiftPressed=SHIFT_PRESSED;
    else
      ShiftPressed=(CtrlState & SHIFT_PRESSED);

    if (KeyCode==VK_F16 && ReadKey==VK_F16 || KeyCode==0)
      return(KEY_NONE);

    if (!rec->Event.KeyEvent.bKeyDown &&
        (KeyCode==VK_SHIFT || KeyCode==VK_CONTROL || KeyCode==VK_MENU) &&
        CurClock-PressedLastTime<500)
    {
      int Key=-1;
      if (ShiftPressedLast && KeyCode==VK_SHIFT)
      {
        Key=KEY_SHIFT;
        //_SVS(SysLog("ShiftPressedLast, Key=KEY_SHIFT"));
      }
      if (KeyCode==VK_CONTROL)
      {
        if (CtrlPressedLast)
        {
          Key=KEY_CTRL;
          //_SVS(SysLog("CtrlPressedLast, Key=KEY_CTRL"));
        }
        else if (RightCtrlPressedLast)
        {
          Key=KEY_RCTRL;
          //_SVS(SysLog("CtrlPressedLast, Key=KEY_RCTRL"));
        }
      }

      if (KeyCode==VK_MENU)
      {
        if (AltPressedLast)
        {
          Key=KEY_ALT;
          //_SVS(SysLog("AltPressedLast, Key=KEY_ALT"));
        }
        else if (RightAltPressedLast)
        {
          Key=KEY_RALT;
          //_SVS(SysLog("RightAltPressedLast, Key=KEY_RALT"));
        }
      }

      if (Key!=-1 && !NotMacros && CtrlObject!=NULL && CtrlObject->Macro.ProcessKey(Key))
        Key=KEY_NONE;
      if (Key!=-1)
        return(Key);
    }

    ShiftPressedLast=FALSE;
    CtrlPressedLast=RightCtrlPressedLast=FALSE;
    AltPressedLast=RightAltPressedLast=FALSE;

    ShiftPressedLast=(KeyCode==VK_SHIFT && rec->Event.KeyEvent.bKeyDown) ||
         (KeyCode==VK_RETURN && ShiftPressed && !rec->Event.KeyEvent.bKeyDown);

    if (!ShiftPressedLast)
      if (KeyCode==VK_CONTROL && rec->Event.KeyEvent.bKeyDown)
      {
        if (CtrlState & RIGHT_CTRL_PRESSED)
        {
          RightCtrlPressedLast=TRUE;
          //_SVS(SysLog("RightCtrlPressedLast=TRUE;"));
        }
        else
        {
          CtrlPressedLast=TRUE;
          //_SVS(SysLog("CtrlPressedLast=TRUE;"));
        }
      }

    if (!ShiftPressedLast && !CtrlPressedLast && !RightCtrlPressedLast)
    {
      if (KeyCode==VK_MENU && rec->Event.KeyEvent.bKeyDown)
      {
        if (CtrlState & RIGHT_ALT_PRESSED)
        {
          RightAltPressedLast=TRUE;
        }
        else
        {
          AltPressedLast=TRUE;
        }
        PressedLastTime=CurClock;
      }
    }
    else
      PressedLastTime=CurClock;

    if (KeyCode==VK_SHIFT || KeyCode==VK_MENU || KeyCode==VK_CONTROL ||
        KeyCode==VK_NUMLOCK || KeyCode==VK_SCROLL)
    {
      /* $ 24.08.2000 SVS
         + ���������� �� ������� KEY_CTRLALTSHIFTPRESS
      */
      switch(KeyCode)
      {
        case VK_SHIFT:
        case VK_MENU:
        case VK_CONTROL:
          if(!IsKeyCASPressed && CtrlPressed && AltPressed && ShiftPressed)
          {
            IsKeyCASPressed=TRUE;
            return (KEY_CTRLALTSHIFTPRESS);
          }
      }
      /* SVS $ */
      return(KEY_NONE);
    }
    Panel::EndDrag();
  }
  if (rec->EventType==MOUSE_EVENT)
  {
    // �������� �� Swap ������ ����
    static int SwapButton=GetSystemMetrics(SM_SWAPBUTTON);
#if defined(MOUSEKEY)
    PrePreMouseEventFlags=PreMouseEventFlags;
#endif
    PreMouseEventFlags=MouseEventFlags;
    MouseEventFlags=rec->Event.MouseEvent.dwEventFlags;

    DWORD CtrlState=rec->Event.MouseEvent.dwControlKeyState;

/*
    // ������ �� ���������� ;-) �������� ����������� ������ ��� �������� �����
    if(CtrlState != (CtrlPressed|AltPressed|ShiftPressed))
    {
      static INPUT_RECORD TempRec[2]={
        {KEY_EVENT,{1,1,VK_F16,0,{0},0}},
        {KEY_EVENT,{0,1,VK_F16,0,{0},0}}
      };
      DWORD WriteCount;
      TempRec[0].Event.KeyEvent.dwControlKeyState=TempRec[1].Event.KeyEvent.dwControlKeyState=CtrlState;
      #if defined(USE_WFUNC_IN)
      if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
        WriteConsoleInputW(hConInp,TempRec,2,&WriteCount);
      else
        WriteConsoleInputA(hConInp,TempRec,2,&WriteCount);
      #else
      WriteConsoleInput(hConInp,TempRec,2,&WriteCount);
      #endif
    }
*/
    CtrlPressed=(CtrlState & (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED));
    AltPressed=(CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED));
    ShiftPressed=(CtrlState & SHIFT_PRESSED);

    DWORD BtnState=rec->Event.MouseEvent.dwButtonState;
    if (SwapButton && WinVer.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS && !IsWindowed())
    {
      if (BtnState & FROM_LEFT_1ST_BUTTON_PRESSED)
        rec->Event.MouseEvent.dwButtonState|=RIGHTMOST_BUTTON_PRESSED;
      else
        rec->Event.MouseEvent.dwButtonState&=~RIGHTMOST_BUTTON_PRESSED;
      if (BtnState & RIGHTMOST_BUTTON_PRESSED)
        rec->Event.MouseEvent.dwButtonState|=FROM_LEFT_1ST_BUTTON_PRESSED;
      else
        rec->Event.MouseEvent.dwButtonState&=~FROM_LEFT_1ST_BUTTON_PRESSED;
    }

    if(MouseEventFlags != MOUSE_MOVED)
    {
//_SVS(SysLog("1. CtrlState=%X PrevRButtonPressed=%d,RButtonPressed=%d",CtrlState,PrevRButtonPressed,RButtonPressed));
      PrevLButtonPressed=LButtonPressed;
      PrevRButtonPressed=RButtonPressed;
      PrevMButtonPressed=MButtonPressed;
    }

    LButtonPressed=(BtnState & FROM_LEFT_1ST_BUTTON_PRESSED);
    RButtonPressed=(BtnState & RIGHTMOST_BUTTON_PRESSED);
    MButtonPressed=(BtnState & FROM_LEFT_2ND_BUTTON_PRESSED);
//_SVS(SysLog("2. BtnState=%X PrevRButtonPressed=%d,RButtonPressed=%d",BtnState,PrevRButtonPressed,RButtonPressed));

    PrevMouseX=MouseX;
    PrevMouseY=MouseY;
    MouseX=rec->Event.MouseEvent.dwMousePosition.X;
    MouseY=rec->Event.MouseEvent.dwMousePosition.Y;
#if defined(MOUSEKEY)
    if(PrePreMouseEventFlags == DOUBLE_CLICK)
    {
      memset(rec,0,sizeof(*rec)); // ����� � ProcessEditorInput ����� ���� �������� - ������ ����� ����������
      rec->EventType = KEY_EVENT;
      return(KEY_NONE);
    }
    if (MouseEventFlags == DOUBLE_CLICK && (LButtonPressed || RButtonPressed))
    {
      CalcKey=LButtonPressed?KEY_MSLDBLCLICK:KEY_MSRDBLCLICK;
      CalcKey |= (CtrlState&SHIFT_PRESSED?KEY_SHIFT:0)|
                 (CtrlState&(LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED)?KEY_CTRL:0)|
                 (CtrlState&(LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED)?KEY_ALT:0);
      memset(rec,0,sizeof(*rec)); // ����� � ProcessEditorInput ����� ���� �������� - ������ ����� ����������
      rec->EventType = KEY_EVENT;
    }
    else
#endif
    /* $ 26.04.2001 VVM
       + ��������� �������� ����� ��� 2000. */
    if (MouseEventFlags == MOUSE_WHEELED)
    { // ���������� ������ � ������� �� ����.�������
      short zDelta = (short)HIWORD(rec->Event.MouseEvent.dwButtonState);
      CalcKey = (zDelta>0)?KEY_MSWHEEL_UP:KEY_MSWHEEL_DOWN;
      /* $ 27.04.2001 SVS
         �� ���� ������ �������� ������� ��� ��������� ������, ��-�� ����
         ������ ���� ������������ � �������� ����� ����� "ShiftMsWheelUp"
      */
      CalcKey |= (CtrlState&SHIFT_PRESSED?KEY_SHIFT:0)|
                 (CtrlState&(LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED)?KEY_CTRL:0)|
                 (CtrlState&(LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED)?KEY_ALT:0);
      /* SVS $ */
      /* $ 14.05.2002 VVM
        - ������� ��� ������ ������. ����� ������ ����� (ProcessEditorInput) */
      memset(rec,0,sizeof(*rec)); // ����� � ProcessEditorInput ����� ���� �������� - ������ ����� ����������
      rec->EventType = KEY_EVENT;
      /* VVM $ */
    } /* if */
    /* VVM $ */
  }
  if (ReadKey!=0 && !GrayKey)
    CalcKey=ReadKey;

  if (!NotMacros && CtrlObject!=NULL && CtrlObject->Macro.ProcessKey(CalcKey))
    CalcKey=KEY_NONE;

  return(CalcKey);
}

int PeekInputRecord(INPUT_RECORD *rec)
{
  DWORD ReadCount;
  DWORD Key;
  ScrBuf.Flush();
  if(KeyQueue && (Key=KeyQueue->Peek()) != NULL)
  {
    int VirtKey,ControlState;
    ReadCount=TranslateKeyToVK(Key,VirtKey,ControlState,rec)?1:0;
  }
  else
  {
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
      PeekConsoleInputW(hConInp,rec,1,&ReadCount);
      WCHAR UnicodeChar=rec->Event.KeyEvent.uChar.UnicodeChar;
      if((UnicodeChar&0xFF00))
      {
        rec->Event.KeyEvent.uChar.UnicodeChar=0;
        UnicodeToAscii(&UnicodeChar,&rec->Event.KeyEvent.uChar.AsciiChar,sizeof(WCHAR));
        CharToOemBuff(&rec->Event.KeyEvent.uChar.AsciiChar,&rec->Event.KeyEvent.uChar.AsciiChar,1);
      }
    }
    else
      PeekConsoleInputA(hConInp,rec,1,&ReadCount);
#else
    PeekConsoleInput(hConInp,rec,1,&ReadCount);
#endif
  }
  if (ReadCount==0)
    return(0);
  return(CalcKeyCode(rec,TRUE));
}


/* $ 24.08.2000 SVS
 + �������� � ������ WaitKey - ����������� ������� ���������� �������
     ���� KeyWait = -1 - ��� � ������
*/
DWORD WaitKey(DWORD KeyWait)
{
  int Visible,Size;
  if(KeyWait == KEY_CTRLALTSHIFTRELEASE)
  {
    GetCursorType(Visible,Size);
    SetCursorType(0,10);
  }

  DWORD Key;
  while (1)
  {
    INPUT_RECORD rec;
    Key=GetInputRecord(&rec);
    if(KeyWait == (DWORD)-1)
    {
      if (Key!=KEY_NONE && Key!=KEY_IDLE)
        break;
    }
    else if(Key == KeyWait)
      break;
  }

  if(KeyWait == KEY_CTRLALTSHIFTRELEASE)
    SetCursorType(Visible,Size);

  return Key;
}
/* SVS $ */

int WriteInput(int Key,DWORD Flags)
{
  if(Flags&(SKEY_VK_KEYS|SKEY_IDLE))
  {
    INPUT_RECORD Rec;
    DWORD WriteCount;

    if(Flags&SKEY_IDLE)
    {
      Rec.EventType=FOCUS_EVENT;
      Rec.Event.FocusEvent.bSetFocus=TRUE;
    }
    else
    {
      Rec.EventType=KEY_EVENT;
      Rec.Event.KeyEvent.bKeyDown=1;
      Rec.Event.KeyEvent.wRepeatCount=1;
      Rec.Event.KeyEvent.wVirtualKeyCode=Key;
      Rec.Event.KeyEvent.wVirtualScanCode=MapVirtualKey(
                    Rec.Event.KeyEvent.wVirtualKeyCode, 0);
      if (Key < 0x30 || Key > 0x5A) // 0-9:;<=>?@@ A..Z  //?????
        Key=0;
      Rec.Event.KeyEvent.uChar.UnicodeChar=Rec.Event.KeyEvent.uChar.AsciiChar=Key;
      Rec.Event.KeyEvent.dwControlKeyState=0;
    }
#if defined(USE_WFUNC_IN)
    if(WinVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
      return WriteConsoleInputW(hConInp,&Rec,1,&WriteCount);
    else
      return WriteConsoleInputA(hConInp,&Rec,1,&WriteCount);
#else
    return WriteConsoleInput(hConInp,&Rec,1,&WriteCount);
#endif
  }
  else if(KeyQueue)
  {
    return KeyQueue->Put(((DWORD)Key)|(Flags&SKEY_NOTMACROS?0x80000000:0));
  }
  else
    return 0;
}


int CheckForEscSilent()
{
  INPUT_RECORD rec;
  int Key;
  if (!CtrlObject->Macro.IsExecuting() && PeekInputRecord(&rec) &&
      ((Key=GetInputRecord(&rec))==KEY_ESC || Key==KEY_BREAK))
    return(TRUE);
  else
    return(FALSE);
}

int ConfirmAbortOp()
{
  SaveScreen SaveScr; // �����! ��������� �� ��������� ��������� �����
  BOOL rc=TRUE;
  IsProcessAssignMacroKey++; // �������� ���� �������
                             // �.�. � ���� ������� ������ ������ Alt-F9!
  if (Opt.Confirm.Esc)
     rc=AbortMessage();
  IsProcessAssignMacroKey--;
  return rc;
}

/* $ 09.02.2001 IS
     ������������� ������� Esc
*/
int CheckForEsc()
{
  if (CheckForEscSilent())
    return(ConfirmAbortOp());
  else
    return(FALSE);
}
/* IS $ */

/* $ 25.07.2000 SVS
    ! ������� KeyToText ������� ���������������� - ����� � ������ FSF
*/
/* $ 01.08.2000 SVS
   ! �������������� ��������� � KeyToText - ������ ������
   Size=0 - �� ���������!
*/
/* $ 10.09.2000 SVS
  ! KeyToText ���������� BOOL
*/

static char *GetShiftKeyName(char *Name, DWORD Key,int& Len)
{
  if((Key&KEY_RCTRL) == KEY_RCTRL)   strcat(Name,ModifKeyName[1].Name);
  else if(Key&KEY_CTRL)              strcat(Name,ModifKeyName[0].Name);
//  else if(Key&KEY_LCTRL)             strcat(Name,ModifKeyName[3].Name);

  if((Key&KEY_RALT) == KEY_RALT)     strcat(Name,ModifKeyName[3].Name);
  else if(Key&KEY_ALT)               strcat(Name,ModifKeyName[2].Name);
//  else if(Key&KEY_LALT)    strcat(Name,ModifKeyName[6].Name);

  if(Key&KEY_SHIFT)                  strcat(Name,ModifKeyName[4].Name);
//  else if(Key&KEY_LSHIFT)  strcat(Name,ModifKeyName[0].Name);
//  else if(Key&KEY_RSHIFT)  strcat(Name,ModifKeyName[1].Name);

  Len=strlen(Name);
  return Name;
}

/* $ 24.09.2000 SVS
 + ������� KeyNameToKey - ��������� ���� ������� �� �����
   ���� ��� �� ����� ��� ��� ������ - ������������ -1
   ����� � �����, �� ��������� � �������!
*/
int WINAPI KeyNameToKey(const char *Name)
{
   if(!Name || !*Name)
     return -1;
   DWORD Key=0;

   // ��� ������������?
   if(Name[0] == '$' && Name[1])
     return KeyNameMacroToKey(Name);
//   if((Key=KeyNameMacroToKey(Name)) != (DWORD)-1)
//     return Key;

   int I, Pos, Len=strlen(Name);

   // ��������� �� ���� �������������
   for(Pos=I=0; Pos < Len && I < sizeof(ModifKeyName)/sizeof(ModifKeyName[0]); ++I)
   {
     if(!memicmp(Name+Pos,ModifKeyName[I].Name,ModifKeyName[I].Len))
     {
       Pos+=ModifKeyName[I].Len;
       Key|=ModifKeyName[I].Key;
     }
   }
//_SVS(SysLog("Name=%s",Name));
   // ���� ���-�� �������� - �����������.
   if(Pos < Len)
   {
     // ������� - FKeys1
     const char* Ptr=Name+Pos;
     for (I=0;I<sizeof(FKeys1)/sizeof(FKeys1[0]);I++)
       if (!memicmp(Ptr,FKeys1[I].Name,FKeys1[I].Len))
       {
         Key|=FKeys1[I].Key;
         Pos+=FKeys1[I].Len;
         break;
       }
     if(I  == sizeof(FKeys1)/sizeof(FKeys1[0]) && (Len == 1 || Pos == Len-1))
     {
       WORD Chr=(WORD)(BYTE)Name[Pos];
       if (Chr > 0 && Chr < 256)
       {
//         if (Key&(0xFF000000-KEY_SHIFT))
//           Chr=LocalUpper(Chr);
         Key|=Chr;
         Pos++;
       }
     }
   }
//_SVS(SysLog("Key=0x%08X (%c) => '%s'",Key,(Key?Key:' '),Name));

   return (!Key || Pos < Len)? -1: Key;
}
/* SVS $*/

BOOL WINAPI KeyToText(int Key0,char *KeyText0,int Size)
{
  if(!KeyText0)
     return FALSE;

  char KeyText[128];
  int I, Len;
  DWORD Key=(DWORD)Key0, FKey=(DWORD)Key0&0xFFFF;

  if(Key&KEY_MACRO_BASE)
    return KeyMacroToText(Key0,KeyText0,Size);

  /* $ 27.12.2001 KM
    ! ������� KeyText (��� � ���� ������), � ��������� ������
      � ������ ����������� �����!
  */
  memset(KeyText,0,sizeof(KeyText));
  /* KM $ */
  GetShiftKeyName(KeyText,Key,Len);

  for (I=0;I<sizeof(FKeys1)/sizeof(FKeys1[0]);I++)
  {
    if (FKey==FKeys1[I].Key)
    {
      strcat(KeyText,FKeys1[I].Name);
      break;
    }
  }

  if(I  == sizeof(FKeys1)/sizeof(FKeys1[0]))
  {
#if defined(SYSLOG)
    for (I=0;I<sizeof(SpecKeyName)/sizeof(SpecKeyName[0]);I++)
      if (FKey==SpecKeyName[I].Key)
      {
        strcat(KeyText,SpecKeyName[I].Name);
        break;
      }
    if(I  == sizeof(SpecKeyName)/sizeof(SpecKeyName[0]))
#endif
    {
      FKey=(Key&0xFF)&(~0x20);
      if (FKey >= 'A' && FKey <= 'Z')
        KeyText[Len]=(char)Key&0xFF;
      else if ((Key&0xFF) > 0 && (Key&0xFF) < 256)
        KeyText[Len]=(char)Key&0xFF;
    }
  }

  if(!KeyText[0])
  {
    *KeyText0='\0';
    return FALSE;
  }

  if(Size > 0)
    strncpy(KeyText0,KeyText,Size);
  else
    strcpy(KeyText0,KeyText);
//_D(SysLog("KeyToText() 0x%08X %s",Key,KeyText));
  return TRUE;
}
/* SVS 10.09.2000 $ */
/* SVS $ */


int TranslateKeyToVK(int Key,int &VirtKey,int &ControlState,INPUT_RECORD *Rec)
{
  int FKey  =Key&0x0000FFFF;
  int FShift=Key&0x7F000000; // ������� ��� ������������ � ������ �����!
  int I;

  VirtKey=0;
  ControlState=(FShift&KEY_SHIFT?PKF_SHIFT:0)|
               (FShift&KEY_ALT?PKF_ALT:0)|
               (FShift&KEY_CTRL?PKF_CONTROL:0);

  for(I=0; I < sizeof(Table_KeyToVK)/sizeof(Table_KeyToVK[0]); ++I)
    if (FKey==Table_KeyToVK[I].Key)
    {
      VirtKey=Table_KeyToVK[I].VK;
      break;
    }

  if(I  == sizeof(Table_KeyToVK)/sizeof(Table_KeyToVK[0]))
  {
    if (FKey>='0' && FKey<='9' || FKey>='A' && FKey<='Z')
      VirtKey=FKey;
    else if(FKey > 0x100 && FKey < KEY_END_FKEY)
      VirtKey=FKey-0x100;
    else if(FKey < 0x100)
      VirtKey=VkKeyScan(FKey)&0xFF;
    else
      VirtKey=FKey;
  }
  if(Rec && VirtKey!=0)
  {
    Rec->EventType=KEY_EVENT;
    Rec->Event.KeyEvent.bKeyDown=1;
    Rec->Event.KeyEvent.wRepeatCount=1;
    Rec->Event.KeyEvent.wVirtualKeyCode=VirtKey;
    Rec->Event.KeyEvent.wVirtualScanCode = MapVirtualKey(
                    Rec->Event.KeyEvent.wVirtualKeyCode, 0);
    if (Key>255)
      Key=0;
    Rec->Event.KeyEvent.uChar.UnicodeChar=
        Rec->Event.KeyEvent.uChar.AsciiChar=Key;
    // ����� ������ � Shift-�������� ������, ������ ��� ControlState
    Rec->Event.KeyEvent.dwControlKeyState=
               (FShift&KEY_SHIFT?SHIFT_PRESSED:0)|
               (FShift&KEY_ALT?LEFT_ALT_PRESSED:0)|
               (FShift&KEY_CTRL?LEFT_CTRL_PRESSED:0)|
               (FShift&KEY_RALT?RIGHT_ALT_PRESSED:0)|
               (FShift&KEY_RCTRL?RIGHT_CTRL_PRESSED:0);
  }
  return(VirtKey!=0);
}


int IsNavKey(DWORD Key)
{
  static DWORD NavKeys[][2]={
    {0,KEY_CTRLC},
    {0,KEY_INS},      {0,KEY_NUMPAD0},
    {0,KEY_CTRLINS},  {0,KEY_CTRLNUMPAD0},

    {1,KEY_LEFT},     {1,KEY_NUMPAD4},
    {1,KEY_RIGHT},    {1,KEY_NUMPAD6},
    {1,KEY_HOME},     {1,KEY_NUMPAD7},
    {1,KEY_END},      {1,KEY_NUMPAD1},
    {1,KEY_UP},       {1,KEY_NUMPAD8},
    {1,KEY_DOWN},     {1,KEY_NUMPAD2},
    {1,KEY_PGUP},     {1,KEY_NUMPAD9},
    {1,KEY_PGDN},     {1,KEY_NUMPAD3},
    //!!!!!!!!!!!
  };

  for (int I=0; I < sizeof(NavKeys)/sizeof(NavKeys[0]); I++)
    if(!NavKeys[I][0] && Key==NavKeys[I][1] ||
       NavKeys[I][0] && (Key&0x00FFFFFF)==(NavKeys[I][1]&0x00FFFFFF))
      return TRUE;
  return FALSE;
}

int IsShiftKey(DWORD Key)
{
  static DWORD ShiftKeys[]={
     KEY_SHIFTLEFT,          KEY_SHIFTNUMPAD4,
     KEY_SHIFTRIGHT,         KEY_SHIFTNUMPAD6,
     KEY_SHIFTHOME,          KEY_SHIFTNUMPAD7,
     KEY_SHIFTEND,           KEY_SHIFTNUMPAD1,
     KEY_SHIFTUP,            KEY_SHIFTNUMPAD8,
     KEY_SHIFTDOWN,          KEY_SHIFTNUMPAD2,
     KEY_SHIFTPGUP,          KEY_SHIFTNUMPAD9,
     KEY_SHIFTPGDN,          KEY_SHIFTNUMPAD3,
     KEY_CTRLSHIFTHOME,      KEY_CTRLSHIFTNUMPAD7,
     KEY_CTRLSHIFTPGUP,      KEY_CTRLSHIFTNUMPAD9,
     KEY_CTRLSHIFTEND,       KEY_CTRLSHIFTNUMPAD1,
     KEY_CTRLSHIFTPGDN,      KEY_CTRLSHIFTNUMPAD3,
     KEY_CTRLSHIFTLEFT,      KEY_CTRLSHIFTNUMPAD4,
     KEY_CTRLSHIFTRIGHT,     KEY_CTRLSHIFTNUMPAD6,
     KEY_ALTSHIFTDOWN,       KEY_ALTSHIFTNUMPAD2,
     KEY_ALTSHIFTLEFT,       KEY_ALTSHIFTNUMPAD4,
     KEY_ALTSHIFTRIGHT,      KEY_ALTSHIFTNUMPAD6,
     KEY_ALTSHIFTUP,         KEY_ALTSHIFTNUMPAD8,
     KEY_ALTSHIFTEND,        KEY_ALTSHIFTNUMPAD1,
     KEY_ALTSHIFTHOME,       KEY_ALTSHIFTNUMPAD7,
     KEY_ALTSHIFTPGDN,       KEY_ALTSHIFTNUMPAD3,
     KEY_ALTSHIFTPGUP,       KEY_ALTSHIFTNUMPAD9,
     KEY_CTRLALTPGUP,        KEY_CTRLALTNUMPAD9,
     KEY_CTRLALTHOME,        KEY_CTRLALTNUMPAD7,
     KEY_CTRLALTPGDN,        KEY_CTRLALTNUMPAD2,
     KEY_CTRLALTEND,         KEY_CTRLALTNUMPAD1,
     KEY_CTRLALTLEFT,        KEY_CTRLALTNUMPAD4,
     KEY_CTRLALTRIGHT,       KEY_CTRLALTNUMPAD6,
     KEY_ALTUP,
     KEY_ALTLEFT,
     KEY_ALTDOWN,
     KEY_ALTRIGHT,
     KEY_ALTHOME,
     KEY_ALTEND,
     KEY_ALTPGUP,
     KEY_ALTPGDN,
     KEY_ALT,
     KEY_CTRL,
  };

  for (int I=0;I<sizeof(ShiftKeys)/sizeof(ShiftKeys[0]);I++)
    if (Key==ShiftKeys[I])
      return TRUE;
  return FALSE;
}


// GetAsyncKeyState(VK_RSHIFT)
int CalcKeyCode(INPUT_RECORD *rec,int RealKey,int *NotMacros)
{
  //_SVS(CleverSysLog Clev("CalcKeyCode"));
  union {
    WCHAR UnicodeChar;
    CHAR  AsciiChar;
  } Char;

  unsigned int ScanCode,KeyCode,CtrlState;
  CtrlState=rec->Event.KeyEvent.dwControlKeyState;
  ScanCode=rec->Event.KeyEvent.wVirtualScanCode;
  KeyCode=rec->Event.KeyEvent.wVirtualKeyCode;
  Char.UnicodeChar=rec->Event.KeyEvent.uChar.UnicodeChar;
  //_SVS(if(KeyCode == VK_DECIMAL || KeyCode == VK_DELETE) SysLog("CalcKeyCode -> CtrlState=%04X KeyCode=%s ScanCode=%08X AsciiChar=%02X ShiftPressed=%d ShiftPressedLast=%d",CtrlState,_VK_KEY_ToName(KeyCode), ScanCode, Char.AsciiChar,ShiftPressed,ShiftPressedLast));

  if(NotMacros)
    *NotMacros=CtrlState&0x80000000?TRUE:FALSE;
//  CtrlState&=~0x80000000;

  if (!RealKey)
  {
    CtrlPressed=(CtrlState & (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED));
    AltPressed=(CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED));
    ShiftPressed=(CtrlState & SHIFT_PRESSED);
  }

  if (rec->EventType!=KEY_EVENT)
    return(KEY_NONE);

  if (!rec->Event.KeyEvent.bKeyDown)
  {
    KeyCodeForALT_LastPressed=0;
    if (KeyCode==VK_MENU && AltValue!=0)
    {
      //FlushInputBuffer();//???
      INPUT_RECORD TempRec;
      DWORD ReadCount;
      ReadConsoleInput(hConInp,&TempRec,1,&ReadCount);

      ReturnAltValue=TRUE;
#if defined(USE_WFUNC_IN)
      AltValue&=0xFFFF;
      rec->Event.KeyEvent.uChar.UnicodeChar=AltValue;
#else
      AltValue&=0x00FF;
      rec->Event.KeyEvent.uChar.AsciiChar=AltValue;
#endif
      //_SVS(SysLog("KeyCode==VK_MENU -> AltValue=%X (%c)",AltValue,AltValue));
      return(AltValue);
    }
    else
      return(KEY_NONE);
  }

  if ((CtrlState & 9)==9)
    if (Char.AsciiChar!=0)
      return(Char.AsciiChar);
    else
      CtrlPressed=0;

  if (Opt.AltGr && CtrlPressed && (rec->Event.KeyEvent.dwControlKeyState & RIGHT_ALT_PRESSED))
    if (Char.AsciiChar=='\\')
      return(KEY_CTRLBACKSLASH);

  if (KeyCode==VK_MENU)
    AltValue=0;

  if (Char.AsciiChar==0 && !CtrlPressed && !AltPressed)
  {
    if (KeyCode==0xc0)
      return(ShiftPressed ? '~':'`');
    if (KeyCode==0xde)
      return(ShiftPressed ? '"':'\'');
  }

  if (Char.AsciiChar<32 && (CtrlPressed || AltPressed))
  {
    switch(KeyCode)
    {
      case 0xbc:
        Char.AsciiChar=',';
        break;
      case 0xbe:
        Char.AsciiChar='.';
        break;
      case 0xdb:
        Char.AsciiChar='[';
        break;
      case 0xdc:
        //Char.AsciiChar=ScanCode==0x29?0x15:'\\'; //???
        Char.AsciiChar='\\';
        break;
      case 0xdd:
        Char.AsciiChar=']';
        break;
      case 0xde:
        Char.AsciiChar='\"';
        break;
    }
  }

  /* $ 24.08.2000 SVS
     "������������ 100 �����" :-)
  */
  if(CtrlPressed && AltPressed && ShiftPressed)
  {
    switch(KeyCode)
    {
      case VK_SHIFT:
      case VK_MENU:
      case VK_CONTROL:
        return (IsKeyCASPressed?KEY_CTRLALTSHIFTPRESS:KEY_CTRLALTSHIFTRELEASE);
    }
  }
  /* SVS $*/
  DWORD Modif=(CtrlPressed?KEY_CTRL:0)|(AltPressed?KEY_ALT:0)|(ShiftPressed?KEY_SHIFT:0);

  if (KeyCode>=VK_F1 && KeyCode<=VK_F12)
//    return(Modif+KEY_F1+((KeyCode-VK_F1)<<8));
    return(Modif+KEY_F1+((KeyCode-VK_F1)));

  int NotShift=!CtrlPressed && !AltPressed && !ShiftPressed;

  // ����� ������ ���������, �.�. ��� ���������� NumLock ������ Shift`�
  // ���� �� ������ ��������� (�������� �������� "������� �����")
  DWORD Modif2=0;

  if(!(CtrlState&ENHANCED_KEY)) //(CtrlState&NUMLOCK_ON) // �� ����������� ����� �������.
  {
    Modif2=(CtrlState & (LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED)?KEY_CTRL:0)|
                (CtrlState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED)?KEY_ALT:0);

    if(CtrlState&NUMLOCK_ON)
    {
      Modif2|=KEY_SHIFT;
      if(KeyCode >= VK_NUMPAD0 && KeyCode <= VK_NUMPAD9 || KeyCode == VK_DECIMAL)
      {
        Modif2&=~KEY_SHIFT;
      }
    }
    else
      Modif2|=GetAsyncKeyState(VK_SHIFT) < 0?KEY_SHIFT:0;
  }

  if (AltPressed && !CtrlPressed && !ShiftPressed)
  {
#if 0
    if (AltValue==0 && (!CtrlObject->Macro.IsRecording() || !Opt.UseNumPad))
    {
      // VK_INSERT  = 0x2D       AS-0 = 0x2D
      // VK_NUMPAD0 = 0x60       A-0  = 0x60
      /*
        � �������� �� ��� ������� - ���, ��� � ����� ��������,
        ������ ��� ������� ���� � �����.
      */
      if(//(CtrlState&NUMLOCK_ON)  && KeyCode==VK_NUMPAD0 && !(CtrlState&ENHANCED_KEY) ||
         (Opt.UseNumPad && KeyCode==VK_INSERT && (CtrlState&ENHANCED_KEY)) ||
         (!Opt.UseNumPad && (KeyCode==VK_INSERT || KeyCode==VK_NUMPAD0))
        )
      {   // CtrlObject->Macro.IsRecording()
      //_SVS(SysLog("IsProcessAssignMacroKey=%d",IsProcessAssignMacroKey));
        if(IsProcessAssignMacroKey && Opt.UseNumPad)
        {
          return KEY_INS|KEY_ALT;
        }
        else
        {
          RunGraber();
        }
        return(KEY_NONE);
      }
    }
#else
    if (AltValue==0)
    {
      if(KeyCode==VK_INSERT || KeyCode==VK_NUMPAD0)
      {
        RunGraber();
        return(KEY_NONE);
      }
    }
#endif

    //_SVS(SysLog("1 AltNumPad -> CalcKeyCode -> KeyCode=%s  ScanCode=0x%0X AltValue=0x%0X CtrlState=%X GetAsyncKeyState(VK_SHIFT)=%X",_VK_KEY_ToName(KeyCode),ScanCode,AltValue,CtrlState,GetAsyncKeyState(VK_SHIFT)));
    if((CtrlState & ENHANCED_KEY)==0
      //(CtrlState&NUMLOCK_ON) && KeyCode >= VK_NUMPAD0 && KeyCode <= VK_NUMPAD9 ||
      // !(CtrlState&NUMLOCK_ON) && KeyCode < VK_NUMPAD0
      )
    {
    //_SVS(SysLog("2 AltNumPad -> CalcKeyCode -> KeyCode=%s  ScanCode=0x%0X AltValue=0x%0X CtrlState=%X GetAsyncKeyState(VK_SHIFT)=%X",_VK_KEY_ToName(KeyCode),ScanCode,AltValue,CtrlState,GetAsyncKeyState(VK_SHIFT)));
      static unsigned int ScanCodes[]={82,79,80,81,75,76,77,71,72,73};
      for (int I=0;I<sizeof(ScanCodes)/sizeof(ScanCodes[0]);I++)
      {
        if (ScanCodes[I]==ScanCode)
        {
          if (RealKey && KeyCodeForALT_LastPressed != KeyCode)
          {
            AltValue=AltValue*10+I;
            KeyCodeForALT_LastPressed=KeyCode;
            //_SVS(SysLog("3 AltNumPad -> CalcKeyCode -> KeyCode=%s  ScanCode=0x%0X AltValue=0x%0X CtrlState=%X GetAsyncKeyState(VK_SHIFT)=%X",_VK_KEY_ToName(KeyCode),ScanCode,AltValue,CtrlState,GetAsyncKeyState(VK_SHIFT)));
          }
          if(AltValue!=0)
            return(KEY_NONE);
        }
      }
    }
  }

  /*
  NumLock=Off
    Down
      CtrlState=0100 KeyCode=0028 ScanCode=00000050 AsciiChar=00         ENHANCED_KEY
      CtrlState=0100 KeyCode=0028 ScanCode=00000050 AsciiChar=00
    Num2
      CtrlState=0000 KeyCode=0028 ScanCode=00000050 AsciiChar=00
      CtrlState=0000 KeyCode=0028 ScanCode=00000050 AsciiChar=00

    Ctrl-8
      CtrlState=0008 KeyCode=0026 ScanCode=00000048 AsciiChar=00
    Ctrl-Shift-8               ^^!!!
      CtrlState=0018 KeyCode=0026 ScanCode=00000048 AsciiChar=00

  ------------------------------------------------------------------------
  NumLock=On

    Down
      CtrlState=0120 KeyCode=0028 ScanCode=00000050 AsciiChar=00         ENHANCED_KEY
      CtrlState=0120 KeyCode=0028 ScanCode=00000050 AsciiChar=00
    Num2
      CtrlState=0020 KeyCode=0062 ScanCode=00000050 AsciiChar=32
      CtrlState=0020 KeyCode=0062 ScanCode=00000050 AsciiChar=32

    Ctrl-8
      CtrlState=0028 KeyCode=0068 ScanCode=00000048 AsciiChar=00
    Ctrl-Shift-8               ^^!!!
      CtrlState=0028 KeyCode=0026 ScanCode=00000048 AsciiChar=00
  */

  /* ------------------------------------------------------------- */
  switch(KeyCode)
  {
    case VK_INSERT:
    case VK_NUMPAD0:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_INS);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD0)
        return '0';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD0:KEY_INS);
    case VK_DOWN:
    case VK_NUMPAD2:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_DOWN);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD2)
        return '2';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD2:KEY_DOWN);
    case VK_LEFT:
    case VK_NUMPAD4:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_LEFT);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD4)
        return '4';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD4:KEY_LEFT);
    case VK_RIGHT:
    case VK_NUMPAD6:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_RIGHT);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD6)
        return '6';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD6:KEY_RIGHT);
    case VK_UP:
    case VK_NUMPAD8:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_UP);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD8)
        return '8';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD8:KEY_UP);
    case VK_END:
    case VK_NUMPAD1:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_END);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD1)
        return '1';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD1:KEY_END);
    case VK_HOME:
    case VK_NUMPAD7:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_HOME);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD7)
        return '7';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD7:KEY_HOME);
    case VK_NEXT:
    case VK_NUMPAD3:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_PGDN);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD3)
        return '3';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD3:KEY_PGDN);
    case VK_PRIOR:
    case VK_NUMPAD9:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_PGUP);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD9)
        return '9';
      return Modif|(Opt.UseNumPad?Modif2|KEY_NUMPAD9:KEY_PGUP);
    case VK_CLEAR:
    case VK_NUMPAD5:
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_NUMPAD5);
      }
      else if((CtrlState&NUMLOCK_ON) && NotShift && KeyCode == VK_NUMPAD5)
        return '5';
      return Modif|(Opt.UseNumPad?Modif2:0)|KEY_NUMPAD5;

    case VK_DECIMAL:
    case VK_DELETE:
      _SVS(SysLog("case VK_DELETE:  Opt.UseNumPad=%08X CtrlState=%X GetAsyncKeyState(VK_SHIFT)=%X",Opt.UseNumPad,CtrlState,GetAsyncKeyState(VK_SHIFT)));
      if(CtrlState&ENHANCED_KEY)
      {
        return(Modif|KEY_DEL);
      }
      else if(NotShift && (CtrlState&NUMLOCK_ON) && KeyCode == VK_DECIMAL ||
              (CtrlState&NUMLOCK_ON) && KeyCode == VK_DELETE && (WinVer.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)) // ������!
        return '.';
      return Modif| (Opt.UseNumPad?Modif2:0)| KEY_DEL;
  }

  switch(KeyCode)
  {
    case VK_APPS:
      return(Modif|KEY_APPS);
    case VK_LWIN:
      return(Modif|KEY_LWIN);
    case VK_RWIN:
      return(Modif|KEY_RWIN);
    case VK_RETURN:
      //  !!!!!!!!!!!!! - ���� "!ShiftPressed", �� Shift-F4 Shift-Enter, ��
      //                  �������� Shift...
      if (ShiftPressed && RealKey && !ShiftPressedLast && !CtrlPressed && !AltPressed)
        return(KEY_ENTER);
      return(Modif|KEY_ENTER);
    case VK_BACK:
      return(Modif|KEY_BS);
    case VK_SPACE:
      return(Modif|KEY_SPACE);
    case VK_TAB:
      return(Modif|KEY_TAB);
    case VK_ADD:
      return(Modif|KEY_ADD);
    case VK_SUBTRACT:
      return(Modif|KEY_SUBTRACT);
    case VK_ESCAPE:
      return(Modif|KEY_ESC);
  }

  /* ------------------------------------------------------------- */
  if (CtrlPressed && AltPressed)
  {
//_SVS(if(KeyCode!=VK_CONTROL && KeyCode!=VK_MENU) SysLog("CtrlAlt -> |0x%08X (%c)|0x%08X (%c)|",KeyCode,(KeyCode?KeyCode:' '),Char.AsciiChar,(Char.AsciiChar?Char.AsciiChar:' ')));
    if (KeyCode>='A' && KeyCode<='Z')
      return(KEY_CTRL|KEY_ALT+KeyCode);
    if(Opt.ShiftsKeyRules) //???
      switch(KeyCode)
      {
        case 0xc0:
          return(KEY_CTRL+KEY_ALT+'~');
        case 0xbd:
          return(KEY_CTRL+KEY_ALT+'-');
        case 0xbb:
          return(KEY_CTRL+KEY_ALT+'=');
        case 0xdc:
          return(KEY_CTRL+KEY_ALT+KEY_BACKSLASH);
        case 0xdd:
          return(KEY_CTRL+KEY_ALT+KEY_BACKBRACKET);
        case 0xdb:
          return(KEY_CTRL+KEY_ALT+KEY_BRACKET);
        case 0xde:
          return(KEY_CTRL+KEY_ALT+KEY_QUOTE);
        case 0xba:
          return(KEY_CTRL+KEY_ALT+KEY_COLON);
        case 0xbf:
          return(KEY_CTRL+KEY_ALT+KEY_SLASH);
        case 0xbe:
          return(KEY_CTRL+KEY_ALT+KEY_DOT);
        case 0xbc:
          return(KEY_CTRL+KEY_ALT+KEY_COMMA);
      }
    switch(KeyCode)
    {
      case VK_DIVIDE:
        return(KEY_CTRLALT|KEY_DIVIDE);
      case VK_MULTIPLY:
        return(KEY_CTRLALT|KEY_MULTIPLY);
      case VK_PAUSE:
        return(KEY_CTRLALT|KEY_BREAK);
    }
    if (Char.AsciiChar)
      return(KEY_CTRL|KEY_ALT+Char.AsciiChar);
    if (!RealKey && (KeyCode==VK_CONTROL || KeyCode==VK_MENU))
      return(KEY_NONE);
    if (KeyCode)
      return(KEY_CTRL|KEY_ALT+KeyCode);
  }


  /* ------------------------------------------------------------- */
  if (AltPressed && ShiftPressed)
  {
//_SVS(if(KeyCode!=VK_MENU && KeyCode!=VK_SHIFT) SysLog("AltShift -> NotMacros=%d %9s|0x%08X (%c)|0x%08X (%c)|WaitInMainLoop=%d WaitInFastFind=%d",*NotMacros,"AltShift",KeyCode,(KeyCode?KeyCode:' '),Char.AsciiChar,(Char.AsciiChar?Char.AsciiChar:' '),WaitInMainLoop,WaitInFastFind));
    if (KeyCode>='0' && KeyCode<='9')
    {
      if(WaitInFastFind>0 &&
        CtrlObject->Macro.GetCurRecord(NULL,NULL) != 1 &&
        CtrlObject->Macro.GetIndex(KEY_ALTSHIFT0+KeyCode-'0',-1) == -1)
      {
        return(KEY_ALT+KEY_SHIFT+Char.AsciiChar);
      }
      else
        return(KEY_ALTSHIFT0+KeyCode-'0');
    }
    if (!WaitInMainLoop && KeyCode>='A' && KeyCode<='Z')
      return(KEY_ALTSHIFT+KeyCode);
    if(Opt.ShiftsKeyRules) //???
      switch(KeyCode)
      {
        case 0xc0:
          return(KEY_ALT+KEY_SHIFT+'~');
        case 0xbd:
          return(KEY_ALT+KEY_SHIFT+'_');
        case 0xbb:
          return(KEY_ALT+KEY_SHIFT+'=');
        case 0xdc:
          return(KEY_ALT+KEY_SHIFT+KEY_BACKSLASH);
        case 0xdd:
          return(KEY_ALT+KEY_SHIFT+KEY_BACKBRACKET);
        case 0xdb:
          return(KEY_ALT+KEY_SHIFT+KEY_BRACKET);
        case 0xde:
          return(KEY_ALT+KEY_SHIFT+KEY_QUOTE);
        case 0xba:
          return(KEY_ALT+KEY_SHIFT+KEY_COLON);
        case 0xbf:
          if(WaitInFastFind)
            return(KEY_ALT+KEY_SHIFT+'?');
          else
            return(KEY_ALT+KEY_SHIFT+KEY_SLASH);
        case 0xbe:
          return(KEY_ALT+KEY_SHIFT+KEY_DOT);
        case 0xbc:
          return(KEY_ALT+KEY_SHIFT+KEY_COMMA);
      }
    switch(KeyCode)
    {
      case VK_DIVIDE:
        if(WaitInFastFind)
          return(KEY_ALT+KEY_SHIFT+'/');
        else
          return(KEY_ALTSHIFT|KEY_DIVIDE);
      case VK_MULTIPLY:
        if(WaitInFastFind)
        {
          return(KEY_ALT+KEY_SHIFT+'*');
        }
        else
          return(KEY_ALTSHIFT|KEY_MULTIPLY);
      case VK_CAPITAL:
        return(KEY_NONE);
      case VK_PAUSE:
        return(KEY_ALTSHIFT|KEY_BREAK);
    }
    if (Char.AsciiChar)
    {
      if (Opt.AltGr && WinVer.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
        if (rec->Event.KeyEvent.dwControlKeyState & RIGHT_ALT_PRESSED)
          return(Char.AsciiChar);
      return(KEY_ALT+KEY_SHIFT+Char.AsciiChar);
    }
    if (!RealKey && (KeyCode==VK_MENU || KeyCode==VK_SHIFT))
      return(KEY_NONE);
    if (KeyCode)
      return(KEY_ALT+KEY_SHIFT+KeyCode);
  }


  /* ------------------------------------------------------------- */
  if (CtrlPressed && ShiftPressed)
  {
//_SVS(if(KeyCode!=VK_CONTROL && KeyCode!=VK_SHIFT) SysLog("CtrlShift -> |0x%08X (%c)|0x%08X (%c)|",KeyCode,(KeyCode?KeyCode:' '),Char.AsciiChar,(Char.AsciiChar?Char.AsciiChar:' ')));
    if (KeyCode>='0' && KeyCode<='9')
      return(KEY_CTRLSHIFT0+KeyCode-'0');
    if (KeyCode>='A' && KeyCode<='Z')
      return(KEY_CTRLSHIFTA+KeyCode-'A');
    switch(KeyCode)
    {
      case 0xbe:
        return(KEY_CTRLSHIFTDOT);
      case 0xdb:
        return(KEY_CTRLSHIFTBRACKET);
      case 0xdd:
        return(KEY_CTRLSHIFTBACKBRACKET);
      case 0xbf:
        return(KEY_CTRLSHIFTSLASH);
      case 0xdc:
        return(KEY_CTRLSHIFTBACKSLASH);
      case VK_DIVIDE:
        return(KEY_CTRLSHIFT|KEY_DIVIDE);
      case VK_MULTIPLY:
        return(KEY_CTRLSHIFT|KEY_MULTIPLY);
    }
    if(Opt.ShiftsKeyRules) //???
      switch(KeyCode)
      {
        case 0xc0:
          return(KEY_CTRL+KEY_SHIFT+'~');
        case 0xbd:
          return(KEY_CTRL+KEY_SHIFT+'-');
        case 0xbb:
          return(KEY_CTRL+KEY_SHIFT+'=');
        case 0xde:
          return(KEY_CTRL+KEY_SHIFT+KEY_QUOTE);
        case 0xba:
          return(KEY_CTRL+KEY_SHIFT+KEY_COLON);
        case 0xbc:
          return(KEY_CTRL+KEY_SHIFT+KEY_COMMA);
      }
    if (Char.AsciiChar)
      return(KEY_CTRL|KEY_SHIFT+Char.AsciiChar);
    if (!RealKey && (KeyCode==VK_CONTROL || KeyCode==VK_SHIFT))
      return(KEY_NONE);
    if (KeyCode)
      return(KEY_CTRL|KEY_SHIFT+KeyCode);
  }


  /* ------------------------------------------------------------- */
  if ((CtrlState & RIGHT_CTRL_PRESSED)==RIGHT_CTRL_PRESSED)
  {
    if (KeyCode>='0' && KeyCode<='9')
      return(KEY_RCTRL0+KeyCode-'0');
  }


  /* ------------------------------------------------------------- */
  if (!CtrlPressed && !AltPressed && !ShiftPressed)
  {
    switch(KeyCode)
    {
      case VK_DIVIDE:
        return(KEY_DIVIDE);
      case VK_CANCEL:
        return(KEY_BREAK);
      case VK_MULTIPLY:
        return(KEY_MULTIPLY);
    }
  }

  /* ------------------------------------------------------------- */
  if (CtrlPressed)
  {
//_SVS(if(KeyCode!=VK_CONTROL) SysLog("Ctrl -> |0x%08X (%c)|0x%08X (%c)|",KeyCode,(KeyCode?KeyCode:' '),Char.AsciiChar,(Char.AsciiChar?Char.AsciiChar:' ')));
    if (KeyCode>='0' && KeyCode<='9')
      return(KEY_CTRL0+KeyCode-'0');
    if (KeyCode>='A' && KeyCode<='Z')
      return(KEY_CTRL+KeyCode);
    switch(KeyCode)
    {
      case 0xbc:
        return(KEY_CTRLCOMMA);
      case 0xbe:
        return(KEY_CTRLDOT);
      case 0xbf:
        return(KEY_CTRLSLASH);
      case 0xdb:
        return(KEY_CTRLBRACKET);
      case 0xdc:
        return(KEY_CTRLBACKSLASH);
      case 0xdd:
        return(KEY_CTRLBACKBRACKET);
      case 0xde:
        return(KEY_CTRLQUOTE);
      case VK_MULTIPLY:
        return(KEY_CTRL|KEY_MULTIPLY);
      case VK_DIVIDE:
        return(KEY_CTRL|KEY_DIVIDE);
    }

    if(Opt.ShiftsKeyRules) //???
      switch(KeyCode)
      {
        case 0xc0:
          return(KEY_CTRL+'~');
        case 0xbd:
          return(KEY_CTRL+'-');
        case 0xbb:
          return(KEY_CTRL+'=');
        case 0xba:
          return(KEY_CTRL+KEY_COLON);
      }

    if (KeyCode)
    {
      if (!RealKey && KeyCode==VK_CONTROL)
        return(KEY_NONE);
      return(KEY_CTRL+KeyCode);
    }
  }

  /* ------------------------------------------------------------- */
  if (AltPressed)
  {
//_SVS(if(KeyCode!=VK_MENU) SysLog("Alt -> |0x%08X (%c)|0x%08X (%c)|",KeyCode,(KeyCode?KeyCode:' '),Char.AsciiChar,(Char.AsciiChar?Char.AsciiChar:' ')));
    if(Opt.ShiftsKeyRules) //???
      switch(KeyCode)
      {
        case 0xc0:
          return(KEY_ALT+'~');
        case 0xbd:
          if(WaitInFastFind)
            return(KEY_ALT+KEY_SHIFT+'_');
          else
            return(KEY_ALT+'-');
        case 0xbb:
          return(KEY_ALT+'=');
        case 0xdc:
          return(KEY_ALT+KEY_BACKSLASH);
        case 0xdd:
          return(KEY_ALT+KEY_BACKBRACKET);
        case 0xdb:
          return(KEY_ALT+KEY_BRACKET);
        case 0xde:
          return(KEY_ALT+KEY_QUOTE);
        case 0xba:
          return(KEY_ALT+KEY_COLON);
        case 0xbf:
          return(KEY_ALT+KEY_SLASH);
      }
    switch(KeyCode)
    {
      case 0xbc:
        return(KEY_ALTCOMMA);
      case 0xbe:
        return(KEY_ALTDOT);
      case VK_DIVIDE:
        if(WaitInFastFind)
          return(KEY_ALT+KEY_SHIFT+'/');
        else
          return(KEY_ALT|KEY_DIVIDE);
      case VK_MULTIPLY:
//        if(WaitInFastFind)
//          return(KEY_ALT+KEY_SHIFT+'*');
//        else
          return(KEY_ALT|KEY_MULTIPLY);
      case VK_PAUSE:
        return(KEY_ALT+KEY_BREAK);
    }
    if (Char.AsciiChar)
    {
      if (Opt.AltGr && WinVer.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
        if (rec->Event.KeyEvent.dwControlKeyState & RIGHT_ALT_PRESSED)
          return(Char.AsciiChar);
      if(!Opt.ShiftsKeyRules || WaitInFastFind > 0)
        return(LocalUpper(Char.AsciiChar)+KEY_ALT);
      else if(WaitInMainLoop ||
              !Opt.HotkeyRules //????
           )
        return(KEY_ALT+Char.AsciiChar);
    }
    if (KeyCode==VK_CAPITAL)
      return(KEY_NONE);
    if (!RealKey && KeyCode==VK_MENU)
      return(KEY_NONE);
    return(KEY_ALT+KeyCode);
  }

  if (Char.AsciiChar)
    return(Char.AsciiChar);
  return(KEY_NONE);
}
