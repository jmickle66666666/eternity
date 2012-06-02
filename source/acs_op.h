// Emacs style mode select -*- C++ -*-
//----------------------------------------------------------------------------
//
// Copyright(C) 2012 David Hill
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//----------------------------------------------------------------------------
//
// ACS instructions.
//
//----------------------------------------------------------------------------

// Internal instructions.
#ifdef ACS_OP
   ACS_OP(NOP, 0)
   ACS_OP(KILL, 0)

   // Special Commands
   ACS_OP(LINESPEC, 2)
   ACS_OP(LINESPEC_IMM, -1)

   // SET
   ACS_OP(SET_LOCALVAR,  1)
   ACS_OP(SET_MAPVAR,    1)
   ACS_OP(SET_WORLDVAR,  1)
   ACS_OP(SET_GLOBALVAR, 1)

   // GET
   ACS_OP(GET_IMM,       1)
   ACS_OP(GET_LOCALVAR,  1)
   ACS_OP(GET_MAPVAR,    1)
   ACS_OP(GET_WORLDVAR,  1)
   ACS_OP(GET_GLOBALVAR, 1)
   ACS_OP(GET_THINGVAR,  1)

   // GETARR
   ACS_OP(GETARR_IMM, 1)

   // Binary Ops
   ACS_OP(ADD_STACK,     0)
   ACS_OP(ADD_LOCALVAR,  1)
   ACS_OP(ADD_MAPVAR,    1)
   ACS_OP(ADD_WORLDVAR,  1)
   ACS_OP(ADD_GLOBALVAR, 1)
   ACS_OP(AND_STACK,     0)
   ACS_OP(CMP_EQ,        0)
   ACS_OP(CMP_NE,        0)
   ACS_OP(CMP_LT,        0)
   ACS_OP(CMP_GT,        0)
   ACS_OP(CMP_LE,        0)
   ACS_OP(CMP_GE,        0)
   ACS_OP(DEC_LOCALVAR,  1)
   ACS_OP(DEC_MAPVAR,    1)
   ACS_OP(DEC_WORLDVAR,  1)
   ACS_OP(DEC_GLOBALVAR, 1)
   ACS_OP(DIV_STACK,     0)
   ACS_OP(DIV_LOCALVAR,  1)
   ACS_OP(DIV_MAPVAR,    1)
   ACS_OP(DIV_WORLDVAR,  1)
   ACS_OP(DIV_GLOBALVAR, 1)
   ACS_OP(DIVX_STACK,    0)
   ACS_OP(IOR_STACK,     0)
   ACS_OP(INC_LOCALVAR,  1)
   ACS_OP(INC_MAPVAR,    1)
   ACS_OP(INC_WORLDVAR,  1)
   ACS_OP(INC_GLOBALVAR, 1)
   ACS_OP(LSH_STACK,     0)
   ACS_OP(MOD_STACK,     0)
   ACS_OP(MOD_LOCALVAR,  1)
   ACS_OP(MOD_MAPVAR,    1)
   ACS_OP(MOD_WORLDVAR,  1)
   ACS_OP(MOD_GLOBALVAR, 1)
   ACS_OP(MUL_STACK,     0)
   ACS_OP(MUL_LOCALVAR,  1)
   ACS_OP(MUL_MAPVAR,    1)
   ACS_OP(MUL_WORLDVAR,  1)
   ACS_OP(MUL_GLOBALVAR, 1)
   ACS_OP(MULX_STACK,    0)
   ACS_OP(RSH_STACK,     0)
   ACS_OP(SUB_STACK,     0)
   ACS_OP(SUB_LOCALVAR,  1)
   ACS_OP(SUB_MAPVAR,    1)
   ACS_OP(SUB_WORLDVAR,  1)
   ACS_OP(SUB_GLOBALVAR, 1)
   ACS_OP(XOR_STACK,     0)

   // Unary Ops
   ACS_OP(NEGATE_STACK, 0)

   // Logical Ops
   ACS_OP(LOGAND_STACK, 0)
   ACS_OP(LOGIOR_STACK, 0)
   ACS_OP(LOGNOT_STACK, 0)

   // Trigonometry Ops
   ACS_OP(TRIG_COS,         0)
   ACS_OP(TRIG_SIN,         0)
   ACS_OP(TRIG_VECTORANGLE, 0)

   // Branching
   ACS_OP(BRANCH_CASE,    2)
   ACS_OP(BRANCH_IMM,     1)
   ACS_OP(BRANCH_NOTZERO, 1)
   ACS_OP(BRANCH_ZERO,    1)

   // Stack Control
   ACS_OP(STACK_COPY, 0)
   ACS_OP(STACK_DROP, 0)
   ACS_OP(STACK_SWAP, 0)

   // Script Control
   ACS_OP(SCRIPT_RESTART,   0)
   ACS_OP(SCRIPT_SUSPEND,   0)
   ACS_OP(SCRIPT_TERMINATE, 0)

   // Printing
   ACS_OP(STARTPRINT,   0)
   ACS_OP(ENDPRINT,     0)
   ACS_OP(ENDPRINTBOLD, 0)
   ACS_OP(PRINTCHAR,    0)
   ACS_OP(PRINTFIXED,   0)
   ACS_OP(PRINTINT,     0)
   ACS_OP(PRINTNAME,    0)
   ACS_OP(PRINTSTRING,  0)

   // Miscellaneous
   ACS_OP(ACTIVATORARMOR,  0)
   ACS_OP(ACTIVATORFRAGS,  0)
   ACS_OP(ACTIVATORHEALTH, 0)
   ACS_OP(ACTIVATORSOUND,  0)
   ACS_OP(AMBIENTSOUND,      0)
   ACS_OP(AMBIENTSOUNDLOCAL, 0)
   ACS_OP(SETGRAVITY,     0)
   ACS_OP(SETGRAVITY_IMM, 1)
   ACS_OP(SETLINEBLOCKING,        0)
   ACS_OP(SETLINEMONSTERBLOCKING, 0)
   ACS_OP(SETLINESPECIAL,         0)
   ACS_OP(SETLINETEXTURE,         0)
   ACS_OP(SETMUSIC,          0)
   ACS_OP(SETMUSIC_IMM,      3)
   ACS_OP(SETMUSICLOCAL,     0)
   ACS_OP(SETMUSICLOCAL_IMM, 3)
   ACS_OP(SETTHINGSPECIAL, 0)
   ACS_OP(SPAWN,         0)
   ACS_OP(SPAWN_IMM,     6)
   ACS_OP(SPAWNSPOT,     0)
   ACS_OP(SPAWNSPOT_IMM, 4)
   ACS_OP(TAGSTRING, 0)
   ACS_OP(DELAY, 0)
   ACS_OP(DELAY_IMM, 1)
   ACS_OP(RANDOM, 0)
   ACS_OP(RANDOM_IMM, 2)
   ACS_OP(THINGCOUNT, 0)
   ACS_OP(THINGCOUNT_IMM, 2)
   ACS_OP(TAGWAIT, 0)
   ACS_OP(TAGWAIT_IMM, 1)
   ACS_OP(POLYWAIT, 0)
   ACS_OP(POLYWAIT_IMM, 1)
   ACS_OP(CHANGEFLOOR, 0)
   ACS_OP(CHANGEFLOOR_IMM, 2)
   ACS_OP(CHANGECEILING, 0)
   ACS_OP(CHANGECEILING_IMM, 2)
   ACS_OP(LINESIDE, 0)
   ACS_OP(SCRIPTWAIT, 0)
   ACS_OP(SCRIPTWAIT_IMM, 1)
   ACS_OP(CLEARLINESPECIAL, 0)
   ACS_OP(PLAYERCOUNT, 0)
   ACS_OP(GAMETYPE, 0)
   ACS_OP(GAMESKILL, 0)
   ACS_OP(TIMER, 0)
   ACS_OP(SECTORSOUND, 0)
   ACS_OP(SOUNDSEQUENCE, 0)
   ACS_OP(THINGSOUND, 0)
