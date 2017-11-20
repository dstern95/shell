#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *read_command_naive(int* totsize){
	int bufsize = 16;
	char *buffer = malloc(sizeof(char) * bufsize);
	int pos = 0;

	// Exemplifies the problem
	char *lesson_buffer = malloc(sizeof(char) * 1);
	lesson_buffer[0] = '5';
	// I don't assign this variable anywhere else

	while(1){
		char c = getchar();
		if(c !='\n')
		  {
		    if(pos >= bufsize)
		      {
			bufsize = bufsize *2;
			buffer = realloc(buffer,bufsize);
		    }
			buffer[pos++] = c;
		}
		else {
			buffer[pos] = '\0'; // null byte

			// Confirm that these two things are both correct
			//printf("buffer: %s\n", buffer);
			//printf("lesson: %s\n", lesson_buffer);
			free(lesson_buffer);
			*totsize = bufsize;
			// Return the collected string
			return buffer;
		}
	}
}


int main(void){

  while(1)
    {
      printf("type in command >>>");
      int totsize = 16;
      char *cmd = read_command_naive(&totsize);
      
      char *p;
      char str[totsize];
      strcpy(str,cmd);
      int totalargnumber = 1;
      char** argv = malloc(sizeof(char *)*1);
      char* holder  = strtok(str," ");
      argv[0] = holder;
      int argcount = 1;
      //takes a char** or string array and puts the parsed string in it
      while(holder != NULL)
	{
	  if(totalargnumber == argcount)
	    {
	      totalargnumber = totalargnumber*2;

	      argv =realloc(argv,sizeof(char *)*totalargnumber);

	    }
	  holder= strtok(NULL," ");
	  argv[argcount] = holder;
	  argcount +=1;
	}
      if (argv[0] == NULL)
	{
	  //do nothing
	}
      else if(!strcmp(argv[0],"cd"))
	{
	  chdir(argv[1]);

	}
      
      else if(!strcmp(argv[0],"exit"))
	{
	  exit(0);
	}
      else
	{
	  //fork splits the program into a child one so they can run at the same time 
	  pid_t pid = fork();
	  int status;

	  if(pid !=0)
	    {
	      waitpid(pid, &status, 0);
	    }
	  else
	    {
	      execvp(argv[0],argv);
	      //after execution if the command is bad it needs to tell the user and exit the status
	      printf("command not found \n");

	      exit(status);
	    }
	}

    }
  return 0;
}
  
