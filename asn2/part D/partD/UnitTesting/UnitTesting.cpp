#include "pch.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <string>
#include "website.h"
//#include "student.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

	TEST_CLASS(UnitTesting)
	{
		
	public:
			
		TEST_METHOD(Student_Constructor)
		{
			string name = "testname";
			student* test = new student(name, 12, 1, 1, 1, true);
			Assert::AreEqual(test->name, name);
			Assert::AreEqual(test->id, 12);
			Assert::AreEqual(test->year, 1);
			Assert::AreEqual(test->year_completion, 1);
			Assert::AreEqual(test->outstanding_fees, true);
		}
		TEST_METHOD(Student_Destructor)
		{
			string name = "testname";
			student* test = new student(name, 12, 1, 1, 1, true);
			test->~student();
			Assert::IsNull(test->theWebsite);
		}
	};
    
}

			// website* theWebsite = new website();
			// student* student1 = new student("Martin", 0, 1, 85, 82, false);
    		// student* student2 = new student("Varun", 1, 1, 60, 70, true);
    		// advisor* enggadv = new advisor("Cathleen");
    		// theWebsite->AddStudent(student1);
    		// theWebsite->AddStudent2(student2);
    		// theWebsite->AddAdvisor(enggadv);
	
		    // int temp_form1[2] = { 1, 2 };
		    // int temp_form2[2] = { 2, 1 };
		
		    // // Part 2: First year program application
		    // student1->ViewForm();
		    // student1->EditForm(temp_form1);
		    // student1->ViewForm();
		
		    // student2->ViewForm();
		    // student2->EditForm(temp_form2);
		    // student2->ViewForm();
		    // enggadv->ProcessPlacement();