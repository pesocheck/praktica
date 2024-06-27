#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <locale.h>

#define SIZE 100

void writeFile(int size)
{
    int min = -1000;
    int max = 1000;
    srand(time(0));

    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", (rand() % (max - min + 1) + min));
    }

    fclose(file);
}

void writeFileData(int* numbers, int size)
{
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", numbers[i]);

    }
    fclose(file);
}

int readFile(const char* filename, int* numbers, int* count, int size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    *count = 0;

    while (fscanf(file, "%d", &numbers[*count]) == 1 && *count < size) {
        (*count)++;
    }

    fclose(file);
    return 0;
}

void insertion_sort(int arr[], int n)
{
    clock_t start_time = clock();

    int i, j, temp;

    for (i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = temp;
    }

    
    clock_t end_time = clock(); 
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    

    FILE* fp = fopen("time.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%.3f seconds", elapsed_time);
        fclose(fp);
    }
    else {
        printf("Error opening file!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int choice;
    int size = 0;
    int* m = nullptr;
    int count;
    char buffer[256];


    while (1) {
        FILE* fp = fopen("time.txt", "r");
        if (fp != NULL) {
            fgets(buffer, 256, fp);
            fclose(fp);
        }
        printf("Выбор действия:\n");
        printf("1. Ввести размер массива\n");
        printf("2. Создать рандомную последовательность и записать в файл\n");
        printf("3. Прочитать данные из файла\n");
        printf("4. Отсортировать список используя метод Шейкерной сортировки\n");
        printf("5. Загрузить отсортированные данные в файл\n");
        printf("6. Выход                                                                   Последняя сортировка заняла: %s\n", buffer);
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:

            printf("Введите размер массива\n");
            std::cin >> size;
            m = new int[size];
            break;
        case 2:
            writeFile(size);
            printf("Данные записанный в файл.\n");
            break;
        case 3:
            if (!m)
            {
                printf("Укажите размер массива");
                std::cin.get();
                std::cin.get();
            }
            else {
                readFile("input.txt", m, &count, size);
                printf("Данные прочитанный с файла.\n");
            }
            break;
        case 4:
            insertion_sort(m, size);
            printf("Данные отсортированный.\n");
            break;
        case 5:
            writeFileData(m, size);
            printf("Данные записанны в файл.\n");
            break;
        case 6:
            delete[] m;
            return 0;
        default:
            printf("Ошибка.\n Попробуте снова.\n");
        }
        system("cls");

    }
    return 0;
}