#include <stdio.h>

int main() {
    int choice;

    while(1) { // Бесконечный цикл, который прерывается только при выборе '3'
        printf("\nMenu:\n");
        printf("1 - Option 1\n");
        printf("2 - Option 2\n");
        printf("3 - Exit\n");
        printf("Enter your choice: ");

        // Считывание введенного пользователем числа
        if(scanf("%d", &choice)!= 1 || choice < 1 || choice > 3) {
            printf("Invalid input Please enter a number between 1 and 3.\n");
            // Очистка буфера ввода, чтобы избежать повторного использования введенных данных
            while(getchar()!= '\n'); 
        } else {
            switch(choice) {
                case 1:
                    printf("Option 1 selected.\n");
                    // Здесь можно добавить код для обработки выбора опции 1
                    break;
                case 2:
                    printf("Option 2 selected.\n");
                    // Здесь можно добавить код для обработки выбора опции 2
                    break;
                case 3:
                    printf("Exiting...\n");
                    return 0; // Завершение программы
                default:
                    printf("Unexpected error occurred.\n");
            }
        }
    }

    return 0;
}
