#pragma once
#include  "g_test_matrix.h"
TEST(Matrix_Test, operator_set){
	Matrix_Test<int, -1> matrix;

	matrix[1][1] = -1;
	ASSERT_EQ(matrix[1][1], -1);
	ASSERT_EQ(matrix.size(), 0);
 
	matrix[100][100] = 314;
	ASSERT_EQ(matrix[100][100], 314);
	ASSERT_EQ(matrix.size(), 1);
}

TEST(Matrix_Test, set_main_diagonal){

	Matrix_Test<int, 0> matrix;

	for(int i = 0; i < 10; ++i){
		matrix[i][i] = i;
	}
 
  ASSERT_EQ(matrix[1][1], 1);
  ASSERT_EQ(matrix[2][2], 2);
  ASSERT_EQ(matrix[3][3], 3);
  ASSERT_EQ(matrix[4][4], 4);
  ASSERT_EQ(matrix[5][5], 5);
  ASSERT_EQ(matrix[6][6], 6);
  ASSERT_EQ(matrix[7][7], 7);
  ASSERT_EQ(matrix[8][8], 8);
  ASSERT_EQ(matrix[9][9], 9);

  ASSERT_EQ(matrix.size(), 9);  
}

TEST(Matrix_Test, set_second_diagonal){

	Matrix_Test<int, 0> matrix;

	for(int i = 0; i < 10; ++i){
		matrix[i][9 - i] = 9 - i;
	}
  
  ASSERT_EQ(matrix[0][9], 9);
  ASSERT_EQ(matrix[1][8], 8);
  ASSERT_EQ(matrix[2][7], 7);
  ASSERT_EQ(matrix[3][6], 6);
  ASSERT_EQ(matrix[4][5], 5);
  ASSERT_EQ(matrix[5][4], 4);
  ASSERT_EQ(matrix[6][3], 3);
  ASSERT_EQ(matrix[7][2], 2);
  ASSERT_EQ(matrix[8][1], 1);

  ASSERT_EQ(matrix.size(), 9);
}

TEST(Matrix_Test, set_main_second_diagonal){

	Matrix_Test<int, 0> matrix;

	for(int i = 0; i < 10; ++i){
		matrix[i][i] = i;
	}

	for(int i = 0; i < 10; ++i){
		matrix[i][9 - i] = 9 - i;
	}
   
  ASSERT_EQ(matrix.size(), 18);
}
