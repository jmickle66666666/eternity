// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2000 James Haley
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
//--------------------------------------------------------------------------
//
// DESCRIPTION:
//      Player related stuff.
//      Bobbing POV/weapon, movement.
//      Pending weapon.
//
//-----------------------------------------------------------------------------

#include "z_zone.h"
#include "doomstat.h"
#include "d_event.h"
#include "c_net.h"
#include "g_game.h"
#include "r_main.h"
#include "p_map.h"
#include "p_spec.h"
#include "p_user.h"
#include "p_maputl.h"

// haleyjd
#include "sounds.h"
#include "s_sound.h"
#include "a_small.h"
#include "e_player.h"
#include "e_states.h"
#include "d_gi.h"

//
// Movement.
//

// 16 pixels of bob

#define MAXBOB  0x100000

boolean onground; // whether player is on ground or in air

//
// P_Thrust
// Moves the given origin along a given angle.
//

void P_Thrust(player_t* player,angle_t angle,fixed_t move)
{
  player->mo->momx += FixedMul(move,finecosine[angle >>= ANGLETOFINESHIFT]);
  player->mo->momy += FixedMul(move,finesine[angle]);
}

//
// P_Bob
// Same as P_Thrust, but only affects bobbing.
//
// killough 10/98: We apply thrust separately between the real physical player
// and the part which affects bobbing. This way, bobbing only comes from player
// motion, nothing external, avoiding many problems, e.g. bobbing should not
// occur on conveyors, unless the player walks on one, and bobbing should be
// reduced at a regular rate, even on ice (where the player coasts).
//
void P_Bob(player_t *player, angle_t angle, fixed_t move)
{
   // e6y
   if(demo_version < 203)
      return;

   player->momx += FixedMul(move,finecosine[angle >>= ANGLETOFINESHIFT]);
   player->momy += FixedMul(move,finesine[angle]);
}

//
// P_CalcHeight
//
// Calculate the walking / running height adjustment
//
void P_CalcHeight(player_t *player)
{
   int     angle;
   fixed_t bob;

   // Regular movement bobbing
   // (needs to be calculated for gun swing
   // even if not on ground)
   // OPTIMIZE: tablify angle
   // Note: a LUT allows for effects
   //  like a ramp with low health.
   
   // killough 10/98: Make bobbing depend only on player-applied motion.
   //
   // Note: don't reduce bobbing here if on ice: if you reduce bobbing here,
   // it causes bobbing jerkiness when the player moves from ice to non-ice,
   // and vice-versa.
   //
   // haleyjd: cph found out this can affect demo sync due to
   // differences it introduces in firing height etc. so it needs to be
   // optioned.
   // 04/11/10: refactored

   player->bob = 0;
   if(demo_version >= 203)
   {
      if(player_bobbing)
      {
         player->bob = (FixedMul(player->momx, player->momx) +
                        FixedMul(player->momy, player->momy)) >> 2;
      }
   }
   else
   {
      if(demo_compatibility || player_bobbing)
      {
         player->bob = (FixedMul(player->mo->momx, player->mo->momx) +
                        FixedMul(player->mo->momy, player->mo->momy)) >> 2;
      }
   }

   // haleyjd 04/11/10:
   // e6y
   if(demo_version == 202 && player->mo->friction > ORIG_FRICTION) // ice?
   {
      if(player->bob > (MAXBOB>>2))
         player->bob = MAXBOB>>2;
   }
   else
   {
      if(player->bob > MAXBOB)
         player->bob = MAXBOB;
   }

   if(!onground || player->cheats & CF_NOMOMENTUM)
   {
      player->viewz = player->mo->z + VIEWHEIGHT;
      
      if(player->viewz > player->mo->ceilingz - 4 * FRACUNIT)
         player->viewz = player->mo->ceilingz - 4 * FRACUNIT;

      // phares 2/25/98:
      // The following line was in the Id source and appears
      // to be a bug. player->viewz is checked in a similar
      // manner at a different exit below.
      
      // player->viewz = player->mo->z + player->viewheight;
      
      return;
   }

   angle = (FINEANGLES / 20 * leveltime) & FINEMASK;
   bob   = FixedMul(player->bob / 2, finesine[angle]);

   // move viewheight
   
   if(player->playerstate == PST_LIVE)
   {
      player->viewheight += player->deltaviewheight;
      
      if(player->viewheight > VIEWHEIGHT)
      {
         player->viewheight = VIEWHEIGHT;
         player->deltaviewheight = 0;
      }

      if(player->viewheight < VIEWHEIGHT / 2)
      {
         player->viewheight = VIEWHEIGHT / 2;
         if(player->deltaviewheight <= 0)
            player->deltaviewheight = 1;
      }

      if(player->deltaviewheight)
      {
         player->deltaviewheight += FRACUNIT / 4;
         if(!player->deltaviewheight)
            player->deltaviewheight = 1;
      }
   }

   player->viewz = player->mo->z + player->viewheight + bob;

   // haleyjd 08/07/04: new floorclip system
   if(player->mo->floorclip && player->playerstate != PST_DEAD && 
      player->mo->z <= player->mo->floorz)
   {
      player->viewz -= player->mo->floorclip;
   }
   
   if(player->viewz > player->mo->ceilingz - 4 * FRACUNIT)
      player->viewz = player->mo->ceilingz - 4 * FRACUNIT;
}

