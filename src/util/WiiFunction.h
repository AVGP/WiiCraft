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

#ifndef WIIFUNCTION_H_
#define WIIFUNCTION_H_

#if defined _WIN32 || defined __CYGWIN__
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef unsigned long u64;
typedef signed short s16;
typedef signed int s32;
typedef signed long s64;
typedef float f32;
typedef unsigned char ubyte;
typedef unsigned int uint;
typedef unsigned int uword;

struct _gx_rmodeobj {
	u8 aa;
	u16 efbHeight;
	u16 fbWidth;
	u8 field_rendering;
	u8 sample_pattern[12][2];
	u8 vfilter[7];
	u16 viHeight;
	u32 viTVMode;
	u16 viWidth;
	u16 viXOrigin;
	u16 viYOrigin;
	u16 xfbHeight;
	u32 xfbMode;
};

typedef struct _gx_rmodeobj GXRModeObj;

struct GRRLIB_texImg {
	uint w; // The width of the texture in pixels.
	uint h; // The height of the texture in pixels.
	int handlex; // Texture handle x.
	int handley; // Texture handle y.
	int offsetx; // Texture offset x.
	int offsety; // Texture offset y.

	bool tiledtex; // Texture is tiled if set to true.
	uint tilew; // The width of one tile in pixels.
	uint tileh; // The height of one tile in pixels.
	uint nbtilew; // Number of tiles for the x axis.
	uint nbtileh; // Number of tiles for the y axis.
	uint tilestart; // Offset to tile starting position.
	f32 ofnormaltexx; // Offset of normalized texture on x.
	f32 ofnormaltexy; // Offset of normalized texture on y.

	void *data; // Pointer to the texture data.
};

typedef struct GRRLIB_texImg GRRLIB_texImg;

#define SYS_RETURNTOMENU 3
#define SYS_POWEROFF_STANDBY 5
#define VI_NON_INTERLACE 1
#define VI_DISPLAY_PIX_SZ 2
#define WPAD_BUTTON_HOME 0x0080
#define SYS_BASE_CACHED (0x80000000)
#define SYS_BASE_UNCACHED (0xC0000000)
#define INVALID_SOCKET -1

#define net_gethostbyname gethostbyname
#define net_socket ::socket
#define net_close close
#define net_ioctl ioctl
#define net_connect ::connect
#define net_setsockopt setsockopt
#define net_write(socket, buf, len) send(socket, buf, len, 0);
#define net_send ::send
#define net_read ::read
#define net_recv ::recv
#define ticks_to_millisecs(ticks) ((ticks)*1000)
#define gettime() time(NULL)

void VIDEO_Init();
GXRModeObj *VIDEO_GetPreferredMode(void *n);
void *SYS_AllocateFramebuffer(GXRModeObj *n);
void *MEM_K0_TO_K1(void *x);
void console_init(void * framebuffer, int xstart, int ystart, int xres,
		int yres, int stride);
void VIDEO_Configure(GXRModeObj *rmode);
void VIDEO_SetNextFramebuffer(void *fb);
void VIDEO_SetBlack(bool black);
void VIDEO_Flush();
void VIDEO_WaitVSync();

enum {
	WPAD_CHAN_ALL = -1,
	WPAD_CHAN_0,
	WPAD_CHAN_1,
	WPAD_CHAN_2,
	WPAD_CHAN_3,
	WPAD_BALANCE_BOARD,
	WPAD_MAX_WIIMOTES,
};

enum {
	WPAD_FMT_BTNS = 0, WPAD_FMT_BTNS_ACC, WPAD_FMT_BTNS_ACC_IR
};

/* IR correction types */
typedef enum ir_position_t {
	WIIUSE_IR_ABOVE, WIIUSE_IR_BELOW
} ir_position_t;

/**
 *	@struct vec2b_t
 *	@brief Unsigned x,y byte vector.
 */
typedef struct vec2b_t {
	ubyte x, y;
} vec2b_t;

/**
 *	@struct vec3b_t
 *	@brief Unsigned x,y,z byte vector.
 */
typedef struct vec3b_t {
	ubyte x, y, z;
} vec3b_t;

/**
 *	@struct vec3b_t
 *	@brief Unsigned x,y,z byte vector.
 */
typedef struct vec3w_t {
	uword x, y, z;
} vec3w_t;

/**
 *	@struct vec3f_t
 *	@brief Signed x,y,z float struct.
 */
typedef struct vec3f_t {
	float x, y, z;
} vec3f_t;

/**
 *	@struct orient_t
 *	@brief Orientation struct.
 *
 *	Yaw, pitch, and roll range from -180 to 180 degrees.
 */
