#include <memory>
#include <unordered_map>

#include "Component.h"
#include "Rectangle2D.h"
#include "SgiTypes.h"

namespace sgieval
{

class Entity
{
    using PtrT = std::shared_ptr<Entity>;
    using CPtrT = std::shared_ptr<const Entity>;
    using RectT = Rectangle2D<CoordT>;
    using ComponentMap = std::unordered_map<Component::Type, Component::PtrT>;

  public:
    Entity(const RectT &boundingBox);

    PtrT DeepCopy() const;

    const RectT &GetBoundingBox() const noexcept;
    void SetBoundingBox(const RectT &box);

    void AddComponent(Component::PtrT comp);
    const ComponentMap &GetAllComponents();
    Component::PtrT GetComponent(Component::Type type);
    Component::CPtrT GetComponent(Component::Type type) const;

  private:
    RectT m_boundingBox;
    ComponentMap m_components;
};

} // namespace sgieval
