#include <stdio.h>
// Add your system includes here.

#include "ftree.h"
#include "hash.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>





int permissions_octal(struct stat buf) {

   	int octal_val = 0;           

	printf("st_mode = %o\n", buf.st_mode);

   	octal_val = buf.st_mode & 0777;       /* 12 = 0000 1100 */ 

   	//might have to delete the line below
   	printf("Line 1 - Value of c is %d\n", octal_val );
   	//***********************

   	return octal_val;
}




struct TreeNode * node_creator(struct stat buf, char *fname){

	struct TreeNode *root = malloc(sizeof(struct TreeNode));


	if (S_ISDIR(buf.st_mode)){

		(*root).fname = &fname; //change this to proper
		(*root).permissions = permissions_octal(buf);
		(*root).hash = NULL;

		(*root).contents = NULL; //fix this
		(*root).next = NULL;
	}

	else if (S_ISREG(buf.st_mode))
	{
		(*root).fname = &fname;//change this to proper
		(*root).permissions = permissions_octal(buf);
		(*root).hash = NULL; //fix this

		(*root).contents = NULL; 
		(*root).next = NULL;
	}

	else if (S_ISLNK(buf.st_mode))
	{
		(*root).fname = &fname;//change this to proper
		(*root).permissions = permissions_octal(buf);
		(*root).hash = NULL; //fix this

		(*root).contents = NULL; 
		(*root).next = NULL;
	}

	return root;
	//this should return a treenode
}




/*
 * Returns the FTree rooted at the path fname.
 */
struct TreeNode *generate_ftree(const char *fname) {
    // Your implementation here.

	//1. Get Info
	DIR *dp;//
	struct dirent *entry;//
	struct stat statbuf;//


	struct stat buf;
	lstat(&fname, &buf);

	if((dp = opendir(fname)) == NULL) 
	{
        fprintf(stderr,"cannot open directory: %s\n", fname);
        return;
    }

    chdir(fname);


	struct TreeNode *rootNode = node_creator(buf, *fname);

	struct TreeNode *currNode = NULL;

	int i = 0;


	while((entry = readdir(dp)) != NULL) 
    {
    	lstat(entry->d_name,&statbuf);

    	struct TreeNode *newNode = node_creator(statbuf, entry->d_name);

    	if (i == 2)
    	{
    		(*rootNode).contents = newNode;
    		*currNode = *newNode;
    		i++;
    	}else if(i>2){

    		(*currNode).next =  newNode;
    		*currNode = *newNode;
    	}

    	if(S_ISDIR(statbuf.st_mode)){
    		if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
    			continue;

    		generate_ftree(entry->d_name);
    	}

    	chdir("..");
    	closedir(dp);
    }
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 */
void print_ftree(struct TreeNode *root) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
    static int depth = 0;
    printf("%*s", depth * 2, "");

    // Your implementation here.


    if ((*root).hash == NULL)
    {
    	print_directory(*root, int depth);
    	if ((*root).contents != NULL)
    	{
    		depth++
    		print_ftree(*root);
    	}
    }

    if ((*root).hash != NULL)
    {
    	depth++
    	print_files(*root, depth);
    }

    if ((*root).next != NULL){
    	print_ftree(*root);
    }

}


void print_directory(struct TreeNode *root, int depth){
	printf("%*s", depth * 2, "===== %s (%d)=====", (*root).fname, (*root).permissions);
}

void print_files(struct TreeNode *root, int depth){
	printf("%*s", depth * 2, "%s (%d)", (*root).fname);

