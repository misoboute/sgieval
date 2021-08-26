#include <gtest/gtest.h>

using testing::Test;

struct Rectangle2DFixture : public Test
{
    Rectangle2DFixture()
    {
    }

    ~Rectangle2DFixture()
    {
    }
};

TEST_F(Rectangle2DFixture, T1)
{
    GTEST_SUCCEED();
}
