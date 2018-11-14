#include<vector>
#include<algorithm>

using namespace std;

struct Student {
	int number;
	int morality;
	int talent;
	int level;
};

bool compareStudent(Student student1, Student student2) {
	if (student1.level == student2.level) {
		if (student1.morality + student1.talent == student2.morality + student2.talent) {
			if (student1.morality == student2.morality) {
				if (student1.number < student2.number) {
					return true;
				} else {
					return false;
				}
			} else {
				if (student1.morality > student2.morality) {
					return true;
				} else {
					return false;
				}
			}
		} else {
			if (student1.morality + student1.talent > student2.morality + student2.talent) {
				return true;
			} else {
				return false;
			}
		}
	} else {
		if (student1.level < student2.level) {
			return true;
		} else {
			return false;
		}
	}
}

int main() {
	int count;
	int minScore;
	int priorityScore;

	scanf("%d%d%d", &count, &minScore, &priorityScore);

	vector<Student> students;
	Student student;

	for (int i = 0; i < count; i++) {
		int number;
		int morality;
		int talent;

		scanf("%d%d%d", &number, &morality, &talent);

		if (morality >= minScore && talent >= minScore) {
			student.number = number;
			student.morality = morality;
			student.talent = talent;
			if (morality >= priorityScore && talent >= priorityScore) {
				student.level = 1;
			} else if (morality >= priorityScore && talent < priorityScore) {
				student.level = 2;
			} else if (morality < priorityScore && talent < priorityScore && morality >= talent) {
				student.level = 3;
			} else {
				student.level = 4;
			}
			students.push_back(student);
		}
	}
	sort(students.begin(), students.end(), compareStudent);

	printf("%d\n", students.size());
	for (int i = 0; i < students.size(); i++) {
		printf("%d %d %d", students[i].number, students[i].morality, students[i].talent);
		if (i != students.size() - 1) {
			printf("\n");
		}
	}
	return 0;
}

