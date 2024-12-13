#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100  // 학생 수의 최대값

// 학생 정보를 저장할 구조체 정의
typedef struct {
    char name[50];  // 학생 이름
    int korean;     // 국어 점수
    int english;    // 영어 점수
    int math;       // 수학 점수
    int total;      // 총점
    float average;  // 평균
    int rank;       // 등수
} Student;

// 함수 선언
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

    // 프로그램이 시작될 때 데이터 파일에서 학생 정보 읽기
    readDataFromFile(students, &studentCount);

    while (1) {
        printMenu();
        printf("선택(1~5): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // .dat 파일에서 데이터 읽기
            readDataFromFile(students, &studentCount);
            break;
        case 2:
            // 추가 학생 정보 입력
            inputStudentData(students, &studentCount);
            break;
        case 3:
            // .dat 파일 저장
            writeDataToFile(students, studentCount);
            break;
        case 4:
            // 성적 확인 (평균 계산 등)
            displayScores(students, studentCount);
            break;
        case 5:
            // 프로그램 종료
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }

    return 0;
}

// 메뉴 출력 함수
void printMenu() {
    printf("\n[Menu]\n");
    printf("1. .dat 파일에서 데이터 읽기\n");
    printf("2. 추가 학생 정보 입력\n");
    printf("3. .dat 파일 저장\n");
    printf("4. 성적 확인 (평균 계산 등)\n");
    printf("5. 종료\n");
}

// .dat 파일에서 데이터 읽기
void readDataFromFile(Student students[], int* studentCount) {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일에서 학생 데이터 읽기
    fread(studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), *studentCount, file);
    fclose(file);

    printf(".dat 파일에서 데이터를 읽었습니다. 총 %d명의 학생 정보가 있습니다.\n", *studentCount);
}

// .dat 파일에 데이터 저장하기
void writeDataToFile(Student students[], int studentCount) {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 학생 수와 학생 데이터를 파일에 저장
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);

    printf(".dat 파일에 데이터를 저장했습니다.\n");
}

// 추가 학생 정보 입력하기
void inputStudentData(Student students[], int* studentCount) {
    if (*studentCount >= MAX_STUDENTS) {
        printf("학생 수가 최대치를 초과했습니다.\n");
        return;
    }

    Student newStudent;

    // 학생 이름과 성적 입력 받기
    printf("학생 이름: ");
    scanf("%s", newStudent.name);
    printf("국어 점수: ");
    scanf("%d", &newStudent.korean);
    printf("영어 점수: ");
    scanf("%d", &newStudent.english);
    printf("수학 점수: ");
    scanf("%d", &newStudent.math);

    // 총점과 평균 계산
    calculateTotalAndAverage(&newStudent);

    // 학생 배열에 추가
    students[*studentCount] = newStudent;
    (*studentCount)++;

    printf("새로운 학생 정보가 추가되었습니다.\n");
}

// 성적 확인 및 평균, 총점, 등수 계산 후 출력
void displayScores(Student students[], int studentCount) {
    if (studentCount == 0) {
        printf("학생 정보가 없습니다.\n");
        return;
    }

    // 등수 계산
    calculateRank(students, studentCount);

    // 성적 출력
    printf("\n%-15s%-8s%-8s%-8s%-8s%-8s%-8s\n", "이름", "국어", "영어", "수학", "총점", "평균", "등수");
    for (int i = 0; i < studentCount; i++) {
        printf("%-15s%-8d%-8d%-8d%-8d%-8.2f%-8d\n",
            students[i].name, students[i].korean, students[i].english, students[i].math,
            students[i].total, students[i].average, students[i].rank);
    }
}

// 총점과 평균 계산 함수
void calculateTotalAndAverage(Student* student) {
    student->total = student->korean + student->english + student->math;
    student->average = student->total / 3.0;
}

// 학생들의 등수 계산 함수
void calculateRank(Student students[], int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        students[i].rank = 1;  // 기본적으로 1등으로 설정
        for (int j = 0; j < studentCount; j++) {
            if (students[i].total < students[j].total) {
                students[i].rank++;  // 총점이 낮으면 등수를 하나씩 증가
            }
        }
    }
}
