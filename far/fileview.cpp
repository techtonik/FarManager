/*
fileview.cpp

�������� ����� - ���������� ��� viewer.cpp

*/

/* Revision: 1.56 22.05.2002 $ */

/*
Modify:
  22.05.2002 SVS
    + ViewerControl()
  13.05.2002 VVM
    + ���������� ��������� ������� ����� ���������������� �� ����.
  26.03.2002 DJ
    ! ��� ������� �������� - �� ����� ����� � �������
  22.03.2002 SVS
    - strcpy - Fuck!
  19.03.2002 SVS
    - BugZ#373 - F3 Ctrl-O - ����� ������
  28.01.2002 OT
    - ��� ��������� �������� ����� �� �������� �����
  28.12.2001 DJ
    ! ����������� ��������� Ctrl-F10
  17.12.2001 KM
    ! ���� !GetCanLoseFocus() ����� �� Alt-F11 ������ ������ ������.
  08.12.2001 OT
    Bugzilla #144 ������� � �����, F4 �� �����, Ctrl-F10.
  27.11.2001 DJ
    + Local � ViewerConfig
  14.11.2001 SVS
    ! Ctrl-F10 �� �������, � ������ �������������
  02.11.2001 IS
    - ������������� ���������� ������ �������� ���� ���������� �� �������
  12.10.2001 VVM
    ! ����������� ������������ ��� ����� � �������.
  11.10.2001 IS
    ! ���� ������� ������� ���� ��� �������� � ������������� � ��������
      �� F6, �� ������� ���� ��� �� �����.
  27.09.2001 IS
    - ����� ������ ��� ������������� strncpy
  08.09.2001 IS
    + �������������� �������� � ������� ������������: DisableHistory
  17.08.2001 KM
    + ��������� ������� SetSaveToSaveAs ��� ��������� ��������� �������
      �� ������� F2 � ����� ShiftF2 ��� ������, � ������ ��������������
      ���������� ����� �� ������.
    ! ������� ����������� � ������� Init ��� ������ SaveToSaveAs.
    - ������ � KeyBar ������� �� ������� F12 ��� CanLoseFocus=TRUE
  11.07.2001 OT
    ������� CtrlAltShift � Manager
  25.06.2001 IS
   ! ��������� const
  14.06.2001 OT
    ! "����" ;-)
  06.06.2001 OT
    ! ������� OnChangeFocus �� ����������� ������� ... ������������� :)
    + �������� ���������� ~FileViewer()... � �������������� ������
  05.06.2001 tran
    + ����� FileView - �������� OnChangeFocus
  27.05.2001 DJ
    - �� ������ DeleteFrame() � ������ ������ ��������
  26.05.2001 OT
    - ����� �������� ��������� � ��������� ������
  20.05.2001 DJ
    - ������� �������
  15.05.2001 OT
    ! NWZ -> NFZ
  14.05.2001 OT
    ! ��������� ������� ������ ���������� ReplaceFrame (��� ������������ � ��������)
  12.05.2001 DJ
    ! ��������� �� OnChangeFocus ���������� � Frame
    ! ����� ������������� ExitCode
  11.05.2001 OT
    ! ��������� Background
  10.05.2001 DJ
    + Alt-F11 - view/edit history
    + Ctrl-F10 ������ ������������� �� ������
  07.05.2001 SVS
    ! SysLog(); -> _D(SysLog());
  07.05.2001 DJ
    - ������ �� ����������
  06.05.2001 DJ
    ! �������� #include
    + ��������� F6 ��� NWZ
  06.05.2001 ��
    ! �������������� Window � Frame :)
  05.05.2001 DJ
    + �������� NWZ
  29.04.2001 ��
    + ��������� NWZ �� ����������
  28.04.2001 VVM
    + KeyBar ���� ����� ������������ �������.
  10.04.2001 IS
    ! �� ������ SetCurDir ��� ctrl-f10, ���� ������ ���� ��� ���� �� ��������
      �������, ��� ����� ���������� ����, ��� ��������� � ���������
      ������� �� ������������.
  29.03.2001 IS
    + ������ � ��������� ������ ViewerOptions ��� KEY_ALTSHIFTF9
  22.03.2001 SVS
    - "���������" ������� ����� ���������� �������
  03.01.2001 SVS
    ! ��� KEY_ALTSHIFTF9 ������ ������� Show()
  19.12.2000 SVS
    + Alt-Shift-F9 - ����� ������� �������� (� ������ IS)
    - [*] ������ "����������" ����� � LNG-������ ��� ������� F9 :-)
      ���������� -����������, �� �� ����������.
  16.12.2000 tran 1.14
    ! Ctrl-F10 ������� �� ��������� ������
  03.11.2000 OT
    ! �������� �������� ������������� ��������
  02.11.2000 OT
    ! �������� �������� �� ����� ������, ����������� ��� ��� �����.
  27.09.2000 SVS
    + ������ ����� � �������������� ������� PrintMan
    ! Ctrl-Alt-Shift - ���������, ���� ����.
  15.09.2000 tran 1.09
    - FKL bug
  14.09.2000 SVS
    - Bug #NN1 - ���������  ���������� KeyBar (��. �������� � Patch#191)
  24.08.2000 SVS
    + ��������� ������� ������ ���������� �� ������� CtrlAltShift
  07.08.2000 SVS
    + ������� �������� ����������� �������������� ������
  22.07.2000 tran 1.06
    + Ctrl-F10 ������� � ���������� �� ���� �� ������� ������
  21.07.2000 tran 1.05
      - �������� ��� CtrlO ��� ����������� �������
  15.07.2000 tran
      + CtrlB ���������/�������� keybar
  04.07.2000 tran
    + �� ���������� ������ ���� ��� ������������� ������� ����
  29.06.2000 tran
    + �������� ���� �������������� ������
  28.06.2000 tran
    - NT Console resize
      adding SetScreenPosition
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/

#include "headers.hpp"
#pragma hdrstop

#include "fileview.hpp"
#include "global.hpp"
#include "fn.hpp"
#include "lang.hpp"
#include "keys.hpp"
#include "ctrlobj.hpp"
#include "filepanels.hpp"
#include "panel.hpp"
#include "history.hpp"
#include "manager.hpp"
#include "fileedit.hpp"
#include "cmdline.hpp"
#include "savescr.hpp"

FileViewer::FileViewer(const char *Name,int EnableSwitch,int DisableHistory,
                       int DisableEdit,long ViewStartPos,char *PluginData,
                       NamesList *ViewNamesList,int ToSaveAs)
{
  _OT(SysLog("[%p] FileViewer::FileViewer(I variant...)", this));
  FileViewer::DisableEdit=DisableEdit;
  SetPosition(0,0,ScrX,ScrY);
  FullScreen=TRUE;
  Init(Name,EnableSwitch,DisableHistory,ViewStartPos,PluginData,ViewNamesList,ToSaveAs);
}


FileViewer::FileViewer(const char *Name,int EnableSwitch,int DisableHistory,
                       const char *Title, int X1,int Y1,int X2,int Y2)
{
  _OT(SysLog("[%p] FileViewer::FileViewer(II variant...)", this));
  DisableEdit=TRUE;
  /* $ 02.11.2001 IS
       ������������� ���������� ������ �������� ���� ���������� �� �������
  */
  if(X1<0) X1=0;
  if(Y1<0) Y1=0;
  /* IS $ */
  SetPosition(X1,Y1,X2,Y2);
  FullScreen=(X1==0 && Y1==0 && X2==ScrX && Y2==ScrY);
  View.SetTitle(Title);
  Init(Name,EnableSwitch,DisableHistory,-1,"",NULL,FALSE);
}


