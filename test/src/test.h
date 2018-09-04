#ifndef TEST_H
#define TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Test : public CppUnit::TestFixture {

   CPPUNIT_TEST_SUITE(Test);
   CPPUNIT_TEST(sort);
   CPPUNIT_TEST(find);
   CPPUNIT_TEST_SUITE_END();

public:
   void sort(); 
   void find(); 
};

#endif // TEST_H
