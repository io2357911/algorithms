#include "test.h"
#include <cppunit/ui/text/TestRunner.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main() {
   CppUnit::TextUi::TestRunner runner;
   CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
   runner.addTest(registry.makeTest());
   runner.run();
   return 0;
}
