/*===================================================================*/
/*                                                                   */
/*  InfoNES.h : NES Emulator for Win32, Linux(x86), Linux(PS2)       */
/*                                                                   */
/*  2000/05/14  InfoNES Project ( based on pNesX )                   */
/*                                                                   */
/*===================================================================*/

#ifndef InfoNES_H_INCLUDED
#define InfoNES_H_INCLUDED

/*-------------------------------------------------------------------*/
/*  Include files                                                    */
/*-------------------------------------------------------------------*/

#include "InfoNES_Types.h"
#include "InfoNES.h"
#include "etk_type.h"

/*-------------------------------------------------------------------*/
/*  NES resources                                                    */
/*-------------------------------------------------------------------*/

#define RAM_SIZE     0x2000
#define SRAM_SIZE    0x2000
#define PPURAM_SIZE  0x4000
#define SPRRAM_SIZE  256

/* RAM */
extern u8 RAM[RAM_SIZE];

/* SRAM */
extern u8 SRAM[SRAM_SIZE];

/* ROM */
extern u8 *ROM;

/* SRAM BANK ( 8Kb ) */
extern u8 *SRAMBANK;

/* ROM BANK ( 8Kb * 4 ) */
extern u8 *ROMBANK0;
extern u8 *ROMBANK1;
extern u8 *ROMBANK2;
extern u8 *ROMBANK3;

/*-------------------------------------------------------------------*/
/*  PPU resources                                                    */
/*-------------------------------------------------------------------*/

/* PPU RAM */
extern u8 PPURAM[];

/* VROM */
extern u8 *VROM;

/* PPU BANK ( 1Kb * 16 ) */
extern u8 *PPUBANK[];

#define NAME_TABLE0  8
#define NAME_TABLE1  9
#define NAME_TABLE2  10
#define NAME_TABLE3  11

#define NAME_TABLE_V_MASK 2
#define NAME_TABLE_H_MASK 1

/* Sprite RAM */
extern u8 SPRRAM[];

#define SPR_Y    0
#define SPR_CHR  1
#define SPR_ATTR 2
#define SPR_X    3
#define SPR_ATTR_COLOR  0x3
#define SPR_ATTR_V_FLIP 0x80
#define SPR_ATTR_H_FLIP 0x40
#define SPR_ATTR_PRI    0x20

/* PPU Register */
extern u8 PPU_R0;
extern u8 PPU_R1;
extern u8 PPU_R2;
extern u8 PPU_R3;
extern u8 PPU_R7;

extern u8 PPU_Scr_V;
extern u8 PPU_Scr_V_Next;
extern u8 PPU_Scr_V_u8;
extern u8 PPU_Scr_V_u8_Next;
extern u8 PPU_Scr_V_Bit;
extern u8 PPU_Scr_V_Bit_Next;

extern u8 PPU_Scr_H;
extern u8 PPU_Scr_H_Next;
extern u8 PPU_Scr_H_u8;
extern u8 PPU_Scr_H_u8_Next;
extern u8 PPU_Scr_H_Bit;
extern u8 PPU_Scr_H_Bit_Next;

extern u8 PPU_Latch_Flag;
extern u16 PPU_Addr;
extern u16 PPU_Temp;
extern u16 PPU_Increment;

extern u8 PPU_Latch_Flag;
extern u8 PPU_UpDown_Clip;

#define R0_NMI_VB      0x80
#define R0_NMI_SP      0x40
#define R0_SP_SIZE     0x20
#define R0_BG_ADDR     0x10
#define R0_SP_ADDR     0x08
#define R0_INC_ADDR    0x04
#define R0_NAME_ADDR   0x03

#define R1_BACKCOLOR   0xe0
#define R1_SHOW_SP     0x10
#define R1_SHOW_SCR    0x08
#define R1_CLIP_SP     0x04
#define R1_CLIP_BG     0x02
#define R1_MONOCHROME  0x01

#define R2_IN_VBLANK   0x80
#define R2_HIT_SP      0x40
#define R2_MAX_SP      0x20
#define R2_WRITE_FLAG  0x10
#define SCAN_UNKNOWN            3
#define SCAN_VBLANK             4

#define SCAN_TOP_OFF_SCREEN_START       0 
#define SCAN_ON_SCREEN_START            8
#define SCAN_BOTTOM_OFF_SCREEN_START  232
#define SCAN_UNKNOWN_START            240

#define SCAN_TOP_OFF_SCREEN     0
#define SCAN_ON_SCREEN          1
#define SCAN_BOTTOM_OFF_SCREEN  2
#define SCAN_VBLANK_START             243
#define SCAN_VBLANK_END               262

#define STEP_PER_SCANLINE             113
#define STEP_PER_FRAME                29828

