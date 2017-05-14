/*  File: hw5.c
    Homework 5, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 5
    03-30-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prompts.h"
#include "catalog.h"
#include "transcript.h"

void printNode(Node n) {

	printf("%d.%c %s ", n -> year, n -> semester, n -> grade);
	printCourse(n -> c);
}

void printTranscript(Node* tScript) {
	Node head = *tScript;

	if (head -> next == NULL) {
        empty_transcript_msg();
    } else {
    	
    	Node currentNode = head -> next;

		while(currentNode != NULL) {

			printNode(currentNode);
        	currentNode = currentNode -> next;
    	}
    }
}

void freeTranscript(Node* tScript) {
    
    while(*tScript) {
    	//free((*tScript) -> c);
    	deleteHead(tScript); 
    }
}

Node create(Course c, char grade[], int year, char semester) {
	Node newNode = malloc(sizeof(node));
	if (newNode == NULL) {
		//output error message
		fprintf(stderr, "space allocation failed");
	}
	newNode -> next = NULL;
	newNode -> c = c;
	strcpy(newNode -> grade, grade);
	newNode -> year = year;
	newNode -> semester = semester; 
	return newNode;
}

void insertAfter(Node n, Node newNode) {
	newNode->next = n->next;
	n->next = newNode;
}

void deleteAfter(Node n) {
	Node deletedNode = n->next;
	if(!deletedNode) {
		return;
	}
	n->next = n->next->next;
	free(deletedNode);
}

void insertHead(Node *head, Node newHead) {
	newHead->next = *head;
	*head = newHead;
}

void deleteHead(Node *head) {
	Node n = (*head);
	*head = n->next;
	free(n);
}

void addCourse(Node* tScript, Course c, char grade[], int year, char semester) {
	
	Node head = *tScript;
	Node newCourse = create(c, grade, year, semester);

	if (head -> next == NULL) {
		insertAfter(head, newCourse);
    } else {

    	Node prevNode = head;
    	Node currentNode = head -> next;

		while(currentNode != NULL) {

        	if (compare(currentNode, newCourse)) {
        	    insertAfter(prevNode, newCourse);
        	    break;
        	} else if (currentNode -> next == NULL) {
        		insertAfter(currentNode, newCourse);
        		break;
        	}
        	prevNode = prevNode -> next;
        	currentNode = currentNode -> next;
    	}
    }
}

void deleteCourse(Node *tScript, Course c) {

    Node prevNode = *tScript;
    Node currentNode = prevNode -> next;
    
    while(currentNode != NULL) {

        if (equals(currentNode -> c, c)) {
            deleteAfter(prevNode);
        }
        prevNode = prevNode -> next;
        currentNode = currentNode -> next;
    }
}

void deleteCourseInSem(Node* tScript, Course c, int year, char semester) {

	Node prevNode = *tScript;
    Node currentNode = prevNode -> next;
    
    while(currentNode != NULL) {

        if (equals(currentNode -> c, c) && currentNode -> year == year
            && currentNode -> semester == semester) {
            deleteAfter(prevNode);
        }
        prevNode = prevNode -> next;
        currentNode = currentNode -> next;
    }
}

int compare(Node n1, Node n2) {
	if (n1 -> year > n2 -> year) {
		return 1;
	}
	if (n1 -> year == n2 -> year) {
		if (n1 -> semester >= n2 -> semester) {
			return 1; //first comes after second
		}
	}
	return 0; //first comes before
}
