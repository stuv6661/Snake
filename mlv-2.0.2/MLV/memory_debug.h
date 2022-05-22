/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MLV__MEMMORY_DEBUG_H__
#define __MLV__MEMMORY_DEBUG_H__

#include <stdlib.h>

void init_memory_debug();

void print_memory_statistics();

void close_memory_debug();

typedef struct _Memory_debug_statistics {
	int nb_create_surface;
	int nb_free_surface;
	int nb_init_sdl;
	int nb_close_sdl;
	int nb_create_semaphore;
	int nb_free_semaphore;
	int nb_malloc;
	int nb_calloc;
	int nb_free;
	int nb_free_wave;
	int nb_load_wave;
	int nb_open_font;
	int nb_close_font;
	int nb_init_ttf;
	int nb_quit_ttf;
} Memory_debug_statistics; 

typedef int Uint32;
typedef int Uint16;
typedef int Uint8;
typedef int Sint32;
typedef int Sint16;

typedef struct SDL_Rect {
	Sint16 x, y;
	Uint16 w, h;
} SDL_Rect;

typedef struct _SDL_Screen {
	int h;
	int w;
} SDL_Surface;

typedef enum {
	SDLK_UNKNOWN,
	SDLK_FIRST,
	SDLK_BACKSPACE,
	SDLK_TAB,
	SDLK_CLEAR,
	SDLK_RETURN,
	SDLK_PAUSE,
	SDLK_ESCAPE,
	SDLK_SPACE,
	SDLK_EXCLAIM,
	SDLK_QUOTEDBL,
	SDLK_HASH,
	SDLK_DOLLAR,
	SDLK_AMPERSAND,
	SDLK_QUOTE,
	SDLK_LEFTPAREN,
	SDLK_RIGHTPAREN,
	SDLK_ASTERISK,
	SDLK_PLUS,
	SDLK_COMMA,
	SDLK_MINUS,
	SDLK_PERIOD,
	SDLK_SLASH,
	SDLK_0,
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_4,
	SDLK_5,
	SDLK_6,
	SDLK_7,
	SDLK_8,
	SDLK_9,
	SDLK_COLON,
	SDLK_SEMICOLON,
	SDLK_LESS,
	SDLK_EQUALS,
	SDLK_GREATER,
	SDLK_QUESTION,
	SDLK_AT,

	SDLK_LEFTBRACKET,
	SDLK_BACKSLASH,
	SDLK_RIGHTBRACKET,
	SDLK_CARET,
	SDLK_UNDERSCORE,
	SDLK_BACKQUOTE,
	SDLK_a,
	SDLK_b,
	SDLK_c,
	SDLK_d,
	SDLK_e,
	SDLK_f,
	SDLK_g,
	SDLK_h,
	SDLK_i,
	SDLK_j,
	SDLK_k,
	SDLK_l,
	SDLK_m,
	SDLK_n,
	SDLK_o,
	SDLK_p,
	SDLK_q,
	SDLK_r,
	SDLK_s,
	SDLK_t,
	SDLK_u,
	SDLK_v,
	SDLK_w,
	SDLK_x,
	SDLK_y,
	SDLK_z,
	SDLK_DELETE,

	SDLK_KP0,
	SDLK_KP1,
	SDLK_KP2,
	SDLK_KP3,
	SDLK_KP4,
	SDLK_KP5,
	SDLK_KP6,
	SDLK_KP7,
	SDLK_KP8,
	SDLK_KP9,
	SDLK_KP_PERIOD,
	SDLK_KP_DIVIDE,
	SDLK_KP_MULTIPLY,
	SDLK_KP_MINUS,
	SDLK_KP_PLUS,
	SDLK_KP_ENTER,
	SDLK_KP_EQUALS,

	SDLK_UP,
	SDLK_DOWN,
	SDLK_RIGHT,
	SDLK_LEFT,
	SDLK_INSERT,
	SDLK_HOME,
	SDLK_END,
	SDLK_PAGEUP,
	SDLK_PAGEDOWN,

	SDLK_F1,
	SDLK_F2,
	SDLK_F3,
	SDLK_F4,
	SDLK_F5,
	SDLK_F6,
	SDLK_F7,
	SDLK_F8,
	SDLK_F9,
	SDLK_F10,
	SDLK_F11,
	SDLK_F12,
	SDLK_F13,
	SDLK_F14,
	SDLK_F15,

	SDLK_NUMLOCK,
	SDLK_CAPSLOCK,
	SDLK_SCROLLOCK,
	SDLK_RSHIFT,
	SDLK_LSHIFT,
	SDLK_RCTRL,
	SDLK_LCTRL,
	SDLK_RALT,
	SDLK_LALT,
	SDLK_RMETA,
	SDLK_LMETA,
	SDLK_LSUPER,
	SDLK_RSUPER,
	SDLK_MODE,
	SDLK_COMPOSE,

	SDLK_HELP,
	SDLK_PRINT,
	SDLK_SYSREQ,
	SDLK_BREAK,
	SDLK_MENU,
	SDLK_POWER,
	SDLK_EURO,
	SDLK_UNDO,

	SDLK_LAST
} SDLKey;

