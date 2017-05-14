#ifndef catalog

#define catalog

	typedef struct _course {
		char division[3]; 
		int department;
		int courseNumber;
		float credits;
		char courseTitle[33];
	} course;

	typedef course *Course;

	void printCourse(Course c);

	//void print(course c);

	int numCourses(FILE* inputFile);

	Course* fillCatalog(FILE* inputFile, int numCourses);

	int equals(Course c1, Course c2);

#endif
