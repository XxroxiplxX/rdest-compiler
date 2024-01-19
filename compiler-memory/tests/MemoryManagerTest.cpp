#include "MemoryManager.h"
#include <gtest/gtest.h>
#include <vector>

namespace ut {
using namespace memory;
class MemoryManagerTest : public ::testing::Test {
public:
  MemoryManager uut;
  std::vector<std::string> values = {"5", "12", "varaible", "main", "x"};
};
TEST_F(MemoryManagerTest, BasicMemoryManagerUtils) {
  uut.assert_const(values[0]);
  uut.assert_argument(values[2], values[3]);
  uut.assert_var(values[4], values[3]);
  EXPECT_EQ(uut.get_constant(values[0])->get_id(), 10);
}
} // namespace ut
