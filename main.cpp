#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Todo {
	int id;
	char title[25];
};

struct Todo todos[100] = {};

void printMenu();
void readTodos();
void backOption();
void createTodo();
int getLastIndexTodo();
void removeTodo();
void updateTodo();
void clearConsole();
int getIndexByTodoId(int todoId);

int main()
{
	int action;
	do {
		printMenu();
		printf("\nSelect an action based on the: ");
		scanf_s("%d", &action);
		if (action == 1)
		{
				clearConsole();
				createTodo();
				backOption();
		}
		if (action == 2)
		{
				clearConsole();
				readTodos();
				backOption();
		}
		if (action == 3)
		{
				clearConsole();
				updateTodo();
				backOption();
		}
		if (action == 4)
		{
				clearConsole();
				removeTodo();
				backOption();
		}
	} while (action != 5);
}

void clearConsole()
{
	system("cls");
}

void printMenu() {
	clearConsole();
	printf("Todo CLI");
	printf("\n1. Create");
	printf("\n2. Read");
	printf("\n3. Update");
	printf("\n4. Delete");
	printf("\n5. Exit");
}

void readTodos() {
	int todoSize = sizeof(todos) / sizeof(todos[0]);
	int todoCount = 0;
	char todosDisplay[100] = "";
	for (int i = 0; i < todoSize; i++)
	{
		if (todos[i].title[0] != '\0') {
			// Create temp variable to store formatted string
			char text[100];
			// Format the string
			sprintf_s(text, "\n%d\t%s", todos[i].id, todos[i].title);
			// Append the formatted string to todosDisplay
			strcat_s(todosDisplay, text);
			todoCount++;
		}
	}
	printf("ID\tTitle");
	printf(todosDisplay);
}

int getLastIndexTodo()
{
	int lastIndex = NULL;
	int todosSize = sizeof(todos) / sizeof(todos[0]);
	for (int i = 0; i < todosSize; i++)
	{
		if (todos[i].title[0] == '\0') {
			lastIndex = i;
			break;
		}
	}
	return lastIndex;
}

void createTodo() {
	// Create temp text
	char text[25];
	// Ask for todo title
	printf("Title of the todo: ");

	// Get user input
	fgetc(stdin);
	fgets(text, sizeof(text), stdin);
	text[strlen(text) - 1] = 0;

	// Get last index 
	int lastIndex = getLastIndexTodo();

	// Create a new todo
	todos[lastIndex].id = lastIndex;
	strcpy_s(todos[lastIndex].title, text);
	
	// Print new todo
	printf("Added: %s", todos[lastIndex].title);
}

int getIndexByTodoId(int todoId)
{
	int index = NULL;
	int todoSize = sizeof(todos) / sizeof(todos[0]);
	for (int i = 0; i < todoSize; i++) {
		if (todos[i].id == todoId)
		{
			return i;
		}
	}
	return index;
}

void removeTodo() {
	int todoId = NULL;
	
	readTodos();

	int lastIndex = getLastIndexTodo();
	if (lastIndex > 0) {
		printf("\nWhat todo would you like to remove: ");
		scanf_s("%d", &todoId);
		int todoIndex = getIndexByTodoId(todoId);
		// Create a struct of the todo we want to delete
		struct Todo deletedTodo = todos[todoIndex];
		
		// Overwrite the todo we want to delete by shifting the todos on to it and sorting
		int todoSize = sizeof(todos) / sizeof(todos[0]);
		for (int i = todoIndex; i < todoSize - 1; i++) {
			todos[i] = todos[i + 1];
		}

		clearConsole();
		printf("You have removed %s\n\n", deletedTodo.title);
		readTodos();
		lastIndex = getLastIndexTodo();
	}
	else {
		printf("\n\nThere aren't any todos to delete");
	}

}

void updateTodo()
{
	int todoId = NULL;

	readTodos();

	int lastIndex = getLastIndexTodo();
	if (lastIndex > 0) {
		printf("\nWhat todo would you like to update: ");
		scanf_s("%d", &todoId);
		int todoIndex = getIndexByTodoId(todoId);
		char text[25];
		printf("\nWhat would you like to change the title to: ");
		
		// Get user input
		fgetc(stdin);
		fgets(text, sizeof(text), stdin);
		text[strlen(text) - 1] = 0;

		// Copy text (from input) into the current todo
		strcpy_s(todos[todoIndex].title, text);

		clearConsole();
		printf("You have updated %s\n\n", todos[todoIndex].title);
		readTodos();
	}
	else {
		printf("\n\nThere aren't any todos to update");
	}
}

void backOption() {
	int action;
	do {
		printf("\n\nEnter 0 to go back to the menu: ");
		scanf_s("%d", &action);
	} while (action != 0);
	clearConsole();
}

