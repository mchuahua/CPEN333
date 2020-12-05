#include "pch.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <string>
#include "website.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

	TEST_CLASS(UnitTesting)
	{
		
	public:
		// Tests the constructor for the student object by asserting the passed in variables to the copied variables within the test student object.
		TEST_METHOD(Student_Constructor_Test)
		{
			string name = "testname";
			student* test = new student(name, 12, 1, 1, 1, true);
			Assert::AreEqual(test->name, name);
			Assert::AreEqual(test->id, 12);
			Assert::AreEqual(test->year, 1);
			Assert::AreEqual(test->year_completion, 1);
			Assert::AreEqual(test->outstanding_fees, true);
		}
		// Tests the destructor functions properly and deletes theWebsite by explicitly calling the destructor before the test method ends. Asserts that the destroyed pointer is NULL.
		TEST_METHOD(Student_Destructor_Test)
		{
			string name = "testname";
			student* test = new student(name, 12, 1, 1, 1, true);
			test->~student();
			Assert::IsNull(test->theWebsite);
		}
		// Tests the website object is properly constructed using the name string that is automatically created and assigned during construction. 
		// This should always be a hardcoded "SSC", as asserted below.
		TEST_METHOD(Website_Name_Test){
			website* test = new website();
			string ssc = "SSC";
			Assert::AreEqual(test->name, ssc); 
		}
		// Tests advisor is properly constructed using the name string that is passed during advisor construction.
		TEST_METHOD(Advisor_Name_Test){
			string name = "Test_name";
			advisor* test_advisor = new advisor(name);
			Assert::AreEqual(test_advisor->name, name);
		}
		// Tests the website-student link is appropriately linked, as mentioned in Prof. Davies' slideset on linking.
		// This test method and the one below assert name equation because AreEqual cannot equate pointer addresses.
		// Might be because AreSame is for equating references, but this case works, so there's no need to change it.
		TEST_METHOD(Website_Student_Link_Test){
			string name = "Test";
			website* test_website = new website();
			student* test_student = new student(name, 0, 1, 12, 42, false);
			test_website->AddStudent(test_student);
			Assert::IsNotNull(test_website->theStudent);
			Assert::IsNotNull(test_student->theWebsite);
			Assert::AreEqual(test_website->theStudent->name, test_student->name);
			Assert::AreEqual(test_student->theWebsite->name, test_website->name);
		}
		// Tests the website advisor link is appropriately linked, as mentioned in Prof. Davies' slideset on linking.
		TEST_METHOD(Website_Advisor_Link_Test){
			string name = "test";
			website* test_website = new website();
			advisor* test_advisor = new advisor(name);
			test_website->AddAdvisor(test_advisor);
			Assert::IsNotNull(test_website->theAdvisor);
			Assert::IsNotNull(test_advisor->theWebsite);
			Assert::AreEqual(test_website->theAdvisor->name, test_advisor->name);
			Assert::AreEqual(test_advisor->theWebsite->name, test_website->name);
		}
		// Tests the form viewed function, which happens when a student views a form. 
		// Uses a test-variable that is not included in the UML diagrams because it is strictly for testing, which increments whenever the ViewForm() function is called.
		// Asserts that form is viewed correctly and there are no early terminations.
		TEST_METHOD(View_Form_Test){
			string name = "test";
			website* test_website = new website();
			student* test_student = new student(name, 0, 1, 12, 42, false);
			test_website->AddStudent(test_student);
			test_student->ViewForm();
			Assert::AreEqual(test_website->formviewed_test, 1);
			test_student->ViewForm();
			Assert::AreEqual(test_website->formviewed_test, 2);
		}
		// Tests to see if the form is edited correctly using a test_form with values of 1 and 2.
		// Asserts in a for loop to check that the form is correctly copied over into the website database (student variables).
		TEST_METHOD(Edit_Form_Test){
			string name = "test";
			website* test_website = new website();
			student* test_student = new student(name, 0, 1, 12, 42, false);
			test_website->AddStudent(test_student);
		    int test_form[2] = { 1, 2 };
			test_student->ViewForm();
			test_student->EditForm(test_form);
			test_student->ViewForm();
			for (int i = 0; i < 2; ++i)
				Assert::AreEqual(test_student->form[i], test_form[i]);
		}
		// Tests to see if the placements are correct. Test student is assigned a grade of 90, which is above the 80 check for advisor.
		// When the Advisor processes placements, the advisor will give the student their first choice, which in this case is ELEC.
		// We assert that it is elec, and not fizz.
		TEST_METHOD(Placement_Test){
			string name = "test";
			string elec = "ELEC";
			string fizz = "FIZZ";
			website* test_website = new website();
			student* test_student = new student(name, 0, 1, 80, 90, false);
			advisor* test_advisor = new advisor(name);
			test_website->AddStudent(test_student);
			test_website->AddAdvisor(test_advisor);
		    int test_form[2] = { 1, 2 };
			test_student->ViewForm();
			test_student->EditForm(test_form);
			test_student->ViewForm();
			test_advisor->ProcessPlacement();
			Assert::AreEqual(test_student->program, elec);
			Assert::AreNotEqual(test_student->program, fizz);
		}
		// This test should fail due to incorrect data
		TEST_METHOD(Failing_Test){
			string name = "test";
			string elec = "ELEC";
			string fizz = "FIZZ";
			website* test_website = new website();
			student* test_student = new student(name, 0, 1, 80, 90, false);
			advisor* test_advisor = new advisor(name);
			test_website->AddStudent(test_student);
			test_website->AddAdvisor(test_advisor);
		    int test_form[2] = { 1, 2 };
			test_student->ViewForm();
			test_student->EditForm(test_form);
			test_student->ViewForm();
			test_advisor->ProcessPlacement();
			Assert::AreEqual(test_student->program, fizz);
			Assert::AreNotEqual(test_student->program, elec);
		}
		TEST_METHOD(Failing_Test2)
		{
			string name = "testname";
			student* test = new student(name, 12, 1, 1, 1, true);
			test->~student();
			Assert::IsNotNull(test->theWebsite);
		}
	};
    
}
