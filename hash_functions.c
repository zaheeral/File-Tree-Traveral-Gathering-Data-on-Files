#include <stdio.h>
#include <stdlib.h>


char *hash(FILE *f) {

/*    FILE *filename;
    filename 
    * filename*/

    char input;
    char user_input; 
    int i = 0;

    while (user_input != EOF){
        //printf("Please add input\n");
        user_input = scanf("%c", &input);

        if (user_input != EOF){

            hash_val[i] = (char)(hash_val[i] ^ input);

            //printf("P: %s\n", hash_val);

            if (i + 1 < block_size){
                i++;
            }else{
                i = i * 0;
            }
        }
    }

}


int check_hash(const char *hash1, const char *hash2, long block_size) {

    // A place holder so that the file will compile without error.
	// Replace with the correct return value.

    int e;

    for (e = 0; e < block_size; e++){
        //check to see if hashs are not empty, else they would be the entirely the same. p[3] == *(p + 3)
        if (hash1[e] != '\0' && hash2[e] != '\0')
        {
            if (hash1[e] != hash2[e])
            {
                printf("%d\n", e);
                return e;
            }
        }
    }
    printf("%ld\n", block_size);
    return block_size;
}









/*    //char hash_val[MAX_BLOCK_SIZE] = {'\0'};

    char user_input[];
    scanf("%s", user_input);

    int len = strlen( user_input );
    int i;
    for (i = 0; i < len; i++){

        printf("%c\n", user_input[i]);

        // The above is how u read character by character of the user input string. 
        // Now want to know if have to read character by character the hash_val ... and how to covert that char
        // into byte and Xor that... shud be easy... but need to know these things.
    }


    int i;
    char user_input[];
    while((user_input = getchar()) != EOF){

        scanf ("%c", user_input);

        


    }*/


















//gcc -Wall -std=c99 -o compute_hash compute_hash.c hash_functions.c 

//echo -n "ABC123123ABC" | ./compute_hash 2
