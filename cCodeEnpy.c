#include <stdio.h>
#include <string.h>

const char *keyWords[] = {
"stdio",
"include", "struct", "enum",
"void","char","short","int","long","double","float","unsigned","main",
"define","typedef","volatile","const","for","if","else","switch","case","default","sizeof",
"break","return","printf","fopen","fread","fwrite","fclose","feof","malloc",
"free","strcpy","strchr","strstr","memset",
};
int main(void)
{
	FILE *fin = fopen("./source.c", "r");
	if (!fin) {
		printf("open file %s fail.\n", "source.c");
		return -1;
	}	
	FILE *fout = fopen("./enpy.c", "w");
	if (!fout) {
		printf("creat file %s fail.\n", "enpy.c");
		fclose(fin);
		return -1;
	}

	char functionOrParmStr[100];
	char strLen = 0;
	memset(functionOrParmStr, 0, sizeof(functionOrParmStr));
	char ch = fgetc(fin);
	while(!feof(fin)){
		if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) ) {
			functionOrParmStr[strLen++] = ch;
		} else {
			if (strLen > 1) {
				char isKeyWords = 0;
				for (int i=0; i<sizeof(keyWords)/sizeof(keyWords[0]); i++) {
					if (0==strcmp(functionOrParmStr, keyWords[i])) {
						isKeyWords = 1;
					}
				}
				if (!isKeyWords) {
					for (int i=0; i<strLen; i++) {
						if (functionOrParmStr[i] == 'z') 
							functionOrParmStr[i] = 'a';
						else if (functionOrParmStr[i] == 'Z') 
							functionOrParmStr[i] = 'A';
						else 
							functionOrParmStr[i] += 1;
					}
				}
			}
			fwrite(functionOrParmStr, 1, strLen, fout);
			strLen = 0;
			memset(functionOrParmStr, 0, sizeof(functionOrParmStr));
			fputc(ch, fout);
		}
		ch = fgetc(fin);
	}
	fclose(fout);
	fclose(fin);
}
