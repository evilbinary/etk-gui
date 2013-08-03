/*===================================================================*/
/*                                                                   */
/*  K6502.h : Header file for K6502                                  */
/*                                                                   */
/*  2000/05/29  InfoNES Project ( based on pNesX )                   */
/*                                                                   */
/*===================================================================*/

#ifndef K6502_H_INCLUDED
#define K6502_H_INCLUDED
#include "Include.h"
/*
// Type definition
#ifndef u32
typedef  int  u32;
#endif

#ifndef u16
typedef  short u16;
#endif

#ifndef u8
typedef  char  u8;
#endif

#ifndef NULL
#define NULL 0
#endif
*/

/* 6502 Flags */
#define FLAG_C 0x01
#define FLAG_Z 0x02
#define FLAG_I 0x04
#define FLAG_D 0x08
#define FLAG_B 0x10
#define FLAG_R 0x20
#define FLAG_V 0x40
#define FLAG_N 0x80

/* Stack Address */
#define BASE_STACK   0x100

/* Interrupt Vectors */
#define VECTOR_NMI   0xfffa
#define VECTOR_RESET 0xfffc
#define VECTOR_IRQ   0xfffe

// NMI Request
#define NMI_REQ  NMI_State = 0;

// IRQ Request
#define IRQ_REQ  IRQ_State = 0;

// Emulator Operation
void K6502_Init();
void K6502_Reset();
void K6502_Set_Int_Wiring( u8 byNMI_Wiring, u8 byIRQ_Wiring );
void K6502_Step( register u16 wClocks );

// I/O Operation (User definition)
static __inline u8 K6502_Read( u16 wAddr);
static __inline u16 K6502_ReadW( u16 wAddr );
static __inline u16 K6502_ReadW2( u16 wAddr );
static __inline u8 K6502_ReadZp( u8 byAddr );
static __inline u16 K6502_ReadZpW( u8 byAddr );
static __inline u8 K6502_ReadAbsX();
static __inline u8 K6502_ReadAbsY();
static __inline u8 K6502_ReadIY();

static __inline void K6502_Write( u16 wAddr, u8 byData );
static __inline void K6502_WriteW( u16 wAddr, u16 wData );

// The state of the IRQ pin
extern u8 IRQ_State;

// The state of the NMI pin
extern u8 NMI_State;

// The number of the clocks that it passed
extern u32 g_wPassedClocks;

#endif /* !K6502_H_INCLUDED */
