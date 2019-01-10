#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80

int main() {

	FILE  *fp1 = fopen("harry.txt", "r");
	FILE  *fp2 = fopen("aligned.txt", "w");

	char ch; //�ܾ� �Է�
	char buffer[MAX]; //�Է����� �� ��
	char * words[MAX]; //������� �� �� -> �ܾ��
	char *token;  //��ū

	int words_i = 0, length = 0; //�ܾ��&���ڼ�
	int index = 0; //�Է����� index
	int flag = 0;
	while (feof(fp1) == 0) //�Ѵܾ �Է¹޴´�
	{
		if (flag == 1) {
			index = 0;
			flag = 0;
		}
		fscanf(fp1, "%c", &ch);
		buffer[index++] = ch; //buffer��� �迭�� ���� ������ -> �Է������� �� ��

		if (ch == '\n') { //�ٹٲ� ���ڰ� ���� �� 
			flag = 1;
			buffer[index - 1] = '\0'; //�Է����Ͽ����� �� ���� �������ֱ� ���� �ι��ڸ� �־ ���� ��������

			token = strtok(buffer, " "); //-> �Է� ������ �� ���� ������ �� strtok �� �ܾ���� ������

			while (token != NULL) { //�Է������� �� ���� ����
				length += strlen(token) + 1; //��������� �� ���� �ܾ� ���� -> ������ �ܾ�� ������ �߰��� ���̷� �ν�
				words[words_i++] = strdup(token); //��������� �� �� �ܾ� ����

				if (length - 1 > 80) { //���� length�� 80���� Ŀ����
					length -= strlen(token) + 2; //�Ʊ� ���������� ���� + �ձ����� ���� ����ؼ� -2��
					int L = (80 - length) / (words_i - 2);
					for (int i = 0; i < words_i - 2; i++) {
						fprintf(fp2, "%s", words[i]);
						if ((L <= 0 && i < 80 - length) || (L > 0 && i < (80 - length) % (words_i - 2))) {
							for (int j = 0; j <= L + 1; j++)
								fprintf(fp2, " ");
						}
						else
							for (int j = 0; j <= L; j++)
								fprintf(fp2, " ");
					}
					fprintf(fp2, "%s\n", words[words_i - 2]); // ������ ���ڴ� ���� XX
					length = strlen(token) + 1; //length �ٽ�
					words_i = 0; //�ʱ�ȭ
					words[words_i++] = strdup(token); //�ٽ� ����
				}
				token = strtok(NULL, " "); //������� �� �� ������
			}
		}
	}

	// ��������
	for (int i = 0; i < words_i; i++)
		fprintf(fp2, "%s ", words[i]);

	fclose(fp1);
	fclose(fp2);

}