/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const int horizpadbar		= 4;
static const int vertpadbar         = 10;

static const char *fonts[]          = { "SauceCodePro Nerd Font:size=11" };

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char col_cyan[]        = "#005577";

/* Transparent Bar */
static const unsigned int baralpha        = 0xcc;
static const unsigned int borderalpha     = OPAQUE;

static const char *colors[][3] = {
	/*               fg           bg          border  */
	[SchemeNorm] =	 { col_gray3, col_gray1,  col_gray2 },
	[SchemeSel]  =	 { col_gray4, col_cyan,   col_cyan },
	[SchemeWarn] =	 { col_black, col_yellow, col_red },
	[SchemeUrgent]=	 { col_white, col_red,    col_red },
};

static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",				NULL,       NULL,       1 << 8,       1,           -1 },
	{ "Chromium",			NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Spotify",			NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Libreoffice",		NULL,       NULL,       1 << 2,       0,           -1 },
	{ "libreoffice-calc",	NULL,		NULL,       1 << 2,       0,           -1 },
	// Engine Development Windows
	{ "Primal Engine",		NULL,		NULL,       1 << 0,       1,           -1 },
	{ "No Title Yet",		NULL,		NULL,       1 << 0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY2,						KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char cmd_rofi[] = "/home/piero/.config/rofi/menu/RUN";
static const char cmd_openfile[] = "/home/piero/.config/rofi/menu/SEARCH";
static const char cmd_system[] = "/home/piero/.config/rofi/menu/SYSTEM";
static const char cmd_configs[] = "/home/piero/.config/rofi/menu/CONFIG";

static const char cmd_printscr[] = "flameshot gui -p /home/piero/Pictures/Screenshots";
static const char cmd_printscrfull[] = "flameshot full -c";

static const char cmd_brightup[] = "light -A 10";
static const char cmd_brightdown[] = "light -U 10";

static const char cmd_audioplay[] = "dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause";
static const char cmd_audionext[] = "dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next";
static const char cmd_audioprev[] = "dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous";

static const char cmd_volmute[] = "amixer -q set Master toggle";
static const char cmd_volup[]   = "amixer -q set Master 5%+ unmute";
static const char cmd_voldown[] = "amixer -q set Master 5%- unmute";

static const char *cmd_term[] = { "st", NULL };
static const char *cmd_chromium[] = { "chromium", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* Menus */
	{ MODKEY,                       XK_Tab,    spawn,          SHCMD(cmd_rofi)  },
	{ MODKEY,                       XK_p,      spawn,		   SHCMD(cmd_openfile)  },
	{ MODKEY|MODKEY2,               XK_Escape, spawn,		   SHCMD(cmd_system)  },
	{ MODKEY|MODKEY2,               XK_Delete, spawn,		   SHCMD(cmd_configs)  },

	/* Utilities */
	{ 0,							XK_Print,  spawn,          SHCMD(cmd_printscr) },
	{ ShiftMask,					XK_Print,  spawn,          SHCMD(cmd_printscrfull) },

	/* Application Shortcuts */
	{ MODKEY,						XK_Return, spawn,          {.v = cmd_term } },
	{ MODKEY,						XK_c,      spawn,          {.v = cmd_chromium } },

	/* Gaps */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|MODKEY2,				XK_plus,   setgaps,        {.i = 0  } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY2,                      XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* Media Controls */
	{ 0,							XF86XK_MonBrightnessUp, spawn, SHCMD(cmd_brightup) },
	{ 0,							XF86XK_MonBrightnessDown, spawn, SHCMD(cmd_brightdown) },

	{ 0,							XF86XK_AudioPlay, spawn, SHCMD(cmd_audioplay) },
	{ 0,							XF86XK_AudioNext, spawn, SHCMD(cmd_audionext) },
	{ 0,							XF86XK_AudioPrev, spawn, SHCMD(cmd_audioprev) },

	{ 0,							XF86XK_AudioRaiseVolume, spawn, SHCMD(cmd_volup) },
	{ 0,							XF86XK_AudioLowerVolume, spawn, SHCMD(cmd_voldown) },
	{ 0,							XF86XK_AudioMute,		 spawn, SHCMD(cmd_volmute) },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = cmd_term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