typedef enum {
	KMOD_NONE,
	KMOD_LSHIFT,
	KMOD_RSHIFT,
	KMOD_LCTRL,
	KMOD_RCTRL,
	KMOD_LALT,
	KMOD_RALT,
	KMOD_LMETA,
	KMOD_RMETA,
	KMOD_NUM,
	KMOD_CAPS,
	KMOD_MODE,
	KMOD_RESERVED
} SDLMod;

typedef struct SDL_keysym {
	Uint8 scancode;			/* hardware specific scancode */
	SDLKey sym;			/* SDL virtual keysym */
	SDLMod mod;			/* current key modifiers */
	Uint16 unicode;			/* translated character */
} SDL_keysym;

/* Event enumerations */
typedef enum SDL_Events {
       SDL_NOEVENT = 0,			/* Unused (do not remove) */
       SDL_ACTIVEEVENT,			/* Application loses/gains visibility */
       SDL_KEYDOWN,			/* Keys pressed */
       SDL_KEYUP,			/* Keys released */
       SDL_MOUSEMOTION,			/* Mouse moved */
       SDL_MOUSEBUTTONDOWN,		/* Mouse button pressed */
       SDL_MOUSEBUTTONUP,		/* Mouse button released */
       SDL_JOYAXISMOTION,		/* Joystick axis motion */
       SDL_JOYBALLMOTION,		/* Joystick trackball motion */
       SDL_JOYHATMOTION,		/* Joystick hat position change */
       SDL_JOYBUTTONDOWN,		/* Joystick button pressed */
       SDL_JOYBUTTONUP,			/* Joystick button released */
       SDL_QUIT,			/* User-requested quit */
       SDL_SYSWMEVENT,			/* System specific event */
       SDL_EVENT_RESERVEDA,		/* Reserved for future use.. */
       SDL_EVENT_RESERVEDB,		/* Reserved for future use.. */
       SDL_VIDEORESIZE,			/* User resized video mode */
       SDL_VIDEOEXPOSE,			/* Screen needs to be redrawn */
       SDL_EVENT_RESERVED2,		/* Reserved for future use.. */
       SDL_EVENT_RESERVED3,		/* Reserved for future use.. */
       SDL_EVENT_RESERVED4,		/* Reserved for future use.. */
       SDL_EVENT_RESERVED5,		/* Reserved for future use.. */
       SDL_EVENT_RESERVED6,		/* Reserved for future use.. */
       SDL_EVENT_RESERVED7,		/* Reserved for future use.. */
       /* Events SDL_USEREVENT through SDL_MAXEVENTS-1 are for your use */
       SDL_USEREVENT = 24,
       /* This last event is only for bounding internal arrays
	  It is the number of bits in the event mask datatype -- Uint32
        */
       SDL_NUMEVENTS = 32
} SDL_EventType;

/* Application visibility event structure */
typedef struct SDL_ActiveEvent {
	Uint8 type;	/* SDL_ACTIVEEVENT */
	Uint8 gain;	/* Whether given states were gained or lost (1/0) */
	Uint8 state;	/* A mask of the focus states */
} SDL_ActiveEvent;

/* Keyboard event structure */
typedef struct SDL_KeyboardEvent {
	Uint8 type;	/* SDL_KEYDOWN or SDL_KEYUP */
	Uint8 which;	/* The keyboard device index */
	Uint8 state;	/* SDL_PRESSED or SDL_RELEASED */
	SDL_keysym keysym;
} SDL_KeyboardEvent;

/* Mouse motion event structure */
typedef struct SDL_MouseMotionEvent {
	Uint8 type;	/* SDL_MOUSEMOTION */
	Uint8 which;	/* The mouse device index */
	Uint8 state;	/* The current button state */
	Uint16 x, y;	/* The X/Y coordinates of the mouse */
	Sint16 xrel;	/* The relative motion in the X direction */
	Sint16 yrel;	/* The relative motion in the Y direction */
} SDL_MouseMotionEvent;

/* Mouse button event structure */
typedef struct SDL_MouseButtonEvent {
	Uint8 type;	/* SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP */
	Uint8 which;	/* The mouse device index */
	Uint8 button;	/* The mouse button index */
	Uint8 state;	/* SDL_PRESSED or SDL_RELEASED */
	Uint16 x, y;	/* The X/Y coordinates of the mouse at press time */
} SDL_MouseButtonEvent;

