# Microsoft Developer Studio Project File - Name="etklib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=etklib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "etklib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "etklib.mak" CFG="etklib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "etklib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "etklib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "etklib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "etklib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\etklib.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir include	copy *.h include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "etklib - Win32 Release"
# Name "etklib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ekt_input_method_pinyin.c
# End Source File
# Begin Source File

SOURCE=.\etk.c
# End Source File
# Begin Source File

SOURCE=.\etk_app.c
# End Source File
# Begin Source File

SOURCE=.\etk_bitmap.c
# End Source File
# Begin Source File

SOURCE=.\etk_button.c
# End Source File
# Begin Source File

SOURCE=.\etk_canvas.c
# End Source File
# Begin Source File

SOURCE=.\etk_color.c
# End Source File
# Begin Source File

SOURCE=.\etk_display.c
# End Source File
# Begin Source File

SOURCE=.\etk_display_sdl.c
# End Source File
# Begin Source File

SOURCE=.\etk_entry.c
# End Source File
# Begin Source File

SOURCE=.\etk_event.c
# End Source File
# Begin Source File

SOURCE=.\etk_font.c
# End Source File
# Begin Source File

SOURCE=.\etk_gconf.c
# End Source File
# Begin Source File

SOURCE=.\etk_image_bmp_decoder.c
# End Source File
# Begin Source File

SOURCE=.\etk_image_decoder.c
# End Source File
# Begin Source File

SOURCE=.\etk_image_jpeg_decoder.c
# End Source File
# Begin Source File

SOURCE=.\etk_input_method.c
# End Source File
# Begin Source File

SOURCE=.\etk_input_method_manager.c
# End Source File
# Begin Source File

SOURCE=.\etk_main_loop.c
# End Source File
# Begin Source File

SOURCE=.\etk_malloc.c
# End Source File
# Begin Source File

SOURCE=.\etk_menu.c
# End Source File
# Begin Source File

SOURCE=.\etk_menu_item.c
# End Source File
# Begin Source File

SOURCE=.\etk_pipe.c
# End Source File
# Begin Source File

SOURCE=.\etk_platform.c
# End Source File
# Begin Source File

SOURCE=.\etk_rect.c
# End Source File
# Begin Source File

SOURCE=.\etk_source.c
# End Source File
# Begin Source File

SOURCE=.\etk_source_default.c
# End Source File
# Begin Source File

SOURCE=.\etk_source_sdl.c
# End Source File
# Begin Source File

SOURCE=.\etk_source_timer.c
# End Source File
# Begin Source File

SOURCE=.\etk_sources_manager.c
# End Source File
# Begin Source File

SOURCE=.\etk_stack.c
# End Source File
# Begin Source File

SOURCE=.\etk_text_buffer.c
# End Source File
# Begin Source File

SOURCE=.\etk_util.c
# End Source File
# Begin Source File

SOURCE=.\etk_widget.c
# End Source File
# Begin Source File

SOURCE=.\etk_win32.c
# End Source File
# Begin Source File

SOURCE=.\etk_window.c
# End Source File
# Begin Source File

SOURCE=.\etk_wnd_manager.c
# End Source File
# Begin Source File

SOURCE=.\jcomapi.c
# End Source File
# Begin Source File

SOURCE=.\jdapimin.c
# End Source File
# Begin Source File

SOURCE=.\jdapistd.c
# End Source File
# Begin Source File

SOURCE=.\jdcoefct.c
# End Source File
# Begin Source File

SOURCE=.\jdcolor.c
# End Source File
# Begin Source File

SOURCE=.\jddctmgr.c
# End Source File
# Begin Source File

SOURCE=.\jdhuff.c
# End Source File
# Begin Source File

SOURCE=.\jdinput.c
# End Source File
# Begin Source File

SOURCE=.\jdmainct.c
# End Source File
# Begin Source File

SOURCE=.\jdmarker.c
# End Source File
# Begin Source File

SOURCE=.\jdmaster.c
# End Source File
# Begin Source File

SOURCE=.\jdmerge.c
# End Source File
# Begin Source File

SOURCE=.\jdphuff.c
# End Source File
# Begin Source File

SOURCE=.\jdpostct.c
# End Source File
# Begin Source File

SOURCE=.\jdsample.c
# End Source File
# Begin Source File

SOURCE=.\jdtrans.c
# End Source File
# Begin Source File

SOURCE=.\jerror.c
# End Source File
# Begin Source File

SOURCE=.\jfdctflt.c
# End Source File
# Begin Source File

SOURCE=.\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=.\jfdctint.c
# End Source File
# Begin Source File

SOURCE=.\jidctflt.c
# End Source File
# Begin Source File

