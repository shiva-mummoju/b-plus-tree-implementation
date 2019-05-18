#include "mysString.h"
#include<stdlib.h>


#define PAGE_SIZE 128


struct student{
	int id;
	char name[32];
};

struct data_page{
	struct student data[3];
	char unused[20];
};


struct index_page{
	int page_id[16];
	int key[15];
	char unused[4];
};

struct marks{
	int sid;
	int subid;
	int mark[4];
};

struct data_page_one{
	char pt;
	char tid;
	char unused[18];
	student data[3];
};

struct data_page_two{
	char pt;
	char table_id;
	char unused[6];
	marks data[6];
};

struct table_page{
	char page_type;
	char table_id;
	char unused[6];
	int rootpageid[10];
	char table_name[10][8];
};

int data_page_count = 0;
int current_offset = 0;
int num_pages_in_pre_level = 0;
int num_pages_in_current_level = 0;
int level = 0;
int total_number_of_pages = 0;

void copy_student_to_datapage_array(student** s, int s_count, data_page** dp, int d_count);
data_page** create_datapage_array(int n);
void write_datapage_to_file(data_page** dp, int count, char* filename);
void load_index_page();

student** create_student_array(char* filename, int number){
	
	student** s = (student**)malloc(sizeof(student*) * 3);
	int i = 0;
	char buff[1000];
	FILE* f = fopen(filename, "r");
	fscanf(f, "%s", buff);
	for ( i = 0; i < number; i = i +3){
		
		s = (student**)malloc(sizeof(student*) * 3);
		
		for (int j = 0; j < 3; j++){
			s[j] = (student*)malloc(sizeof(student));
			s[j]->id = 0;
		}
		int p = 0;
		for ( p = 0; p < 3 && i+p< number; p++){
			fscanf(f, "%s", buff);
			char* token = strtok(buff, ",");
			s[p]->id = strtoint(token);
			//printf("%d\n", s[j]->id);
			token = strtok(NULL, ",");
			strcpy(s[p]->name, token);
			//printf("%d %s\n", s[p]->id, s[p]->name);
		}
		

		data_page** dp = create_datapage_array(1);
		copy_student_to_datapage_array(s, p, dp, 1);
		free(dp);
		free(s);
	}
	

	fclose(f);

	num_pages_in_pre_level = data_page_count;
	level = 1;
	load_index_page();
	return s;
}




data_page** create_datapage_array(int number){
	data_page** dp = (data_page**)malloc(sizeof(data_page*)*number);
	for (int i = 0; i < number; i++){
		dp[i] = (data_page*)malloc(sizeof(data_page));
	}
	return dp;
}


void copy_student_to_datapage_array(student** s,int s_count,data_page** dp,int d_count){
	int count = 0;
	int p = 0;
	for (int i = 0; i < d_count; i++){
		for (int j = 0; j < 3; j++){
			if (p > s_count){
				dp[i]->data[j].id = 0;
				continue;
			}
			dp[i]->data[j] = *s[p++];
		}
		for (int k = 0; k < 20; k++){
			dp[i]->unused[k] = '0';
		}
	}

	write_datapage_to_file(dp, s_count, "target.txt");
}



void write_datapage_to_file(data_page** dp, int count, char* filename){

	FILE* t = fopen(filename, "ab");
	data_page_count++;
	total_number_of_pages++;
	for (int i = 0; i < count; i++){
		//printf(" writing %d %s\n", dp[0]->data[i].id, dp[0]->data[i].name);
	}
	fwrite(*dp, sizeof(data_page), 1, t);
	fclose(t);
}




index_page* create_index_page(int number){
	index_page* ip = (index_page*)malloc(sizeof(index_page)*number);
	return ip;
}

void display_content_file(char* filename){
	data_page** dp = (data_page**)malloc(sizeof(data_page**)*16);
	for (int i = 0; i < 16; i++){
		dp[i] = (data_page*)malloc(sizeof(data_page));
	}


	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 3; j++){
		//	printf("%d %s\n", dp[i]->data[j].id, dp[i]->data[j].name);

		}
	}

	//fclose(f);
	
}

//void copy_datapage_offset_indexpage(data_page** dp, int d_count, index_page** ip){
//	for (int i = 0; i < d_count; i++){
//		(*ip)->key
//	}
//}


void display_datapage(data_page** dpd,int number){

	data_page* dp = (data_page*)malloc(sizeof(data_page) * number);
	FILE* f = fopen("target.txt", "rb");
	char c = 0;
	

	fread(dp, sizeof(data_page), number, f);

	for (int i = 0; i < number; i++){
		for (int k = 0; k < 3; k++){
			printf("%d %s\n", dp[i].data[k].id, dp[i].data[k].name);
		}
	}

	fclose(f);
}



