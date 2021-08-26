#pragma once

#include <iostream>
#include <vector>

#include "../sgievallib/Entity.h"

namespace sgieval
{

class DebugEntityGrid
{
  public:
    using PairT = std::pair<Entity::TimestampT, Entity::TimestampT>;

    static PairT MakeSortedPair(Entity::TimestampT t1, Entity::TimestampT t2)
    {
        return t1 > t2 ? std::make_pair(t2, t1) : std::make_pair(t1, t2);
    }

    void ImportEntities(const std::vector<Entity::PtrT> &entities)
    {
        for (const auto &e : entities)
        {
            m_timestampToEntitiesMap[e->GetTimestamp()] = e;
        }
    }

    void AddEntityPair(const Entity &e1, const Entity &e2)
    {
        m_entityPairs.insert(MakeSortedPair(e1.GetTimestamp(), e2.GetTimestamp()));
    }

    void RemoveEntityPair(const Entity &e1, const Entity &e2)
    {
        m_entityPairs.erase(m_entityPairs.find(MakeSortedPair(e1.GetTimestamp(), e2.GetTimestamp())));
    }

    void DumpPairs(std::ostream &os)
    {
        os << "Remaining pairs: " << m_entityPairs.size() << std::endl;
        for (const auto &p : m_entityPairs)
        {
            const auto b1 = m_timestampToEntitiesMap[p.first]->GetBoundingBox();
            const auto b2 = m_timestampToEntitiesMap[p.second]->GetBoundingBox();
            os << "Ent #" << p.first << " / Ent #" << p.second << ": " << b1 << " / " << b2 << std::endl;
        }
    }

    static DebugEntityGrid ms_instance;

  private:
    std::set<PairT> m_entityPairs;
    std::unordered_map<Entity::TimestampT, Entity::PtrT> m_timestampToEntitiesMap;
};

} // namespace sgieval