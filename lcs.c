#include<stdio.h>
#include<string.h>

char s1[20],s2[20],b[20][20],x[20];
int c[20][20],m,n,count=0;

void LCS()
{
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            b[i][j]='.';
        }
    }  

    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='d';
            }
            else if(c[i-1][j]>c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]='u';
            }
            else
            {
                c[i][j]=c[i][j-1];
                b[i][j]='l';                
            }
        }
    }   
    

}


void PRINT_LCS(int i,int j)
{
    if(i==0 || j==0)
        return;
    if(b[i][j]=='d')
    {
        PRINT_LCS(i-1,j-1);
        x[count]=s1[i-1];   
        count++;
    }
    else if(b[i][j]=='u')
    {
        PRINT_LCS(i-1,j);
    }
    else
    {
        PRINT_LCS(i,j-1);
    }
}
void main()
{
    printf("Enter sequence1:");
    scanf("%s",s1);
    printf("Enter sequence2:");
    scanf("%s",s2);

    m=strlen(s1);
    n=strlen(s2);


    LCS();

    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    
    PRINT_LCS(m,n);

    printf("final ans:\n");
    
    for(int i=0;i<count;i++)
    {
        printf("%c",x[i]);
    }

}