void load_index_page(){
	int printing_count = 0;
	printf("Load index page called:  \n" );
	
	if (num_pages_in_pre_level < 16){
		return;
	}
	printf("num of pages in pre level: %d\n", num_pages_in_pre_level);




	FILE* f_read = fopen("target.txt", "rb"); 
	FILE* f_write = fopen("target.txt", "ab");

	index_page** ip = (index_page**)malloc(sizeof(index_page*) * 1);
	*ip = (index_page*)malloc(sizeof(index_page) * 1);
	
	data_page** dp = (data_page**)malloc(sizeof(data_page*)*1);
	*dp = (data_page*)malloc(sizeof(data_page) * 1);

	index_page** input = (index_page**)malloc(sizeof(index_page*) * 1);
	*input = (index_page*)malloc(sizeof(data_page) * 1);
	
	memset(*ip, 0, sizeof(index_page*));
	memset(*dp, 0, sizeof(data_page*));
	memset(*input, 0, sizeof(index_page));
	
	
	//calcuating the number of nodes required in this level
	num_pages_in_current_level = num_pages_in_pre_level / 16 ;
	if (num_pages_in_pre_level % 16 > 0){
		num_pages_in_current_level++;
	}

	printf("Number of pages in current level: %d\n", num_pages_in_current_level);

	int local_count_pre_pages =0;
	
	printf("Current offset recorded as: %d\n", current_offset);
	//take the reading head to the current offset position

	printf("doing fseek till current offset: %d\n", current_offset);
	fseek(f_read, current_offset, SEEK_SET);
	

	if (level <= 1){

		//reading the first pages which should be ignored
		fread(*dp, sizeof(data_page), 1, f_read);
		ip[0]->page_id[0] = current_offset;
		local_count_pre_pages++;
		current_offset = current_offset + 128;

		

		//loop till all the pages in the current level is added
		for (int i = 0; i < num_pages_in_current_level; i++){
			int k = 0;

			if (i != 0){
				fread(*dp, sizeof(data_page), 1, f_read);
				ip[0]->page_id[0] = current_offset;
				current_offset = current_offset + 128;
				//local_count_pre_pages++;
			}


			for ( k = 0; k < 15 && local_count_pre_pages< num_pages_in_pre_level ; k++){

				if (fread(*dp, sizeof(data_page), 1, f_read)){
					
					ip[0]->key[k] = dp[0]->data[0].id;
					ip[0]->page_id[k+1] = current_offset;
					current_offset = current_offset + PAGE_SIZE;
					local_count_pre_pages++;

				}
			}

					//printf("%d", printing_count);
					printing_count++;
					for (int d = 0; d < 16 ; d++){
						printf(" %d %d\n", ip[0]->page_id[d], ip[0]->key[d]);
					}
					printf("\n");
					total_number_of_pages++;
					
					//add this page to the store using the f_write 
					fwrite(*ip, sizeof(index_page), 1, f_write);
			
		}

		if (num_pages_in_pre_level % 16 == 0){
			level++;
			printf("incrementing level. level is now: %d", level);
		}
	}
	else{
		//we are talking about the next level. index nodes created from index nodes.
		//reading the first pages which should be ignored
		fseek(f_read, (total_number_of_pages - num_pages_in_pre_level ) * 128, SEEK_SET);

		current_offset = (total_number_of_pages - num_pages_in_pre_level)*128;

		printf("totl number of pages: %d total number of pages in pre level: %d\n", total_number_of_pages, num_pages_in_pre_level);

		printf("In the second level\n");
		//reading the first pages which should be ignored
		fread(*input, sizeof(index_page), 1, f_read);
		ip[0]->page_id[0] = current_offset;
		//local_count_pre_pages++;
		current_offset = current_offset + 128;



		//loop till all the pages in the current level is added
		for (int i = 0; i < num_pages_in_current_level; i++){
			int k = 0;

			if (i != 0){
				fread(*input, sizeof(index_page), 1, f_read);
				ip[0]->page_id[0] = current_offset;
				current_offset = current_offset + 128;
				local_count_pre_pages++;
			}


			for (k = 0; k < 15 && local_count_pre_pages< num_pages_in_pre_level; k++){

				if (fread(*input, sizeof(index_page), 1, f_read)){

					ip[0]->key[k] = input[0]->key[0];
					ip[0]->page_id[k + 1] = current_offset;	
					current_offset = current_offset + PAGE_SIZE;
					local_count_pre_pages++;

				}
			}

			//printf("%d", printing_count);
			printing_count++;
			for (int d = 0; d < 16; d++){
				printf(" %d %d\n", ip[0]->page_id[d], ip[0]->key[d]);
			}
			printf("\n");
			total_number_of_pages++;

			//add this page to the store using the f_write 
			fwrite(*ip, sizeof(index_page), 1, f_write);

		}

		if (num_pages_in_pre_level % 16 == 0){
			level++;
			printf("incrementing level. level is now: %d", level);
		}


	}
	
	fclose(f_read);
	fclose(f_write);

	//the current no of pages become the pre no of pages
	num_pages_in_pre_level = num_pages_in_current_level;

	printf("done.\n");

	if (num_pages_in_pre_level > 1){
		// we need to add another index page
		printf("calling load index again\n");
		load_index_page();
	}
	else{
		return;
	}


}