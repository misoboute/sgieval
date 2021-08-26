#include <gtest/gtest.h>

#include "Rectangle2D.h"

using testing::Test;

struct Rectangle2DFixture : public Test
{
    using RectT = sgieval::Rectangle2D<float>;

    Rectangle2DFixture()
    {
    }

    ~Rectangle2DFixture()
    {
    }
};

TEST_F(Rectangle2DFixture, NoIntersection)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(-10, -10, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, OnlyIntersectInX)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(11, -10, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, OnlyIntersectInXWithEqualX)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(10, -10, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, OnlyIntersectInY)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(-10, 9, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, OnlyIntersectInXWithEqualY)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(-10, 10, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, HorizontallyAdjacent)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(13, 10, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, VerticallyAdjacent)
{
    RectT r1(10, 10, 2, 1);
    RectT r2(10, 12, 4, 3);

    EXPECT_FALSE(r1.IntersectsWith(r2));
    EXPECT_FALSE(r2.IntersectsWith(r1));
}

TEST_F(Rectangle2DFixture, Intersect)
{
    RectT r1(-0.75, -0.4, 2, 1);
    RectT r2(2, 1.5, 4, 3);

    EXPECT_TRUE(r1.IntersectsWith(r2));
    EXPECT_TRUE(r2.IntersectsWith(r1));
}
