#pragma once

#include "Component.h"

namespace sgieval
{

class AttackComponent : public Component
{
  public:
    AttackComponent()
    {
    }

    AttackComponent(const AttackComponent &other) : m_attackPower(other.m_attackPower)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Attack;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<AttackComponent>(*this);
    }

  private:
    unsigned int m_attackPower = 0;
};

} // namespace sgieval
