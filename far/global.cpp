/*
global.cpp

���������� ����������

*/

/* Revision: 1.36 30.03.2002 $ */

/*
Modify:
  30.03.2002 OT
    - ����� ����������� ���� �314 (���� 1250) ���������� ��������
      ���� �� ������.
  19.03.2002 SVS
    + MAC_EOL_fmt
  01.03.2002 SVS
    ! FarTmpXXXXXX - ������� �� �������������.
  21.02.2002 SVS
    + ProcessException - ������� �������� ��������� ����������
  22.01.2002 SVS
    + OnliEditorViewerUsed,  =TRUE, ���� ����� ��� /e ��� /v
  15.01.2002 SVS
    ! ������� ������ ������� ��� ���� ��������� ������ FarTmpXXXXXX
  14.01.2002 SVS
    + DOS_EOL_fmt[], UNIX_EOL_fmt (�� editor.cpp)
  26.11.2001 SVS
    + MouseEventFlags, PreMouseEventFlags - ���� ������� ����
  23.10.2001 SVS
    + WidthNameForMessage - 38% ��� ������� �������� ����� � �������-���������
  21.10.2001 SVS
    + PrevScrX,PrevScrY - ���������� ������� ������� (��� ����������������
      ��������)
  19.10.2001 SVS
    + PreRedraw* - ��� ����������� BugZ#85
  03.10.2001 SVS
    ! � ��������� ���������� ���������, ��� IsDebuggerPresent() ���� ������
      � NT, ��� ���... ��� ����� �� �����������!
  18.09.2001 SVS
    ! "FarTmpXXXXXX" -> "FARTMPXXXXXX".
  07.08.2001 SVS
    + IsProcessVE_FindFile - ���� ������� "������/��������" �� �����
      ������ ������?
  25.07.2001 SVS
    + IsProcessAssignMacroKey - ���� ������� ���������� ������� � �������?
  25.07.2001 SVS
    ! Copyright ��������� �� ctrlobj.cpp.
  24.07.2001 SVS
    + NotUseCAS: ���� �� ������ ������ Ctrl-Alt-Shift
  27.06.2001 SVS
    + LanguageLoaded
  25.06.2001 SVS
    ! ����� SEARCHSTRINGBUFSIZE
  21.05.2001 OT
    + ���������� CONSOLE_SCREEN_BUFFER_INFO InitScreenBufferInfo, CurScreenBufferInfo
      ����� ��� ����� ������������� ��������� AltF9
  12.05.2001 DJ
    ! ��� ��������� #include: ����� #include "ctrlobj.hpp", � ��������� ��
      CtrlObject �������� � ctrlobj.hpp; ��� ������� ���������
  06.05.2001 DJ
    ! �������� #include
  26.04.2001 VVM
    - ������� ����� MouseWheeled
  24.04.2001 SVS
    + MouseWheeled - ������� ����, ��� ��������� ������
  01.03.2001 SVS
    + RegColorsHighlight - ��� ����������
  24.01.2001 SVS
    + KeyQueue - ���������� ������� ����������
  09.01.2001 SVS
    + WaitInFastFind - ��������� �� ��������� ������� ��� ������� ShiftsKeyRules
  30.12.2000 SVS
    + IsCryptFileASupport
  22.12.2000 SVS
    + hConOut,hConInp ������ ��������� �� interf.cpp
  07.12.2000 SVS
    + ������ ������� �� ����� farversion.inc
  11.11.2000 SVS
    ! "FarTmpXXXXXX" �������� �� ���������� FarTmpXXXXXX
  23.08.2000 SVS
    + MButtonPressed - ��� ������� ������� ����.
  03.08.2000 KM 1.04
    + ��������� ���������� ���������� int GlobalSearchWholeWords.
  03.08.2000 SVS
    ! WordDiv -> Opt.WordDiv
  03.08.2000 SVS
    + ���� ��� ������ �������� ��������
  07.07.2000 SVS
    + �������������� ���� �� ������� (����� ��� ��������������)
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/

#include "headers.hpp"
#pragma hdrstop

#include "global.hpp"
#include "farqueue.hpp"

/* $ 29.06.2000 tran
  ����� char *CopyRight �� inc ����� */
#include "copyright.inc"
/* tran $ */

/* $ 07.12.2000 SVS
   + ������ ������� �� ����� farversion.inc
*/
#include "farversion.inc"
/* SVS $ */

OSVERSIONINFO WinVer={0};

struct Options Opt;

// ������� ���������� (Win2K) ���������? (��� SetAttr!)
BOOL IsCryptFileASupport=FALSE;

// �������� ���� ��������?
BOOL LanguageLoaded=FALSE;

// ���� �� ������ ������ Ctrl-Alt-Shift
BOOL NotUseCAS=FALSE;

// ���� ������� ���������� ������� � �������?
BOOL IsProcessAssignMacroKey=FALSE;

// ���� ������� "������/��������" �� ����� ������ ������?
BOOL IsProcessVE_FindFile=FALSE;

// ���� ������� �������� ������ � �������?
int WaitInFastFind=FALSE;

// �� �������� � �������� �����?
int WaitInMainLoop=FALSE;

// "��������������" ������� ����� ������
FarQueue<DWORD> *KeyQueue=NULL;
int AltPressed=0,CtrlPressed=0,ShiftPressed=0;
int LButtonPressed=0,RButtonPressed=0,MButtonPressed=0;
int PrevMouseX=0,PrevMouseY=0,MouseX=0,MouseY=0;
int PreMouseEventFlags=0,MouseEventFlags=0;

CONSOLE_SCREEN_BUFFER_INFO InitScreenBufferInfo;
CONSOLE_SCREEN_BUFFER_INFO CurScreenBufferInfo;
int ScrX,ScrY;
int PrevScrX,PrevScrY;
HANDLE hConOut,hConInp;

clock_t StartIdleTime;

DWORD InitialConsoleMode;

clock_t StartExecTime;

char FarPath[NM];
/* $ 03.08.2000 SVS
    + ���� ��� ������ �������� ��������
*/
char MainPluginsPath[NM];
/* SVS $ */

char LastFarTitle[512];
char RegColorsHighlight[]="Colors\\Highlight";


char GlobalSearchString[SEARCHSTRINGBUFSIZE];
int GlobalSearchCase;
/* $ 29.07.2000 KM
   ���������� ����������, �������� �������� "Whole words" ��� ������
*/
int GlobalSearchWholeWords;
/* KM $*/
int GlobalSearchReverse;

int ScreenSaverActive;

Editor *CurrentEditor;
int CloseFAR=FALSE,CloseFARMenu=FALSE;

// ��� �����������
int  RegVer;
char RegName[256];

int CmpNameSearchMode;
int DisablePluginsOutput;
int CmdMode;

PISDEBUGGERPRESENT pIsDebuggerPresent=NULL;

PREREDRAWFUNC PreRedrawFunc=NULL;
struct PreRedrawParamStruct PreRedrawParam={0};

int WidthNameForMessage=0;

const char DOS_EOL_fmt[]  ="\r\n",
           UNIX_EOL_fmt[] ="\n",
           MAC_EOL_fmt[]  ="\r";

int OnliEditorViewerUsed=FALSE;

BOOL ProcessException=FALSE;