void FileViewer::Init(const char *name,int EnableSwitch,int disableHistory, ///
                      long ViewStartPos,char *PluginData,
                      NamesList *ViewNamesList,int ToSaveAs)
{
  RedrawTitle = FALSE;
  ViewKeyBar.SetOwner(this);
  ViewKeyBar.SetPosition(X1,Y2,X2,Y2);
  /* $ 07.05.2001 DJ */
  KeyBarVisible = Opt.ShowKeyBarViewer;
  /* DJ $ */
  /* $ 20.05.2001 DJ */
  MacroMode = MACRO_VIEWER;
  /* DJ $ */
  View.SetPluginData(PluginData);
  /* $ 07.08.2000 SVS
  */
  View.SetHostFileViewer(this);
  /* SVS $ */

  DisableHistory=disableHistory; ///
  strncpy(Name,name,sizeof(Name)-1); ///
  SetCanLoseFocus(EnableSwitch);

  /* $ 17.08.2001 KM
    ��������� ��� ������ �� AltF7. ��� �������������� ���������� ����� ��
    ������ ��� ������� F2 ������� ����� ShiftF2.
  */
  SaveToSaveAs=ToSaveAs;
  /* KM $ */

  /* $ 07.08.2000 SVS
    ! ���, �������� KeyBar ������� � ��������� ������� */
  InitKeyBar();
  /* SVS $*/

  /* $ 04.07.2000 tran
     + add TRUE as 'warning' parameter */
  if (!View.OpenFile(Name,TRUE))
  /* tran 04.07.2000 $ */
  {
    /* $ 26.03.2002 DJ
       ��� ������� �������� - �� ����� ����� � �������
    */
    DisableHistory = TRUE;
    /* DJ $ */
    FrameManager->DeleteFrame(this);
    ExitCode=FALSE;
    return;
  }

  if (ViewStartPos!=-1)
    View.SetFilePos(ViewStartPos);
  if (ViewNamesList)
    View.SetNamesList(ViewNamesList);
  ExitCode=TRUE;
  ViewKeyBar.Show();
  /* $ 15.07.2000 tran
     dirty trick :( */
  if ( Opt.ShowKeyBarViewer==0 )
    ViewKeyBar.Hide0();
  /* tran 15.07.2000 $ */


  sprintf(NewTitle,MSG(MInViewer),PointToName(Name));
  SetFarTitle(NewTitle);
  ShowConsoleTitle();
  F3KeyOnly=TRUE;
  if (EnableSwitch) {
    FrameManager->InsertFrame(this);
  } else {
    FrameManager->ExecuteFrame(this);
  }
}


