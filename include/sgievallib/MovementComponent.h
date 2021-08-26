#pragma once

#include "Component.h"

namespace sgieval
{

class MovementComponent : public Component
{
  public:
    MovementComponent()
    {
    }

    MovementComponent(const MovementComponent &other) : m_speed(other.m_speed)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Health;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<MovementComponent>(*this);
    }

  private:
    float m_speed = 0;
};

} // namespace sgieval
