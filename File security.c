#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAX 512
#define SIZE 20
void encryption(char filename[20],int a,int b)
{
        int fd=open(filename,O_RDWR);
        int fd1=open(filename,O_RDWR);
        char buffer;
	char cipher;
	if(fd==-1)
	{
		printf("\nFile not found");
		exit(1);
	}printf("2");
	//lseek(fd,2*sizeof(int),SEEK_SET);
	while(read(fd,&buffer,sizeof(buffer))!=0)
	{
			 if(buffer>='A'&&buffer<='Z')
			{

				cipher= (char) ((((a * (buffer-'A') ) + b) % 26) + 'A');
			}
			else
			{
				cipher=buffer^b;
			}
			write(fd1,&cipher,sizeof(cipher));
	}
	close(fd);
	close(fd1);
}

void decryption(char filename[20], int a,int b)
{
	int fd=open(filename,O_RDWR);
	int fd1=open(filename,O_RDWR);
	char buffer;
	char cipher;
	int i,flag;
	if(fd<0||fd1<0)
	{
		printf("\nFile not opened");
		exit(1);
	}
	int a_inv=0;
	for(i=0;i<26;i++)
	{
		flag=(a*i)%26;
		if(flag==1)
		{
			a_inv=i;
		}
	}
	while(read(fd,&buffer,sizeof(buffer))!=0)
	{
		 if(buffer>='A'&&buffer<='Z')
		{

			cipher= (char) (((a_inv * ((buffer+'A' - b)) % 26)) + 'A');
		}
		else
		{
			cipher= buffer^b;
		}
	write(fd1,&cipher,sizeof(cipher));
	}
	close(fd);
	close(fd1);

}
int main()
{
	char filename[20];
	int a,b;
	int choice;
	int i,j,index;
	FILE *fp1,*fp2;
	char u[MAX],p1[MAX];
	int fd,a1[MAX],b1[MAX];
	char f1[MAX],f2[MAX][SIZE];
  	char username[MAX]="os";
	char password[MAX]="project";
	char pass[MAX]="decryptpass";
	printf("\nUSERNAME:");
	scanf("%s",u);
	printf("\nPASSWORD:");
	scanf("%s",p1);
	//printf("%s",u);
	//printf("%d %d",strcmp(u,username),strcmp(p1,password));
	if((strcmp(u,username)==0)&&(strcmp(p1,password)==0))
	{
		while(1)
		{
			printf("\n1.ENCRYPT\n2.DECRYPT\n3.EXIT");
			printf("\nEnter choice..");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
					printf("\nEnter the filename..");
					scanf("%s",filename);
					printf("\nEnter the encryption key..");
					scanf("%d%d",&a,&b);
					fp1=fopen("key.txt","a");
					fprintf(fp1,"\n%s %d %d",filename,a,b);
					encryption(filename,a,b);
					fclose(fp1);
					break;
				case 2:
					printf("\nEnter the filename..");
					scanf("%s",f1);
					printf("\nEnter the password..");
					scanf("%s",p1);
					index=-1;
					fd=0;
					fp2=fopen("key.txt","r");
					do
					{
						//printf("%s\n",f1);
						fscanf(fp2,"%s %d %d",f2[i],&a1[i],&b1[i]);
						i++;
					}while(!feof(fp2));
					for(j=0;j<i;j++)
					{
						if(strcmp(f1,f2[j])==0)
						{
							index=j;
							//printf("%d\n",index);
						}
					}
					if(index!=-1)
					{
						if(strcmp(p1,pass)==0)
							{

								decryption(f1,a1[index],b1[index]);
								fd=1;
							}
							else
							{
								printf("\nwrong password");
								exit(1);
							}
					}
					if(fd==0)
					{
						printf("\nThe file is not decrypted");
					}
					exit(1);
                case 3: exit(0);
			}
		}
	}
	else
	{
		printf("\nThe password or username is wrong");
	}
}