typedef struct orient_t {
	float roll; // roll, this may be smoothed if enabled
	float pitch; // pitch, this may be smoothed if enabled
	float yaw;

	float a_roll; // absolute roll, unsmoothed
	float a_pitch; // absolute pitch, unsmoothed
} orient_t;

/**
 *	@struct gforce_t
 *	@brief Gravity force struct.
 */
typedef struct gforce_t {
	float x, y, z;
} gforce_t;

/**
 *	@struct accel_t
 *	@brief Accelerometer struct. For any device with an accelerometer.
 */
typedef struct accel_t {
	struct vec3w_t cal_zero; // zero calibration
	struct vec3w_t cal_g; // 1g difference around 0cal

	float st_roll; // last smoothed roll value
	float st_pitch; // last smoothed roll pitch
	float st_alpha; // alpha value for smoothing [0-1]
} accel_t;

/**
 *	@struct ir_dot_t
 *	@brief A single IR source.
 */
typedef struct ir_dot_t {
	ubyte visible; // if the IR source is visible

	short rx; // raw X coordinate (0-1023)
	short ry; // raw Y coordinate (0-767)

	ubyte size; // size of the IR dot (0-15)
} ir_dot_t;

typedef struct fdot_t {
	float x, y;
} fdot_t;

typedef struct sb_t {
	fdot_t dots[2];
	fdot_t acc_dots[2];
	fdot_t rot_dots[2];
	float angle;
	float off_angle;
	float score;
} sb_t;

/**
 *	@enum aspect_t
 *	@brief Screen aspect ratio.
 */
typedef enum aspect_t {
	WIIUSE_ASPECT_4_3, WIIUSE_ASPECT_16_9
} aspect_t;

/**
 *	@struct ir_t
 *	@brief IR struct. Hold all data related to the IR tracking.
 */
typedef struct ir_t {
	struct ir_dot_t dot[4]; // IR dots
	ubyte num_dots; // number of dots at this time

	int state; // keeps track of the IR state

	int raw_valid; // is the raw position valid?
	sb_t sensorbar; // sensor bar, detected or guessed
	float ax; // raw X coordinate
	float ay; // raw Y coordinate
	float distance; // pixel width of the sensor bar
	float z; // calculated distance in meters
	float angle; // angle of the wiimote to the sensor bar

	int smooth_valid; // is the smoothed position valid?
	float sx; // smoothed X coordinate
	float sy; // smoothed Y coordinate
	float error_cnt; // error count, for smoothing algorithm
	float glitch_cnt; // glitch count, same

	int valid; // is the bounded position valid?
	float x; // bounded X coordinate
	float y; // bounded Y coordinate
	enum aspect_t aspect; // aspect ratio of the screen
	enum ir_position_t pos; // IR sensor bar position
	unsigned int vres[2]; // IR virtual screen resolution
	int offset[2]; // IR XY correction offset

} ir_t;

/**
 *	@struct joystick_t
 *	@brief Joystick calibration structure.
 *
 *	The angle \a ang is relative to the positive y-axis into quadrant I
 *	and ranges from 0 to 360 degrees.  So if the joystick is held straight
 *	upwards then angle is 0 degrees.  If it is held to the right it is 90,
 *	down is 180, and left is 270.
 *
 *	The magnitude \a mag is the distance from the center to where the
 *	joystick is being held.  The magnitude ranges from 0 to 1.
 *	If the joystick is only slightly tilted from the center the magnitude
 *	will be low, but if it is closer to the outter edge the value will
 *	be higher.
 */
typedef struct joystick_t {
	struct vec2b_t max; // maximum joystick values
	struct vec2b_t min; // minimum joystick values
	struct vec2b_t center; // center joystick values
	struct vec2b_t pos; // raw position values

	float ang; // angle the joystick is being held
	float mag; // magnitude of the joystick (range 0-1)
} joystick_t;

/**
 *	@struct nunchuk_t
 *	@brief Nunchuk expansion device.
 */
typedef struct nunchuk_t {
	struct accel_t accel_calib; // nunchuk accelerometer calibration
	struct joystick_t js; // joystick calibration

	int* flags; // options flag (points to wiimote_t.flags)

	ubyte btns; // what buttons have just been pressed
	ubyte btns_last; // what buttons have just been pressed
	ubyte btns_held; // what buttons are being held down
	ubyte btns_released; // what buttons were just released this

	struct vec3w_t accel; // current raw acceleration data
	struct orient_t orient; // current orientation on each axis
	struct gforce_t gforce; // current gravity forces on each axis
} nunchuk_t;

/**
 *	@struct classic_ctrl_t
 *	@brief Classic controller expansion device.
 */
