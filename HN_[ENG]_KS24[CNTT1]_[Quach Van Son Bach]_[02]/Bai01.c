//
// Created by Macbook on 16/07/2025.
//
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//
// Id (integer) – Mã của một nhiệm vụ
// Type (string) – Loại hoạt động
// Duration (integer) – Thời gian thực hiện hoạt động
// Calories (integer) – Số calo tiêu thụ
// Date (string) – Thời gian thực hiện hoạt động


typedef struct {
    int id;
    char *type;
    int duration;
    int calories;
    char *  date;
}Activity;


typedef struct Node {
    Activity infor;
    struct Node* next;
}Node;


Node *createNode(const int id, const char *type, const int duration, const int calories, const char *date) {
    Node *newNode  = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error\n");
        return NULL;
    }


    newNode -> infor.date = (char *)malloc(strlen(date) *sizeof(char));
    newNode -> infor.type = (char *)malloc(strlen(type) *sizeof(char));
    strcpy(newNode -> infor.date , date);
    strcpy(newNode -> infor.type , type);
    newNode -> infor.id = id;
    newNode -> infor.duration = duration;
    newNode -> infor.calories = calories;

    newNode -> next = NULL;
    return newNode;
}


// Thêm hoạt động trong ngày
Node *addActivity(Node *activity);
// Hiển thị danh sách hoạt động

void showAllActivity(const Node *activity);
// Xóa hoạt động
Node *deleteAc(Node *activity);
// Cập nhật thông tin hoạt động
Node *updateInfor(Node *activity);
// Thống kê tổng  tiêu thụ/ngày
void sumCaloriesOnDay(const Node *activity);
// Sắp xếp hoạt động
void SortByCalories(const Node *activity);
// Tìm kiếm hoạt động
void findActivityByType(const Node *activity);
// Thoát chương trình

int main(void) {
    int choice;
    Node *activity = NULL;


    do {
        printf("---------------MENU-------------\n");
        printf("1. Thêm hoạt động trong ngày\n");
        printf("2. Hiển thị danh sách hoạt động\n");
        printf("3. Xóa hoạt động\n");
        printf("4. Cập nhật thông tin hoạt động\n");
        printf("5. Thống kê tổng calories tiêu thụ/ngày\n");
        printf("6.Sắp xếp hoạt động \n");
        printf("7.Tìm kiếm hoạt động\n");
        printf("8. Thoát chương trình \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                activity = addActivity(activity);
                break;
            case 2:
                showAllActivity(activity);
                break;
            case 3:
                activity = deleteAc(activity);
                break;
            case 4:
                activity = updateInfor(activity);
                break;
            case 5:
                sumCaloriesOnDay(activity);
                break;
            case 6:
                SortByCalories(activity);
                break;
            case 7:
                findActivityByType(activity);
                break;
            case 8:
                free(activity);
                break;

            default:
                printf("invalid\n");
                break;
        }


    }while ( choice != 8);

    return 0;
}


Node *addActivity(Node *activity) {
    int id, Duration, Calories;
    char Type[30];
    char date[30];

    printf("------ADD Activity------\n");
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    printf("Type: ");
    fgets(Type, sizeof(Type), stdin);
    Type[strlen(Type) - 1] = '\0';

    printf("Duration: ");
    scanf("%d", &Duration);

    printf("Calories: ");
    scanf("%d", &Calories);
    getchar();

    printf("Date: ");
    fgets(date, sizeof(date), stdin);
    date[strlen(date) - 1] = '\0';

    Node *newNode = createNode(id, Type, Duration, Calories, date);
    if (newNode == NULL) {
        printf("Add failed!\n");
        return activity;
    }

    printf("Add success!\n");


    if (activity == NULL) {
        return newNode;
    }

    Node *current = activity;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return activity;
}










void showAllActivity(const Node *activity) {

    if (activity == NULL) {
        printf("Activity list is empty !!\n");
    }


    const Node *current = activity;
    printf("-------------Activity list----------\n");
    int i = 1;
    while (current != NULL) {
        printf("%d. ID: %4d | Type: %10s | Duration: %4d | Calories: %4d | Date %10s \n", i++,
            current -> infor.id, current -> infor.type, current -> infor.duration, current -> infor.calories, current -> infor.date);
        current = current -> next;
    }

    printf("-------------END----------\n");



}