#endif//ACS_OP

// ACS0 instructions.
#ifdef ACS0_OP
   /*   0 */ ACS0_OP(NOP, NOP, 0)
   /*   1 */ ACS0_OP(SCRIPT_TERMINATE, SCRIPT_TERMINATE, 0)
   /*   2 */ ACS0_OP(SCRIPT_SUSPEND, SCRIPT_SUSPEND, 0)
   /*   3 */ ACS0_OP(GET_IMM, GET_IMM, 1)
   /*   4 */ ACS0_OP(LINESPEC,     LINESPEC1,     1)
   /*   5 */ ACS0_OP(LINESPEC,     LINESPEC2,     1)
   /*   6 */ ACS0_OP(LINESPEC,     LINESPEC3,     1)
   /*   7 */ ACS0_OP(LINESPEC,     LINESPEC4,     1)
   /*   8 */ ACS0_OP(LINESPEC,     LINESPEC5,     1)
   /*   9 */ ACS0_OP(LINESPEC_IMM, LINESPEC1_IMM, 2)
   /*  10 */ ACS0_OP(LINESPEC_IMM, LINESPEC2_IMM, 3)
   /*  11 */ ACS0_OP(LINESPEC_IMM, LINESPEC3_IMM, 4)
   /*  12 */ ACS0_OP(LINESPEC_IMM, LINESPEC4_IMM, 5)
   /*  13 */ ACS0_OP(LINESPEC_IMM, LINESPEC5_IMM, 6)
   /*  14 */ ACS0_OP(ADD_STACK, ADD_STACK, 0)
   /*  15 */ ACS0_OP(SUB_STACK, SUB_STACK, 0)
   /*  16 */ ACS0_OP(MUL_STACK, MUL_STACK, 0)
   /*  17 */ ACS0_OP(DIV_STACK, DIV_STACK, 0)
   /*  18 */ ACS0_OP(MOD_STACK, MOD_STACK, 0)
   /*  19 */ ACS0_OP(CMP_EQ, CMP_EQ, 0)
   /*  20 */ ACS0_OP(CMP_NE, CMP_NE, 0)
   /*  21 */ ACS0_OP(CMP_LT, CMP_LT, 0)
   /*  22 */ ACS0_OP(CMP_GT, CMP_GT, 0)
   /*  23 */ ACS0_OP(CMP_LE, CMP_LE, 0)
   /*  24 */ ACS0_OP(CMP_GE, CMP_GE, 0)
   /*  25 */ ACS0_OP(SET_LOCALVAR, SET_LOCALVAR, 1)
   /*  26 */ ACS0_OP(SET_MAPVAR,   SET_MAPVAR,   1)
   /*  27 */ ACS0_OP(SET_WORLDVAR, SET_WORLDVAR, 1)
   /*  28 */ ACS0_OP(GET_LOCALVAR, GET_LOCALVAR, 1)
   /*  29 */ ACS0_OP(GET_MAPVAR,   GET_MAPVAR,   1)
   /*  30 */ ACS0_OP(GET_WORLDVAR, GET_WORLDVAR, 1)
   /*  31 */ ACS0_OP(ADD_LOCALVAR, ADD_LOCALVAR, 1)
   /*  32 */ ACS0_OP(ADD_MAPVAR,   ADD_MAPVAR,   1)
   /*  33 */ ACS0_OP(ADD_WORLDVAR, ADD_WORLDVAR, 1)
   /*  34 */ ACS0_OP(SUB_LOCALVAR, SUB_LOCALVAR, 1)
   /*  35 */ ACS0_OP(SUB_MAPVAR,   SUB_MAPVAR,   1)
   /*  36 */ ACS0_OP(SUB_WORLDVAR, SUB_WORLDVAR, 1)
   /*  37 */ ACS0_OP(MUL_LOCALVAR, MUL_LOCALVAR, 1)
   /*  38 */ ACS0_OP(MUL_MAPVAR,   MUL_MAPVAR,   1)
   /*  39 */ ACS0_OP(MUL_WORLDVAR, MUL_WORLDVAR, 1)
   /*  40 */ ACS0_OP(DIV_LOCALVAR, DIV_LOCALVAR, 1)
   /*  41 */ ACS0_OP(DIV_MAPVAR,   DIV_MAPVAR,   1)
   /*  42 */ ACS0_OP(DIV_WORLDVAR, DIV_WORLDVAR, 1)
   /*  43 */ ACS0_OP(MOD_LOCALVAR, MOD_LOCALVAR, 1)
   /*  44 */ ACS0_OP(MOD_MAPVAR,   MOD_MAPVAR,   1)
   /*  45 */ ACS0_OP(MOD_WORLDVAR, MOD_WORLDVAR, 1)
   /*  46 */ ACS0_OP(INC_LOCALVAR, INC_LOCALVAR, 1)
   /*  47 */ ACS0_OP(INC_MAPVAR,   INC_MAPVAR,   1)
   /*  48 */ ACS0_OP(INC_WORLDVAR, INC_WORLDVAR, 1)
   /*  49 */ ACS0_OP(DEC_LOCALVAR, DEC_LOCALVAR, 1)
   /*  50 */ ACS0_OP(DEC_MAPVAR,   DEC_MAPVAR,   1)
   /*  51 */ ACS0_OP(DEC_WORLDVAR, DEC_WORLDVAR, 1)
   /*  52 */ ACS0_OP(BRANCH_IMM, BRANCH_IMM, 1)
   /*  53 */ ACS0_OP(BRANCH_NOTZERO, BRANCH_NOTZERO, 1)
   /*  54 */ ACS0_OP(STACK_DROP, STACK_DROP, 0)
   /*  55 */ ACS0_OP(DELAY,     DELAY,     0)
   /*  56 */ ACS0_OP(DELAY_IMM, DELAY_IMM, 1)
   /*  57 */ ACS0_OP(RANDOM,     RANDOM,     0)
   /*  58 */ ACS0_OP(RANDOM_IMM, RANDOM_IMM, 2)
   /*  59 */ ACS0_OP(THINGCOUNT,     THINGCOUNT,     0)
   /*  60 */ ACS0_OP(THINGCOUNT_IMM, THINGCOUNT_IMM, 2)
   /*  61 */ ACS0_OP(TAGWAIT,     TAGWAIT,     0)
   /*  62 */ ACS0_OP(TAGWAIT_IMM, TAGWAIT_IMM, 1)
   /*  63 */ ACS0_OP(POLYWAIT,     POLYWAIT,     0)
   /*  64 */ ACS0_OP(POLYWAIT_IMM, POLYWAIT_IMM, 1)
   /*  65 */ ACS0_OP(CHANGEFLOOR,     CHANGEFLOOR,     0)
   /*  66 */ ACS0_OP(CHANGEFLOOR_IMM, CHANGEFLOOR_IMM, 2)
   /*  67 */ ACS0_OP(CHANGECEILING,     CHANGECEILING,     0)
   /*  68 */ ACS0_OP(CHANGECEILING_IMM, CHANGECEILING_IMM, 2)
   /*  69 */ ACS0_OP(SCRIPT_RESTART, SCRIPT_RESTART, 0)
   /*  70 */ ACS0_OP(LOGAND_STACK, LOGAND_STACK, 0)
   /*  71 */ ACS0_OP(LOGIOR_STACK, LOGIOR_STACK, 0)
   /*  72 */ ACS0_OP(AND_STACK, AND_STACK, 0)
   /*  73 */ ACS0_OP(IOR_STACK, IOR_STACK, 0)
   /*  74 */ ACS0_OP(XOR_STACK, XOR_STACK, 0)
   /*  75 */ ACS0_OP(LOGNOT_STACK, LOGNOT_STACK, 0)
   /*  76 */ ACS0_OP(LSH_STACK, LSH_STACK, 0)
   /*  77 */ ACS0_OP(RSH_STACK, RSH_STACK, 0)
   /*  78 */ ACS0_OP(NEGATE_STACK, NEGATE_STACK, 0)
   /*  79 */ ACS0_OP(BRANCH_ZERO, BRANCH_ZERO, 1)
   /*  80 */ ACS0_OP(LINESIDE, LINESIDE, 0)
   /*  81 */ ACS0_OP(SCRIPTWAIT,     SCRIPTWAIT,     0)
   /*  82 */ ACS0_OP(SCRIPTWAIT_IMM, SCRIPTWAIT_IMM, 1)
   /*  83 */ ACS0_OP(CLEARLINESPECIAL, CLEARLINESPECIAL, 0)
   /*  84 */ ACS0_OP(BRANCH_CASE, BRANCH_CASE, 2)
   /*  85 */ ACS0_OP(STARTPRINT, STARTPRINT, 0)
   /*  86 */ ACS0_OP(ENDPRINT, ENDPRINT, 0)
   /*  87 */ ACS0_OP(PRINTSTRING, PRINTSTRING, 0)
   /*  88 */ ACS0_OP(PRINTINT, PRINTINT, 0)
   /*  89 */ ACS0_OP(PRINTCHAR, PRINTCHAR, 0)
   /*  90 */ ACS0_OP(PLAYERCOUNT, PLAYERCOUNT, 0)
   /*  91 */ ACS0_OP(GAMETYPE, GAMETYPE, 0)
   /*  92 */ ACS0_OP(GAMESKILL, GAMESKILL, 0)
   /*  93 */ ACS0_OP(TIMER, TIMER, 0)
   /*  94 */ ACS0_OP(SECTORSOUND, SECTORSOUND, 0)
   /*  95 */ ACS0_OP(AMBIENTSOUND, AMBIENTSOUND, 0)
   /*  96 */ ACS0_OP(SOUNDSEQUENCE, SOUNDSEQUENCE, 0)
   /*  97 */ ACS0_OP(SETLINETEXTURE, SETLINETEXTURE, 0)
   /*  98 */ ACS0_OP(SETLINEBLOCKING, SETLINEBLOCKING, 0)
   /*  99 */ ACS0_OP(SETLINESPECIAL, SETLINESPECIAL, 0)
   /* 100 */ ACS0_OP(THINGSOUND, THINGSOUND, 0)
   /* 101 */ ACS0_OP(ENDPRINTBOLD, ENDPRINTBOLD, 0)
