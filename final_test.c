#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100  // �л� ���� �ִ밪

// �л� ������ ������ ����ü ����
typedef struct {
    char name[50];  // �л� �̸�
    int korean;     // ���� ����
    int english;    // ���� ����
    int math;       // ���� ����
    int total;      // ����
    float average;  // ���
    int rank;       // ���
} Student;

// �Լ� ����
void readDataFromFile(Student students[], int* studentCount);
void writeDataToFile(Student students[], int studentCount);
void inputStudentData(Student students[], int* studentCount);
void displayScores(Student students[], int studentCount);
void calculateTotalAndAverage(Student* student);
void calculateRank(Student students[], int studentCount);
void printMenu();

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    // ���α׷��� ���۵� �� ������ ���Ͽ��� �л� ���� �б�
    readDataFromFile(students, &studentCount);

    while (1) {
        printMenu();
        printf("����(1~5): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // .dat ���Ͽ��� ������ �б�
            readDataFromFile(students, &studentCount);
            break;
        case 2:
            // �߰� �л� ���� �Է�
            inputStudentData(students, &studentCount);
            break;
        case 3:
            // .dat ���� ����
            writeDataToFile(students, studentCount);
            break;
        case 4:
            // ���� Ȯ�� (��� ��� ��)
            displayScores(students, studentCount);
            break;
        case 5:
            // ���α׷� ����
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �������ּ���.\n");
        }
    }

    return 0;
}

// �޴� ��� �Լ�
void printMenu() {
    printf("\n[Menu]\n");
    printf("1. .dat ���Ͽ��� ������ �б�\n");
    printf("2. �߰� �л� ���� �Է�\n");
    printf("3. .dat ���� ����\n");
    printf("4. ���� Ȯ�� (��� ��� ��)\n");
    printf("5. ����\n");
}

// .dat ���Ͽ��� ������ �б�
void readDataFromFile(Student students[], int* studentCount) {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���Ͽ��� �л� ������ �б�
    fread(studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), *studentCount, file);
    fclose(file);

    printf(".dat ���Ͽ��� �����͸� �о����ϴ�. �� %d���� �л� ������ �ֽ��ϴ�.\n", *studentCount);
}

// .dat ���Ͽ� ������ �����ϱ�
void writeDataToFile(Student students[], int studentCount) {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // �л� ���� �л� �����͸� ���Ͽ� ����
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);

    printf(".dat ���Ͽ� �����͸� �����߽��ϴ�.\n");
}

// �߰� �л� ���� �Է��ϱ�
void inputStudentData(Student students[], int* studentCount) {
    if (*studentCount >= MAX_STUDENTS) {
        printf("�л� ���� �ִ�ġ�� �ʰ��߽��ϴ�.\n");
        return;
    }

    Student newStudent;

    // �л� �̸��� ���� �Է� �ޱ�
    printf("�л� �̸�: ");
    scanf("%s", newStudent.name);
    printf("���� ����: ");
    scanf("%d", &newStudent.korean);
    printf("���� ����: ");
    scanf("%d", &newStudent.english);
    printf("���� ����: ");
    scanf("%d", &newStudent.math);

    // ������ ��� ���
    calculateTotalAndAverage(&newStudent);

    // �л� �迭�� �߰�
    students[*studentCount] = newStudent;
    (*studentCount)++;

    printf("���ο� �л� ������ �߰��Ǿ����ϴ�.\n");
}

// ���� Ȯ�� �� ���, ����, ��� ��� �� ���
void displayScores(Student students[], int studentCount) {
    if (studentCount == 0) {
        printf("�л� ������ �����ϴ�.\n");
        return;
    }

    // ��� ���
    calculateRank(students, studentCount);

    // ���� ���
    printf("\n%-15s%-8s%-8s%-8s%-8s%-8s%-8s\n", "�̸�", "����", "����", "����", "����", "���", "���");
    for (int i = 0; i < studentCount; i++) {
        printf("%-15s%-8d%-8d%-8d%-8d%-8.2f%-8d\n",
            students[i].name, students[i].korean, students[i].english, students[i].math,
            students[i].total, students[i].average, students[i].rank);
    }
}

// ������ ��� ��� �Լ�
void calculateTotalAndAverage(Student* student) {
    student->total = student->korean + student->english + student->math;
    student->average = student->total / 3.0;
}

// �л����� ��� ��� �Լ�
void calculateRank(Student students[], int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        students[i].rank = 1;  // �⺻������ 1������ ����
        for (int j = 0; j < studentCount; j++) {
            if (students[i].total < students[j].total) {
                students[i].rank++;  // ������ ������ ����� �ϳ��� ����
            }
        }
    }
}