//
// P_MovePlayer
//
// Adds momentum if the player is not in the air
//
// killough 10/98: simplified
//
void P_MovePlayer(player_t* player)
{
   ticcmd_t *cmd = &player->cmd;
   mobj_t *mo = player->mo;
   
   mo->angle += cmd->angleturn << 16;
   
   // haleyjd: OVER_UNDER
   onground = mo->z <= mo->floorz ||
      (!comp[comp_overunder] && mo->intflags & MIF_ONMOBJ);
   
   // killough 10/98:
   //
   // We must apply thrust to the player and bobbing separately, to avoid
   // anomalies. The thrust applied to bobbing is always the same strength on
   // ice, because the player still "works just as hard" to move, while the
   // thrust applied to the movement varies with 'movefactor'.
   
   if((!demo_compatibility && demo_version < 203) || 
      (cmd->forwardmove | cmd->sidemove)) // killough 10/98
   {
      if (onground || mo->flags & MF_BOUNCES) // killough 8/9/98
      {
         int friction, movefactor = P_GetMoveFactor(mo, &friction);

         // killough 11/98:
         // On sludge, make bobbing depend on efficiency.
         // On ice, make it depend on effort.
         
         int bobfactor =
            friction < ORIG_FRICTION ? movefactor : ORIG_FRICTION_FACTOR;

         if (cmd->forwardmove)
         {
            P_Bob(player,mo->angle,cmd->forwardmove*bobfactor);
            P_Thrust(player,mo->angle,cmd->forwardmove*movefactor);
         }
         
         if (cmd->sidemove)
         {
            P_Bob(player,mo->angle-ANG90,cmd->sidemove*bobfactor);
            P_Thrust(player,mo->angle-ANG90,cmd->sidemove*movefactor);
         }
      }

      if(mo->state == states[mo->info->spawnstate])
         P_SetMobjState(mo, mo->info->seestate);
   }
}

#define ANG5 (ANG90/18)

//
// P_DeathThink
//
// Fall on your face when dying.
// Decrease POV height to floor height.
//
void P_DeathThink(player_t *player)
{
   angle_t angle;
   angle_t delta;
   
   P_MovePsprites(player);
   
   // fall to the ground
   
   if(player->viewheight > 6 * FRACUNIT)
      player->viewheight -= FRACUNIT;
   
   if(player->viewheight < 6 * FRACUNIT)
      player->viewheight = 6 * FRACUNIT;
   
   player->deltaviewheight = 0;

   // haleyjd: never bob player view when dead, and always treat player like
   //          he is on the ground
   if(demo_version >= 333)
   {
      onground = true;
      player->momx = player->momy = 0;
   }
   else
   {
      onground = player->mo->z <= player->mo->floorz ||
                    (!comp[comp_overunder] &&
                     player->mo->intflags & MIF_ONMOBJ);
   }
   
   P_CalcHeight(player);
   
   if(player->attacker && player->attacker != player->mo)
   {
      angle = P_PointToAngle(player->mo->x,
                              player->mo->y,
                              player->attacker->x,
                              player->attacker->y);

      delta = angle - player->mo->angle;
      
      if(delta < ANG5 || delta > (unsigned int)-ANG5)
      {
         // Looking at killer,
         //  so fade damage flash down.
         
         player->mo->angle = angle;
         
         if(player->damagecount)
            player->damagecount--;
      }
      else 
         if(delta < ANG180)
            player->mo->angle += ANG5;
         else
            player->mo->angle -= ANG5;
   }
   else if(player->damagecount)
      player->damagecount--;

   // haleyjd 10/05/08:
   // handle looking slightly up when the player is attached to a non-player
   // object and is dead. This was done for the decapitation deaths in Heretic
   // and Hexen.
   if(!E_IsPlayerClassThingType(player->mo->type))
   {
      if(player->mo->z <= player->mo->floorz && player->pitch > -ANGLE_1 * 15)
         player->pitch -= 2*ANGLE_1/3;
   }
      
   if(player->cmd.buttons & BT_USE)
      player->playerstate = PST_REBORN;
}

