#ifndef TEST_H
#define TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Test : public CppUnit::TestFixture {

   CPPUNIT_TEST_SUITE(Test);
   CPPUNIT_TEST(sort);
   CPPUNIT_TEST(find);
   CPPUNIT_TEST(polynomial_deriative);
   CPPUNIT_TEST(graph_search);
   CPPUNIT_TEST(binary_search);
   CPPUNIT_TEST(bigint);
   CPPUNIT_TEST_SUITE_END();

public:
   void sort(); 
   void find(); 
   void polynomial_deriative(); 
   void graph_search(); 
   void binary_search(); 
   void bigint(); 
};

#endif // TEST_H
