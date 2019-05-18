#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int strlen(char* str){
	int i = 0;
	if (str == NULL){
		return 0;
	}
	while (true){
		if (str[i] == '\0'){
			break;
		}
		i = i + 1;
	}
	return i;
}

int getnumber(char c){
	if (c == '1'){
		return 1;
	}
	else if (c == '2'){
		return 2;
	}
	else if (c == '3'){
		return 3;
	}
	else if (c == '4'){
		return 4;
	}
	else if (c == '5'){
		return 5;
	}
	else if (c == '6'){
		return 6;
	}
	else if (c == '7'){
		return 7;
	}
	else if (c == '8'){
		return 8;
	}
	else if (c == '9'){
		return 9;
	}
	else if (c =='0'){
		return 0;
	}
}

int strtoint(char* s){
	int n = strlen(s);
	int sum = 0;
	for (int i = 0; i < n; i++){
		sum = sum * 10 + getnumber(s[i]);
	}
	return sum;
}


char* subString(char* source, int start, int end){
	char* result = (char*)malloc(sizeof(char)*(end - start + 1));
	int result_count = 0;
	for (int i = start; i <= end; i++){
		result[result_count++] = source[i];
	}
	result[result_count] = '\0';
	return result;
}

char* strconcat(char* s1, char* s2){
	int total = strlen(s1) + strlen(s2);
	char* res = (char*)malloc(sizeof(char)*(total + 1));
	int i = 0;
	for (i = 0; i < strlen(s1); i++){
		res[i] = s1[i];
	}
	for (int j = 0; j < strlen(s2); j++){
		res[i++] = s2[j];
	}
	res[i] = '\0';
	return res;
}

int strcmp(char* s1, char* s2){
	if (strlen(s1) == strlen(s2)){
		for (int i = 0; i < strlen(s1); i++){
			if (s1[i] != s2[i]){
				return -1;
			}
		}
		return 0;
	}
	else{
		return -1;
	}
}

void strcpy(char* s1, char* s2){
	int len = strlen(s2);
	int i;
	for (i = 0; i < len; i++){
		s1[i] = s2[i];
	}
	s1[i] = '\0';
}


bool ifInside(char ch, char* delim){
	for (int i = 0; i < strlen(delim); i++){
		if (delim[i] == ch){
			return true;
		}
	}
	return false;
}

char** mystrtok(char* str, char* delim){
	int len = strlen(str);
	int count = 0;
	for (int i = 0; i < len; i++){
		if (ifInside(str[i], delim) && i != (len - 1)){
			count++;
		}
	}
	count++;

	char** result = (char**)malloc(sizeof(char*)*count);
	int result_count = 0;
	int pre = 0;
	for (int i = 0; i < len; i++)
	{
		if (ifInside(str[i], delim) && i != (len - 1)){
			result[result_count++] = subString(str, pre, i);
		}
		pre = i;
	}
	return result;
}



char* strip(char* s){
	int count = 0;
	int i;
	for (i = 0; i < strlen(s); i++){
		if (s[i] == '\n' || s[i] == '\t' || s[i] == ' '){
			continue;
		}
		count++;
	}
	char* res = (char*)malloc(sizeof(char)*(count + 1));
	for (i = 0; i < count; i++){
		if (s[i] == '\n' || s[i] == '\t' || s[i] == ' '){
			continue;
		}
		res[i] = s[i];
	}
	res[i] = '\0';
	return res;

}