//
// P_HereticCurrent
//
// Applies Heretic current effects to the player.
//
// haleyjd 09/09/07: Rewritten to use msecnodes and eliminate the redundant 
// mobj_t::floorsec field.
//
static void P_HereticCurrent(player_t *player)
{
   msecnode_t *m;
   mobj_t     *thing = player->mo;

   // don't affect the player if noclipping is on (pushes you through walls)
   if(thing->flags & MF_NOCLIP)
      return;
   
   // determine what touched sector the player is standing on
   for(m = thing->touching_sectorlist; m; m = m->m_tnext)
   {
      if(thing->z == m->m_sector->floorheight)
         break;
   }

   if(m)
   {
      sector_t *sec = m->m_sector;

      if(sec->hticPushType >= 20 && sec->hticPushType <= 39)
         P_Thrust(player, sec->hticPushAngle, sec->hticPushForce);
   }
}

//
// P_SectorIsSpecial
//
// haleyjd 12/28/08: Determines whether or not a sector is special.
//
d_inline static boolean P_SectorIsSpecial(sector_t *sector)
{
   return (sector->special || sector->flags || sector->damage);
}

//
// P_PlayerThink
//
void P_PlayerThink(player_t *player)
{
   ticcmd_t*    cmd;
   weapontype_t newweapon;

   // killough 2/8/98, 3/21/98:
   // (this code is necessary despite questions raised elsewhere in a comment)

   if(player->cheats & CF_NOCLIP)
      player->mo->flags |= MF_NOCLIP;
   else
      player->mo->flags &= ~MF_NOCLIP;

   // chain saw run forward

   cmd = &player->cmd;
   if(player->mo->flags & MF_JUSTATTACKED)
   {
      cmd->angleturn = 0;
      cmd->forwardmove = 0xc800/512;
      cmd->sidemove = 0;
      player->mo->flags &= ~MF_JUSTATTACKED;
   }

   if(player->playerstate == PST_DEAD)
   {
      P_DeathThink(player);
      return;
   }

   // haleyjd 04/03/05: new yshear code
   if(!allowmlook)
      player->pitch = 0;
   else
   {
      int look = cmd->look;

      if(look)
      {
         // test for special centerview value
         if(look == -32768)
            player->pitch = 0;
         else
         {
            player->pitch -= look << 16;
            if(player->pitch < -ANGLE_1*32)
               player->pitch = -ANGLE_1*32;
            else if(player->pitch > ANGLE_1*32)
               player->pitch = ANGLE_1*32;
         }
      }
   }

   // haleyjd: count down jump timer
   if(player->jumptime)
      player->jumptime--;

   // Move around.
   // Reactiontime is used to prevent movement
   //  for a bit after a teleport.
   
   if(player->mo->reactiontime)
      player->mo->reactiontime--;
   else
   {
      P_MovePlayer(player);

      // Handle actions   -- joek 12/22/07
      
      if(cmd->actions & AC_JUMP)
      {
         if((player->mo->z == player->mo->floorz || 
             (player->mo->intflags & MIF_ONMOBJ)) && !player->jumptime)
         {
            player->mo->momz += 8*FRACUNIT; // PCLASS_FIXME: make jump height pclass property
            player->mo->intflags &= ~MIF_ONMOBJ;
            player->jumptime = 18;
         }
      }
   }
  
   P_CalcHeight (player); // Determines view height and bobbing
   
   // haleyjd: are we falling? might need to scream :->
   if(!comp[comp_fallingdmg] && demo_version >= 329)
   {  
      if(player->mo->momz >= 0)
         player->mo->intflags &= ~MIF_SCREAMED;

      if(player->mo->momz <= -35*FRACUNIT && 
         player->mo->momz >= -40*FRACUNIT &&
         !(player->mo->intflags & MIF_SCREAMED))
      {
         player->mo->intflags |= MIF_SCREAMED;
         S_StartSound(player->mo, GameModeInfo->playerSounds[sk_plfall]);
      }
   }

   // Determine if there's anything about the sector you're in that's
   // going to affect you, like painful floors.

   if(P_SectorIsSpecial(player->mo->subsector->sector))
      P_PlayerInSpecialSector(player);

   // haleyjd 08/23/05: terrain-based effects
   P_PlayerOnSpecialFlat(player);

   // haleyjd: Heretic current specials
   P_HereticCurrent(player);

   // Sprite Height problem...                                         // phares
   // Future code:                                                     //  |
   // It's possible that at this point the player is standing on top   //  V
   // of a Thing that could cause him some damage, like a torch or
   // burning barrel. We need a way to generalize Thing damage by
   // grabbing a bit in the Thing's options to indicate damage. Since
   // this is competing with other attributes we may want to add,
   // we'll put this off for future consideration when more is
   // known.

   // Future Code:                                                     //  ^
   // Check to see if the object you've been standing on has moved     //  |
   // out from underneath you.                                         // phares

   // haleyjd: burn damage is now implemented, but is handled elsewhere.
   
   // Check for weapon change.
   
   // A special event has no other buttons.

   if(cmd->buttons & BT_SPECIAL)
      cmd->buttons = 0;

   if(cmd->buttons & BT_CHANGE)
   {
      // The actual changing of the weapon is done
      //  when the weapon psprite can do it
      //  (read: not in the middle of an attack).
      
      newweapon = (weapontype_t)((cmd->buttons & BT_WEAPONMASK) >> BT_WEAPONSHIFT);
      
      // killough 3/22/98: For demo compatibility we must perform the fist
      // and SSG weapons switches here, rather than in G_BuildTiccmd(). For
      // other games which rely on user preferences, we must use the latter.

      // WEAPON_FIXME: bunch of crap.

      if(demo_compatibility)
      { 
         // compatibility mode -- required for old demos -- killough
         if(newweapon == wp_fist && player->weaponowned[wp_chainsaw] &&
            (player->readyweapon != wp_chainsaw ||
             !player->powers[pw_strength]))
            newweapon = wp_chainsaw;
         if(enable_ssg &&
            newweapon == wp_shotgun &&
            player->weaponowned[wp_supershotgun] &&
            player->readyweapon != wp_supershotgun)
            newweapon = wp_supershotgun;
      }

      // killough 2/8/98, 3/22/98 -- end of weapon selection changes

      // WEAPON_FIXME: shareware availability -> weapon property

      if(player->weaponowned[newweapon] && newweapon != player->readyweapon)
      {
         // Do not go to plasma or BFG in shareware, even if cheated.
         if((newweapon != wp_plasma && newweapon != wp_bfg)
            || (GameModeInfo->id != shareware) )
            player->pendingweapon = newweapon;
      }
   }

   // check for use
   
   if(cmd->buttons & BT_USE)
   {
      if(!player->usedown)
      {
         P_UseLines(player);
         player->usedown = true;
      }
   }
   else
      player->usedown = false;

   // cycle psprites

   P_MovePsprites (player);

   // Counters, time dependent power ups.

   // Strength counts up to diminish fade.

   if(player->powers[pw_strength])
      player->powers[pw_strength]++;

   // killough 1/98: Make idbeholdx toggle:

   if(player->powers[pw_invulnerability] > 0) // killough
      player->powers[pw_invulnerability]--;

   if(player->powers[pw_invisibility] > 0)
   {
      if(!--player->powers[pw_invisibility] )
         player->mo->flags &= ~MF_SHADOW;
   }

   if(player->powers[pw_infrared] > 0)        // killough
      player->powers[pw_infrared]--;

   if(player->powers[pw_ironfeet] > 0)        // killough
      player->powers[pw_ironfeet]--;

   if(player->powers[pw_ghost] > 0)        // haleyjd
   {
      if(!--player->powers[pw_ghost])
         player->mo->flags3 &= ~MF3_GHOST;
   }

   if(player->powers[pw_totalinvis] > 0) // haleyjd
   {
      player->mo->flags2 &= ~MF2_DONTDRAW; // flash   
      player->powers[pw_totalinvis]--;  
      player->mo->flags2 |=               
         player->powers[pw_totalinvis] &&
         (player->powers[pw_totalinvis] > 4*32 ||
          player->powers[pw_totalinvis] & 8)
          ? MF2_DONTDRAW : 0;
   }

   if(player->damagecount)
      player->damagecount--;

   if(player->bonuscount)
      player->bonuscount--;

   // Handling colormaps.
   // killough 3/20/98: reformat to terse C syntax

   // sf: removed MBF beta stuff

   player->fixedcolormap = 
      (player->powers[pw_invulnerability] > 4*32 ||    
       player->powers[pw_invulnerability] & 8) ? INVERSECOLORMAP :
      (player->powers[pw_infrared] > 4*32 || player->powers[pw_infrared] & 8);

   // haleyjd 01/21/07: clear earthquake flag before running quake thinkers later
   player->quake = 0;
}

