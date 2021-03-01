/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 0;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 15;       /* horiz inner gap between windows */
static unsigned int gappiv    = 20;       /* vert inner gap between windows */
static unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const char dmenufont[]       = "monospace:size=12";
static const unsigned int baralpha = 185;
static const unsigned int borderalpha = OPAQUE;
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";
static char *fonts[]          = {
	"SauceCodePro Nerd Font:pixelsize=14:antialias=true:autohint=true",
	"Noto Color Emoji:pixelsize=17:antialias=true:autohint=true: style=Regular"
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "📖", "", "💼", "", "🔬", "📺", "🎹", "💻", "🐧" };
//some icons嗢📊

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           1 << 7,    0,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
	{ "qutebrowser", NULL, NULL,           1 << 5,    0,          0,          -1,        -1 },
{ "Xfce4-terminal",  NULL,     NULL,            0,        0,          1,           0,        -1 },
	{ "St",      NULL,     NULL,            0,        0,          1,           0,        -1 },
	{ NULL,      NULL, "Event Tester",      0,        0,          0,           1,        -1 },//xev
	{ "vlc",     NULL,    NULL,       1 << 5,         0,	      0,           0,        -1 },
{ NULL,     NULL,   "Sxiv - redyt",       1 << 8,         0,	      0,           0,        -1 },
	{ "Surf",  "surf",    NULL,       1 << 7,         0,	      0,           0,        -1 },
	{ NULL,      NULL,    "Video",       0,           1,	      0,           0,        -1 },
	{ NULL,      NULL,    "Notes",       0,           1,	      0,           0,        -1 },
	{ NULL,      NULL,    "/bin/sh",     0,           1,	      0,           0,        -1 },
{ "Qalculate-gtk",   NULL,     NULL,         0,           1,	      0,           0,        -1 },
	{ NULL,      NULL,    "Music",      1 << 6,       0,          0,           1,        -1 },
 { "Pavucontrol",    NULL,     NULL,           0,         1,          0,          -1,        -1 },
      { NULL,    NULL,  "Firefox Update",      0,         1,          0,          -1,        -1 },
	{ "Thunar",  NULL,     NULL,       1 << 2,        0,          0,           0,        -1 },
{ "libreoffice-writer",  "libreoffice",  NULL,  1 << 4,  0,	      0,	   0,        -1 },
{ NULL,       NULL,   "LibreOffice",         1 << 4,      1,          0,           0,        -1 },
	/*{ "Pcmanfm",   NULL,       NULL,       1 << 2,       0, 		    -1},*/
	//{ "tm",    NULL,         NULL,     1 << 4,          0,        0,            1,         -1},
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Layout layouts[] = {
	/* symbol     arrange function */

 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
 	{ "🧐",		monocle },		/* All windows on top of eachother */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
//	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	//{ "🐚",	spiral },		/* Fibonacci spiral */
	//{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	//{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */

	//{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */


	//{ "===",      bstackhoriz },
	//{ "HHH",      grid },
	//{ "###",      nrowgrid },
	//{ "---",      horizgrid },
	//{ ":::",      gaplessgrid },
	//{ "🥏",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[] = { "surf", "start.duckduckgo.com" };
static const char *syncthing[] = { "surf", "127.0.0.1:1210" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,         {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,         {.v = termcmd } },
//	{ MODKEY|ShiftMask,             XK_Return, spawn,         SHCMD("samedir &") },
	{ MODKEY|ShiftMask,     	XK_w,	   spawn,         {.v = web } },
	{ MODKEY|ControlMask,		XK_w,	   spawn,         {.v = syncthing } },
//	{ MODKEY|ShiftMask,             XK_c,      spawn,         {.v = qal } },
	{ MODKEY,		        XK_c,      spawn,         SHCMD("st -e calcurse") },
	{ MODKEY,	         	XK_z,      spawn,	  SHCMD("redyt") },
	{ MODKEY,		    XK_grave,      spawn,	  SHCMD("dmenuunicode") },
	{ MODKEY|ControlMask,	    XK_grave,	togglebar,	  {0} },
	//{ MODKEY,	       XK_semicolon,	   spawn,	  SHCMD("dmenu_mpc") },
	{ MODKEY,		XK_apostrophe,	    spawn,	  SHCMD("clipmenu") },
	{ MODKEY,			XK_b,	   spawn,	  SHCMD("Books001") },
	{ MODKEY|ShiftMask,		XK_b,	   spawn,	  SHCMD("Boletin001") },
	{ MODKEY,			XK_y,	   spawn,	  SHCMD("termyt -r") },
	{ MODKEY|ShiftMask,		XK_y,	   spawn,	  SHCMD("dmenuhandler") },
	{ MODKEY,		    XK_slash,	   spawn,	  SHCMD("dmenu_browser") },
	{ MODKEY,		XK_m,	   spawn,	  SHCMD("st -t 'FileManager🗄️' -e vifmrun") },
//	{ MODKEY|ShiftMask,	XK_m,	   spawn,	  SHCMD("samedir") },
	{ MODKEY|ShiftMask,	        XK_n,      spawn,	  SHCMD("xdotool click 1") },
	{ MODKEY,			XK_v,	   spawn,	  SHCMD("st -e ncmpcpp -q") },
	{ MODKEY,			XK_t,	   spawn,	  SHCMD("testi") },
	{ MODKEY,		XK_BackSpace,	   spawn,	  SHCMD("Sysfunctions001") },
	{ MODKEY,		XK_Escape,	   spawn,	  SHCMD("Sysfunctions001") },
	//{ MODKEY|ShiftMask,		XK_f,      spawn,	  SHCMD("thunar") },
//	{ MODKEY,                 XK_backslash,    focusstack,     {.i = +1 } },
//	{ MODKEY|ShiftMask,       XK_backslash,    focusstack,     {.i = -1 } },
	{ MODKEY,		XK_semicolon,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_semicolon,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_w,        zoom,         {0} },
	{ MODKEY,	                XK_Tab,      view,         {0} },
	{ MODKEY,	                XK_space,    view,         {0} },
{ MODKEY,	XK_e,	spawn,	SHCMD("st -t NewsBoat -e newsboat -q; sleep 4 && pkill -RTMIN+6 dwmblocks || sleep 10 && pkill -RTMIN+6 dwmblocks") },
{ MODKEY,	XK_x,	spawn,	SHCMD("st -t Notes -e nvim -c 'startinsert' ~/Docs/testi/pre-Uni.txt") },
{ MODKEY|ShiftMask,	XK_x, spawn,  SHCMD("st -t Notes -e nvim -c 'startinsert' ~/Docs/testi/Music") },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                 XK_o,    shiftview,     {.i = +1 } },
	{ MODKEY,	          XK_i,    shiftview,     {.i = -1 } },
	{ MODKEY,                 XK_j,    focusstack,     {.i = +1 } },
	{ MODKEY,                 XK_k,    focusstack,     {.i = -1 } },
//	{ MODKEY|ControlMask,     XK_k,    cyclelayout,     {.i = +1 } },
//	{ MODKEY|ControlMask,     XK_j,    cyclelayout,     {.i = -1 } },
	{ MODKEY,		XK_backslash,    cyclelayout,     {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_backslash,    cyclelayout,     {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_space,  togglefloating,	{0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
//	{ MODKEY,                       XK_k,	shiftview,         {.i = +1 } },
//	{ MODKEY,                       XK_j,	shiftview,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,   tagtoleft,         {0} },
	{ MODKEY|ShiftMask,             XK_k,  tagtoright,         {0} },
	{ MODKEY,                       XK_F1,	togglefullscreen, {0} },
	{ MODKEY|ControlMask,        	XK_F1,	togglefakefullscreen, {0} },
	{ MODKEY,			XK_F2,      spawn,	  SHCMD("dmenu_man") },
	{ MODKEY,			XK_F5,      quit,           {1} },
	{ MODKEY,	 		XK_F7,      spawn,	  SHCMD("st -e nvim -c VimwikiIndex") },
	{ MODKEY,	         	XK_F9,      spawn,	  SHCMD("dmenumount") },
	{ MODKEY|ControlMask,	 	XK_F9,      spawn,	  SHCMD("dmenumountq") },
	{ MODKEY,			XK_F8,	    spawn,	  SHCMD("setkeys001 & notify-send 'Keyboard⌨️ ' 'Keyboard remapping...\nRerunning customs shorcuts...'") },
	{ MODKEY|ShiftMask,		XK_F8,	    spawn,	  SHCMD("setxkbmap -layout us -variant altgr-intl -option nodeadkeys & notify-send 'Keyboard⌨️ ' 'Keyboard remapping...\nRunning keyboard defaults, US altgr-intl variant with nodeadkeys...'") },
	{ MODKEY,                       XK_F12,     xrdb,           {.v = NULL } },
	{ 0,				XK_Print,	spawn,		SHCMD("scrot -u -se 'mv $f ~/Downloads && magick mogrify -fuzz 4% -define trim:percent-background=0% -trim +repage -format png ~/Downloads/$f'") },
	{ ShiftMask,			XK_Print,	spawn,		SHCMD("scrot") },
//	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, //monocle
//	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, //tile
//	{ MODKEY,			XK_n,		setlayout,	{.v = &layouts[2]} }, //bstack
//	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[3]} }, //spiral
//	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[4]} }, //dwindle
//	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[5]} }, //deck
//{ MODKEY,			XK_f,		setlayout,	{.v = &layouts[6]} }, //centeredmaster

				/* Audio */
//	{ 0,            XF86XK_AudioLowerVolume,   spawn,         {.v = downvol } },
//	{ 0,            XF86XK_AudioMute,          spawn,         {.v = mutevol } },
//	{ 0,            XF86XK_AudioRaiseVolume,   spawn,         {.v = upvol   } },
{ 0, XF86XK_AudioLowerVolume,	spawn,	SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
{ 0, XF86XK_AudioRaiseVolume,	spawn,	SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
{ 0, XF86XK_AudioMute,		spawn,	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
{ MODKEY,	XK_minus,	spawn,	SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
{ MODKEY,	XK_equal,	spawn,	SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
//{ MODKEY|ShiftMask,  XK_minus, spawn,	SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
//{ MODKEY|ShiftMask,  XK_equal, spawn,	SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
{ MODKEY|ShiftMask,  XK_minus,	spawn,	SHCMD("mpc volume -3") },
{ MODKEY|ShiftMask,  XK_equal,	spawn,	SHCMD("mpc volume +3") },
{ MODKEY|ShiftMask,	XK_bracketleft,		spawn,	SHCMD("mpc seek -10") },
{ MODKEY|ShiftMask,	XK_bracketright,	spawn,	SHCMD("mpc seek +10") },
	{ 0,	XF86XK_AudioPrev,		spawn,	SHCMD("mpc volume -3") },
	{ 0,	XF86XK_AudioNext,		spawn,	SHCMD("mpc volume +3") },
	{ 0,	XF86XK_Calculator,		spawn,	SHCMD("Screenshots001") },
	{ 0,	XF86XK_Sleep,			spawn,	SHCMD("sudo zzz") },
	{ 0,	XF86XK_ScreenSaver,		spawn,	SHCMD("xset dpms force off") },
//{ 0, XF86XK_ScreenSaver,	spawn,	SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0,	XF86XK_AudioStop,		spawn,	SHCMD("mpc toggle; kill -45 $(pidof dwmblocks)") },
	{ MODKEY,	XK_bracketleft,		spawn,	SHCMD("mpc prev; kill -45 $(pidof dwmblocks)") },
	{ MODKEY,	XK_bracketright,	spawn,	SHCMD("mpc next; kill -45 $(pidof dwmblocks)") },
	{ MODKEY,		XK_p,		spawn,	SHCMD("mpc toggle; kill -45 $(pidof dwmblocks)") },
//	{ MODKEY|ShiftMask,	XK_p,		spawn,	SHCMD("mpdnoti") },
	{ MODKEY|ControlMask,	XK_p,		spawn,	SHCMD("mpdnoti") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_c,      quit,          {0} },

				/* GAPS */
	{ MODKEY,			XK_f,      incrgaps,       {.i = +3 } },
	{ MODKEY,			XK_g,      incrgaps,       {.i = -3 } },
	{ MODKEY,			XK_n,	  togglegaps,	   {0} },
	{ MODKEY|ControlMask,   	XK_n,    defaultgaps,	   {0} },
//	{ MODKEY,			XK_i,	incrigaps,      {.i = +3 } },
//	{ MODKEY,			XK_g,	incrigaps,      {.i = -3 } },
//	{ MODKEY|ShiftMask,		XK_o,	incrogaps,      {.i = -3 } },
//	{ MODKEY,			XK_o,	incrogaps,      {.i = +3 } },
//	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
//	{ MODKEY|ControlMask,           XK_o,	setcfact,       {.f =  0.00} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button1,  	spawn,	SHCMD("Screenshots001") },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,	0,	Button3,  	spawn,	SHCMD("scrot -u -se 'mv $f ~/Downloads'") },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
//	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
//	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

