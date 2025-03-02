#include <gtest/gtest.h>
#include "Real_Pair.h"

// g++ test_real_pair.cpp Real_Pair.cpp -o test_real_pair -I C:/googletest/include -L C:/googletest/lib -lgtest -lgtest_main -pthread -lucrt -lmingwex
// g++ test_real_pair.cpp Real_Pair.cpp -o test_real_pair -lgtest -lgtest_main -pthread -lucrt -lmingwex


// ✅ 덧셈 연산 테스트
TEST(RealPairTest, Addition) {
    Real_Pair p1(2.0, 3.0);
    Real_Pair p2(4.0, 1.0);
    Real_Pair result = p1 + p2;
    
    EXPECT_DOUBLE_EQ(result.x, 6.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
}

// ✅ 뺄셈 연산 테스트
TEST(RealPairTest, Subtraction) {
    Real_Pair p1(5.0, 7.0);
    Real_Pair p2(2.0, 3.0);
    Real_Pair result = p1 - p2;
    
    EXPECT_DOUBLE_EQ(result.x, 3.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
}

// ✅ 거리 계산 테스트
TEST(RealPairTest, Distance) {
    Real_Pair p1(0.0, 0.0);
    Real_Pair p2(3.0, 4.0);

    EXPECT_DOUBLE_EQ(distance(p1, p2), 5.0); // 피타고라스 정리 (3-4-5 삼각형)
}

// ✅ 기본 생성자 테스트
TEST(RealPairTest, DefaultConstructor) {
    Real_Pair p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

// ✅ 복사 생성자 테스트
TEST(RealPairTest, CopyConstructor) {
    Real_Pair p1(10.0, 15.0);
    Real_Pair p2 = p1;
    EXPECT_DOUBLE_EQ(p2.x, 10.0);
    EXPECT_DOUBLE_EQ(p2.y, 15.0);
}

// Google Test 실행을 위한 main 함수
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
