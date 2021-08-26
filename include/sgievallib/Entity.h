#pragma once

#include <memory>
#include <set>
#include <unordered_map>

#include "Component.h"
#include "Rectangle2D.h"
#include "SgiTypes.h"

namespace sgieval
{

class Entity
{
  public:
    using PtrT = std::shared_ptr<Entity>;
    using CPtrT = std::shared_ptr<const Entity>;
    using RectT = Rectangle2D<CoordT>;
    using ComponentMap = std::unordered_map<Component::Type, Component::PtrT>;
    using TimestampT = std::uintmax_t;

    Entity(const RectT &boundingBox);

    PtrT DeepCopy() const;

    TimestampT GetTimestamp() const noexcept;

    bool IntersectsWith(const Entity &other) const noexcept;
    const RectT &GetBoundingBox() const noexcept;
    void SetBoundingBox(const RectT &box);

    void AddComponent(Component::PtrT comp);
    const ComponentMap &GetAllComponents();
    Component::PtrT GetComponent(Component::Type type);
    Component::CPtrT GetComponent(Component::Type type) const;

  private:
    static TimestampT GenerateTimeStamp();

    static TimestampT m_lastTimestamp;

    const TimestampT Timestamp;
    RectT m_boundingBox;
    ComponentMap m_components;
};

} // namespace sgieval