/* Joystick axis motion event structure */
typedef struct SDL_JoyAxisEvent {
	Uint8 type;	/* SDL_JOYAXISMOTION */
	Uint8 which;	/* The joystick device index */
	Uint8 axis;	/* The joystick axis index */
	Sint16 value;	/* The axis value (range: -32768 to 32767) */
} SDL_JoyAxisEvent;

/* Joystick trackball motion event structure */
typedef struct SDL_JoyBallEvent {
	Uint8 type;	/* SDL_JOYBALLMOTION */
	Uint8 which;	/* The joystick device index */
	Uint8 ball;	/* The joystick trackball index */
	Sint16 xrel;	/* The relative motion in the X direction */
	Sint16 yrel;	/* The relative motion in the Y direction */
} SDL_JoyBallEvent;

/* Joystick hat position change event structure */
typedef struct SDL_JoyHatEvent {
	Uint8 type;	/* SDL_JOYHATMOTION */
	Uint8 which;	/* The joystick device index */
	Uint8 hat;	/* The joystick hat index */
	Uint8 value;	/* The hat position value:
			    SDL_HAT_LEFTUP   SDL_HAT_UP       SDL_HAT_RIGHTUP
			    SDL_HAT_LEFT     SDL_HAT_CENTERED SDL_HAT_RIGHT
			    SDL_HAT_LEFTDOWN SDL_HAT_DOWN     SDL_HAT_RIGHTDOWN
			   Note that zero means the POV is centered.
			*/
} SDL_JoyHatEvent;

/* Joystick button event structure */
typedef struct SDL_JoyButtonEvent {
	Uint8 type;	/* SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP */
	Uint8 which;	/* The joystick device index */
	Uint8 button;	/* The joystick button index */
	Uint8 state;	/* SDL_PRESSED or SDL_RELEASED */
} SDL_JoyButtonEvent;

/* The "window resized" event
   When you get this event, you are responsible for setting a new video
   mode with the new width and height.
 */
typedef struct SDL_ResizeEvent {
	Uint8 type;	/* SDL_VIDEORESIZE */
	int w;		/* New width */
	int h;		/* New height */
} SDL_ResizeEvent;

/* The "screen redraw" event */
typedef struct SDL_ExposeEvent {
	Uint8 type;	/* SDL_VIDEOEXPOSE */
} SDL_ExposeEvent;

/* The "quit requested" event */
typedef struct SDL_QuitEvent {
	Uint8 type;	/* SDL_QUIT */
} SDL_QuitEvent;

/* A user-defined event type */
typedef struct SDL_UserEvent {
	Uint8 type;	/* SDL_USEREVENT through SDL_NUMEVENTS-1 */
	int code;	/* User defined event code */
	void *data1;	/* User defined data pointer */
	void *data2;	/* User defined data pointer */
} SDL_UserEvent;

/* If you want to use this event, you should include SDL_syswm.h */
struct SDL_SysWMmsg;
typedef struct SDL_SysWMmsg SDL_SysWMmsg;
typedef struct SDL_SysWMEvent {
	Uint8 type;
	SDL_SysWMmsg *msg;
} SDL_SysWMEvent;

/* General event structure */
typedef union SDL_Event {
	Uint8 type;
	SDL_ActiveEvent active;
	SDL_KeyboardEvent key;
	SDL_MouseMotionEvent motion;
	SDL_MouseButtonEvent button;
	SDL_JoyAxisEvent jaxis;
	SDL_JoyBallEvent jball;
	SDL_JoyHatEvent jhat;
	SDL_JoyButtonEvent jbutton;
	SDL_ResizeEvent resize;
	SDL_ExposeEvent expose;
	SDL_QuitEvent quit;
	SDL_UserEvent user;
	SDL_SysWMEvent syswm;
} SDL_Event;

#define SDL_BUTTON_LEFT		1
#define SDL_BUTTON_MIDDLE	2
#define SDL_BUTTON_RIGHT	3

void filledCircleColor( SDL_Surface* screen, int x, int y, int radius, Uint32 color);
void circleColor( SDL_Surface* screen, int x, int y, int radius, Uint32 color);
void ellipseColor( SDL_Surface* screen, int x, int y, int radius_x, int radius_y, Uint32 color );
void filledEllipseColor( SDL_Surface* screen, int x, int y, int radius_x, int radius_y, Uint32 color);
void polygonColor( SDL_Surface* screen, Sint16* vx, Sint16* vy, int npoints, Uint32 color);
void filledPolygonColor( SDL_Surface* screen, Sint16* vx, Sint16* vy, int npoints, Uint32 color);
void rectangleColor( SDL_Surface* screen, int x, int y, int width, int height, Uint32 color);
void boxColor( SDL_Surface* screen, int x, int y, int width, int height, Uint32 color);
void lineColor( SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint32 color);
void pixelColor( SDL_Surface* screen, int x, int y, Uint32 color);
void stringColor( SDL_Surface* screen, int x, int y, const char *text, Uint32 color);