Node *deleteAc(Node *activity) {
    if (activity == NULL) {
        printf("Activity list is empty !!\n");
        return activity;
    }
    int id;
    printf("Enter the id to delete: ");
    scanf("%d", &id);

    if (activity -> infor.id == id) {
        Node *temp = activity;
        activity = temp -> next;
        free(temp->infor.type);
        free(temp->infor.date);
        free(temp);
        return activity;
    }


    Node *prev = activity;
    Node *current = activity -> next;
    while (current != NULL) {
        if (current -> infor.id == id ) {
            prev -> next = current -> next;
            free(current->infor.type);
            free(current->infor.date);
            free(current);
            printf("Deleted activity with ID %d\n", id);
            return activity;

        }
        prev = current;
        current = current ->next;

    }
    printf("Don't Have id in list \n");
    return activity;
}



Node *updateInfor(Node *activity) {
    if (activity == NULL) {
        printf("Activity list is empty !!\n");
        return activity;
    }
    int id, Duration, Calories;
    char Type[30];
    char date[30];
    printf("Enter the id to Update: ");
    scanf("%d", &id);


    Node *current = activity;
    if (current == NULL) {
        return activity;
    }
    while (current != NULL) {

        if (current -> infor.id == id) {


            getchar();
            printf("Type to update: ");
            fgets(Type, sizeof(Type), stdin);
            Type[strlen(Type) - 1] = '\0';

            printf("Duration to update: ");
            scanf("%d", &Duration);

            printf("Calories to update: ");
            scanf("%d", &Calories);
            getchar();

            printf("Date to update: ");
            fgets(date, sizeof(date), stdin);
            date[strlen(date) - 1] = '\0';


            strcpy(current -> infor.type, Type);
            strcpy(current -> infor.date , date);
            current -> infor.duration = Duration;
            current -> infor.calories = Calories;
            break;
        }


        current =  current -> next;
    }

    if (current == NULL) {
        printf("don't find id: \n");
    }
    return activity;

}


void sumCaloriesOnDay(const Node *activity) {
    if (activity == NULL) {
        printf("Activity list is empty !!\n");
        return;
    }
    char date[30];
    getchar();
    printf("Enter Date to calculater calories: ");
    fgets(date, sizeof(date), stdin);
    date[strlen(date) - 1] = '\0';

    const Node *current = activity;

    int sum = 0;
    while (current != NULL) {
        if (strcmp(current -> infor.date, date) == 0) {
            sum += current -> infor.calories;
        }

        current = current -> next;
    }

    printf("Total Calories: %d\n", sum);

}



void SortByCalories(const Node *activity) {
    if (activity == NULL) {
        printf("Activity list is empty !!\n");
        return;
    }
    Node *current = activity;

    while(current != NULL) {
        Node* minNode = current;
        Node* nextNode = current->next;

        while (nextNode != NULL) {
            if (nextNode->infor.calories < minNode->infor.calories) {
                minNode = nextNode;
            }
            nextNode = nextNode->next;

        }

        if (minNode != nextNode) {
            const Activity temp = current-> infor;
            current-> infor = minNode -> infor;
            minNode -> infor = temp;

        }
        current = current -> next;
    }
    showAllActivity(activity);

}

void findActivityByType(const Node *activity) {
    if (activity == NULL) {
        printf("Activity list is empty !!\n");
        return;
    }
    char Type[30];
    getchar();
    printf("Type: ");
    fgets(Type, sizeof(Type), stdin);
    Type[strlen(Type) - 1] = '\0';

    const Node *current = activity;

    int i;
    int sum = 0;
    while (current != NULL) {
        if (strcmp(current -> infor.type, Type) == 0) {
            printf("%d. ID: %4d | Type: %10s | Duration: %4d | Calories: %4d | Date %10s \n", i++,
     current -> infor.id, current -> infor.type, current -> infor.duration, current -> infor.calories, current -> infor.date);

            current = current -> next;
        }


    }
}



