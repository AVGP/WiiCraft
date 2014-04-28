/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "WiiFunction.h"

#if defined _WIN32 || defined __CYGWIN__
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdarg.h>

void VIDEO_Init() {
}

GXRModeObj *VIDEO_GetPreferredMode(void *n) {
	GXRModeObj *t = (GXRModeObj *) malloc(sizeof(GXRModeObj));

	t->fbWidth = 2;
	t->xfbHeight = 2;

	return t;
}

void *SYS_AllocateFramebuffer(GXRModeObj *n) {
	return NULL;
}

void *MEM_K0_TO_K1(void *x) {
	return (void*) ((u32) (x) + (SYS_BASE_UNCACHED - SYS_BASE_CACHED));
}

void console_init(void * framebuffer, int xstart, int ystart, int xres,
		int yres, int stride) {
}

void VIDEO_Configure(GXRModeObj *rmode) {
}

void VIDEO_SetNextFramebuffer(void *fb) {
}

void VIDEO_SetBlack(bool black) {
}

void VIDEO_Flush() {
}

void VIDEO_WaitVSync() {
}

void WPAD_Init() {
}

void WPAD_Shutdown() {
}

void WPAD_ScanPads() {
}

u32 WPAD_ButtonsDown(int chan) {
	return 0x0000;
	//return 0x0080;
}

s32 WPAD_SetDataFormat(s32 chan, s32 fmt) {
	return 0;
}

s32 WPAD_SetVRes(s32 chan, u32 xres, u32 yres) {
	return 0;
}

void WPAD_IR(int chan, struct ir_t *ir) {
}

WPADData *WPAD_Data(int chan) {
	WPADData *data = new WPADData();
	data->ir.x = 0;
	data->ir.y = 0;
	data->ir.angle = 0;
	return data;
}

void GRRLIB_SetAntiAliasing(const bool aa) {
}

bool GRRLIB_GetAntiAliasing() {
	return false;
}

void GRRLIB_SetBackgroundColour(u8 r, u8 g, u8 b, u8 a) {
}

GRRLIB_texImg* GRRLIB_LoadTexturePNG(const u8 *my_png) {
	GRRLIB_texImg *data = new GRRLIB_texImg();
	data->h = 4;
	data->w = 4;

	return data;
}

void GRRLIB_2dMode() {
}

void GRRLIB_Camera3dSettings(f32 posx, f32 posy, f32 posz, f32 upx, f32 upy,
		f32 upz, f32 lookx, f32 looky, f32 lookz) {
}

void GRRLIB_3dMode(f32 minDist, f32 maxDist, f32 fov, bool texturemode,
		bool normalmode) {
}

void GRRLIB_Render(void) {
	std::cout << std::flush;
	system("echo -e \"\\033c\"");
	usleep(16666);
}

int GRRLIB_Init(void) {
	return 0;
}

void GRRLIB_Exit(void) {
}

void GRRLIB_DrawImg(const f32 xpos, const f32 ypos, const GRRLIB_texImg *tex,
		const f32 degrees, const f32 scaleX, const f32 scaleY,
		const u32 color) {
}

void GRRLIB_FreeTexture(GRRLIB_texImg *tex) {
}

void GRRLIB_FillScreen(u32 color) {
}

GRRLIB_texImg *GRRLIB_LoadTexture(const unsigned char *textur) {
	GRRLIB_texImg *data = new GRRLIB_texImg();
	data->h = 4;
	data->w = 4;

	return data;
}

void GRRLIB_InitTileSet(GRRLIB_texImg *textur, int w, int h, int s) {
	textur->tilestart = s;
	textur->tileh = h;
	textur->tilew = w;
	textur->nbtilew = 16;
	textur->nbtileh = 16;
	textur->ofnormaltexx = 16;
	textur->ofnormaltexy = 16;
}

void GRRLIB_Printf(float x, float y, GRRLIB_texImg *, u32 color, int scale,
		const char *text, ...) {
	va_list arglist;
	va_start(arglist, text);
	int anzahl = va_arg(arglist, int);

	printf(text, anzahl);
	printf("\n");

	va_end(arglist);
}

void GRRLIB_Rectangle(const f32 x, const f32 y, const f32 width,
		const f32 height, const u32 color, const u8 filled) {
}

void GRRLIB_DrawTile(f32 xpos, f32 ypos, GRRLIB_texImg * textur, float degrees,
		float scaleX, f32 scaleY, u8 alpha, int frame) {
}

void GRRLIB_ObjectView(f32 posx, f32 posy, f32 posz, f32 angx, f32 angy,
		f32 angz, f32 scalx, f32 scaly, f32 scalz) {
}

void GRRLIB_SetTexture(GRRLIB_texImg *tex, bool rep) {
}

void GX_Position3f32(float x, float y, float z) {
}

void GX_Begin(s32 type, s32 tex, int num) {
}

void GX_End() {
}

void GX_Color1u32(s32 color) {
}

void GX_TexCoord2f32(float x, float y) {
}
void GX_InitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
		GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
		GXBool mipmap) {
}
void GX_InitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
		f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
		GXBool do_edge_lod, GXAnisotropy max_aniso) {
}
void GX_SetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf,
		const u8 vfilter[7]) {
}
void GX_LoadTexObj(const GXTexObj* obj, GXTexMapID id) {
}
void GX_SetTevOp(GXTevStageID id, GXTevMode mode) {
}
void GX_SetVtxDesc(GXAttr attr, GXAttrType type) {
}
#endif
