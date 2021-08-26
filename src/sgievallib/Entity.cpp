#include "Entity.h"

using namespace sgieval;

Entity::TimestampT Entity::m_lastTimestamp = 0;

Entity::TimestampT Entity::GenerateTimeStamp()
{
    return ++m_lastTimestamp;
}

Entity::Entity(const RectT &boundingBox) : Timestamp(GenerateTimeStamp()), m_boundingBox(boundingBox)
{
}

Entity::PtrT Entity::DeepCopy() const
{
    auto copy = std::make_shared<Entity>(m_boundingBox);
    for (const auto &comp : m_components)
    {
        copy->AddComponent(comp.second->DeepCopy());
    }
    return copy;
}

Entity::TimestampT Entity::GetTimestamp() const noexcept
{
    return Timestamp;
}

bool Entity::IntersectsWith(const Entity &other) const noexcept
{
    return m_boundingBox.IntersectsWith(other.m_boundingBox);
}

const Entity::RectT &Entity::GetBoundingBox() const noexcept
{
    return m_boundingBox;
}

void Entity::SetBoundingBox(const RectT &box)
{
    m_boundingBox = box;
}

void Entity::AddComponent(Component::PtrT comp)
{
    m_components[comp->GetType()] = comp;
}

Component::PtrT Entity::GetComponent(Component::Type type)
{
    return m_components.at(type);
}

Component::CPtrT Entity::GetComponent(Component::Type type) const
{
    return m_components.at(type);
}

const Entity::ComponentMap &Entity::GetAllComponents()
{
    return m_components;
}