/* $ 07.08.2000 SVS
  ������� ������������� KeyBar Labels
*/
void FileViewer::InitKeyBar(void)
{
  /* $ 29.06.2000 tran
     ������� �������� ���� �������������� ������ */
  char *FViewKeys[]={MSG(MViewF1),MSG(MViewF2),MSG(MViewF3),MSG(MViewF4),MSG(MViewF5),DisableEdit ? "":MSG(MViewF6),MSG(MViewF7),MSG(MViewF8),MSG(MViewF9),MSG(MViewF10),MSG(MViewF11),(GetCanLoseFocus())?MSG(MViewF12):""};
  char *FViewShiftKeys[]={MSG(MViewShiftF1),MSG(MViewShiftF2),MSG(MViewShiftF3),MSG(MViewShiftF4),MSG(MViewShiftF5),MSG(MViewShiftF6),MSG(MViewShiftF7),MSG(MViewShiftF8),MSG(MViewShiftF9),MSG(MViewShiftF10),MSG(MViewShiftF11),MSG(MViewShiftF12)};
  /* $ 17.12.2001 KM
     ! ���� !GetCanLoseFocus() ����� �� Alt-F11 ������ ������ ������.
  */
  char *FViewAltKeys[]={MSG(MViewAltF1),MSG(MViewAltF2),MSG(MViewAltF3),MSG(MViewAltF4),MSG(MViewAltF5),MSG(MViewAltF6),MSG(MViewAltF7),MSG(MViewAltF8),MSG(MViewAltF9),MSG(MViewAltF10),(GetCanLoseFocus())?MSG(MViewAltF11):"",MSG(MViewAltF12)};
  /* KM $ */
  char *FViewCtrlKeys[]={MSG(MViewCtrlF1),MSG(MViewCtrlF2),MSG(MViewCtrlF3),MSG(MViewCtrlF4),MSG(MViewCtrlF5),MSG(MViewCtrlF6),MSG(MViewCtrlF7),MSG(MViewCtrlF8),MSG(MViewCtrlF9),MSG(MViewCtrlF10),MSG(MViewCtrlF11),MSG(MViewCtrlF12)};

  if(CtrlObject->Plugins.FindPlugin(SYSID_PRINTMANAGER) == -1)
    FViewAltKeys[5-1]="";

  /* $ 07.08.2000 SVS
     ������� �������� ����������� �������������� ������ */
  char *FViewAltShiftKeys[]={MSG(MViewAltShiftF1),MSG(MViewAltShiftF2),MSG(MViewAltShiftF3),MSG(MViewAltShiftF4),MSG(MViewAltShiftF5),MSG(MViewAltShiftF6),MSG(MViewAltShiftF7),MSG(MViewAltShiftF8),MSG(MViewAltShiftF9),MSG(MViewAltShiftF10),MSG(MViewAltShiftF11),MSG(MViewAltShiftF12)};
  char *FViewCtrlShiftKeys[]={MSG(MViewCtrlShiftF1),MSG(MViewCtrlShiftF2),MSG(MViewCtrlShiftF3),MSG(MViewCtrlShiftF4),MSG(MViewCtrlShiftF5),MSG(MViewCtrlShiftF6),MSG(MViewCtrlShiftF7),MSG(MViewCtrlShiftF8),MSG(MViewCtrlShiftF9),MSG(MViewCtrlShiftF10),MSG(MViewCtrlShiftF11),MSG(MViewCtrlShiftF12)};
  char *FViewCtrlAltKeys[]={MSG(MViewCtrlAltF1),MSG(MViewCtrlAltF2),MSG(MViewCtrlAltF3),MSG(MViewCtrlAltF4),MSG(MViewCtrlAltF5),MSG(MViewCtrlAltF6),MSG(MViewCtrlAltF7),MSG(MViewCtrlAltF8),MSG(MViewCtrlAltF9),MSG(MViewCtrlAltF10),MSG(MViewCtrlAltF11),MSG(MViewCtrlAltF12)};
  /* SVS $*/

  ViewKeyBar.Set(FViewKeys,sizeof(FViewKeys)/sizeof(FViewKeys[0]));
  ViewKeyBar.SetShift(FViewShiftKeys,sizeof(FViewShiftKeys)/sizeof(FViewShiftKeys[0]));
  ViewKeyBar.SetAlt(FViewAltKeys,sizeof(FViewAltKeys)/sizeof(FViewAltKeys[0]));
  ViewKeyBar.SetCtrl(FViewCtrlKeys,sizeof(FViewCtrlKeys)/sizeof(FViewCtrlKeys[0]));
  /* $ 07.08.2000 SVS
     ������� �������� ����������� �������������� ������ */
  ViewKeyBar.SetCtrlAlt(FViewCtrlAltKeys,sizeof(FViewCtrlAltKeys)/sizeof(FViewCtrlAltKeys[0]));
  ViewKeyBar.SetCtrlShift(FViewCtrlShiftKeys,sizeof(FViewCtrlShiftKeys)/sizeof(FViewCtrlShiftKeys[0]));
  ViewKeyBar.SetAltShift(FViewAltShiftKeys,sizeof(FViewAltShiftKeys)/sizeof(FViewAltShiftKeys[0]));
  /* SVS $ */
  /* tran $ */

  SetKeyBar(&ViewKeyBar);
  /* $ 15.07.2000 tran
     ShowKeyBarViewer support*/
  View.SetPosition(X1,Y1,X2,Y2-(Opt.ShowKeyBarViewer?1:0));
  /* tran 15.07.2000 $ */

  View.SetViewKeyBar(&ViewKeyBar);
}
/* SVS $ */

