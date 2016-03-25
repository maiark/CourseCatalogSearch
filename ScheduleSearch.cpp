//LAB 6B
//MAIAR KHATTAB
//COMSC210

#include <fstream>
#include <iostream>
using namespace std;
#include <string>
#include<vector>
#include <deque>
#include <algorithm>//for my sort
#include <cstring>
#include<ctime>

struct Course
{
	string name;
	int count;
	bool operator ==(const Course& equal) const
	{
		return this->name == equal.name;
	}
};
struct SubjectCode
{
	string name;
	int count;
	deque<Course> course;
	bool operator ==(const SubjectCode& equal) const
	{
		return this->name == equal.name;
	}
	
};
struct key
{
	string term;
	string section;
	bool operator ==(const key& equals) const
	{
		return this->term == equals.term &&
			this->section == equals.section;
	}
};
void coursePrint(const Course& c)
{
	cout << c.name << ", " << c.count << ", " << endl;
}


void Print(const SubjectCode& subjectCode)
{
	int sum = 0;
	for (Course c : subjectCode.course)
		sum += c.count;
		cout << endl << subjectCode.name << "," << subjectCode.course.size() << " courses " <<
		 sum << " classe(s)  " << endl;
	for (Course c : subjectCode.course)
		cout << c.name << " " << c.count << endl;
}

int main()
{

	const char* const tab = "\t";
	int count = 0;//for progress bar 

	deque<SubjectCode> subjectCodesa;
	
	deque<key>nonDupList;
	deque<key> dupList;
	// open the file
	ifstream fin;
	fin.open("dvc-schedule.txt");
	//fin.open("test.txt");
	if (!fin.good())
		throw(exception("I/O Error"));

	clock_t startTime = clock();

	// Read the file
	while (fin.good())
	{

		if (count % 1000 == 0)
			cout << '.'; count++;
		cout.flush();
		string line;
		getline(fin, line);
		if (line[0] == 0)  continue;

		size_t current, next = -1;
		current = next + 1;
		next = line.find_first_of("\t\n", current);
		string term = line.substr(current, next - current);

		current = next + 1;
		next = line.find_first_of("\t\n", current);
		string section = line.substr(current, next - current);

		current = next + 1;
		string course;
		if (current < line.length())
		{
			next = line.find_first_of("\t\n", current);
			course = line.substr(current, next - current);
		}

		current = next + 1;
		string instructor;
		if (current < line.length())
		{
			next = line.find_first_of("\t\n", current);
			instructor = line.substr(current, next - current);
		}

		current = next + 1;
		string whenWhere;
		if (current < line.length())
		{
			next = line.find_first_of("\t\n", current);
			whenWhere = line.substr(current, next - current);
		}

		if (course.find('-') == string::npos)
			continue;
       string subjectCode(course.begin(), course.begin() + course.find('-'));

		key curCourse;
		curCourse.section = section;
		curCourse.term = term;
		// Look through the nonDupList to see if the curCourse is there.
		
		deque<key>::iterator where = find(nonDupList.begin(), nonDupList.end(), curCourse);

		// If it is there - then it is a dup, put in dupList. 
		if (where != nonDupList.end())
		{
			dupList.push_back(curCourse);
			
		}
		// Else - not a dup - put it in nonDupList
		else
		{
			//nonDupList[nonDupCount++] = curCourse;
			nonDupList.push_back(curCourse);
			SubjectCode curCourse2;
			curCourse2.count = 1;
			curCourse2.name = subjectCode;
			deque<SubjectCode>::iterator here = find(subjectCodesa.begin(), subjectCodesa.end(), curCourse2);
			// if not found, here is subjectCodesa.end()
			Course c;
			c.name = course;
			c.count = 1;

			if (here == subjectCodesa.end())
			{
				// subjcode not found
				//   push the subjcode with the one course in.
				//     make a course
				//     push into curCourse2
				curCourse2.course.push_back(c);
				//     push into subjectCodesa
			
				subjectCodesa.push_back(curCourse2);
				

			}
			else
			{
				// found the subj code
				//  Need to check if the course exists already
				deque<Course>::iterator where2 = find(here->course.begin(), here->course.end(), c);
				//  found the course
				//    increment the course in the subjcode
				//  not found course
				if (where2 == here->course.end())
				{
					//    insert the new course in the subjcode
					here->course.push_back(c);
					
				}
				else
				{
					where2->count++;
				}

			}


		}



	}//end of while that reads file


	// Close the file
	fin.close();
	cout << endl << endl;
	int cc = 0;//code counter

	for (int i = 1; i < cc; i++)
	{
		int s = i;

	}
	int k = 0;
	int m = 0;
	int N = subjectCodesa.size();
	string t1;
	int t2;
	deque<Course>t3;

	for (k = 0; k<N - 1; k++)
	{
		
			m = 0;
			while (m < N - k - 1)
			{
				if (subjectCodesa[m].name>subjectCodesa[m + 1].name )
				{
					t1 = subjectCodesa[m].name;
					subjectCodesa[m].name = subjectCodesa[m + 1].name;
					subjectCodesa[m + 1].name = t1;

					t2 = subjectCodesa[m].count;
					subjectCodesa[m].count = subjectCodesa[m + 1].count;
				    subjectCodesa[m + 1].count = t2;
					
					t3 = subjectCodesa[m].course;
					subjectCodesa[m].course = subjectCodesa[m + 1].course;
					subjectCodesa[m + 1].course = t3;


				}
				m++;
			}	
	}
	
	

	double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
	
	cout << "The elapased seconds it took to parse file: " << elapsedSeconds << " seconds" << endl;
	cout << dupList.size() << " duplicates" << endl;
	for (int i = 0; i < subjectCodesa.size(); i++)
	{
		Print(subjectCodesa[i]);
		
		
	}
	cin.get();
	return 0;

}


