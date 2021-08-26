#include "Component.h"

namespace sgieval
{

class AttackComponent : public Component
{
  public:
    AttackComponent(unsigned int attackPower) : m_attackPower(attackPower)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Attack;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<AttackComponent>(m_attackPower);
    }

  private:
    unsigned int m_attackPower = 0;
};

} // namespace sgieval
