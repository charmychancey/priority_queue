#include <gtest/gtest.h>
#include <functional>

#include "pqueue.h"

TEST(PQueue, less) {
  PQueue<int> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
}

TEST(PQueue, great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
}

class MyClass {
 public:
  explicit MyClass(int n) : n_(n) {}
  bool operator < (const MyClass &mc) const { return n_ < mc.n_; }
  int n() { return n_; }
 private:
  int n_;
};

TEST(PQueue, custom_class) {
  std::vector<MyClass> vec{MyClass(42), MyClass(23), MyClass(2), MyClass(34)};

  PQueue<MyClass> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top().n(), vec[2].n());
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top().n(), vec[1].n());
}
template<typename T>
class PtrCmp {
 public:
  // stuff
  PtrCmp() {}
  const bool operator()(const T &lhs, const T &rhs) {
    return *lhs < *rhs;
  }
 private:
  // stuff
};

TEST(PQueue, custom_class_pointer) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23),
                            new MyClass(2), new MyClass(34)};

  PQueue<MyClass*, PtrCmp<MyClass*>> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);
}

TEST(PQueue, perc_up) {
  PQueue<int> pq;

  pq.Push(5);
  EXPECT_EQ(pq.Top(), 5);
  pq.Push(4);
  EXPECT_EQ(pq.Top(), 4);
  pq.Push(3);
  EXPECT_EQ(pq.Top(), 3);
  pq.Push(6);
  EXPECT_EQ(pq.Top(), 3);
  pq.Push(1);
  EXPECT_EQ(pq.Top(), 1);
  pq.Push(-1);
  EXPECT_EQ(pq.Top(), -1);
}

TEST(PQueue, perc_up_great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(5);
  EXPECT_EQ(pq.Top(), 5);
  pq.Push(6);
  EXPECT_EQ(pq.Top(), 6);
  pq.Push(8);
  EXPECT_EQ(pq.Top(), 8);
  pq.Push(10);
  EXPECT_EQ(pq.Top(), 10);
  pq.Push(2);
  EXPECT_EQ(pq.Top(), 10);
  pq.Push(-1);
  EXPECT_EQ(pq.Top(), 10);
}

TEST(PQueue, perc_Down) {
  PQueue<int> pq;

  pq.Push(5);
  pq.Push(10);
  pq.Push(4);
  pq.Push(1);
  pq.Push(2);
  pq.Push(3);
  EXPECT_EQ(pq.Top(), 1);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 10);
  pq.Pop();
}

TEST(PQueue, perc_Down_great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(5);
  pq.Push(10);
  pq.Push(4);
  pq.Push(1);
  pq.Push(2);
  pq.Push(3);
  EXPECT_EQ(pq.Top(), 10);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 1);
  pq.Pop();
}

TEST(PQueue, dif_type) {
  PQueue<char, std::greater<char>> pq;

  pq.Push('C');
  pq.Push('A');
  pq.Push('b');
  pq.Push('D');

  EXPECT_EQ(pq.Top(), 'b');
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 'D');
}

TEST(PQueue, empty_exceptions) {
  PQueue<int> pq;

  EXPECT_THROW(pq.Top(), std::underflow_error);
  EXPECT_THROW(pq.Pop(), std::underflow_error);
}

#if 0
TEST(PQueue, custom_class_pointer) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23),
                            new MyClass(2), new MyClass(34)};

  PQueue<MyClass*, /* ??? */> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);
}
#endif

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
