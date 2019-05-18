#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//#include "mysString.h"
#include<string.h>
#include "btree.h"




int main(){
	
	struct data_page** dp;
	struct student** s;
	struct index_page** ip;
	char page_buffer[128]; char buff[36];
	char unusedchar[20] = { '0' };
	char unusedname[32] = { '0' };
	dp = (data_page**)malloc(sizeof(data_page**)*16);
	for (int i = 0; i < 16; i++){
		dp[i] = (data_page*)malloc(sizeof(data_page));
	}

	s = create_student_array("randomuserdata.csv", 768);
	//write_datapage_to_file(dp, 16, "target.txt");
	//display_datapage(dp,256);

	//load_index_page();

	//display_content_file("target.txt");



	

	getchar();
	return 0;
}








