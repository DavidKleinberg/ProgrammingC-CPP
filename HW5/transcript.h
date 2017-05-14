#ifndef transcript

#define transcript

	typedef struct _node {
		//pointer to a course so that changes made in the catalog are universal
		Course c;
		char grade[3];
		int year;
		char semester;
		struct _node *next;
	} node;

	typedef node *Node;

	void printNode(Node n);
	void printTranscript(Node* tScript);
	void freeTranscript(Node* tScript);
	Node create(Course c, char grade[], int year, char semester);
	void insertAfter(Node n, Node newNode);
	void deleteAfter(Node n);
	void insertHead(Node *head, Node newHead);
	void deleteHead(Node *head);
	int compare(Node n1, Node n2);
	void addCourse(Node *head, Course c, char grade[], int year, char semester);
	void deleteCourse(Node *tScript, Course c);
	void deleteCourseInSem(Node* tScript, Course c, int year, char semester);

#endif
