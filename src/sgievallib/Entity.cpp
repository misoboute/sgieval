#include "Entity.h"

using namespace sgieval;

Entity::Entity(const RectT &boundingBox) : m_boundingBox(boundingBox)
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
