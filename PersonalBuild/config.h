/* See LICENSE file for copyright and license details. */

/* Appearance: colors on here are not used, see loadxrdb function on dwm.c */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 15;       /* horiz inner gap between windows */
static unsigned int gappiv    = 20;       /* vert inner gap between windows */
static unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int pertag       = 1;        /* 0 means global layout across all tags (default) */
static const int pertagbar    = 0;        /* 0 means using pertag, but with the same barpos */
static const int gapspertag   = 1;        /* 0 means global gaps across all tags (default) */
static const unsigned int baralpha    = 185;	/* Bar opacity (0-255) */
static const unsigned int borderalpha = OPAQUE;	/* Borders (0xffU) */
static char *fonts[] = {
	"Hack Nerd Font:pixelsize=12:antialias=true:autohint=true", /* Powerline */
//	"SauceCodePro Nerd Font:pixelsize=14:antialias=true:autohint=true",
//	"Noto Color Emoji:pixelsize=16:antialias=true:autohint=true: style=Regular" /* Emojis */
	"JoyPixels:pixelsize=14:antialias=true:autohint=true"
};
/* Pywal, 8 bytes because xrdb macro asks for at least 8 (>7)*/
static char color0[8], color1[8], color2[8], color3[8], color4[8], color5[8], color6[8], color7[8], color8[8];
static char bg_wal[8], fg_wal[8], cursor_wal[8];
static char *colors[][3]	      = {
			/* fg		bg		border	    description		*/
	[SchemeNorm]   = { fg_wal,	color0,		color0 }, /*Normal tags section */
	[SchemeSel]    = { color0,	color1,		color2 }, /*Selected tag*/
	[SchemeLt]     = { color2,	color0,		NULL }, /*Layout*/
	[SchemeTitle]  = { color0,	color2,		NULL }, /*window title*/
	[SchemeStatus] = { color3,	color0,		NULL }, /*StatusBar*/
	[SchemeUrgent] = { fg_wal,	color0,		fg_wal }, /*background color for urgent tag*/
	[SchemeNotify] = { fg_wal,	color0,		NULL }, /*Little red bar on urgent tag*/
	[SchemeIndOn]  = { color4,	color0,		NULL }, /*rectangle on active tag*/
	[SchemeIndOff] = { color2,	color0,		NULL }, /*rectablge on def tag*/
};
static const unsigned int alphas[][3] = {
			/* fg		bg		border     */
	[SchemeNorm]   = { OPAQUE,	baralpha,	borderalpha },
	[SchemeSel]    = { OPAQUE,	baralpha,	borderalpha },
};

/* tags */
static const char *tags[]     = { "📖", "", "💼", "", "🔬", "🎹", "📺", "💻", "🐧" };
static const int taglayouts[] = {    0,   1,    0,   0,    0,    0,    0,    0,    0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 * tags, isfloating, isterminal, noswallow, isfakefullscreen
	 */
	RULE(.class = "Gimp",		.tags = 1 << 7)
	RULE(.class = "vlc",		.tags = 1 << 6)
	RULE(.class = "qutebrowser",	.tags = 1 << 5)
	RULE(.class = "Surf",		.tags = 1 << 7)
	RULE(.title = "Music",		.tags = 1 << 6)
	RULE(.title = "Sxiv - redyt",	.tags = 1 << 8)
	RULE(.title = "Sxiv - walld",	.tags = 1 << 8)
	RULE(.class = "libreoffice",	.tags = 1 << 3)
//	RULE(.title = "LibreOffice",	.isfloating = 1, .noswallow = 1)
//	RULE(.class = "Firefox",	.tags = 1 << 1, .isfakefullscreen = 1)
	RULE(.class = "firefox",	.tags = 1 << 1, .isfakefullscreen = 1)
	RULE(.class = "Brave-browser",	.tags = 1 << 4, .isfakefullscreen = 1)
	RULE(.class = "Video",       .isfloating = 1)
	RULE(.class = "Pavucontrol", .isfloating = 1)
	RULE(.class = "Pcmanfm",     .isfloating = 1)
//	RULE(.title = "pulsemixer",  .isfloating = 1)
	RULE(.title = "About Mozilla Firefox",	.isfloating = 1)
	RULE(.class = "St", .isterminal = 1)
	RULE(.title = "Event Tester", .noswallow = 1) /* xev */
	RULE(.title = "Firefox Update", .isfloating = 1)
	RULE(.instance = "notes", .tags = SPTAG(0), .isfloating = 1)
	RULE(.instance = "calc" , .tags = SPTAG(1), .isfloating = 1)
	RULE(.instance = "pre"  , .tags = SPTAG(2), .isfloating = 1)
	RULE(.instance = "diary", .tags = SPTAG(3), .isfloating = 1)
	RULE(.instance = "music", .tags = SPTAG(4), .isfloating = 1)
	RULE(.instance = "pulsemixer", .tags = SPTAG(5), .isfloating = 1)
};

