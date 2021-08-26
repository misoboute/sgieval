#include "Component.h"

namespace sgieval
{

class HealthComponent : public Component
{
  public:
    HealthComponent(int health) : m_health(health)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Health;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<HealthComponent>(m_health);
    }

  private:
    int m_health = 0;
};

} // namespace sgieval
