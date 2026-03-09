#pragma once

/* Template to create own theme

        === Default Colors ===
DEF_BG      -- Background color
DEF_FG      -- Foreground color
DEF_TTL     -- Section title color

        === Section Colors ===
BG_SEC_DIR
BG_SEC_CNT
BG_SEC_INF
BG_SEC_REC
BG_SEC_CPB

FG_SEC_DIR
FG_SEC_CNT
FG_SEC_INF
FG_SEC_REC
FG_SEC_CPB

*/

#ifdef THEME_DARK
#define DEF_BG      0x000000
#define DEF_FG      0xFFFFFF
#endif

#ifdef THEME_LIGHT
#define DEF_BG      0xFFFFFF
#define DEF_FG      0x000000
#endif