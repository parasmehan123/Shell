#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEBUG 0
void func(char *a);
void write_debug_msg(char *a);
int main()
{	
	while(1)
	{
		char cur_dir[100];
		printf("%s ₹ ",getcwd(cur_dir,100));

		char a[100000]="";
		int i=0;
		scanf("%[^\n]",a);
		getchar();
		while(i<strlen(a) && a[i]==' ')
			i+=1;
		if(i==strlen(a))
			continue;
		else if((i+4<strlen(a) && a[i+4]==' ' && a[i]=='e' && a[i+1]=='x' && a[i+2]=='i' && a[i+3]=='t') ||(i+4==strlen(a) && a[i]=='e' && a[i+1]=='x' && a[i+2]=='i' && a[i+3]=='t'))
				break;
		if(DEBUG)
		{
			write_debug_msg("input a:");
			write_debug_msg(a+i);
		}
		// printf("%s\n",a);
		int pid = fork();
		if(pid == 0)
		{
			func(a+i);
		}
		else if(pid > 0)
		{
			pid = wait(NULL);
		}
		else
		{
			printf("fork error!!\n");
		}

	}
	if(DEBUG)
		write_debug_msg("program exited!!");
	return 0;
}


void func(char *a)
{
	// close(2);
	// open("log.txt", O_WRONLY | O_APPEND | O_CREAT);
	if(strcmp(a,"")==0)
	{
		if(DEBUG)
			write_debug_msg("null input");
		exit(0);
	}

	if(DEBUG)
	{
		// printf("func called %s length %ld\n",a,strlen(a));
		write_debug_msg("function called with string");
		write_debug_msg(a);
	}
	int next=0,len=strlen(a),pip=0;
	while(next<len && a[next]!='|')
		next+=1;
	if(next<len)
	{
		if(DEBUG)
			write_debug_msg(a);
		a[next]='\0';
		if(DEBUG)
			write_debug_msg(a);
		pip=1;
	}
	char *args[1000],*tmp[1000];
	int no_args=1,argc=0;
	char * token = strtok(a, " ");
	tmp[0]=token;
	while( token != NULL ) 
	{
		token = strtok(NULL, " ");	
		tmp[no_args]=token;
		no_args+=1;
	}		
	for(int i=0;i<no_args-1;i++)
	{
		if(strlen(tmp[i])>=2 && tmp[i][0]=='1' && tmp[i][1]=='>')
		{
			char filename[1000];
			for(int j=2;j<strlen(tmp[i]);j++)
				filename[j-2]=tmp[i][j];
			if(DEBUG)
			{
				write_debug_msg("CASE 1> filename");
				write_debug_msg(filename);
			}
			close(1);
			creat(filename,0666);
		}
		else if(strlen(tmp[i])>=4 && tmp[i][0]=='2' && tmp[i][1]=='>' && tmp[i][2]=='&' && tmp[i][3]=='1')
		{
			close(2);
			dup(1);
		}
		else if(strlen(tmp[i])>=2 && tmp[i][0]=='2' && tmp[i][1]=='>')
		{
			close(2);
			char filename[1000];
			for(int j=2;j<strlen(tmp[i]);j++)
				filename[j-2]=tmp[i][j];
			creat(filename,0666);
			if(DEBUG)
			{
				write_debug_msg("CASE 2> filename");
				write_debug_msg(filename);
			}
		}
		else if(strlen(tmp[i])>=2 && tmp[i][0]=='>' && tmp[i][1]=='>')
		{
			i+=1;
			char filename[1000];
			for(int j=0;j<strlen(tmp[i]);j++)
				filename[j]=tmp[i][j];
			if(DEBUG)
			{
				write_debug_msg("CASE >> filename");
				write_debug_msg(filename);
			}
			close(1);
			open(filename, O_WRONLY | O_APPEND | O_CREAT);
		}
		else if(tmp[i][0]=='>')
		{

			i+=1;
			char filename[1000];
			for(int j=0;j<strlen(tmp[i]);j++)
				filename[j]=tmp[i][j];
			close(1);
			creat(filename,0666);
			if(DEBUG)
			{
				write_debug_msg("CASE > filename");
				write_debug_msg(filename);
			}	
		}
		else if(tmp[i][0]=='<')
		{
			close(0);
			i+=1;
			char filename[1000];
			for(int j=0;j<strlen(tmp[i]);j++)
				filename[j]=tmp[i][j];
			open(filename, O_RDONLY);
			if(DEBUG)
			{
				write_debug_msg("CASE < filename");
				write_debug_msg(filename);
			}	
		}
		else
		{
			args[argc]=tmp[i];
			argc+=1;
		}
		
	}
	if(DEBUG)
	{
		write_debug_msg("1argument ------- ");
		for(int k=0;k<argc;k++)
		{
			write_debug_msg(args[k]);
		}
		write_debug_msg("2argument ------- ");
		args[argc]=NULL;
	}
	if(pip==1)
	{
		if(DEBUG)
			write_debug_msg("pipe present!!!");
		
		int fd[2];
		pipe(fd);
		int pid=fork();
		if(pid==0)
		{
			if(DEBUG)
				write_debug_msg("calling child function");
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			if(DEBUG)
			{
				write_debug_msg("executing commands :");
				write_debug_msg(args[0]);
			}
			execvp(args[0],args);
			printf("execv error\n");
			exit(0);
		}
		else
		{
			if(DEBUG)		
				write_debug_msg("calling parent function");
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);

			func(a+next+1);
		}

		exit(0);
	}
	else
	{
		if(DEBUG)
		{
			write_debug_msg("pip not present!! executing commands :");
			write_debug_msg(args[0]);		
		}
		
		execvp(args[0],args);
		printf("execv error\n");
		exit(0);	
	}
	

}

void write_debug_msg(char *a)
{
	FILE *fp=fopen("log.txt","a");
	fprintf(fp,"%s\n",a);
	fclose(fp);
}