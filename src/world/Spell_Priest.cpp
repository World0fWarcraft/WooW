/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

class DispersionSpell : public Spell
{
		SPELL_FACTORY_FUNCTION(DispersionSpell);

		void DoAfterHandleEffect(Unit* target, uint32 i)
		{
			if( p_caster != NULL )
			{
				// Mana regeneration
				p_caster->CastSpell(target, 60069, true);
				// Remove snares and movement impairing effects and make player immune to them
				p_caster->CastSpell(target, 63230, true);
			}
		}
};

void SpellFactoryMgr::SetupPriest()
{
	AddSpellById(47585, &DispersionSpell::Create);
}