#endif//ACS0_OP

#ifdef ACSE_OP
   /* 102 */ ACSE_OP(ACTIVATORSOUND, ACTIVATORSOUND, 0)
   /* 103 */ ACSE_OP(AMBIENTSOUNDLOCAL, AMBIENTSOUNDLOCAL, 0)
   /* 104 */ ACSE_OP(SETLINEMONSTERBLOCKING, SETLINEMONSTERBLOCKING, 0)
   /* 105 */ ACSE_OP(KILL, OPCODE105, 0)
   /* 106 */ ACSE_OP(KILL, OPCODE106, 0)
   /* 107 */ ACSE_OP(KILL, OPCODE107, 0)
   /* 108 */ ACSE_OP(KILL, OPCODE108, 0)
   /* 109 */ ACSE_OP(KILL, OPCODE109, 0)
   /* 110 */ ACSE_OP(KILL, OPCODE110, 0)
   /* 111 */ ACSE_OP(KILL, OPCODE111, 0)
   /* 112 */ ACSE_OP(KILL, OPCODE112, 0)
   /* 113 */ ACSE_OP(KILL, OPCODE113, 0)
   /* 114 */ ACSE_OP(KILL, OPCODE114, 0)
   /* 115 */ ACSE_OP(KILL, OPCODE115, 0)
   /* 116 */ ACSE_OP(KILL, OPCODE116, 0)
   /* 117 */ ACSE_OP(KILL, OPCODE117, 0)
   /* 118 */ ACSE_OP(KILL, OPCODE118, 0)
   /* 119 */ ACSE_OP(KILL, ACTIVATORTEAM, 0)
   /* 120 */ ACSE_OP(ACTIVATORHEALTH, ACTIVATORHEALTH, 0)
   /* 121 */ ACSE_OP(ACTIVATORARMOR,  ACTIVATORARMOR,  0)
   /* 122 */ ACSE_OP(ACTIVATORFRAGS,  ACTIVATORFRAGS,  0)
   /* 123 */ ACSE_OP(KILL, OPCODE123, 0)
   /* 124 */ ACSE_OP(KILL, BLUETEAMCOUNT, 0)
   /* 125 */ ACSE_OP(KILL, REDTEAMCOUNT, 0)
   /* 126 */ ACSE_OP(KILL, BLUETEAMSCORE, 0)
   /* 127 */ ACSE_OP(KILL, REDTEAMSCORE, 0)
   /* 128 */ ACSE_OP(GAMETYPE, GAMETYPE_ONEFLAGCTF, 0)
   /* 129 */ ACSE_OP(KILL, GETINVASIONWAVE, 0)
   /* 130 */ ACSE_OP(KILL, GETINVASIONSTATE, 0)
   /* 131 */ ACSE_OP(PRINTNAME, PRINTNAME, 0)
   /* 132 */ ACSE_OP(SETMUSIC, SETMUSIC_ST, 0)
   /* 133 */ ACSE_OP(KILL, CONSOLECOMMAND_IMM, 3)
   /* 134 */ ACSE_OP(KILL, CONSOLECOMMAND,     0)
   /* 135 */ ACSE_OP(GAMETYPE, GAMETYPE_SINGLEPLAYER, 0)
   /* 136 */ ACSE_OP(MULX_STACK, MULX_STACK, 0)
   /* 137 */ ACSE_OP(DIVX_STACK, DIVX_STACK, 0)
   /* 138 */ ACSE_OP(SETGRAVITY,     SETGRAVITY,     0)
   /* 139 */ ACSE_OP(SETGRAVITY_IMM, SETGRAVITY_IMM, 1)
   /* 140 */ ACSE_OP(KILL, SETAIRCONTROL,     0)
   /* 141 */ ACSE_OP(KILL, SETAIRCONTROL_IMM, 1)
   /* 142 */ ACSE_OP(KILL, CLEARINVENTORY, 0)
   /* 143 */ ACSE_OP(KILL, GIVEINVENTORY,     0)
   /* 144 */ ACSE_OP(KILL, GIVEINVENTORY_IMM, 2)
   /* 145 */ ACSE_OP(KILL, TAKEINVENTORY,     0)
   /* 146 */ ACSE_OP(KILL, TAKEINVENTORY_IMM, 2)
   /* 147 */ ACSE_OP(KILL, CHECKINVENTORY,     0)
   /* 148 */ ACSE_OP(KILL, CHECKINVENTORY_IMM, 1)
   /* 149 */ ACSE_OP(SPAWN,     SPAWN,     0)
   /* 150 */ ACSE_OP(SPAWN_IMM, SPAWN_IMM, 6)
   /* 151 */ ACSE_OP(SPAWNSPOT,     SPAWNSPOT,     0)
   /* 152 */ ACSE_OP(SPAWNSPOT_IMM, SPAWNSPOT_IMM, 4)
   /* 153 */ ACSE_OP(SETMUSIC,     SETMUSIC,     0)
   /* 154 */ ACSE_OP(SETMUSIC_IMM, SETMUSIC_IMM, 3)
   /* 155 */ ACSE_OP(SETMUSICLOCAL,     SETMUSICLOCAL,     0)
   /* 156 */ ACSE_OP(SETMUSICLOCAL_IMM, SETMUSICLOCAL_IMM, 3)
   /* 157 */ ACSE_OP(PRINTFIXED, PRINTFIXED, 0)
   /* 158 */ ACSE_OP(PRINTSTRING, PRINTLANGUAGE, 0)
   /* 159 */ ACSE_OP(KILL, STARTPRINTHUDOPTION, 0)
   /* 160 */ ACSE_OP(KILL, ENDPRINTHUDOPTION, 0)
   /* 161 */ ACSE_OP(KILL, ENDPRINTHUD, 0)
   /* 162 */ ACSE_OP(KILL, ENDPRINTHUDBOLD, 0)
   /* 163 */ ACSE_OP(KILL, OPCODE163, 0)
   /* 164 */ ACSE_OP(KILL, OPCODE164, 0)
   /* 165 */ ACSE_OP(KILL, SETFONT,     0)
   /* 166 */ ACSE_OP(KILL, SETFONT_IMM, 1)
   /* 167 */ ACSE_OP(GET_IMM, GET_IMM_BYTE, 1)
   /* 168 */ ACSE_OP(LINESPEC_IMM, LINESPEC1_IMM_BYTE, 2)
   /* 169 */ ACSE_OP(LINESPEC_IMM, LINESPEC2_IMM_BYTE, 3)
   /* 170 */ ACSE_OP(LINESPEC_IMM, LINESPEC3_IMM_BYTE, 4)
   /* 171 */ ACSE_OP(LINESPEC_IMM, LINESPEC4_IMM_BYTE, 5)
   /* 172 */ ACSE_OP(LINESPEC_IMM, LINESPEC5_IMM_BYTE, 6)
   /* 173 */ ACSE_OP(DELAY_IMM, DELAY_IMM_BYTE, 1)
   /* 174 */ ACSE_OP(RANDOM_IMM, RANDOM_IMM_BYTE, 2)
   /* 175 */ ACSE_OP(GETARR_IMM, GETARR_IMM_BYTE, -1)
   /* 176 */ ACSE_OP(GETARR_IMM, GET2_IMM_BYTE, 2)
   /* 177 */ ACSE_OP(GETARR_IMM, GET3_IMM_BYTE, 3)
   /* 178 */ ACSE_OP(GETARR_IMM, GET4_IMM_BYTE, 4)
   /* 179 */ ACSE_OP(GETARR_IMM, GET5_IMM_BYTE, 5)
   /* 180 */ ACSE_OP(SETTHINGSPECIAL, SETTHINGSPECIAL, 0)
   /* 181 */ ACSE_OP(SET_GLOBALVAR, SET_GLOBALVAR, 1)
   /* 182 */ ACSE_OP(GET_GLOBALVAR, GET_GLOBALVAR, 1)
   /* 183 */ ACSE_OP(ADD_GLOBALVAR, ADD_GLOBALVAR, 1)
   /* 184 */ ACSE_OP(SUB_GLOBALVAR, SUB_GLOBALVAR, 1)
   /* 185 */ ACSE_OP(MUL_GLOBALVAR, MUL_GLOBALVAR, 1)
   /* 186 */ ACSE_OP(DIV_GLOBALVAR, DIV_GLOBALVAR, 1)
   /* 187 */ ACSE_OP(MOD_GLOBALVAR, MOD_GLOBALVAR, 1)
   /* 188 */ ACSE_OP(INC_GLOBALVAR, INC_GLOBALVAR, 1)
   /* 189 */ ACSE_OP(DEC_GLOBALVAR, DEC_GLOBALVAR, 1)
   /* 190 */ ACSE_OP(KILL, FADETO, 0)
   /* 191 */ ACSE_OP(KILL, FADERANGE, 0)
   /* 192 */ ACSE_OP(KILL, CANCELFADE, 0)
   /* 193 */ ACSE_OP(KILL, PLAYMOVIE, 0)
   /* 194 */ ACSE_OP(KILL, SETFLOORTRIGGER, 0)
   /* 195 */ ACSE_OP(KILL, SETCEILINGTRIGGER, 0)
   /* 196 */ ACSE_OP(GET_THINGVAR, GET_THINGX, 0)
   /* 197 */ ACSE_OP(GET_THINGVAR, GET_THINGY, 0)
   /* 198 */ ACSE_OP(GET_THINGVAR, GET_THINGZ, 0)
   /* 199 */ ACSE_OP(KILL, STARTTRANSLATION, 0)
   /* 200 */ ACSE_OP(KILL, TRANSLATIONRANGE1, 0)
   /* 201 */ ACSE_OP(KILL, TRANSLATIONRANGE2, 0)
   /* 202 */ ACSE_OP(KILL, ENDTRANSLATION, 0)
   /* 203 */ ACSE_OP(KILL, CALL, 1)
   /* 204 */ ACSE_OP(KILL, CALLDISCARD, 1)
   /* 205 */ ACSE_OP(KILL, RETURNVOID, 0)
   /* 206 */ ACSE_OP(KILL, RETURN, 0)
   /* 207 */ ACSE_OP(KILL, GET_MAPARR, 1)
   /* 208 */ ACSE_OP(KILL, SET_MAPARR, 1)
   /* 209 */ ACSE_OP(KILL, ADD_MAPARR, 1)
   /* 210 */ ACSE_OP(KILL, SUB_MAPARR, 1)
   /* 211 */ ACSE_OP(KILL, MUL_MAPARR, 1)
   /* 212 */ ACSE_OP(KILL, DIV_MAPARR, 1)
   /* 213 */ ACSE_OP(KILL, MOD_MAPARR, 1)
   /* 214 */ ACSE_OP(KILL, INC_MAPARR, 1)
   /* 215 */ ACSE_OP(KILL, DEC_MAPARR, 1)
   /* 216 */ ACSE_OP(STACK_COPY, STACK_COPY, 0)
   /* 217 */ ACSE_OP(STACK_SWAP, STACK_SWAP, 0)
   /* 218 */ ACSE_OP(KILL, OPCODE218, 0)
   /* 219 */ ACSE_OP(KILL, OPCODE219, 0)
   /* 220 */ ACSE_OP(TRIG_SIN, TRIG_SIN, 0)
   /* 221 */ ACSE_OP(TRIG_COS, TRIG_COS, 0)
   /* 222 */ ACSE_OP(TRIG_VECTORANGLE, TRIG_VECTORANGLE, 0)
   /* 223 */ ACSE_OP(KILL, CHECKWEAPON, 0)
   /* 224 */ ACSE_OP(KILL, SETWEAPON, 0)
   /* 225 */ ACSE_OP(TAGSTRING, TAGSTRING, 0)
#endif//ACSE_OP

// EOF

