/*	firmware.cpp - 20070111
 *	________________________________________________________________
 *	
 *	Sdr1kUsb - SDR-1000 USB hardware control
 *	Written by Sami Aintila (OH2BFO), Attocon Oy
 *	________________________________________________________________
 *	
 *	Copyright (c) 2006-2007 Attocon Oy.
 *	All rights reserved.
 *	
 *	Redistribution and use in source and binary forms, with or 
 *	without modification, are permitted provided that the following 
 *	conditions are met:
 *	1. Redistributions of source code must retain the above 
 *	copyright notice, this list of conditions and the following 
 *	disclaimer. 
 *	2. Redistributions in binary form must reproduce the above 
 *	copyright notice, this list of conditions and the following 
 *	disclaimer in the documentation and/or other materials provided 
 *	with the distribution. 
 *	3. Neither the name of the copyright holders nor the names of 
 *	their contributors may be used to endorse or promote products 
 *	derived from this software without specific prior written 
 *	permission. 
 *	
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 *	CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 *	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 *	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 *	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR 
 *	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 *	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 *	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 *	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdr1kusb.h"

//	------------------------------------------------------------

uint8 reset[] = { 0, 1 };
uint8 vector[] = { 0x02,0x02,0x00 };	// LJMP 0x200

//	------------------------------------------------------------
//	USBtoPIO v2.8 with EEPROM support

uint8 fx1_code[] = {
0x75,0x81,0x5F,0xE4,0xF5,0x8E,0xFC,0xFD,0xF5,0x30,0xF5,0x31,0xF5,0x80,0xF5,0x90,
0xF5,0xA0,0xF5,0xB0,0xF5,0xB1,0xF5,0xB5,0xF4,0xF5,0xB2,0x75,0xB3,0x1B,0xF5,0xB4,
0xF5,0xB6,0x90,0xE6,0x00,0x74,0x10,0xF0,0x75,0x92,0xE7,0x78,0xC0,0x79,0x11,0x90,
0xE6,0x78,0x74,0x80,0xF0,0x05,0x86,0x90,0xE6,0x79,0x74,0xA0,0xF0,0x05,0x86,0xE0,
0x30,0xE0,0xFC,0xE4,0x05,0x86,0xF0,0x05,0x86,0xE0,0x30,0xE0,0xFC,0x74,0x80,0xF0,
0x74,0xA1,0x05,0x86,0xF0,0x05,0x86,0xE0,0x30,0xE0,0xFC,0x05,0x86,0xE0,0x05,0x86,
0xB9,0x11,0x03,0x19,0x80,0xF1,0xF2,0x08,0xD9,0xED,0x74,0x40,0xF0,0x90,0xE6,0x8F,
0x74,0x10,0xF0,0x90,0xE6,0x8D,0xF0,0xE5,0xBA,0x20,0xE1,0xFB,0x90,0xE6,0x8D,0xE0,
0xC3,0x13,0x60,0x18,0xFF,0x75,0x92,0xE7,0x78,0x80,0xE2,0xFA,0x08,0xE2,0xFB,0x08,
0x30,0xE7,0x4F,0x30,0xE6,0x2F,0x71,0x10,0xDF,0xF0,0x8F,0x80,0xE5,0xBA,0x20,0xE2,
0xD2,0xE4,0xA2,0x92,0x13,0xA2,0xB7,0x13,0xA2,0xB6,0x13,0xA2,0xB4,0x13,0xA2,0xB5,
0x13,0x90,0xE7,0xC0,0xF0,0xA3,0xE5,0x30,0xF0,0xA3,0xE5,0x31,0xF0,0x90,0xE6,0x8F,
0x74,0x03,0xF0,0x80,0xAE,0x8A,0x80,0x13,0x50,0x02,0xD2,0x90,0x13,0x50,0x04,0xD2,
0x91,0x8A,0x04,0x13,0x50,0x02,0xD2,0x93,0x13,0x50,0x02,0xD2,0x94,0xE4,0xF5,0x90,
0x80,0xB6,0x20,0xE6,0x1D,0x8A,0x80,0xD2,0x93,0xC2,0x93,0xF5,0x80,0xD2,0x86,0xD2,
0x94,0xC2,0x94,0xC2,0x86,0xD2,0x94,0xC2,0x94,0x75,0x80,0x40,0xD2,0x94,0xC2,0x94,
0x80,0x96,0xF5,0x80,0xD2,0x94,0xC2,0x94,0xD2,0x87,0xD2,0x94,0xC2,0x94,0x80,0xE9,
0x54,0x18,0x53,0x04,0xC0,0x4C,0x44,0x24,0xF5,0x80,0xBB,0xC7,0x29,0x90,0x03,0xD6,
0xEA,0x54,0xC7,0xFD,0x7E,0x32,0xE0,0x54,0x38,0x4D,0x71,0x51,0xE0,0x54,0x03,0x60,
0x11,0xA2,0xB4,0x20,0xE1,0x07,0xE5,0x30,0x33,0xF5,0x30,0x80,0x05,0xE5,0x31,0x33,
0xF5,0x31,0xA3,0xDE,0xE1,0x22,0xEA,0x70,0x08,0xC2,0x82,0xD2,0x91,0xC2,0x91,0x80,
0x78,0x33,0x92,0x80,0xD2,0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,
0x33,0x92,0x80,0xD2,0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,
0x92,0x80,0xD2,0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,0x92,
0x80,0xD2,0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,0x92,0x80,
0xD2,0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,0x92,0x80,0xD2,
0x91,0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,0x92,0x80,0xD2,0x91,
0xC2,0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0x33,0x92,0x80,0xD2,0x91,0xC2,
0x91,0xD2,0x81,0xD2,0x91,0xC2,0x91,0xC2,0x81,0xC2,0x85,0xD2,0x91,0xC2,0x91,0xD2,
0x85,0xD2,0x91,0xC2,0x91,0x22,0x10,0x18,0x10,0x18,0x00,0x08,0x00,0x08,0x00,0x09,
0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x01,0x20,0x10,
0x18,0x10,0x18,0x10,0x18,0x00,0x08,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,
0x0A,0x00,0x0A,0x00,0x0A,0x00,0x02,0x20
};

int32 fx1_fwSize[] = { 1, sizeof(vector), sizeof(fx1_code), 1, 0 };
int32 fx1_fwAddr[] = { 0xE600, 0, 0x200, 0xE600 };
uint8* fx1_fwBytes[] = { reset + 1, vector, fx1_code, reset };

//	------------------------------------------------------------
//	USBtoPIO v2.7 for old adapter

uint8 fx_code[] = {
0x75,0x81,0x5F,0xE4,0xF5,0x8E,0xF5,0x20,0xFC,0x90,0x03,0x81,0xE0,0x60,0x0C,0xF5,
0x92,0xA3,0xE0,0xA3,0x60,0xF6,0xF8,0xE0,0xF2,0x80,0xF6,0x75,0x92,0x7D,0x90,0x7F,
0xC8,0xE0,0x20,0xE1,0xF9,0x90,0x7F,0xC9,0xE0,0xC3,0x13,0x60,0x1E,0xFF,0x90,0x78,
0x35,0x05,0x86,0x90,0x79,0x71,0x78,0xC0,0xE2,0xF5,0x2F,0x08,0xE2,0xFB,0x08,0x30,
0xE7,0x4A,0x30,0xE6,0x38,0x51,0xB7,0x05,0x86,0xDF,0xED,0x90,0x7F,0xC9,0xF0,0x90,
0x7F,0xB8,0xE0,0x20,0xE1,0xC8,0x90,0x78,0x38,0xE0,0x54,0x1F,0x23,0x23,0x23,0x53,
0x20,0x07,0x42,0x20,0x90,0x7E,0x00,0xE5,0x20,0xF0,0xA3,0xE5,0x30,0xF0,0xA3,0xE5,
0x31,0xF0,0x90,0x7F,0xB9,0x74,0x03,0xF0,0x53,0x20,0xF8,0x80,0xA1,0x54,0x0F,0xF0,
0x05,0x86,0x30,0xE1,0x02,0xAC,0x2F,0xE5,0x2F,0xF0,0x80,0xBB,0x20,0xE6,0x1B,0x74,
0x04,0xF0,0x05,0x86,0xE5,0x2F,0xF0,0x05,0x86,0x74,0x08,0xF0,0x05,0x86,0xEB,0xD2,
0xE6,0xF0,0xC2,0xE6,0xF0,0x74,0x40,0xF0,0x80,0x9D,0x74,0x08,0xF0,0x05,0x86,0x74,
0x40,0xF0,0x74,0xC0,0xF0,0x80,0xEE,0x54,0x18,0x53,0x04,0xC0,0x4C,0x44,0x24,0xFC,
0x7A,0x02,0xEA,0xF0,0x05,0x86,0xBB,0xC7,0x34,0xC0,0x92,0x75,0x92,0x03,0x79,0x4F,
0xE5,0x2F,0x54,0xC7,0xFD,0x7E,0x32,0xE3,0x54,0x38,0x4D,0xF5,0x2F,0x71,0x07,0xE3,
0x54,0x03,0x60,0x11,0xA2,0xA3,0x20,0xE1,0x07,0xE5,0x30,0x33,0xF5,0x30,0x80,0x05,
0xE5,0x31,0x33,0xF5,0x31,0x09,0xDE,0xDF,0xD2,0x01,0xD0,0x92,0x22,0xE5,0x2F,0x70,
0x06,0xEC,0xC2,0xE2,0xF0,0x80,0x41,0xEC,0xA2,0x7F,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,
0xA2,0x7E,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,0xA2,0x7D,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,
0xA2,0x7C,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,0xA2,0x7B,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,
0xA2,0x7A,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,0xA2,0x79,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,
0xA2,0x78,0x92,0xE0,0xF0,0x6A,0xF0,0x6A,0xC2,0xE5,0xF0,0xD2,0xE5,0xF0,0x22,0x10,
0x18,0x10,0x18,0x00,0x08,0x00,0x08,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,
0x09,0x00,0x09,0x00,0x09,0x00,0x01,0x20,0x10,0x18,0x10,0x18,0x10,0x18,0x00,0x08,
0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x02,
0x20,0x78,0x25,0x81,0x26,0x00,0x43,0xFF,0x49,0x01,0x4A,0x82,0x4B,0x10,0x4C,0x3B,
0x00,0x79,0x60,0x05,0x68,0x02,0x70,0x00,0x61,0x05,0x69,0x02,0x62,0x3F,0x6A,0x03,
0x72,0x00,0x00,0x7F,0x92,0x00,0x93,0x10,0x95,0x3B,0x9C,0xFF,0x9E,0xFF,0xB8,0x02,
0xC8,0x00,0x00,0x00
};

int32 fx_fwSize[] = { 1, sizeof(vector), sizeof(fx_code), 1, 0 };
int32 fx_fwAddr[] = { 0x7F92, 0, 0x200, 0x7F92 };
uint8* fx_fwBytes[] = { reset + 1, vector, fx_code, reset };

//	------------------------------------------------------------

Sdr1kUsbHardware hwdata[] = {
/*
	"Cypress (Anchor Chips) EZ-USB",
	0x0547, 0x2131, 0x82, 0x02, 0,
	an2131_fwSize, an2131_fwAddr, an2131_fwBytes,
*/
	"Cypress EZ-USB FX",
	0x0547, 0x2235, 0x82, 0x02, 0,
	fx_fwSize, fx_fwAddr, fx_fwBytes,
//	
	"Cypress EZ-USB FX1",
	0x04B4, 0x6473, 0x81, 0x01, 16,
	fx1_fwSize, fx1_fwAddr, fx1_fwBytes,
//	
	"FlexRadio SDR-1000 USB Adapter",
	0x16C0, 0x06E0, 0x81, 0x01, 16,
	fx1_fwSize, fx1_fwAddr, fx1_fwBytes
};

int32 Sdr1kUsb::hwcount = 3;
Sdr1kUsbHardware* Sdr1kUsb::hardware = hwdata;

//	------------------------------------------------------------
