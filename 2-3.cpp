
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#define BUFFER_SIZE 1000
char *words[BUFFER_SIZE];
char write[BUFFER_SIZE];
char buf[BUFFER_SIZE];
char buf2[BUFFER_SIZE];
int main() 
{
	int leng = 0, i = 0, jump = 0;
	FILE *fp = fopen("har.txt", "r");
	FILE *fp_out = fopen("words2.txt", "w");
	while (1) {
		if (leng < 80) {
			strcpy(buf2, buf);
			leng += strlen(buf) + 1;
			words[i] = strdup(buf);
			//마지막줄
			if (fscanf(fp, "%s", buf) == EOF) {
				for (int j = 0; j < i+1; j++) {
					strcat(write, words[j]);
					if (j < i)
						strcat(write, " ");
				}
				fprintf(fp_out, "%s\n", write);
				break;
			}
			//
			i++;
		}
		else if (leng == 80) {
				i--;
			for (int j = 0; j < i+1 ; j++) {
				strcat(write, words[j]);
				if (j == 0)
					strcat(write, "  ");
				else if (j < i)
					strcat(write, " ");
			}
			fprintf(fp_out, "%s\n", write);

			for (int i = 0; i < BUFFER_SIZE; i++)
				words[i] = { '\0' };
			i = 1, leng = strlen(buf)+1, write[0] = {'\0'};
			words[0] = strdup(buf);
		}
		else {//		
			jump = 80 - (leng - strlen(buf2) - 1);
			i--;
			for (int j = 0; j < i ; j++) {
				strcat(write, words[j]);
				if (jump >=0&&j<i) {
					strcat(write,"  ");
					jump--;
				}
				else if(j<i)
					strcat(write," ");
			}
			fprintf(fp_out, "%s\n", write);
			for (int i = 0; i < BUFFER_SIZE; i++)
				words[i] = {'\0'};
			i = 2, leng = strlen(buf) + 1+strlen(buf2)+1;
			words[0] = strdup(buf2);
			words[1] = strdup(buf);
			buf2[0] = { '\0' };
			write[0] = { '\0' };
		}
	}
	fclose(fp), fclose(fp_out);
	return 0;
}