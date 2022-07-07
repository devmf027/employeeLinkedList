/*
 ============================================================================
 Name        : final.c
 Author      : Dariel Mizrachi
 Version     : 1.0.0
 Copyright   : All Rights Reserved
 Description : Employees administration system
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node { // defines a new struct type called employee
	char *name;
	char *id_num;
	char *salary;
	struct node *next;
	struct node *prev;
} employee;

int addEmployee(char *name, char *id_num, char *salary, employee *current,		// Adds a new employee to the list ordered by ID number
		employee **head_pointer);
int removeEmployee(char *id_num, employee *current, employee **head_pointer);	// Removes an existent employee from the list
void printList(employee *current);												// Prints the whole list
int idCmp(char *id1, char *id2);												// Compares between 2 ID numbers
employee* createEmployee(char *name, char *id_num, char *salary);				// Creates a new employee node
int nameValidation(char *name, int len);										// Checks if name is valid
int idValidation(char *id, int len);											// Checks id ID number is valid
int salaryValidation(char *salary, int len);									// Checks if salary is valid
int flushStdin();																// Clears the rest of the input buffer after buffer overflow

int main() {
	puts("Welcome to the interactive employees administration system.\n");		// Welcome message

employee *head = NULL; 											// Initialize a new employee pointer head to NULL
	employee **head_ptr = &head;								// Initialize a pointer to the pointer head

	char menuCh = 0;											// Initialize the menu option char to 0
	while (!(menuCh == 'e' || menuCh == 'E')) {					// while is different from 'e' or 'E' (Exit)
		puts("		    MAIN MENU			");
		puts("////////////////////////////////////////////////////");
		puts("// * Press 'a' to add a new employee to the list. //");	// Shows option char 'a' to add an employee
		if (head != NULL) {										// If head is NULL there is nothing to remove or print
			puts("// * Press 'r' to remove an employee.             //");
			puts("// * Press 'p' to print the list.                 //");
		}
		puts("// * Press 'e' to exit.                           //");	// Shows option char 'e' to exit
		puts("////////////////////////////////////////////////////");
		menuCh = getc(stdin);									// Gets user char input with an option
		flushStdin();											// frees the rest of the input buffer
		char name[100];											// Declare a new string named name
		char id[100];											// Declare a new string named id
		char salary[100];										// Declare a new string named salary

		////////////////////////////////////////////////////
		//			ADDS A NEW EMPLOYEE TO THE LIST		  //
		////////////////////////////////////////////////////

		if (menuCh == 'a' || menuCh == 'A') {					// If 'a' or 'A' are chosen

			///////NAME INPUT AND VALIDATION///////

			int isValidName = 0;								// Initialize while condition variable
			while (isValidName == 0) {							// If condition equals 0. name validation failed
				puts("Please enter the employee name.");
				fgets(name, 98, stdin);							// Gets user input for the employee name
				int nameLen = strlen(name);						// Stores name length
				isValidName = nameValidation(name, nameLen);	// Stores name validity check result
				if (isValidName == 0) {							// If is not a valid name
					puts("Please enter a valid name.\n");
				}
			} // while validation end
			strtok(name, "\n");													// Remove the new line char from the string

			///////ID INPUT AND VALIDATION///////

			int isValidId = 0;													// Initialize while condition variable
			while (isValidId == 0) {											// If condition equals 0. id validation failed
				puts("Please enter the employee ID number.");
				fgets(id, 98, stdin);											// Gets user input for the employee id
				int idLen = strlen(id);											// Stores id length
				isValidId = idValidation(id, idLen);							// If condition equals 0. id validation failed
				if (isValidId == 0) {
					puts("Please enter a valid ID number. Maximum 9 digits.\n");// If is not a valid id
				}
			} // while validation end
			strtok(id, "\n");														// Remove the new line char from the string

			///////SALARY INPUT AND VALIDATION///////

			int isValidSalary = 0;													// Initialize while condition variable
			while (isValidSalary == 0) {											// If condition equals 0. id validation failed
				puts("Please enter the employee Salary.");
				fgets(salary, 98, stdin);											// Gets user input for the employee salary
				int salaryLen = strlen(salary);										// Stores salary length
				isValidSalary = salaryValidation(salary, salaryLen);				// If condition equals 0. salary validation failed
				if (isValidSalary == 0) {											// If is not a valid salary
					puts("Please enter a valid salary. Only digits!\n");
				}
			} // while validation end
			strtok(salary, "\n");													// Remove the new line char from the string

			///////ADDS EMPLOYEE///////

			if (head == NULL) {														// If the list is empty
				head = createEmployee(name, id, salary);							// Creates and stores in head the first employee
				continue;															// Shows the option menu again
			} else {																// If the list is not empty
				int isAdded = addEmployee(name, id, salary, head, head_ptr);		// Creates and adds an employee ordered by ID number to the list. Returns 1 if succeeded
				if (isAdded == 1) {													// If is not repeated ID number
					puts("Employee added successfully.\n");
				} else {
					puts(															// If ID number already exists in the list
							"Repeated ID number. Please enter a different number.\n");
				}
				continue;															// Shows the option menu again
			}

		//////////////////////////////////////////////////////////
		//			REMOVES AN EMPLOYEE FROM THE LIST			//
		//////////////////////////////////////////////////////////

		} else if (head != NULL) {													// If the list is not empty
			if (menuCh == 'r' || menuCh == 'R') {									// If 'r' or 'R' are chosen. For removing an existent employee by ID number

				///////ID INPUT AND VALIDATION///////

				int isValidId = 0;													// Initialize while condition variable
				while (isValidId == 0) {											// If condition equals 0. id validation failed
					puts("Please enter the employee ID number to remove.");
					fgets(id, 98, stdin);											// Gets user input for the employee id
					int idLen = strlen(id);											// Stores id length
					isValidId = idValidation(id, idLen);							// If condition equals 0. id validation failed
					if (isValidId == 0) {											// If is not a valid id
						puts(
								"Please enter a valid ID number. Maximum 9 digits.\n");
					}
				} // while validation end
				strtok(id, "\n");													// Remove the new line char from the string

				///////REMOVES EMPLOYEE///////

				int isRemoved = removeEmployee(id, head, head_ptr);					// Searches and remove an employee by ID number from the list. Returns 1 if succeeded
				if (isRemoved == 1) {												// If the ID number exists in the list
					puts("Employee successfully removed.");
				} else if (isRemoved == 0) {										// If doesn't exist
					puts("ID number not found.");
				} else {															// if removeEmployee returned -1, the last employee was removed
					puts("Last employee removed. The list is empty.");
				}
				puts("");															// Adds a new line
				continue;															// Shows the option menu again

			//////////////////////////////////////////////
			//			PRINTS THE COMPLETE LIST		//
			//////////////////////////////////////////////

			} else if (menuCh == 'p' || menuCh == 'P') {							// If 'p' or 'P' are chosen. For printing the entire employee list
				printList(head);													// Prints the list
				puts("");															// Adds a new line
				continue;															// Shows the option menu again
			}

		}

		////////////////////////////////////////
		//			EXITS THE SYSTEM		  //
		////////////////////////////////////////

		if (!(menuCh == 'e' || menuCh == 'E')) {									// If the selected option is not valid
			puts("Please enter a valid option.\n");
		}

	} // Main menu while loop end

	puts("Thanks for using the interactive employees administration system.");		// Goodbye message

	return 1;

} // End of function main

int addEmployee(char *name, char *id_num, char *salary, employee *current,employee **head_pointer) {
	employee *newEmployee = createEmployee(name, id_num, salary);
	do {
		int isGreater = idCmp(id_num, current->id_num);
		if (isGreater == 1) { 												 	 // If newEmployee id is bigger than current employee id
			if (current->next == NULL) { 										 // If is the tail of the list
				current->next = newEmployee; 									 // Current employee next variable points to new employee
				newEmployee->prev = current;									 // Current employee prev variable points to current employee. The new employee is the tail
				return 1;														 // Returns success

			} else if (idCmp(newEmployee->id_num, current->next->id_num) == 0) { // Else if new employee id is smaller than the next employee id in the list
				newEmployee->next = current->next; 								 // New employee next points to the next employee in the list
				newEmployee->prev = current;									 // New employee prev points to the current employee
				current->next = newEmployee;    								 // Current next points to new employee
				return 1;														 // Returns success

			} else { 															 // If new employee id is bigger than current->next id
				current = current->next;										 // Move to the next employee in the list. Current employee is next employee
				continue;														 // Jumps back to "do"
			}
		} else if (isGreater == -1) {											 // If id number already exists in the list
			return 0;															 // Returns failure
		} else {																 // Is the smallest id number. Is the first element of the list
			newEmployee->next = current;										 // New employee next points to the actual head to the list
			current->prev = newEmployee;										 // Actual head prev points to the new head
			*head_pointer = newEmployee;										 // Head pointer points to the new employee
			return 1;															 // Returns success
		}
	} while (current != NULL);													 // Checks up to the last element of the list

	return 0;																	 // Returns failure
}

int removeEmployee(char *id_num, employee *current, employee **head_pointer) {
	int isEqual = idCmp(id_num, current->id_num);			// Stores the result of comparing two ID numbers
	if (current->prev == NULL && isEqual == -1) {			// If is the head of the list
		*head_pointer = current->next;						// Head pointer points to the next employee. The new head
		if (current->next != NULL) {						// If is not the only element in the list
			current->next->prev = NULL;						// The new head prev points to NULL

			return 1;										// Returns success
		}
		return -1;											// Returns -1. The list is empty
	}

	while (current != NULL){								// If is not the end of the list
		isEqual = idCmp(id_num, current->id_num);			// Stores the result of comparing two ID numbers
		if (current->next != NULL) {						// If is in the middle of the list
			if (isEqual == -1) {							// If the ID numbers match
				current->prev->next = current->next;		// Previous employee next points to the next employee
				current->next->prev = current->prev;		// Next employee prev points to the previous employee
				return 1;									// Returns success
			}
		} else {											// If current employee is the l tail of the list
			if (isEqual == -1) {							// If the ID numbers match
				current->prev->next = NULL;				    // Previous employee (new tail) next points to NULL
				return 1;									// Returns success
			}
		}
		current = current->next;							// Move to the next employee in the list. Current employee is next employee
	}
	return 0;												// Return failure
}

void printList(employee *current) {
	while (current != NULL) {													// Iterates all over the list
		printf("%s %s %s\n", current->name, current->id_num, current->salary);	// Prints name, id number and salary of current employee
		current = current->next;												// Move to the next employee in the list. Current employee is next employee
	}
}

int idCmp(char *id1, char *id2) {

	if (strlen(id1) > strlen(id2)) {	// If id1 is greater than id2
		return 1;						// Returns 1
	}
	if (strlen(id1) < strlen(id2)) {	// If id1 is smaller than id2
		return 0;						// Returns 0
	}
	int i = 0;							// i for the index
	while (i < strlen(id1)) {			// while i is smaller than id1. id1 = id2
		if (id1[i] == id2[i]) {			// If is same number and same position
			i++;						// Check next number
			continue;					// Jump back to while
		} else if (id1[i] > id2[i]) {	// If id1 number is greater than id2 number
			return 1;					// Returns 1
		} else {						// If id1 number is smaller than id2 number
			return 0;					// Return 0
		}
	}									// If is the same id number
	return -1;							// Returns -1
}

employee* createEmployee(char *name, char *id_num, char *salary) {
	employee *newEmployee = NULL;						// Initialize an employee pointer to NULL
	newEmployee = (employee*) malloc(sizeof(employee)); // Allocates the exact memory size to hold the values of variables for a new employee
	newEmployee->name = strdup(name);					// Copies the name into the employee name variable
	newEmployee->id_num = strdup(id_num);				// Copies the id into the employee id variable
	newEmployee->salary = strdup(salary);				// Copies the salary into the employee salary variable
	newEmployee->next = NULL;							// Employee next points to NULL
	newEmployee->prev = NULL;							// Employee prev points to NULL
	return newEmployee;									// Returns the new created employee pointer
}

int nameValidation(char *name, int len) {
	for (int i = 0; i < len - 1; i++) {	// Checks from the first name char to the last name char without the end char '\0'
		if (!isalpha(name[i])) {		// If is not an alphabet char
			return 0;					// Returns failure
		}
	}
	return 1;							// Returns success
}

int idValidation(char *id, int len) {
	if (len > 10) {						// If id number has more than 10 characters including '\0'
		return 0;						// Returns failure
	}
	if (id[0] == '0') {					// If the first char is '0'
		return 0;						// Returns failure
	}
	for (int i = 0; i < len - 1; i++) {			// Checks only the numbers of the id
		if (!(id[i] >= '0' && id[i] <= '9')) {  // If is not a number
			return 0;
		}										// Returns failure
	}

	return 1;									// Returns success
}

int salaryValidation(char *salary, int len) {
	for (int i = 0; i < len - 1; i++) {					// Checks only the numbers of the salary
		if (!(salary[i] >= '0' && salary[i] <= '9')) {	// If is not a number
			return 0;									// Returns failure
		}
	}
	return 1;											// Returns success
}

int flushStdin() {
	int c;
	while ((c = getc(stdin)) != '\n' && c != EOF);  // Flush the rest of the input
	return 1;										// Returns success
}

