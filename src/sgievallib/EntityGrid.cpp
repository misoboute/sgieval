#include "EntityGrid.h"

#include <cmath>

using namespace sgieval;

EntityGrid::EntityGrid(size_t entitiesCount, CoordT minX, CoordT maxX, CoordT minY, CoordT maxY)
    : MinX(minX), MaxX(maxX), MinY(minY), MaxY(maxY), Rows(CalcOptimalGridRows(entitiesCount, minX, maxX, minY, maxY)),
      Cols(CalcOptimalGridColumns(entitiesCount, Rows))
{
    m_grid.resize(Rows * Cols);
}

size_t EntityGrid::CalcOptimalGridRows(size_t entitiesCount, CoordT minX, CoordT maxX, CoordT minY, CoordT maxY)
{
    const auto worldWidthToHeightRatio = (maxX - minX) / (maxY - minY);
    return static_cast<size_t>(std::ceil(std::sqrt(entitiesCount / worldWidthToHeightRatio)));
}

size_t EntityGrid::CalcOptimalGridColumns(size_t entitiesCount, size_t rowsCount)
{
    return entitiesCount / rowsCount;
}

size_t EntityGrid::XCoordToCol(CoordT x) const noexcept
{
    return static_cast<size_t>((x - MinX) / (MaxX - MinX) * Cols);
}

size_t EntityGrid::YCoordToRow(CoordT y) const noexcept
{
    return static_cast<size_t>((y - MinY) / (MaxY - MinY) * Rows);
}

const EntityGrid::EntityCollectionT &EntityGrid::GetCell(size_t row, size_t col) const
{
    return m_grid[row * Cols + col];
}

EntityGrid::EntityCollectionT &EntityGrid::GetCell(size_t row, size_t col)
{
    return m_grid[row * Cols + col];
}

void EntityGrid::ImportEntites(const EntityCollectionT &entities)
{
    for (const auto &e : entities)
    {
        const auto bb = e->GetBoundingBox();
        const auto colBegin = XCoordToCol(bb.GetLeft());
        const auto colEnd = XCoordToCol(bb.GetRight());
        const auto rowBegin = YCoordToRow(bb.GetBottom());
        const auto rowEnd = YCoordToRow(bb.GetTop());
        for (size_t c = colBegin; c <= colEnd; ++c)
        {
            for (size_t r = rowBegin; r <= rowEnd; ++r)
            {
                GetCell(r, c).push_back(e);
            }
        }
        // auto ts = e->GetTimestamp();
        // if (ts == 6 || ts == 1772)
        // {
        //     std::cout << "ts: " << ts << ", row: " << row << ", col: " << col << std::endl;
        // }
    }
}

unsigned int EntityGrid::CountIntersections() const
{
    UnsortedUIntPairSet intersections;
    for (size_t row = 0; row < Rows; ++row)
    {
        for (size_t col = 0; col < Cols; col++)
        {
            const auto &currentCell = GetCell(row, col);
            FindIntersectionsInEntities(intersections, currentCell);
            auto hasNextRow = row < Rows - 1;
            auto hasNextColumn = col < Cols - 1;
            auto hasPrevColumn = col > 0;
            for (const auto ent : currentCell)
            {
                if (hasNextRow)
                {
                    FindEntityIntersectionsWithEntities(intersections, *ent, GetCell(row + 1, col));
                }
                if (hasNextColumn)
                {
                    FindEntityIntersectionsWithEntities(intersections, *ent, GetCell(row, col + 1));
                }
                if (hasNextRow && hasNextColumn)
                {
                    FindEntityIntersectionsWithEntities(intersections, *ent, GetCell(row + 1, col + 1));
                }
                if (hasNextRow && hasPrevColumn)
                {
                    FindEntityIntersectionsWithEntities(intersections, *ent, GetCell(row + 1, col - 1));
                }
            }
        }
    }
    return intersections.Count();
}

void EntityGrid::FindIntersectionsInEntities(UnsortedUIntPairSet &intersections,
                                             const EntityCollectionT &entities) const
{
    auto intersectionCount = 0;
    const auto entitiesSize = entities.size();
    for (auto i = 0; i < entitiesSize; ++i)
    {
        for (auto j = i + 1; j < entitiesSize; ++j)
        {
            const auto ts1 = entities[i]->GetTimestamp();
            const auto ts2 = entities[j]->GetTimestamp();
            if (ts1 != ts2 && !intersections.HasPair(ts1, ts2) && entities[i]->IntersectsWith(*entities[j]))
            {
                intersections.AddPair(ts1, ts2);
            }
        }
    }
}

void EntityGrid::FindEntityIntersectionsWithEntities(UnsortedUIntPairSet &intersections, const Entity &ent,
                                                     const EntityCollectionT &entities) const
{
    for (const auto &otherEnt : entities)
    {
        const auto ts1 = ent.GetTimestamp();
        const auto ts2 = otherEnt->GetTimestamp();
        if (ts1 != ts2 && !intersections.HasPair(ts1, ts2) && ent.IntersectsWith(*otherEnt))
        {
            intersections.AddPair(ts1, ts2);
        }
    }
}
