#pragma once

namespace sgieval
{

template <typename T> class Rectangle2D
{
  public:
    using CoordT = T;

    Rectangle2D(CoordT x, CoordT y, CoordT width, CoordT height)
        : m_x(x), m_y(y), m_halfWidth(width / 2), m_halfHeight(height / 2)
    {
    }

    CoordT GetX() const noexcept
    {
        return m_x;
    }

    CoordT GetY() const noexcept
    {
        return m_y;
    }

    CoordT GetHalfWidth() const noexcept
    {
        return m_halfWidth;
    }

    CoordT GetHalfHeight() const noexcept
    {
        return m_halfHeight;
    }

    CoordT GetWidth() const noexcept
    {
        return m_halfWidth * 2;
    }

    CoordT GetHeight() const noexcept
    {
        return m_halfHeight * 2;
    }

    bool IntersectsWith(const Rectangle2D &other) const noexcept;

  private:
    bool DoIntersectAlongOneCoordinate(CoordT coord1, CoordT halfLength1, CoordT coord2,
                                       CoordT halfLength2) const noexcept;

    CoordT m_x;
    CoordT m_y;
    CoordT m_halfWidth;
    CoordT m_halfHeight;
};

template <typename T>
bool Rectangle2D<T>::DoIntersectAlongOneCoordinate(CoordT coord1, CoordT halfLength1, CoordT coord2,
                                                   CoordT halfLength2) const noexcept
{
    if (coord1 < coord2)
    {
        return coord2 < coord1 + halfLength1 + halfLength2;
    }
    else if (coord1 > coord2)
    {
        return coord1 < coord2 + halfLength1 + halfLength2;
    }
    else
    {
        return true;
    }
}

template <typename T> bool Rectangle2D<T>::IntersectsWith(const Rectangle2D<T> &other) const noexcept
{
    auto horizontal = DoIntersectAlongOneCoordinate(m_x, m_halfWidth, other.m_x, other.m_halfWidth);
    auto vertical = DoIntersectAlongOneCoordinate(m_y, m_halfHeight, other.m_y, other.m_halfHeight);
    return horizontal && vertical;
}

} // namespace sgieval
