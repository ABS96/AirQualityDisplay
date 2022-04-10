#include <color.h>
#include <unity.h>

void test_color()
{
  TEST_ASSERT_TRUE(getColorForAqi(0) == green);
  TEST_ASSERT_TRUE(getColorForAqi(33) == green);
  TEST_ASSERT_TRUE(getColorForAqi(50) == green);
  TEST_ASSERT_TRUE(getColorForAqi(51) == yellow);
  TEST_ASSERT_TRUE(getColorForAqi(60) == yellow);
  TEST_ASSERT_TRUE(getColorForAqi(100) == yellow);
  TEST_ASSERT_TRUE(getColorForAqi(101) == orange);
  TEST_ASSERT_TRUE(getColorForAqi(116) == orange);
  TEST_ASSERT_TRUE(getColorForAqi(150) == orange);
  TEST_ASSERT_TRUE(getColorForAqi(151) == red);
  TEST_ASSERT_TRUE(getColorForAqi(170) == red);
  TEST_ASSERT_TRUE(getColorForAqi(200) == red);
  TEST_ASSERT_TRUE(getColorForAqi(201) == purple);
  TEST_ASSERT_TRUE(getColorForAqi(283) == purple);
  TEST_ASSERT_TRUE(getColorForAqi(300) == purple);
  TEST_ASSERT_TRUE(getColorForAqi(301) == blue);
  TEST_ASSERT_TRUE(getColorForAqi(999) == blue);
}

void process()
{
  UNITY_BEGIN();
  RUN_TEST(test_color);
  UNITY_END();
}

int main(int argc, char **argv)
{
  process();
  return 0;
}