#pragma once

#define BIT0 0b1
#define BIT1 0b10
#define BIT2 0b100
#define BIT3 0b1000
#define BIT4 0b10000
#define BIT5 0b100000
#define BIT6 0b1000000
#define BIT7 0b10000000

#define INV_BIT0 0b11111110
#define INV_BIT1 0b11111101
#define INV_BIT2 0b11111011
#define INV_BIT3 0b11110111
#define INV_BIT4 0b11101111
#define INV_BIT5 0b11011111
#define INV_BIT6 0b10111111
#define INV_BIT7 0b01111111

#define GET_BIT0(arg) (arg & BIT0)
#define GET_BIT1(arg) (arg & BIT1)
#define GET_BIT2(arg) (arg & BIT2)
#define GET_BIT3(arg) (arg & BIT3)
#define GET_BIT4(arg) (arg & BIT4)
#define GET_BIT5(arg) (arg & BIT5)
#define GET_BIT6(arg) (arg & BIT6)
#define GET_BIT7(arg) (arg & BIT7)

#define SET_BIT0(arg) (arg)
#define SET_BIT1(arg) (arg << 1)
#define SET_BIT2(arg) (arg << 2)
#define SET_BIT3(arg) (arg << 3)
#define SET_BIT4(arg) (arg << 4)
#define SET_BIT5(arg) (arg << 5)
#define SET_BIT6(arg) (arg << 6)
#define SET_BIT7(arg) (arg << 7)

#define RM_BIT0(arg) (arg & INV_BIT0)
#define RM_BIT1(arg) (arg & INV_BIT1)
#define RM_BIT2(arg) (arg & INV_BIT2)
#define RM_BIT3(arg) (arg & INV_BIT3)
#define RM_BIT4(arg) (arg & INV_BIT4)
#define RM_BIT5(arg) (arg & INV_BIT5)
#define RM_BIT6(arg) (arg & INV_BIT6)
#define RM_BIT7(arg) (arg & INV_BIT7)