int SDL_BlitSurface( SDL_Surface* src, SDL_Rect* rectangle_src, SDL_Surface* dst, SDL_Rect* rectangle_dest);

int SDL_PollEvent( SDL_Event* event );

#define SDL_HWSURFACE 1
#define SDL_SRCALPHA 1
#define SDL_ALPHA_TRANSPARENT 1
#define SDL_RLEACCEL 1
#define SDL_ALPHA_OPAQUE 1

void SDL_SetAlpha(SDL_Surface* surface, int prop1, int prop2);

SDL_Surface* SDL_LoadBMP( const char* path );
SDL_Surface* SDL_CreateRGBSurface( int prop1, int w, int h, int resol, int r, int g, int b, int prop2 );
void SDL_FreeSurface( SDL_Surface* surface );
SDL_Surface* rotozoomSurface( SDL_Surface* surface, double rotation, double zoom, int antialias);

SDL_Surface* rotozoomSurfaceXY( SDL_Surface* surface, double rotation, double zoomx, double zoomy, int antialias);

#define SDL_INIT_VIDEO 1
#define SDL_INIT_TIMER 1
#define SDL_INIT_AUDIO 1
#define SDL_DOUBLEBUF 1
#define SDL_INIT_EVENTTHREAD 1

typedef int (*SDL_EventFilter)(const SDL_Event *event);


int SDL_Init( int flags );
void SDL_Quit();
char* SDL_GetError();
SDL_Surface* SDL_SetVideoMode( int w, int h, int bits, int flags );
void SDL_WM_SetCaption( const char* wind, const char* icon );
void SDL_SetEventFilter( SDL_EventFilter filter );
void SDL_Flip( SDL_Surface* surface );

#define SDL_PRESSED 0
#define SDL_RELEASED 1

#define SDL_ENABLE 1

typedef struct _SDL_sem {
} SDL_sem;

int SDL_SemWait( SDL_sem* semaphore );
int SDL_SemPost( SDL_sem* semaphore );

SDL_sem* SDL_CreateSemaphore( int );
void SDL_DestroySemaphore( SDL_sem* semaphore );

void SDL_EnableUNICODE( int flags );

int SDL_PushEvent( SDL_Event* event );

int SDL_GetTicks();

void SDL_Delay( int milliseconds );

void* memory_debug_malloc( size_t size, int line, char* file );

void* memory_debug_calloc( size_t nmemb, size_t size, int line, char* file );

void memory_debug_free( void* ptr, int line, char* file );

typedef struct{
  int freq;
  Uint16 format;
  Uint8 channels;
  Uint8 silence;
  Uint16 samples;
  Uint32 size;
  void (*callback)(void *userdata, Uint8 *stream, int len);
  void *userdata;
} SDL_AudioSpec;

void SDL_LockAudio();

void SDL_UnlockAudio();

void SDL_MixAudio(Uint8 *dst, Uint8 *src, Uint32 len, int volume);

SDL_AudioSpec* SDL_LoadWAV(const char *file, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);

void SDL_FreeWAV(Uint8 *audio_buf);

void SDL_PauseAudio(int pause_on);

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained);

void SDL_CloseAudio();


/* Audio format flags (defaults to LSB byte order) */
#define AUDIO_U8	0x0008	/* Unsigned 8-bit samples */
#define AUDIO_S8	0x8008	/* Signed 8-bit samples */
#define AUDIO_U16LSB	0x0010	/* Unsigned 16-bit samples */
#define AUDIO_S16LSB	0x8010	/* Signed 16-bit samples */
#define AUDIO_U16MSB	0x1010	/* As above, but big-endian byte order */
#define AUDIO_S16MSB	0x9010	/* As above, but big-endian byte order */
#define AUDIO_U16	AUDIO_U16LSB
#define AUDIO_S16	AUDIO_S16LSB

#define SDL_MIX_MAXVOLUME 128


typedef struct {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 unused;
} SDL_Color;

#define SDL_SRCCOLORKEY	0x00001000	/* Blit uses a source color key */

int SDL_SetColorKey(SDL_Surface *surface, Uint32 flag, Uint32 key);


/*
typedef struct {
} GList;
*/

typedef struct {
} TTF_Font;

int TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h);

int TTF_Init(void);

void TTF_Quit(void);

TTF_Font * TTF_OpenFont(const char *file, int ptsize);

#define TTF_GetError	SDL_GetError

void TTF_SetFontStyle(TTF_Font *font, int style);

#define TTF_STYLE_NORMAL	0x00

void TTF_CloseFont(TTF_Font *font);

SDL_Surface * TTF_RenderUTF8_Solid(TTF_Font *font, const char *text, SDL_Color fg);

#endif