/* Develop Scroll Registers */
#define InfoNES_SetupScr() \
{ \
  /* V-Scroll Register */ \
  PPU_Scr_V_Next = ( u8 )( PPU_Addr & 0x001f ); \
  PPU_Scr_V_u8_Next = PPU_Scr_V_Next >> 3; \
  PPU_Scr_V_Bit_Next = PPU_Scr_V_Next & 0x07; \
  \
  /* H-Scroll Register */ \
  PPU_Scr_H_Next = ( u8 )( ( PPU_Addr & 0x03e0 ) >> 5 ); \
  PPU_Scr_H_u8_Next = PPU_Scr_H_Next >> 3; \
  PPU_Scr_H_Bit_Next = PPU_Scr_H_Next & 0x07; \
}

/* Current Scanline */
extern u16 PPU_Scanline;

/* Scanline Table */
extern u8 PPU_ScanTable[];

/* Name Table Bank */
extern u8 PPU_NameTableBank;

/* BG Base Address */
extern u8 *PPU_BG_Base;

/* Sprite Base Address */
extern u8 *PPU_SP_Base;

/* Sprite Height */
extern u16 PPU_SP_Height;

/* NES display size */
#define NES_DISP_WIDTH      256
#define NES_DISP_HEIGHT     240

/* VRAM Write Enable ( 0: Disable, 1: Enable ) */
extern u8 byVramWriteEnable;

/* Frame IRQ ( 0: Disabled, 1: Enabled )*/
extern u8 FrameIRQ_Enable;
extern u16 FrameStep;

/*-------------------------------------------------------------------*/
/*  Display and Others resouces                                      */
/*-------------------------------------------------------------------*/

/* Frame Skip */
extern u16 FrameSkip;
extern u16 FrameCnt;
extern u16 FrameWait;

extern u16 DoubleFrame[ 2 ][ NES_DISP_WIDTH * NES_DISP_HEIGHT ];
extern u16 *WorkFrame;
extern u16 WorkFrameIdx;

extern u8 ChrBuf[];

extern u8 ChrBufUpdate;

extern u16 PalTable[];

/*-------------------------------------------------------------------*/
/*  APU and Pad resources                                            */
/*-------------------------------------------------------------------*/

extern u8 APU_Reg[];
extern int APU_Mute;

extern u32 PAD1_Latch;
extern u32 PAD2_Latch;
extern u32 PAD_System;
extern u32 PAD1_Bit;
extern u32 PAD2_Bit;

#define PAD_SYS_QUIT   1
#define PAD_SYS_OK     2
#define PAD_SYS_CANCEL 4
#define PAD_SYS_UP     8
#define PAD_SYS_DOWN   0x10
#define PAD_SYS_LEFT   0x20
#define PAD_SYS_RIGHT  0x40

#define PAD_PUSH(a,b)  ( ( (a) & (b) ) != 0 )

/*-------------------------------------------------------------------*/
/*  Mapper Function                                                  */
/*-------------------------------------------------------------------*/

/* Initialize Mapper */
extern void (*MapperInit)();
/* Write to Mapper */
extern void (*MapperWrite)( u16 wAddr, u8 byData );
/* Write to SRAM */
extern void (*MapperSram)( u16 wAddr, u8 byData );
/* Write to APU */
extern void (*MapperApu)( u16 wAddr, u8 byData );
/* Read from Apu */
extern u8 (*MapperReadApu)( u16 wAddr );
/* Callback at VSync */
extern void (*MapperVSync)();
/* Callback at HSync */
extern void (*MapperHSync)();
/* Callback at PPU read/write */
extern void (*MapperPPU)( u16 wAddr );
/* Callback at Rendering Screen 1:BG, 0:Sprite */
extern void (*MapperRenderScreen)( u8 byMode );

/*-------------------------------------------------------------------*/
/*  ROM information                                                  */
/*-------------------------------------------------------------------*/

/* .nes File Header */
struct NesHeader_tag
{
  u8 byID[ 4 ];
  u8 byRomSize;
  u8 byVRomSize;
  u8 byInfo1;
  u8 byInfo2;
  u8 byReserve[ 8 ];
};

/* .nes File Header */
extern struct NesHeader_tag NesHeader;

/* Mapper No. */
extern u8 MapperNo;

/* Other */
extern u8 ROM_Mirroring;
extern u8 ROM_SRAM;
extern u8 ROM_Trainer;
extern u8 ROM_FourScr;

/*-------------------------------------------------------------------*/
/*  Function prototypes                                              */
/*-------------------------------------------------------------------*/
 



/* Initialize InfoNES */
void InfoNES_Init();

/* Completion treatment */
void InfoNES_Fin();

/* Load a cassette */
int InfoNES_Load( const char *pszFileName );

/* Reset InfoNES */
int InfoNES_Reset();

/* Initialize PPU */
void InfoNES_SetupPPU();

/* Set up a Mirroring of Name Table */
void InfoNES_Mirroring( int nType );

/* The main loop of InfoNES */ 
void InfoNES_Main();

/* The loop of emulation */
void InfoNES_Cycle();

/* A function in H-Sync */
int InfoNES_HSync();

/* Render a scanline */
void InfoNES_DrawLine();

/* Get a position of scanline hits sprite #0 */
void InfoNES_GetSprHitY();

/* Develop character data */
void InfoNES_SetupChr();

#endif /* !InfoNES_H_INCLUDED */
