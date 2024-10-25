#include "suites.h"

int main() {
  int failed;
  Suite *suite[] = {
      all_calculation_suite(),
  };

  SRunner *runner;

  for (size_t i = 0; i < sizeof(suite) / sizeof(char *); i++) {
    runner = srunner_create(suite[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? 0 : 1;
}
