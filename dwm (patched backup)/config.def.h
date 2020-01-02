/*  ____ _____  */
/* |  _ \_   _|  Derek Taylor (DistroTube) */
/* | | | || |  	http://www.youtube.com/c/DistroTube */
/* | |_| || |  	http://www.gitlab.com/dwt1/ */
/* |____/ |_|  	*/ 

#include "selfrestart.c"

/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* pixel gap between clients */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Mononoki Nerd Font:size=12" };
static const char dmenufont[]       = "Mononoki Nerd Font:size=10";
static const char col_gray1[]       = "#222222"; /* background color unfocused windows */
static const char col_gray2[]       = "#444444"; /* border     color unfocused windows */
static const char col_gray3[]       = "#bbbbbb"; /* font       color unfocused windows */
static const char col_gray4[]       = "#eeeeee"; /* font       color   focused windows */
static const char col_cyan[]        = "#24DEFF"; /* border     color   focused windows */
static const unsigned int baralpha = 0xee;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =   { col_gray3, col_gray1,  col_gray2 },  /* statusbar unfocused icon-workspace */ 
	[SchemeSel]  =   { col_gray4, "#7C24FF",  col_cyan  },  /* statusbar   focused icon-workspace */
	[SchemeTitle]  = { col_gray1, "#24A3FF",  col_cyan  },  /* statusbar   focused text-workspace */
	
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "", "", "🎮", "", "", "", "", "", "" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Oblogout", NULL,       NULL,       0,            1,             1,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 4,       1,             1,           -1 },
	{ "Steam",    NULL,       NULL,       1 << 2,       1,             1,           -1 },
	{ "Thunar",   NULL,       NULL,       1 << 7,       0,             0,           -1 },
	{ "Pcmanfm",  NULL,       NULL,       1 << 7,       0,             0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,             0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }*/
#define CMD(cmd) { .v   = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray1, NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *tabbed_surf[]    = { "tabbed", "surf", "-pe", NULL };
static const char *web_browser[]    = { "firefox", NULL};
static const char *file_explorer[]  = { "thunar", NULL };
static const char *logout_manager[] = { "oblogout", NULL };
static const char *steam_launcher[] = { "steam", NULL };

static Key keys[] = {
	/* modifier               key              function        argument */
	{ Mod1Mask|ControlMask,   XK_Return,       spawn,          {.v = dmenucmd } },
	{ MODKEY,                 XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,                 XK_b,            togglebar,      {0} },
	{ MODKEY|ShiftMask,       XK_j,            rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_k,            rotatestack,    {.i = -1 } },
	{ MODKEY,                 XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                 XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                 XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                 XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                 XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                 XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,       XK_Return,       zoom,           {0} },
	{ MODKEY,                 XK_Tab,          view,           {0} },
	{ MODKEY|ShiftMask,       XK_c,            killclient,     {0} },
	{ MODKEY,                 XK_q,            killclient,     {0} },
	{ MODKEY,                 XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                 XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                 XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                 XK_u,            setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                 XK_o,            setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                 XK_g,            setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                 XK_s,            setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                 XK_d,            setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ControlMask,     XK_comma,        cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,     XK_period,       cyclelayout,    {.i = +1 } },
	{ MODKEY,                 XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,       XK_space,        togglefloating, {0} },
	{ MODKEY,                 XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,       XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                 XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,                 XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,       XK_period,       tagmon,         {.i = +1 } },	
	
    /* Dmenu scripts launched with ALT + CTRL + KEY  */
	{ Mod1Mask|ControlMask,   XK_e,            spawn,          CMD("./.dmenu/dmenu-edit-configs.sh") },
	{ Mod1Mask|ControlMask,   XK_r,            spawn,          CMD("./.dmenu/dmenu-reddio.sh") },
	{ Mod1Mask|ControlMask,   XK_p,            spawn,          CMD("passmenu") },
	{ Mod1Mask|ControlMask,   XK_s,            spawn,          CMD("./.dmenu/dmenu-surfraw.sh") },
    
    /* Apps Launched with SUPER + ALT + KEY  */
	{ MODKEY|Mod1Mask,        XK_l,            spawn,          CMD("st -e lynx -cfg=~/.lynx/lynx.cfg -lss=~/.lynx/lynx.lss gopher://distro.tube") },
	{ MODKEY|Mod1Mask,        XK_f,            spawn,          CMD("st -e sh ./.config/vifm/scripts/vifmrun") },
	{ MODKEY|Mod1Mask,        XK_i,            spawn,          CMD("st -e irssi") },
	{ MODKEY|Mod1Mask,        XK_n,            spawn,          CMD("st -e newsboat") },
	{ MODKEY|Mod1Mask,        XK_r,            spawn,          CMD("st -e rtv") },
	{ MODKEY|Mod1Mask,        XK_e,            spawn,          CMD("st -e neomutt") },
	
		/* Apps Launched with ALT + KEY  */
	{ Mod1Mask,               XK_r,            spawn,          CMD("st -e ranger") },
	{ Mod1Mask,               XK_h,            spawn,          CMD("st -e htop") },
	{ Mod1Mask,               XK_t,            spawn,          CMD("st -e rtorrent") },
	{ Mod1Mask,               XK_s,            spawn,          {.v = tabbed_surf } },
	{ Mod1Mask,               XK_f,            spawn,          {.v = web_browser } },
	{ Mod1Mask,               XK_o,            spawn,          {.v = file_explorer } },
	{ Mod1Mask,               XK_x,            spawn,          {.v = logout_manager } },
	{ Mod1Mask,               XK_s,            spawn,          {.v = steam_launcher } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,		quit,			{0} },
	{ MODKEY|ShiftMask, 			XK_r, 		self_restart,	{0} },
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
