#ifndef SPEEDTESTS_CORE_HASHTEST_H_
#define SPEEDTESTS_CORE_HASHTEST_H_

#include "../testcore/testcore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void HashtestBeforeRun(TestRun *test_run, size_t run);
void HashtestAfterRun(TestRun *test_run, size_t run);

void HashtestUTHashAdd(void *user_data);
void HashtestBoostAdd(void *user_data);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // SPEEDTESTS_CORE_HASHTEST_H_
