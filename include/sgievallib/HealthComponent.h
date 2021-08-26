#pragma once

#include "Component.h"

namespace sgieval
{

class HealthComponent : public Component
{
  public:
    HealthComponent()
    {
    }

    HealthComponent(const HealthComponent &other) : m_health(other.m_health)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Health;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<HealthComponent>(*this);
    }

  private:
    int m_health = 0;
};

} // namespace sgieval
