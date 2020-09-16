/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int vertpad	    = 0;
static const int sidepad	    = 0;
static const int user_bh            = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {
	"jet brains mono:pixelsize=15:antialias=true",
	"noto color emoji:pixelsize=13:antialias=true",
	"monospace:size=13",
};
static const char dmenufont[]       = "jetbrains mono:size=13";

// Nord theme
static const char  nord0[] = "#2E3440";
static const char  nord1[] = "#3B4252";
static const char  nord2[] = "#434C5E";
static const char  nord3[] = "#4C566A";
static const char  nord4[] = "#D8DEE9";
static const char  nord5[] = "#E5E9F0";
static const char  nord6[] = "#ECEFF4";
static const char  nord7[] = "#8FBCBB"; // turquoise
static const char  nord8[] = "#88C0D0"; // cyan
static const char  nord9[] = "#81A1C1"; // light blue
static const char nord10[] = "#5E81AC"; // blue
static const char nord11[] = "#BF616A"; // red
static const char nord12[] = "#D08770"; // orange
static const char nord13[] = "#EBCB8B"; // yellow
static const char nord14[] = "#A3BE8C"; // green
static const char nord15[] = "#B48EAD"; // magenta

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { nord4 , nord1 , nord8 },
	[SchemeSel]  = { nord4 , nord8 , nord8 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7","8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "TelegramDesktop", NULL, NULL, 	2,	    0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.625; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[~@]",     dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", nord1, "-nf", nord4, "-sb", nord8, "-sf", nord3, NULL };
static const char *termcmd[]  = { "st", NULL };
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ SUPER,                        XK_space,  spawn,          {.v = dmenucmd } },
	{ SUPER,		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ SUPER,                        XK_j,      focusstack,     {.i = +1 } },
	{ SUPER,                        XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ SUPER,                        XK_h,      setmfact,       {.f = -0.1} },
	{ SUPER,                        XK_l,      setmfact,       {.f = +0.1} },
	{ MODKEY,			XK_h,	   movestack,	   {.i = +1 } },
	{ MODKEY,			XK_l,	   movestack,      {.i = -1 } },
	{ MODKEY|SUPER,                 XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|SUPER,                 XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|SUPER|ShiftMask,       XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|SUPER|ShiftMask,       XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|SUPER|ControlMask,     XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|SUPER|ControlMask,     XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|SUPER,                 XK_0,      togglegaps,     {0} },
	{ MODKEY|SUPER|ShiftMask,       XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|SUPER,                 XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|SUPER,                 XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ SUPER|ShiftMask,              XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

