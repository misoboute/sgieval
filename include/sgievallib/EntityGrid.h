#pragma once

#include <vector>

#include "Entity.h"
#include "UnsortedUIntPairSet.h"

namespace sgieval
{

class EntityGrid
{

  public:
    using EntityCollectionT = std::vector<Entity::PtrT>;
    EntityGrid(size_t entitiesCount, CoordT minX, CoordT maxX, CoordT minY, CoordT maxY);

    void ImportEntites(const EntityCollectionT &entities);
    unsigned int CountIntersections() const;

  private:
    static size_t CalcOptimalGridRows(size_t entitiesCount, CoordT minX, CoordT maxX, CoordT minY, CoordT maxY);
    static size_t CalcOptimalGridColumns(size_t entitiesCount, size_t rowsCount);

    inline size_t XCoordToCol(CoordT x) const noexcept;
    inline size_t YCoordToRow(CoordT y) const noexcept;
    inline const EntityCollectionT &GetCell(size_t row, size_t col) const;
    inline EntityCollectionT &GetCell(size_t row, size_t col);

    void FindIntersectionsInEntities(UnsortedUIntPairSet &intersections, const EntityCollectionT &entities) const;
    void FindEntityIntersectionsWithEntities(UnsortedUIntPairSet &intersections, const Entity &ent,
                                             const EntityCollectionT &entities) const;

    const CoordT MinX, MaxX, MinY, MaxY;
    const size_t Rows;
    const size_t Cols;

    std::vector<EntityCollectionT> m_grid;
};

} // namespace sgieval
