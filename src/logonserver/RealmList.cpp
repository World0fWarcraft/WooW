/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file
    \ingroup realmd
*/

#include "Common.h"
#include "RealmList.h"
#include "../shared/Singleton.h"
#include "Database/DatabaseEnv.h"

//INSTANTIATE_SINGLETON_1( RealmList );

extern Database* Database_Realm;

RealmList::RealmList( ) : m_UpdateInterval(0), m_NextUpdateTime(time(NULL))
{
}

RealmList& sRealmList
{
    static RealmList realmlist;
    return realmlist;
}

/// Load the realm list from the database
void RealmList::Initialize(uint32 updateInterval)
{
    m_UpdateInterval = updateInterval;

    ///- Get the content of the realmlist table in the database
    UpdateRealms(true);
}

void RealmList::UpdateRealm( uint32 ID, const std::string& name, const std::string& address, uint32 port, uint8 icon, uint8 color, uint8 timezone, float popu)//, uint16 build)
{
    ///- Create new if not exist or update existed
    Realm& realm = m_realms[name];

    realm.Id      = ID;
    realm.Icon      = icon;
    realm.flags     = color;
    realm.TimeZone  = timezone;
    realm.Population        = popu;
//    realm.GameBuild        = build;

    ///- Append port to IP address.
    std::ostringstream ss;
    ss << address << ":" << port;
    realm.Address   = ss.str();
}

void RealmList::UpdateIfNeed()
{
    // maybe disabled or updated recently
    if(!m_UpdateInterval || m_NextUpdateTime > time(NULL))
        return;

    m_NextUpdateTime = time(NULL) + m_UpdateInterval;

    // Clears Realm list
    m_realms.clear();

    // Get the content of the realmlist table in the database
    UpdateRealms(false);
}

void RealmList::UpdateRealms(bool init)
{
    sLog.outDetail("Updating Realm List...");
	////                                            0    1       2      3     4    5 flgs      6         7           8
//	QueryResult *result = Database_Realm->Query( "SELECT id, name, address, port, icon, color, timezone, population, realmbuilds FROM realmlist WHERE color <> 3 " );
	QueryResult *result = Database_Realm->Query( "SELECT id, name, address, port, icon, color, timezone, population, realmbuilds FROM realmlist " );

    ///- Circle through results and add them to the realm map
    if(result)
    {
        do
        {
            Field *fields = result->Fetch();

            UpdateRealm(fields[0].GetUInt32(), fields[1].GetString(),fields[2].GetString(),fields[3].GetUInt32(),fields[4].GetUInt8(), fields[5].GetUInt8(), fields[6].GetUInt8(), fields[7].GetFloat());// , fields[8].GetUInt32());
 
            if(init)
                sLog.outString("Added realm \"%s\".", fields[1].GetString());
        } while( result->NextRow() );
        delete result;
    }
}
