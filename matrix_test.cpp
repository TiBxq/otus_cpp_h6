#include <gtest/gtest.h>
#include <string>

#include "matrix.h"

TEST(matrix, matrix_test1)
{
    Matrix<int, 0> matrix;
    matrix[10][15] = 7;
    matrix[10][15] = 4;
    matrix[100500][100500] = 100500;
    matrix[100500][100500] = 100500;
    matrix[4][5] = 3;
    matrix[4][5] = 0;
    matrix[3][4] = 5;

    ASSERT_EQ(matrix.size(), 3);
    ASSERT_EQ(matrix[10][15].get(), 4);
    ASSERT_EQ(matrix[100500][100500].get(), 100500);
    ASSERT_EQ(matrix[4][5].get(), 0);
    ASSERT_EQ(matrix[3][4].get(), 5);
    ASSERT_EQ(matrix[2][3].get(), 0);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}