void FileViewer::Show()
{
  if (FullScreen)
  {
    /* $ 15.07.2000 tran
       + keybar hide/show support */
    if ( Opt.ShowKeyBarViewer )
    {
        ViewKeyBar.SetPosition(0,ScrY,ScrX,ScrY);
        ViewKeyBar.Redraw();
    }
    SetPosition(0,0,ScrX,ScrY-(Opt.ShowKeyBarViewer?1:0));
    View.SetPosition(0,0,ScrX,ScrY-(Opt.ShowKeyBarViewer?1:0));
    /* tran 15.07.2000 $ */
  }
  ScreenObject::Show();
}


void FileViewer::DisplayObject()
{
  View.Show();
}


int FileViewer::ProcessKey(int Key)
{
  if (RedrawTitle && ((Key & 0x00ffffff) < KEY_END_FKEY))
    ShowConsoleTitle();

  if (Key!=KEY_F3 && Key!=KEY_NUMPAD5)
    F3KeyOnly=FALSE;
  switch(Key)
  {
    /* $ 22.07.2000 tran
       + ����� �� ctrl-f10 � ���������� ������� �� ���� */
    case KEY_CTRLF10:
      {
        if (View.isTemporary()){
          return(TRUE);
        }
        SaveScreen Sc;
        /* $ 28.12.2001 DJ
           ����������� ��������� Ctrl-F10
        */
        char FileName[NM];
        View.GetFileName(FileName);
        CtrlObject->Cp()->GoToFile (FileName);
        RedrawTitle = TRUE;
        /* DJ $ */
        return (TRUE);
      }
    /* tran 22.07.2000 $ */
    /* $ 15.07.2000 tran
       + CtrlB switch KeyBar*/
    case KEY_CTRLB:
      Opt.ShowKeyBarViewer=!Opt.ShowKeyBarViewer;
      if ( Opt.ShowKeyBarViewer )
        ViewKeyBar.Show();
      else
        ViewKeyBar.Hide0(); // 0 mean - Don't purge saved screen
      Show();
      /* $ 07.05.2001 DJ */
      KeyBarVisible = Opt.ShowKeyBarViewer;
      /* DJ $ */
      return (TRUE);
    /* tran 15.07.2000 $ */
    /* $ 24.08.2000 SVS
       + ��������� ������� ������ ���������� �� ������� CtrlAltShift
    */
/* $ KEY_CTRLALTSHIFTPRESS ������� � manager OT */
    case KEY_CTRLO:
      FrameManager->ShowBackground();
      SetCursorType(FALSE,0);
      WaitKey();
      FrameManager->RefreshFrame();
      return(TRUE);
    /* SVS $ */
    case KEY_F3:
    case KEY_NUMPAD5:
      if (F3KeyOnly)
        return(TRUE);
    case KEY_ESC:
    case KEY_F10:
      FrameManager->DeleteFrame();
      return(TRUE);
    case KEY_F6:
      if (!DisableEdit)
      {
        /* $ 11.10.2001 IS
            ���� ������������� � ��������, �� ������� ���� ��� ��
            �����
        */
        SetTempViewName("");
        /* IS $ */
        SetExitCode(0);
        char ViewFileName[NM];
        View.GetFileName(ViewFileName);
        long FilePos=View.GetFilePos();
        /* $ 06.05.2001 DJ ��������� F6 ��� NWZ */
        FileEditor *ShellEditor = new FileEditor (ViewFileName, FALSE, GetCanLoseFocus(),
          -2, FilePos, FALSE, NULL, SaveToSaveAs);
        ShellEditor->SetEnableF6 (TRUE);
        /* $ 07.05.2001 DJ ��������� NamesList */
        ShellEditor->SetNamesList (View.GetNamesList());
        /* DJ $ */
        /* DJ $ */
        FrameManager->DeleteFrame(this); // Insert ��� ���� ������ ������������
        ShowTime(2);
      }
      return(TRUE);

    /* $ 27.09.2000 SVS
       + ������ ����� � �������������� ������� PrintMan
    */
    case KEY_ALTF5:
    {
      if(CtrlObject->Plugins.FindPlugin(SYSID_PRINTMANAGER) != -1)
        CtrlObject->Plugins.CallPlugin(SYSID_PRINTMANAGER,OPEN_VIEWER,0); // printman
      return TRUE;
    }
    /* SVS $*/

    /* $ 19.12.2000 SVS
       ����� ������� �������� (� ������ IS)
    */
    case KEY_ALTSHIFTF9:
      /* $ 29.03.2001 IS
           ������ � ��������� ������ ViewerOptions
      */
      struct ViewerOptions ViOpt;

      ViOpt.TabSize=View.GetTabSize();
      ViOpt.AutoDetectTable=View.GetAutoDetectTable();
      ViOpt.ShowScrollbar=View.GetShowScrollbar();
      ViOpt.ShowArrows=View.GetShowArrows();

      /* $ 27.11.2001 DJ
         Local � ViewerConfig
      */
      ViewerConfig(ViOpt,1);
      /* DJ $ */

      View.SetTabSize(ViOpt.TabSize);
      View.SetAutoDetectTable(ViOpt.AutoDetectTable);
      View.SetShowScrollbar(ViOpt.ShowScrollbar);
      View.SetShowArrows(ViOpt.ShowArrows);
      /* IS $ */
      if ( Opt.ShowKeyBarViewer )
        ViewKeyBar.Show();
      View.Show();
      return TRUE;
    /* SVS $ */

    /* $ 10.05.2001 DJ
       Alt-F11 - show view/edit history
    */
    case KEY_ALTF11:
      if (GetCanLoseFocus())
        CtrlObject->CmdLine->ShowViewEditHistory();
      return TRUE;
    /* DJ $ */

    default:
//      ���� ����� - �� ������� (�� �������� � ���������� :-)
//      if (CtrlObject->Macro.IsExecuting() || !View.ProcessViewerInput(&ReadRec))
      {
        /* $ 22.03.2001 SVS
           ��� ������� �� ��������� :-)
        */
        if (!CtrlObject->Macro.IsExecuting())
          if ( Opt.ShowKeyBarViewer )
              ViewKeyBar.Show();
        /* SVS $ */
        if (!ViewKeyBar.ProcessKey(Key))
          return(View.ProcessKey(Key));
      }
      return(TRUE);
  }
}