/* layout(s) */
static float mfact     = 0.55;	/* factor of master area size [0.05..0.95] */
static int nmaster     = 1;	/* number of clients in master area */
static int resizehints = 0;	/* 1 means respect size hints in tiled resizals */
//#define FORCE_VSPLIT 1	/* nrowgrid: force two clients to always split vertically */

static const Layout layouts[] = {
	/* symbol	arrange function			Description			*/
 	{ "[]=",	tile },			/* Master on left, slaves on right */
 	{ "🧐",		monocle },		/* All windows on top of eachother */
 	{ "{}",		alphamonocle },		/* monocle but windows aren't stacked */
	{ ">M>",	centeredfloatmaster},	/* Centermaster but master floats */
	//{ "TTT",	bstack },		/* Master on top, slaves on bottom */
	//{ "🐚",	spiral },		/* Fibonacci spiral */
	//{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	//{ "[D]",	deck },			/* Master on left, slaves in monocle mode on right */
	//{ "|M|",	centeredmaster },	/* Master in middle, slaves on sides */
	//{ "===",      bstackhoriz },		/* Bstack but slaves stacked "monocle"-like */
	//{ "HHH",      grid },			/* windows in a grid */
	//{ "###",      nrowgrid },		/* Gaplessgrid with no gaps, but not equal size */
	//{ "---",      horizgrid },		/* Gaplessgrid but with horizontal order */
	//{ ":::",      gaplessgrid },		/* grid ajusted in such that there are no gaps */
	//{ "🐷", 	pidgin },		/* Basically grid? */
	//{ ")M(",	ego },
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
#define SCRATCH(KEY,NUM) \
	{ MODKEY,            		KEY,  	togglescratch,	{.ui = NUM } },
/* helper for spawning shell commands in the pre dwm-5.0 fashion, maybe use shkd?*/
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* macro for any dmenu commands, colorize them */
#define DMENUARGS "-m", dmenumon, "-nb", color0, "-nf", color8, "-sb", color2, "-sf", color0
/* commands */
static const char *dmenucmd[]  = { "dmenu_run_i", DMENUARGS, NULL };
static const char *clip[]      = { "clipmenu", "-i", "-l", "25", DMENUARGS, NULL };
//static const char *passmenu[]  = { "passmenu", "-i", "-l", "25", "-p", "Passmenu:", DMENUARGS, NULL };
//static const char *passmenu[]  = { "clipctl", "disable", "&&", "passmenu", "-i", "-l", "25", "-p", "Passmenu:", DMENUARGS, "&&", "clipctl", "enable", "&&", "notify-send", "Password will be deleted on 45 seconds❌", NULL };
//static const char *passmenu[]  = { "sh", "-c", "clipctl disable && passmenu -i -l 25 -p 'Passmenu:' && notify-send Password will be deleted on 45 seconds❌ ; clipctl enable", NULL };
static const char *termcmd[]   = { "st", NULL };
static const char *syncthing[] = { "surf", "127.0.0.1:1210", NULL };
static const char *web[]       = { "surf", "start.duckduckgo.com", NULL };
static const char *vifm[]      = { "sh",  "-c", "st -t 'FileManager🗄️' -e vifmrun", NULL };
static const char *samevifm[]  = { "samedirvifm", NULL };

/* scratchpads */
#define NOTES		"-e", "nvim", "+$", "+startinsert!"
const char *spcmd0[] = { "st", "-n", "notes", "-g", "100x25", NOTES, "/home/faber/Docs/testi/testi", NULL };
const char *spcmd1[] = { "st", "-n", "calc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd2[] = { "st", "-n", "pre", "-g", "70x25", NOTES, "/home/faber/Docs/testi/pre-Uni.txt", NULL };
const char *spcmd3[] = { "st", "-n", "diary", "-g", "115x30" , NULL };
const char *spcmd4[] = { "st", "-n", "music", "-g", "105x27", "-e", "ncmpcpp", "-q", NULL };
const char *spcmd5[] = { "st", "-n", "pulsemixer", "-g", "110x28", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = { {spcmd0}, {spcmd1}, {spcmd2}, {spcmd3}, {spcmd4}, {spcmd5} };
/*static Sp scratchpads[] = {
	* name          cmd  *
	{"notes",    spcmd1},
	{"calc",     spcmd2},
	{"pre",      spcmd3},
	{"diary",    spcmd4},
	{"music",    spcmd5},
};*/

static Key keys[] = {
	/* modifier(s)			key	function	argument */

				/* Commands */
	{ MODKEY,		   XK_Return,	spawn,		{ .v = termcmd }	},
	{ MODKEY,			XK_d,   spawn,		{ .v = dmenucmd }	},
	{ MODKEY,			XK_m,	spawn,		{ .v = vifm }		},
	{ MODKEY|ShiftMask,		XK_m,	spawn,		{ .v = samevifm }	},
	{ MODKEY,	       XK_apostrophe,	spawn,		{ .v = clip }		},
	{ MODKEY|ShiftMask,		XK_w,	spawn,		{ .v = web }		},
	{ MODKEY|ControlMask,		XK_w,	spawn,		{ .v = syncthing }	},
//	{ MODKEY|ShiftMask,    XK_apostrophe,	spawn,		{ .v = passmenu }	},
	{ MODKEY|ShiftMask,    XK_apostrophe,	spawn, SHCMD("clipctl disable && passmenu -i -l 25 -p 'Passmenu:' && clipctl enable && notify-send 'Password will be deleted on 45 seconds❌'")		},
	{ MODKEY,			XK_e,  	togglescratch,	{.ui = 0 } },/* notes */
	{ MODKEY,			XK_x,	togglescratch,	{.ui = 1 } },/* bc */
	{ MODKEY|ControlMask,		XK_s,	togglescratch,	{.ui = 2 } },/* uni */
	{ MODKEY,			XK_s,	togglescratch,	{.ui = 3 } },/* diary */
	{ MODKEY,			XK_n,	togglescratch,	{.ui = 4 } },/* ncmpcpp */
	{ MODKEY|ShiftMask,		XK_p,	togglescratch,	{.ui = 5 } },/* pulsemixer */
//	{ MODKEY,		   XK_Num_Lock,	togglescratch,	{.ui = 1 } },/* bc */

				/* Navigation */
	{ MODKEY,			XK_j,	focusstack,	{ .i = -1 }		},
	{ MODKEY|ShiftMask,		XK_j,	shiftag,	{ .i = -1 }		},
	{ MODKEY|ControlMask,		XK_j,	shiftboth,	{ .i = -1 }		},
	{ MODKEY|ControlMask|ShiftMask,	XK_j,	shiftagclients,	{ .i = -1 }		},
	{ MODKEY|ControlMask|ShiftMask,	XK_j,	shiftagclients,	{ .i = +1 }		},
	{ MODKEY|ControlMask,		XK_k,	shiftboth,	{ .i = +1 }		},
	{ MODKEY,                       XK_k,	focusstack,	{ .i = +1 }		},
	{ MODKEY|ShiftMask,             XK_k,	shiftag,	{ .i = +1 }		},
	{ MODKEY,                       XK_h,	setmfact,	{ .f = -0.05 }		},
	{ MODKEY|ShiftMask,             XK_h,	setcfact,	{ .f = +0.05 }		},
	{ MODKEY,                       XK_l,	setmfact,	{ .f = +0.05 }		},
	{ MODKEY|ShiftMask,             XK_l,	setcfact,	{ .f = -0.05 }		},
	{ MODKEY,                       XK_o, shiftviewclients,	{ .i = +1 }		},
	{ MODKEY|ShiftMask,             XK_o,	shiftview,	{ .i = +1 }		},
	{ MODKEY,	                XK_i, shiftviewclients,	{ .i = -1 }		},
	{ MODKEY|ShiftMask,             XK_i,	shiftview,	{ .i = -1 }		},
	{ MODKEY,		XK_semicolon,	incnmaster,	{ .i = +1 }		},
	{ MODKEY|ShiftMask,	XK_semicolon,	incnmaster,	{ .i = -1 }		},
	{ MODKEY,	                XK_q,	killclient,		{0}		},
	{ MODKEY|ShiftMask,         XK_space,	togglefloating,		{0}		},
	{ MODKEY,                       XK_0,	view,		{.ui = ~SPTAGMASK }	},
	{ MODKEY|ShiftMask,             XK_0,	tag,		{.ui = ~SPTAGMASK }	},
	{ MODKEY,                       XK_F1,	fullscreen,		{0}		},
	{ MODKEY|ControlMask,        	XK_F1,	fakefullscreen,		{0}		},
	{ MODKEY,                       XK_w,	zoom,			{0}		},
	{ MODKEY,	              XK_Tab,	view,			{0}		},
	{ MODKEY,	            XK_space,	view,			{0}		},
	{ MODKEY|ControlMask,	    XK_grave,	togglebar,		{0}		},
//	{ MODKEY|ShiftMask,	    XK_grave,	toggletopbar,		{0}		},
//	{ MODKEY|ShiftMask,             XK_c,	quit,           	{0}		},
	{ MODKEY,			XK_F5,	/*restart*/	quit,	{1}		},
	{ MODKEY,                   XK_comma,	focusmon,	{.i = -1 }		},
	{ MODKEY,                  XK_period,	focusmon,	{.i = +1 }		},
	{ MODKEY|ShiftMask,         XK_comma,	tagmon,		{.i = -1 }		},
	{ MODKEY|ShiftMask,        XK_period,	tagmon,		{.i = +1 }		},
	  TAGKEYS(			XK_1,				0)
	  TAGKEYS(			XK_2,				1)
	  TAGKEYS(			XK_3,				2)
	  TAGKEYS(			XK_4,				3)
	  TAGKEYS(			XK_5,				4)
	  TAGKEYS(			XK_6,				5)
	  TAGKEYS(			XK_7,				6)
	  TAGKEYS(			XK_8,				7)
	  TAGKEYS(			XK_9,				8)

			/* Custom bindings (may be better using shkd) */
	{ MODKEY,			XK_b,	spawn,	SHCMD("Books001")		},
	//{ MODKEY,			XK_b,	spawncmd,	{ "Books001", NULL }	},
	{ MODKEY|ShiftMask,		XK_u,	spawn,	SHCMD("bookmenu")		},
	{ MODKEY|ShiftMask,		XK_b,	spawn,	SHCMD("Boletin001")		},
	{ MODKEY,		        XK_c,	spawn,	SHCMD("st -e calcurse")		},
	{ MODKEY,	         	XK_z,	spawn,	SHCMD("redyt -r")		},
	{ MODKEY|ShiftMask,	      	XK_z,	spawn,	SHCMD("walldown")		},
	{ MODKEY,		    XK_grave,	spawn,	SHCMD("dmenuunicode")		},
	{ MODKEY|ShiftMask,	   XK_Return,	spawn,	SHCMD("samedir &")		},
//	{ MODKEY,	        XK_semicolon,	spawn,	SHCMD("dmenu_mpc")		},
//	{ MODKEY|ShiftMask,	    XK_slash,	spawn,	SHCMD("tuxi -q")		},
	{ MODKEY,			XK_u,	spawn,	SHCMD("clipmagick")		},
	{ MODKEY,			XK_y,	spawn,	SHCMD("termyt -r")		},
	{ MODKEY|ShiftMask,		XK_y,	spawn,	SHCMD("dmenuhandler")		},
	{ MODKEY,		    XK_slash,	spawn,	SHCMD("dmenu_browser")		},
	{ MODKEY|ShiftMask,	        XK_n,	spawn,	SHCMD("xdotool click 1")	},
	{ MODKEY,			XK_v,	spawn,	SHCMD("killall xcompmgr || \
								setsid xcompmgr &")	},
	{ MODKEY,			XK_t,	spawn,	SHCMD("testi")			},
	{ MODKEY,		   XK_Escape,	spawn,	SHCMD("Sysfunctions001")	},
//{ MODKEY,	XK_e,	spawn,	SHCMD("st -t NewsBoat -e newsboat -q; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY,			XK_r,	spawn,	SHCMD("st -t NewsBoat -e newsboat -q") },
//					XK_F1, FullScreen
//	{ MODKEY,			XK_F2,	spawn,	SHCMD("dmenu_man")		},
//	{ MODKEY,	         	XK_F3,	spawn,	SHCMD("dmenumount")		},
	{ MODKEY,	         	XK_F3,	spawn,	SHCMD("dmenumount")		},
	{ MODKEY,		 	XK_F4,	spawn,	SHCMD("syncthing & kill -55 $(pidof dwmblocks)") },
//					XK_F5,	reload
	{ MODKEY,	         	XK_F6,	spawn,	SHCMD("dmenumount")		},
	{ MODKEY,		 	XK_F7,	spawn,	SHCMD("dmenumountq")		},
//	{ MODKEY,	 		XK_F7,	spawn,	SHCMD("st -e nvim -c VimwikiIndex") },
	{ MODKEY,		 	XK_F8,	spawn,	SHCMD("sleep 0.2 ; xdotool key Caps_Lock") },
	{ MODKEY,			XK_F9,	spawn,	SHCMD("setkeys & notify-send -t 2400 \
		'Keyboard remapping⌨️ ' 'WAIT!\nRerunning <b>customs</b> shorcuts'")	},
	{ MODKEY,			XK_F10,	spawn,	SHCMD("setxkbmap -layout us -variant altgr-intl -option nodeadkeys & notify-send 'Keyboard⌨️ ' 'Keyboard remapping...\nRunning keyboard defaults, US altgr-intl variant with nodeadkeys...'") },
	//{ MODKEY,			XK_F11,	spawn,	SHCMD("setbg $HOME/Media/Pictures/Wallpapers &") },
	{ MODKEY,                       XK_F11,	random_wall,	{.v = NULL }		},
	{ MODKEY,                       XK_F12,	xrdb,		{.v = NULL }		},
	{ 0,			    XK_Print,	spawn,	SHCMD("scrot -u -se 'mv $f ~/Downloads && magick mogrify -fuzz 4% -define trim:percent-background=0% -trim +repage -format png ~/Downloads/$f'") },
	{ MODKEY,		    XK_Print,	spawn,	SHCMD("dmenurecord")		},
	{ ShiftMask,		    XK_Print,	spawn,	SHCMD("scrot")			},

					/* LAYOUTS */
	{ MODKEY,		XK_backslash,   cyclelayout,	{.i = +1 }		},
	{ MODKEY|ShiftMask,	XK_backslash,   cyclelayout,	{.i = -1 }		},
//	{ MODKEY,			XK_t,	setlayout,	{.v = &layouts[0]} }, //monocle
//	{ MODKEY|ShiftMask,		XK_t,	setlayout,	{.v = &layouts[1]} }, //tile
//	{ MODKEY,			XK_n,	setlayout,	{.v = &layouts[2]} }, //bstack
//	{ MODKEY|ShiftMask,		XK_i,	setlayout,	{.v = &layouts[3]} }, //spiral
//	{ MODKEY,			XK_i,	setlayout,	{.v = &layouts[4]} }, //dwindle
//	{ MODKEY|ShiftMask,		XK_f,	setlayout,	{.v = &layouts[5]} }, //deck
//	{ MODKEY,			XK_f,	setlayout,	{.v = &layouts[6]} }, //centeredmaster

				/* Media */
	{ MODKEY|ShiftMask,		XK_minus,	spawn,	SHCMD("mpc volume -3")	},
	{ MODKEY|ShiftMask,		XK_equal,	spawn,	SHCMD("mpc volume +3")	},
	{ MODKEY|ShiftMask,		XK_bracketleft,	spawn,	SHCMD("mpc seek -10")	},
	{ MODKEY|ShiftMask,		XK_bracketright,spawn,	SHCMD("mpc seek +10")	},
{ 0, XF86XK_AudioLowerVolume,	spawn,	SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
{ 0, XF86XK_AudioRaiseVolume,	spawn,	SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
{ 0, XF86XK_AudioMute,		spawn,	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
{ MODKEY,	XK_minus,	spawn,	SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
{ MODKEY,	XK_equal,	spawn,	SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
{ MODKEY,	 XK_BackSpace,	spawn,	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
//{ 0,	XF86XK_Calculator,	spawn,	SHCMD("sleep 0.2 ; scrot -se 'mv $f ~/Downloads'") },
//{ 0, XF86XK_ScreenSaver,	spawn,	SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
//	{ 0,	XF86XK_AudioStop,		spawn,	SHCMD("mpc toggle) },
	{ 0,	XF86XK_Sleep,			spawn,	SHCMD("sudo zzz")		},
	{ 0,	XF86XK_ScreenSaver,		spawn,	SHCMD("xset dpms force off")	},
	{ 0,	XF86XK_MonBrightnessUp,		spawn,	SHCMD("sudo brightnessctl -q set +1%") },
	{ 0,	XF86XK_MonBrightnessDown,	spawn,	SHCMD("sudo brightnessctl -q set 1%-") },
	{ 0,	XF86XK_AudioPlay,		spawn,	SHCMD("mpc toggle")		},
	{ 0,	XF86XK_AudioPrev,		spawn,	SHCMD("mpc prev")		},
	{ 0,	XF86XK_AudioNext,		spawn,	SHCMD("mpc next")		},
	{ MODKEY,		XK_p,		spawn,	SHCMD("mpc toggle") },
	{ MODKEY,	XK_bracketleft,		spawn,	SHCMD("mpc prev") },
	{ MODKEY,	XK_bracketright,	spawn,	SHCMD("mpc next") },
	{ MODKEY|ControlMask,	XK_p,		spawn,	SHCMD("mpdnoti")		},
//	{ MODKEY|ShiftMask,	XK_p,		spawn,	SHCMD("st -e pulsemixer")	},

				/* GAPS */
	{ MODKEY,			XK_f,	incrgaps,	{.i = +3 }		},
	{ MODKEY,			XK_g,	incrgaps,	{.i = -3 }		},
	{ MODKEY,			XK_a,	togglegaps,		{0}		},
	{ MODKEY|ControlMask,   	XK_a,	defaultgaps,		{0}		},
	{ MODKEY|ShiftMask,		XK_a,	togglesmartgaps,	{0}		},
//	{ MODKEY|ControlMask,           XK_o,	setcfact,	{.f =  0.00}		},
};

/* button definitions
 * click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button1,  spawn,  SHCMD("sleep 0.2 ; scrot -se 'mv $f ~/Downloads'") },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,		0,		Button3,  spawn, SHCMD("scrot -u -se 'mv $f ~/Downloads'") },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};