typedef struct classic_ctrl_t {
	short btns; // what buttons have just been pressed
	short btns_last; // what buttons have just been pressed
	short btns_held; // what buttons are being held down
	short btns_released; // what buttons were just released this

	ubyte rs_raw;
	ubyte ls_raw;

	float r_shoulder; // right shoulder button (range 0-1)
	float l_shoulder; // left shoulder button (range 0-1)

	struct joystick_t ljs; // left joystick calibration
	struct joystick_t rjs; // right joystick calibration
} classic_ctrl_t;

/**
 *	@struct guitar_hero_3_t
 *	@brief Guitar Hero 3 expansion device.
 */
typedef struct guitar_hero_3_t {
	short btns; // what buttons have just been pressed
	short btns_last; // what buttons have just been pressed
	short btns_held; // what buttons are being held down
	short btns_released; // what buttons were just released this

	ubyte wb_raw;
	float whammy_bar; // whammy bar (range 0-1)

	struct joystick_t js; // joystick calibration
} guitar_hero_3_t;

/**
 * @struct wii_board_t
 * @brief Wii Balance Board expansion device.
 */
typedef struct wii_board_t {
	float tl; /* Interpolated */
	float tr;
	float bl;
	float br; /* End interp */
	short rtl; /* RAW */
	short rtr;
	short rbl;
	short rbr; /* /RAW */
	short ctl[3]; /* Calibration */
	short ctr[3];
	short cbl[3];
	short cbr[3]; /* /Calibration */
	float x;
	float y;
} wii_board_t;

/**
 *	@struct expansion_t
 *	@brief Generic expansion device plugged into wiimote.
 */
typedef struct expansion_t {
	int type; // type of expansion attached

	union {
		struct nunchuk_t nunchuk;
		struct classic_ctrl_t classic;
		struct guitar_hero_3_t gh3;
		struct wii_board_t wb;
	};
} expansion_t;

typedef struct _wpad_data {
	s16 err;
	u32 data_present;
	u32 btns_h;
	u32 btns_l;
	u32 btns_d;
	u32 btns_u;
	struct ir_t ir;
	struct vec3w_t accel;
	struct orient_t orient;
	struct gforce_t gforce;
	struct expansion_t exp;
} WPADData;

void WPAD_Init();
void WPAD_Shutdown();
void WPAD_ScanPads();
u32 WPAD_ButtonsDown(int chan);
s32 WPAD_SetDataFormat(s32 chan, s32 fmt);
s32 WPAD_SetVRes(s32 chan, u32 xres, u32 yres);
void WPAD_IR(int chan, struct ir_t *ir);
WPADData *WPAD_Data(int chan);

void GRRLIB_SetAntiAliasing(const bool aa);
bool GRRLIB_GetAntiAliasing();
void GRRLIB_SetBackgroundColour(u8 r, u8 g, u8 b, u8 a);
GRRLIB_texImg* GRRLIB_LoadTexturePNG(const u8 *my_png);
void GRRLIB_2dMode();
void GRRLIB_Camera3dSettings(f32 posx, f32 posy, f32 posz, f32 upx, f32 upy,
		f32 upz, f32 lookx, f32 looky, f32 lookz);
void GRRLIB_3dMode(f32 minDist, f32 maxDist, f32 fov, bool texturemode,
		bool normalmode);
void GRRLIB_Render(void);
int GRRLIB_Init(void);
void GRRLIB_Exit(void);
void GRRLIB_DrawImg(const f32 xpos, const f32 ypos, const GRRLIB_texImg *tex,
		const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color);
void GRRLIB_FreeTexture(GRRLIB_texImg *tex);
void GRRLIB_FillScreen(u32 color);
GRRLIB_texImg *GRRLIB_LoadTexture(const unsigned char *textur);
void GRRLIB_InitTileSet(GRRLIB_texImg *textur, int w, int h, int s);
void GRRLIB_Printf(float x, float y, GRRLIB_texImg *, u32 color, int scale,
		const char *text, ...);
void GRRLIB_Rectangle(const f32 x, const f32 y, const f32 width,
		const f32 height, const u32 color, const u8 filled);
void GRRLIB_DrawTile(f32 xpos, f32 ypos, GRRLIB_texImg * textur, float degrees,
		float scaleX, f32 scaleY, u8 alpha, int frame);
void GRRLIB_ObjectView(f32 posx, f32 posy, f32 posz, f32 angx, f32 angy,
		f32 angz, f32 scalx, f32 scaly, f32 scalz);
void GRRLIB_SetTexture(GRRLIB_texImg *tex, bool rep);

typedef u8 GXBool;

#define GX_FALSE    ((GXBool)0)
#define GX_TRUE     ((GXBool)1)
#define GX_DISABLE  ((GXBool)0)
#define GX_ENABLE   ((GXBool)1)

typedef struct {
	u8 pad[];
} GXTexObj;

