#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int make_magic(char arr[], int size, int* my_var, int* number_of_blocks, int* flag_error, int* is_in_comment, int* identificators, long* count_ident){
	int i;
	int is_in_string = 0;
	int in_identificator = 0;
	//char ident[50];
	int j = 0;

	for (i = 0; i < size; i++){

		if(*is_in_comment){
			if (arr[i] == '*' && arr[i+1] == '/'){
				(*is_in_comment) = 0;
			} else {
				continue;
			}
		}

		if(is_in_string){
			if ((arr[i] == '\'') || arr[i] == '\"'){
				if (arr[i-1] == '\\') continue;
				is_in_string = 0;
				continue;
			} else {
				continue;
			}
		}

		if ((arr[i] == '_' || isalpha(arr[i])) && !in_identificator) {
			in_identificator = 1;
			(*count_ident)++;
			//ident[j] = arr[i];
			j++;
			continue;
		}

		if(in_identificator){
			if (isdigit(arr[i]) || isalpha(arr[i]) || arr[i] == '_'){

				//ident[j] = '\0';
				//ident[j] = arr[i];
				(*count_ident)++;
				j++;
				continue;

			} else {

				j = 0;
				in_identificator = 0;
				//(*count_ident)++;
			}

		}

		if ((arr[i] == '\'') || (arr[i] == '\"')){
			is_in_string = 1;
			continue;
		}

		if (arr[i] == '/'){
			if(arr[i+1] == '/'){
				break;
			} else if (arr[i+1] == '*') {
				*is_in_comment = 1;
				i+=1;
				continue;
			}
		}

		if (arr[i] == '{'){
			(*my_var)++;
			//printf("%d\n", *my_var);
		}
		if(arr[i] == '}') {
			(*my_var)--;
			//printf("%d\n", *my_var);
			(*number_of_blocks)++;
		}
		if(*my_var < 0) *flag_error = 1;

	}
	return 1;
}

int main(){
	char c;
	int number_of_identifiers = 0;
	int is_in_comment = 0;
	int flag_error = 0;
	int number_of_blocks = 0;
	int my_var = 0;
	char arr[256];
	int counter = 0;
	long count_identificators = 0;

	//Menu variables
	int option = 0;
	char first_name[256];
	char second_name[256];
	FILE *outputFile, *inputFile;
	//End of menu variables

	printf("1. Chetene programata ot fail i zapis na rezultata vyv fail(potrebitelqt trqbva da vyvede imenata na dvata faila, kato faila s programata trqbva da zavyrshva s .C)\n");
	printf("2. Chetene programata ot fail i izvejdane na rezultata na ekrana(failyt, vyveden ot potrebitelq, trqbva da zavyrshva na .C)\n");
	printf("3. Chetene na programata ot klaviatura i izvejdane vyv fail, zadaden ot potrebitelq\n");
	printf("4. Chetene na programata ot klaviaturata i izvejdane na ekrana\n");
	printf("ZA KRAI NATISNETE ENTER + CTRL Z + ENTER\n");

	scanf("%d", &option);

	switch(option){

		case 1: 	printf("Vyvedete pyrvo faila, ot koito shte se chete:");
			while(1){
				scanf("%s", first_name);
				if(!(first_name[strlen(first_name)-1] == 'c' && first_name[strlen(first_name)-2] == '.')){
					printf("Please input a valid name...\n");
					continue;
				}
				break;
			}

			scanf("%s", second_name);

			inputFile = fopen(first_name, "r");
			outputFile = fopen(second_name, "w");

			while(1){
				c = fgetc(inputFile);
				if (c == EOF){
					break;
				}
				if (c == '\n'){
					arr[counter] = '\0';
					make_magic(arr, counter, &my_var, &number_of_blocks,
						&flag_error, &is_in_comment, &number_of_identifiers, &count_identificators);
					counter = 0;
				}
				arr[counter] = c;
				counter++;
			}

			fprintf(outputFile, "Number of blocks:%d\n", number_of_blocks);
			fprintf(outputFile, "Number of symbols in identificators: %ld\n", count_identificators);

			if (flag_error || (my_var != 0)){
				fprintf(outputFile, "Error!\n");
			}

			fclose(inputFile);
			fclose(outputFile);

			return 0;
		case 2: printf("Vyvedete pyrvo faila, ot koito shte se chete:");
			while(1){
				scanf("%s", first_name);
				if(!(first_name[strlen(first_name)-1] == 'c' && first_name[strlen(first_name)-2] == '.')){
					printf("Please input a valid name...\n");
					continue;
				}

				break;
			}

			inputFile = fopen(first_name, "r");

			while(1){
				c = fgetc(inputFile);
				if (c == EOF){
					break;
				}
				if (c == '\n'){
					arr[counter] = '\0';
					make_magic(arr, counter, &my_var, &number_of_blocks,
						&flag_error, &is_in_comment, &number_of_identifiers, &count_identificators);
					counter = 0;
				}
				arr[counter] = c;
				counter++;
			}

			fprintf(stdout, "Number of blocks:%d\n", number_of_blocks);
			fprintf(stdout, "Number of identificators: %ld\n", count_identificators);

			if (flag_error || (my_var != 0)){
				fprintf(stdout, "Error! There is an unclosed block!\n");
			}

			fclose(inputFile);
			return 0;
		case 3: 	printf("Vyvedete pyrvo faila, v koito shte se izvejda rezultatyt:");
			scanf("%s", second_name);
			outputFile = fopen(second_name, "w");

			while(1){
				c = fgetc(stdin);
				if (c == EOF){
					break;
				}
				if (c == '\n'){
					arr[counter] = '\0';
					make_magic(arr, counter, &my_var, &number_of_blocks,
						&flag_error, &is_in_comment, &number_of_identifiers, &count_identificators);
					counter = 0;
				}
				arr[counter] = c;
				counter++;
			}

			fprintf(outputFile, "Number of blocks:%d\n", number_of_blocks);
			fprintf(outputFile, "Number of symbols in identificators: %ld\n", count_identificators);

			if (flag_error || (my_var != 0)){
				fprintf(outputFile, "Error! There is an unclosed block! \n");
			}

			fclose(outputFile);

			return 0;
		case 4:
			while(1){
				c = fgetc(stdin);
				if (c == EOF){
					break;
				}
				if (c == '\n'){
					arr[counter] = '\0';
					make_magic(arr, counter, &my_var, &number_of_blocks,
						&flag_error, &is_in_comment, &number_of_identifiers, &count_identificators);
					counter = 0;
				}
				arr[counter] = c;
				counter++;
			}

			fprintf(stdout, "Number of blocks:%d\n", number_of_blocks);
			fprintf(stdout, "Number of symbols in identificators: %ld\n", count_identificators);

			if (flag_error || (my_var != 0)){
				fprintf(stdout, "Error! There is an unclosed block!\n");
			}

			return 0;
		default:
			printf("Invalid input...\n");
			return 0;
	}
}
