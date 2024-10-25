#include <check.h>
#include <stdio.h>

#include "../s21_smart_calc.h"

START_TEST(test_1) {
  char *str = "134.5675673+456.8946571";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 591.4622244, 1e-6);
}
END_TEST

START_TEST(test_2) {
  char *str = "134.5675673-456.8946571";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, -322.3270898, 1e-6);
}
END_TEST

START_TEST(test_3) {
  char *str = "134.5675673*456.8946571";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 61483.2025183, 1e-6);
}
END_TEST

START_TEST(test_4) {
  char *str = "134.5675673/456.8946571";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.2945265, 1e-6);
}
END_TEST

START_TEST(test_5) {
  char *str = "101%10";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 1, 1e-6);
}
END_TEST

START_TEST(test_6) {
  char *str = "8.11^2.12";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 84.5520635, 1e-6);
}
END_TEST

START_TEST(test_7) {
  char *str = "+156+344";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 500, 1e-6);
}
END_TEST

START_TEST(test_8) {
  char *str = "cos(2.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, -0.8568889, 1e-6);
}
END_TEST

START_TEST(test_9) {
  char *str = "sin(2.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.5155014, 1e-6);
}
END_TEST

START_TEST(test_10) {
  char *str = "tan(2.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, -0.6015966, 1e-6);
}
END_TEST

START_TEST(test_11) {
  char *str = "ln(2.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.9555114, 1e-6);
}
END_TEST

START_TEST(test_12) {
  char *str = "ln(2.6)-log(2.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.5405380, 1e-6);
}
END_TEST

START_TEST(test_13) {
  char *str = "asin(0.5)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.5235987, 1e-6);
}
END_TEST

START_TEST(test_14) {
  char *str = "acos(0.5)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 1.0471975, 1e-6);
}
END_TEST

START_TEST(test_15) {
  char *str = "atan(0.5)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.4636476, 1e-6);
}
END_TEST

START_TEST(test_16) {
  char *str = "sqrt(115.6)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 10.7517440, 1e-6);
}
END_TEST

START_TEST(test_17) {
  char *str = "log(2.8)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 0.4471580, 1e-6);
}
END_TEST

START_TEST(test_18) {
  char *str = "58-(-5)/2^3-12";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 46.625, 1e-6);
}
END_TEST

START_TEST(test_19) {
  char *str = "3*sin(cos(tan(10)))";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 2.1459451, 1e-6);
}
END_TEST

START_TEST(test_20) {
  char *str = "5*(28-(9-(5-(1+1))))";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 110, 1e-6);
}
END_TEST

START_TEST(test_21) {
  char *str = "sin(5)^2+cos(5)^2";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 1, 1e-6);
}
END_TEST

START_TEST(test_22) {
  char *str = "78-(-86.23)+9*tan(4)";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 174.6503915, 1e-6);
}
END_TEST

START_TEST(test_30) {
  char *str = "58*5^8/6+sqrt(45*sin(0.66))";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 3776046.91931, 1e-6);
}
END_TEST

START_TEST(test_31) {
  char *str = "1000 + 1000 * x";
  double result = all_calculation(str, "1");
  ck_assert_double_eq_tol(result, 2000.000000, 1e-6);
}
END_TEST

START_TEST(test_32) {
  char *str = "12 + 331 * ( 4 / 2 - sin(1) )";
  double result = all_calculation(str, "");
  ck_assert_double_eq_tol(result, 395.473104, 1e-6);
}
END_TEST

START_TEST(test_33) {
  char *str = " ";
  double result = all_calculation(str, "");
  ck_assert_ldouble_nan(result);
}
END_TEST

START_TEST(test_34) {
  char *str = "7/0";
  double result = all_calculation(str, "");
  ck_assert_ldouble_infinite(result);
}
END_TEST

START_TEST(test_35) {
  char *str = "dad";
  double result = all_calculation(str, "");
  ck_assert_ldouble_nan(result);
}
END_TEST

START_TEST(test_37) {
  StringStack *stack = create_string_stack();
  pop_string(stack);
  peep_string(stack);
  free(stack);
}
END_TEST

Suite *all_calculation_suite() {
  Suite *suite = suite_create("s21_all_calculation_suite");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_1);
  tcase_add_test(tcase, test_2);
  tcase_add_test(tcase, test_3);
  tcase_add_test(tcase, test_4);
  tcase_add_test(tcase, test_5);
  tcase_add_test(tcase, test_6);
  tcase_add_test(tcase, test_7);
  tcase_add_test(tcase, test_8);
  tcase_add_test(tcase, test_9);
  tcase_add_test(tcase, test_10);
  tcase_add_test(tcase, test_11);
  tcase_add_test(tcase, test_12);
  tcase_add_test(tcase, test_13);
  tcase_add_test(tcase, test_14);
  tcase_add_test(tcase, test_15);
  tcase_add_test(tcase, test_16);
  tcase_add_test(tcase, test_17);
  tcase_add_test(tcase, test_18);
  tcase_add_test(tcase, test_19);
  tcase_add_test(tcase, test_20);
  tcase_add_test(tcase, test_21);
  tcase_add_test(tcase, test_22);

  tcase_add_test(tcase, test_30);
  tcase_add_test(tcase, test_31);

  tcase_add_test(tcase, test_32);
  tcase_add_test(tcase, test_33);
  tcase_add_test(tcase, test_34);
  tcase_add_test(tcase, test_35);

  tcase_add_test(tcase, test_37);

  // tcase_add_test(tcase, test_23);
  // tcase_add_test(tcase, test_24);
  // tcase_add_test(tcase, test_25);
  // tcase_add_test(tcase, test_26);
  // tcase_add_test(tcase, test_27);
  // tcase_add_test(tcase, test_28);
  // tcase_add_test(tcase, test_29);

  suite_add_tcase(suite, tcase);
  return suite;
}
