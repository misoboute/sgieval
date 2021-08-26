#include <memory>

namespace sgieval
{

class Component
{
  public:
    using PtrT = std::shared_ptr<Component>;
    using CPtrT = std::shared_ptr<const Component>;

    enum class Type
    {
        Health,
        Attack,
        Movement
    };

    virtual ~Component() = default;

    virtual PtrT DeepCopy() const = 0;
    virtual Type GetType() const noexcept = 0;
};

} // namespace sgieval
