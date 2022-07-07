#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char * name;
    char * id_num;
    int salary;
    struct node * next;
}employee;

employee * addEmployee(char * name, char * id_num, int salary, employee* head);
int idCmp(char * id1, char * id2);
employee * createEmployee(char * name, char * id_num, int salary, employee * pointer);


int main()
{
    employee * head = NULL;
    head = addEmployee("Alan", "123456789", 23000, head);
    employee * newEmployee2 = addEmployee("Maria", "214365978", 23000, head);
    employee * newEmployee3 = addEmployee("Caro", "432187659", 23000, head);
    while(head->next != NULL){
    printf("%s %s %d\n", head->name, head->id_num, head->salary);
    head = head->next;
    }
    if(head == NULL) return 1;

    return 0;
}

employee * addEmployee(char * name, char * id_num, int salary, employee * pointer){
    if(pointer == NULL){
        employee * current = createEmployee(name, id_num, salary, pointer);
        return current;
    }
    employee * current = pointer;
    while(current->next != NULL){
        if(idCmp(id_num, current->id_num) == 1){ // if param id is greater than current id
                if(idCmp(id_num, current->next->id_num) == 0){
                    employee * newEmployee = createEmployee(name, id_num, salary, pointer);
                    newEmployee->next = current->next;
                    current->next = newEmployee;
                    return newEmployee;
                }
                current = current->next;
                continue;
        }
    }
        employee * newEmployee = createEmployee(name, id_num, salary, pointer);
        current->next = newEmployee;
        return newEmployee;
}

int idCmp(char * id1, char * id2){
    if(strlen(id1)>strlen(id2)){
        return 1;
    }
    if(strlen(id1)<strlen(id2)){
        return 0;
    }
    for(int i=0; i<9; i++){
        if(id1[0] == id2[0]){
            continue;
        }
        else if(id1[0] > id2[0]){
            return 1;
        }
        else {
            return 0;
        }
    }

    return -1;
}

employee * createEmployee(char * name, char * id_num, int salary, employee * pointer){
    employee * newEmployee = NULL;
    newEmployee = (employee *) malloc(sizeof(employee));
    newEmployee->id_num = id_num;
    newEmployee->name = name;
    newEmployee->salary = salary;
    if(pointer == NULL){
        newEmployee->next = NULL;
        return newEmployee;
    }
    if(pointer->next != NULL){
        newEmployee->next = pointer->next;
    }else{
        newEmployee->next = NULL;
    }
    return newEmployee;
}