int FileViewer::ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent)
{
  F3KeyOnly=FALSE;
  if (!View.ProcessMouse(MouseEvent))
    if (!ViewKeyBar.ProcessMouse(MouseEvent))
      return(FALSE);
  return(TRUE);
}


int FileViewer::GetTypeAndName(char *Type,char *Name)
{
  if ( Type ) strcpy(Type,MSG(MScreensView));
  if ( Name ) View.GetFileName(Name);
  return(MODALTYPE_VIEWER);
}


void FileViewer::ShowConsoleTitle()
{
  View.ShowConsoleTitle();
  RedrawTitle = FALSE;
}


void FileViewer::SetTempViewName(const char *Name)
{
  View.SetTempViewName(Name);
}


FileViewer::~FileViewer()
{
  _OT(SysLog("[%p] ~FileViewer::FileViewer()",this));
}

void FileViewer::OnDestroy()
{
  _OT(SysLog("[%p] FileViewer::OnDestroy()",this));
  if (!DisableHistory && (CtrlObject->Cp()->ActivePanel!=NULL || strcmp(Name,"-")!=0))
  {
    char FullFileName[NM];
    View.GetFileName(FullFileName);
    CtrlObject->ViewHistory->AddToHistory(FullFileName,MSG(MHistoryView),0);
  }
}

int FileViewer::FastHide()
{
  return Opt.AllCtrlAltShiftRule & CASR_VIEWER;
}

int FileViewer::ViewerControl(int Command,void *Param)
{
  _VCTLLOG(CleverSysLog SL("FileViewer::ViewerControl()"));
  _VCTLLOG(SysLog("Command=%s (%d) Param=0x%08X",_VCTL_ToName(Command),Command,Param));
  return View.ViewerControl(Command,Param);
}