#ifndef EE_NO_SMALL_SUPPORT
// Small native functions for player stuff

static cell AMX_NATIVE_CALL sm_getplayername(AMX *amx, cell *params)
{
   int err, pnum, packed;
   cell *cstr;

   pnum   = (int)params[1] - 1;
   packed = (int)params[3];

   if((err = amx_GetAddr(amx, params[2], &cstr)) != AMX_ERR_NONE)
   {
      amx_RaiseError(amx, err);
      return 0;
   }

   if(pnum < 0 || pnum >= MAXPLAYERS)
   {
      amx_RaiseError(amx, AMX_ERR_BOUNDS);
      return 0;
   }

   if(!playeringame[pnum])
      amx_SetString(cstr, "null", packed, 0);
   else
      amx_SetString(cstr, players[pnum].name, packed, 0);

   return 0;
}

AMX_NATIVE_INFO user_Natives[] =
{
   { "_GetPlayerName", sm_getplayername },
   { NULL, NULL }
};
#endif

//----------------------------------------------------------------------------
//
// $Log: p_user.c,v $
// Revision 1.14  1998/05/12  12:47:25  phares
// Removed OVER UNDER code
//
// Revision 1.13  1998/05/10  23:38:04  killough
// Add #include p_user.h to ensure consistent prototypes
//
// Revision 1.12  1998/05/05  15:35:20  phares
// Documentation and Reformatting changes
//
// Revision 1.11  1998/05/03  23:21:04  killough
// Fix #includes and remove unnecessary decls at the top, nothing else
//
// Revision 1.10  1998/03/23  15:24:50  phares
// Changed pushers to linedef control
//
// Revision 1.9  1998/03/23  03:35:24  killough
// Move weapons changes to G_BuildTiccmd, fix idclip
//
// Revision 1.8  1998/03/12  14:28:50  phares
// friction and IDCLIP changes
//
// Revision 1.7  1998/03/09  18:26:55  phares
// Fixed bug in neighboring variable friction sectors
//
// Revision 1.6  1998/02/27  08:10:08  phares
// Added optional player bobbing
//
// Revision 1.5  1998/02/24  08:46:42  phares
// Pushers, recoil, new friction, and over/under work
//
// Revision 1.4  1998/02/15  02:47:57  phares
// User-defined keys
//
// Revision 1.3  1998/02/09  03:13:20  killough
// Improve weapon control and add preferences
//
// Revision 1.2  1998/01/26  19:24:34  phares
// First rev with no ^Ms
//
// Revision 1.1.1.1  1998/01/19  14:03:01  rand
// Lee's Jan 19 sources
//
//----------------------------------------------------------------------------
