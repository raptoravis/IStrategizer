#include "StarCraftMap.h"
#include <string>

#include "BWAPI.h"
#include "MapArea.h"
#include "GamePlayer.h"
#include "DefinitionCrossMapping.h"
#include "StarCraftEntity.h"
#include "RtsGame.h"

using namespace IStrategizer;
using namespace BWAPI;
using namespace std;

StarCraftMap::StarCraftMap(RtsGame* pGame, unsigned cellSize, unsigned worldWidth, unsigned worldHeight) :
    WorldMap(pGame, cellSize, worldWidth, worldHeight)
{ }
//----------------------------------------------------------------------------------------------
MapArea StarCraftMap::GetSpecialBuildingPosition(EntityClassType p_buildingType) const
{
    if (!m_isOnline)
        DEBUG_THROW(InvalidOperationException(XcptHere));

    MapArea candidatePosition = MapArea::Null();

    // Get the player base tile position
    MapArea colony = g_Game->Self()->GetColonyMapArea();
    Vector2 colonyTile = colony.Pos();

    // Get the unit type object
    UnitType type;
    TID unitTypeId;
    string typeName;
    unitTypeId = g_Database.EntityMapping.GetBySecond(p_buildingType);
    typeName = g_Database.EntityIdentMapping.GetByFirst(unitTypeId);
    type = BWAPI::UnitType::getType(typeName);

    if (type.isRefinery())
    {
        int bestDistance = INT_MAX;
        Unitset geysers = Broodwar->getGeysers();
        Unit currentGeyser;

        for (unsigned i = 0; i < geysers.size(); ++i)
        {
            currentGeyser = geysers[i];
            Vector2 currentPosition = Vector2(
                UnitPositionFromTilePosition(currentGeyser->getTilePosition().x),
                UnitPositionFromTilePosition(currentGeyser->getTilePosition().y));
            int currentDistance = colonyTile.Distance(currentPosition);

            if (currentDistance <= bestDistance)
            {
                bestDistance = currentDistance;
                candidatePosition = MapArea(
                    currentPosition,
                    type.tileWidth(),
                    type.tileHeight());
            }
        }
        _ASSERTE(CanBuildHere(candidatePosition.Pos(), p_buildingType));
    }

    return candidatePosition;
}
//----------------------------------------------------------------------------------------------
bool StarCraftMap::CanBuildHere(Vector2 p_worldPosition, EntityClassType p_buildingType) const
{
    if (!m_isOnline)
        DEBUG_THROW(InvalidOperationException(XcptHere));

    UnitType type;
    TID unitTypeId;
    string typeName;

    unitTypeId = g_Database.EntityMapping.GetBySecond(p_buildingType);
    typeName = g_Database.EntityIdentMapping.GetByFirst(unitTypeId);
    type = BWAPI::UnitType::getType(typeName);

    if (type.isAddon())
    {
        type = type.whatBuilds().first;
    }
    
    return Broodwar->canBuildHere(TilePosition(TilePositionFromUnitPosition(p_worldPosition.X), TilePositionFromUnitPosition(p_worldPosition.Y)), type);
}