typedef struct _vecf {
	f32 x;
	f32 y;
	f32 z;
} guVector;

enum {
	GX_QUADS
};

enum {
	GX_VTXFMT0
};

enum GXTexFmt {
	GX_TF_I4,
	GX_TF_I8,
	GX_TF_IA4,
	GX_TF_IA8,
	GX_TF_RGB565,
	GX_TF_RGB5A3,
	GX_TF_RGBA8,
	GX_TF_CMPRl,
	GX_TF_Z8,
	GX_TF_Z16,
	GX_TF_Z24X8,
	GX_CTF_R4,
	GX_CTF_RA4,
	GX_CTF_RA8,
	GX_CTF_A8,
	GX_CTF_R8,
	GX_CTF_G8,
	GX_CTF_B8,
	GX_CTF_RG8,
	GX_CTF_GB8,
	GX_CTF_Z4,
	GX_CTF_Z8M,
	GX_CTF_Z8L,
	GX_CTF_Z16L
};

enum GXTexWrapMode {
	GX_CLAMP, GX_REPEAT, GX_MIRROR, GX_MAX_TEXWRAPMODE
};

enum GXTexFilter {
	GX_NEAR,
	GX_LINEAR,
	GX_NEAR_MIP_NEAR,
	GX_LIN_MIP_NEAR,
	GX_NEAR_MIP_LIN,
	GX_LIN_MIP_LIN
};

enum GXAnisotropy {
	GX_ANISO_1, GX_ANISO_2, GX_ANISO_4, GX_MAX_ANISOTROPY
};

enum GXTexMapID {
	GX_TEXMAP0,
	GX_TEXMAP1,
	GX_TEXMAP2,
	GX_TEXMAP3,
	GX_TEXMAP4,
	GX_TEXMAP5,
	GX_TEXMAP6,
	GX_TEXMAP7,
	GX_MAX_TEXMAP,
	GX_TEXMAP_NULL,
	GX_TEXMAP_DISABLE
};

enum GXTevStageID {
	GX_TEVSTAGE0,
	GX_TEVSTAGE1,
	GX_TEVSTAGE2,
	GX_TEVSTAGE3,
	GX_TEVSTAGE4,
	GX_TEVSTAGE5,
	GX_TEVSTAGE6,
	GX_TEVSTAGE7,
	GX_TEVSTAGE8,
	GX_TEVSTAGE9,
	GX_TEVSTAGE10,
	GX_TEVSTAGE11,
	GX_TEVSTAGE12,
	GX_TEVSTAGE13,
	GX_TEVSTAGE14,
	GX_TEVSTAGE15,
	GX_MAX_TEVSTAGE
};

enum GXTevMode {
	GX_DECAL, GX_MODULATE, GX_REPLACE, GX_PASSCLR, GX_BLEND
};

enum GXAttr {
	GX_VA_PNMTXIDX,
	GX_VA_TEX0MTXIDX,
	GX_VA_TEX1MTXIDX,
	GX_VA_TEX2MTXIDX,
	GX_VA_TEX3MTXIDX,
	GX_VA_TEX4MTXIDX,
	GX_VA_TEX5MTXIDX,
	GX_VA_TEX6MTXIDX,
	GX_VA_TEX7MTXIDX,
	GX_VA_POS,
	GX_VA_NRM,
	GX_VA_NBT,
	GX_VA_CLR0,
	GX_VA_CLR1,
	GX_VA_TEX0,
	GX_VA_TEX1,
	GX_VA_TEX2,
	GX_VA_TEX3,
	GX_VA_TEX4,
	GX_VA_TEX5,
	GX_VA_TEX6,
	GX_VA_TEX7,
	GX_POS_MTX_ARRAY,
	GX_NRM_MTX_ARRAY,
	GX_TEX_MTX_ARRAY,
	GX_LIGHT_ARRAY,
	GX_VA_MAX_ATTR,
	GX_VA_NULL,
};

enum GXAttrType {
	GX_NONE, GX_DIRECT, GX_INDEX8, GX_INDEX16
};
void GX_Position3f32(float x, float y, float z);
void GX_Begin(s32 type, s32 tex, int num);
void GX_End();
void GX_Color1u32(s32 color);
void GX_TexCoord2f32(float x, float y);
void GX_InitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
		GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
		GXBool mipmap);
void GX_InitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
		f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
		GXBool do_edge_lod, GXAnisotropy max_aniso);
void GX_SetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf,
		const u8 vfilter[7]);
void GX_LoadTexObj(const GXTexObj* obj, GXTexMapID id);
void GX_SetTevOp(GXTevStageID id, GXTevMode mode);
void GX_SetVtxDesc(GXAttr attr, GXAttrType type);

#endif

#endif /* WIIFUNCTION_H_ */