SOURCE=.\jidctfst.c
# End Source File
# Begin Source File

SOURCE=.\jidctint.c
# End Source File
# Begin Source File

SOURCE=.\jidctred.c
# End Source File
# Begin Source File

SOURCE=.\jmemmgr.c
# End Source File
# Begin Source File

SOURCE=.\jmemsysextern.c
# End Source File
# Begin Source File

SOURCE=.\jpegdec.c
# End Source File
# Begin Source File

SOURCE=.\jquant1.c
# End Source File
# Begin Source File

SOURCE=.\jquant2.c
# End Source File
# Begin Source File

SOURCE=.\jutils.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\mine.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ekt_input_method_pinyin.h
# End Source File
# Begin Source File

SOURCE=.\etk.h
# End Source File
# Begin Source File

SOURCE=.\etk_app.h
# End Source File
# Begin Source File

SOURCE=.\etk_bitmap.h
# End Source File
# Begin Source File

SOURCE=.\etk_button.h
# End Source File
# Begin Source File

SOURCE=.\etk_canvas.h
# End Source File
# Begin Source File

SOURCE=.\etk_color.h
# End Source File
# Begin Source File

SOURCE=.\etk_display.h
# End Source File
# Begin Source File

SOURCE=.\etk_display_sdl.h
# End Source File
# Begin Source File

SOURCE=.\etk_entry.h
# End Source File
# Begin Source File

SOURCE=.\etk_event.h
# End Source File
# Begin Source File

SOURCE=.\etk_font.h
# End Source File
# Begin Source File

SOURCE=.\etk_gconf.h
# End Source File
# Begin Source File

SOURCE=.\etk_global.h
# End Source File
# Begin Source File

SOURCE=.\etk_image_bmp_decoder.h
# End Source File
# Begin Source File

SOURCE=.\etk_image_decoder.h
# End Source File
# Begin Source File

SOURCE=.\etk_image_jpeg_decoder.h
# End Source File
# Begin Source File

SOURCE=.\etk_input_method.h
# End Source File
# Begin Source File

SOURCE=.\etk_input_method_manager.h
# End Source File
# Begin Source File

SOURCE=.\etk_key.h
# End Source File
# Begin Source File

SOURCE=.\etk_main_loop.h
# End Source File
# Begin Source File

SOURCE=.\etk_malloc.h
# End Source File
# Begin Source File

SOURCE=.\etk_menu.h
# End Source File
# Begin Source File

SOURCE=.\etk_menu_item.h
# End Source File
# Begin Source File

SOURCE=.\etk_pipe.h
# End Source File
# Begin Source File

SOURCE=.\etk_platform.h
# End Source File
# Begin Source File

SOURCE=.\etk_rect.h
# End Source File
# Begin Source File

SOURCE=.\etk_source.h
# End Source File
# Begin Source File

SOURCE=.\etk_source_default.h
# End Source File
# Begin Source File

SOURCE=.\etk_source_sdl.h
# End Source File
# Begin Source File

SOURCE=.\etk_source_timer.h
# End Source File
# Begin Source File

SOURCE=.\etk_sources_manager.h
# End Source File
# Begin Source File

SOURCE=.\etk_stack.h
# End Source File
# Begin Source File

SOURCE=.\etk_text_buffer.h
# End Source File
# Begin Source File

SOURCE=.\etk_type.h
# End Source File
# Begin Source File

SOURCE=.\etk_util.h
# End Source File
# Begin Source File

SOURCE=.\etk_widget.h
# End Source File
# Begin Source File

SOURCE=.\etk_win32.h
# End Source File
# Begin Source File

SOURCE=.\etk_window.h
# End Source File
# Begin Source File

SOURCE=.\etk_wnd_manager.h
# End Source File
# Begin Source File

SOURCE=.\jconfig.h
# End Source File
# Begin Source File

SOURCE=.\jdct.h
# End Source File
# Begin Source File

SOURCE=.\jdhuff.h
# End Source File
# Begin Source File

SOURCE=.\jerror.h
# End Source File
# Begin Source File

SOURCE=.\jinclude.h
# End Source File
# Begin Source File

SOURCE=.\jmemsys.h
# End Source File
# Begin Source File

SOURCE=.\jmorecfg.h
# End Source File
# Begin Source File

SOURCE=.\jpegdec.h
# End Source File
# Begin Source File

SOURCE=.\jpegint.h
# End Source File
# Begin Source File

SOURCE=.\jpeglib.h
# End Source File
# Begin Source File

SOURCE=.\jversion.h
# End Source File
# Begin Source File

SOURCE=.\mine.h
# End Source File
# Begin Source File

SOURCE=.\queue.h
# End Source File
# End Group
# End Target
# End Project
