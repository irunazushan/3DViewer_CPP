#include "viever_test.h"

TEST(VIEVER, viever_test_1) {
  Controller m_controller;
  m_controller.setFilename_c("./Object_files/cube_first.obj");
  std::vector<double> vec1 = m_controller.getVertexes_c();
  ASSERT_EQ(vec1[0], 0.5);
  ASSERT_EQ(vec1[1], 0.5);
  ASSERT_EQ(vec1[2], -0.5);
  ASSERT_EQ(vec1[3], 0.5);
  ASSERT_EQ(vec1[4], -0.5);
  ASSERT_EQ(vec1[5], -0.5);
  ASSERT_EQ(vec1[6], 0.5);
  ASSERT_EQ(vec1[7], 0.5);
  ASSERT_EQ(vec1[8], 0.5);
  ASSERT_EQ(vec1.size(), 24);
  std::vector<facets> vec2 = m_controller.getPolygon_c();
  ASSERT_EQ(vec2.size(), 12);
  ASSERT_EQ(m_controller.getFacetsCount(), 36);
}

TEST(VIEVER, Viever_test_2) {
  Controller m_controller;
  std::string str1 = "ERROR: Too few vertexes!";

  try {
    m_controller.setFilename_c("./Object_files/wrong.obj");
  } catch (std::string error_message) {
    ASSERT_EQ(str1, error_message);
  }

  std::string str2 = "ERROR: Too few vertexes in the polygon!";
  try {
    m_controller.setFilename_c("./Object_files/wrong2.obj");
  } catch (std::string error_message) {
    ASSERT_EQ(str2, error_message);
  }

  std::string str3 = "ERROR: The wrong vertex data!";
  try {
    m_controller.setFilename_c("./Object_files/wrong3.obj");
  } catch (std::string error_message) {
    ASSERT_EQ(str3, error_message);
  }

  std::string str4 = "ERROR: Too few facets!";
  try {
    m_controller.setFilename_c("./Object_files/wrong4.obj");
  } catch (std::string error_message) {
    ASSERT_EQ(str4, error_message);
  }

  std::string str5 = "ERROR: The file doesn't exist!";
  try {
    m_controller.setFilename_c("./Object_files/wrong5.obj");
  } catch (std::string error_message) {
    ASSERT_EQ(str5, error_message);
  }

  std::string str6 = "ERROR: The file has a wrong format";
  try {
    m_controller.setFilename_c("./Makefile");
  } catch (std::string error_message) {
    ASSERT_EQ(str6, error_message);
  }
}

TEST(VIEVER, Viever_test_3) {
  Controller m_controller;
  m_controller.setFilename_c("./Object_files/cube_first.obj");
  std::vector<double> vec1 = m_controller.getVertexes_c();
  ASSERT_EQ(vec1[0], 0.5);
  ASSERT_EQ(vec1[1], 0.5);
  ASSERT_EQ(vec1[2], -0.5);
  ASSERT_EQ(vec1[3], 0.5);
  ASSERT_EQ(vec1[4], -0.5);
  ASSERT_EQ(vec1[5], -0.5);
  ASSERT_EQ(vec1[6], 0.5);
  ASSERT_EQ(vec1[7], 0.5);
  ASSERT_EQ(vec1[8], 0.5);
  ASSERT_EQ(vec1.size(), 24);

  m_controller.moveFigure_c(0.5, 0.5, 0.5);
  vec1 = m_controller.getVertexes_c();
  ASSERT_EQ(vec1[0], 1);
  ASSERT_EQ(vec1[1], 1);
  ASSERT_EQ(vec1[2], 0);
  ASSERT_EQ(vec1[3], 1);
  ASSERT_EQ(vec1[4], 0);
  ASSERT_EQ(vec1[5], 0);
  ASSERT_EQ(vec1[6], 1);
  ASSERT_EQ(vec1[7], 1);
  ASSERT_EQ(vec1[8], 1);
  ASSERT_EQ(vec1.size(), 24);

  m_controller.changeFigure_c(2);
  vec1 = m_controller.getVertexes_c();
  ASSERT_EQ(vec1[0], 2);
  ASSERT_EQ(vec1[1], 2);
  ASSERT_EQ(vec1[2], 0);
  ASSERT_EQ(vec1[3], 2);
  ASSERT_EQ(vec1[4], 0);
  ASSERT_EQ(vec1[5], 0);
  ASSERT_EQ(vec1[6], 2);
  ASSERT_EQ(vec1[7], 2);
  ASSERT_EQ(vec1[8], 2);
  ASSERT_EQ(vec1.size(), 24);

  m_controller.rotateFigure_c(360, 360, 360);
  vec1 = m_controller.getVertexes_c();
  ASSERT_NEAR(vec1[0], 2, 1E-06);
  ASSERT_NEAR(vec1[1], 2, 1E-06);
  ASSERT_NEAR(vec1[2], 0, 1E-06);
  ASSERT_NEAR(vec1[3], 2, 1E-06);
  ASSERT_NEAR(vec1[4], 0, 1E-06);
  ASSERT_NEAR(vec1[5], 0, 1E-06);
  ASSERT_NEAR(vec1[6], 2, 1E-06);
  ASSERT_NEAR(vec1[7], 2, 1E-06);
  ASSERT_NEAR(vec1[8], 2, 1E-06);
  ASSERT_EQ(vec1.size(), 24);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
