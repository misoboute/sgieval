#include "Component.h"

namespace sgieval
{

class MovementComponent : public Component
{
  public:
    MovementComponent(float speed) : m_speed(speed)
    {
    }

    Type GetType() const noexcept override
    {
        return Type::Health;
    }

    virtual PtrT DeepCopy() const override
    {
        return std::make_shared<MovementComponent>(m_speed);
    }

  private:
    float m_speed = 0;
};

} // namespace sgieval
