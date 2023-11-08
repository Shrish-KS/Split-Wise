#include <stdio.h>

// Declaration of structures

// Structure used in spliiting function
struct split
{
    char name[20];
    float spent;
};

// Structure used in reminder function
struct reminder
{
	   
    int money_owed,timelimit,day;
    char debt_paid;
};

// Declaration of functions

int temp();
void splitting(struct split s1[],float total,int n);
void balance(int n,char name[n][20],int *);
void reminder();

int main()
{
    int choice,res=0;
    int num,i;
    float total;
    struct split s[1000];

    // Menu driven input

    printf("MENU!!!");
    printf("\nEnter 1 for splitting");
    printf("\nEnter 2 for balacing");
    printf("\nEnter 3 for reminder");
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    while(choice!=0)
    {
    switch(choice)
    {
        case 1:printf("Enter the total number of people in the group:"); 
               
               // getting the neccesary inputs

               scanf("%d",&num);
               printf("Enter the total money spent:");
               scanf("%f",&total);
               for(i=0;i<num;i++)
               {
                printf("Enter the name of person %d:",i+1);
                scanf("%s",s[i].name);
                s[i].spent=0;
               }

                //Calling splitting function

               splitting(s,total,num);
               break;

                //Calling temp function

        case 2:res=temp();               
               break;

               //Calling reminder function

        case 3:reminder();
               break;
        default:printf("\nYou have entered a wrong choice!!!Try Again");
                break;
    }
    printf("\nMENU!!!");
    printf("\nEnter 1 for splitting");
    printf("\nEnter 2 for balacing");
    printf("\nEnter 3 for reminder");
    printf("\nEnter 0 if you wish to exit");
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    }
    return 0;
}

//temp function definition

int temp()
{
    int n,i;
    printf("Enter the number of people in the group: ");
    scanf("%d",&n);

    //declaring 2-D arrays to store names

    char name[n][20];
    int cash[n];
    for(i=0;i<n;i++)
    {
     printf("Enter name(%i): ",i+1);
     scanf("%s",name[i]);
     printf("Enter the Amount spent by %s: ",name[i]);
     scanf("%d",&cash[i]);
    }

    //calling balance function

    balance(n,name,cash);
    return 0;
}

//splitting function definition

void splitting(struct split s1[],float total,int n)
{
    int choice,i;
    float split;

    // getting the choice to decide how to split the total amount among the group members

    printf("[1] SPLIT THE AMOUNT EQUALLY\n");
    printf("[2] SPLIT IT PERCENTAGE WISE\n");
    printf("Select from the above options: ");
    scanf("%d",&choice);
    if (choice==1)
    {
        split=total/n;
        for(i=0;i<n;i++)
        {
           s1[i].spent=split;
        }
    }
    else if (choice==2)
    {
        float ratios[n];
        printf("Enter the percentages: \n");
        for (int i=0;i<n;i++)
        {
            printf("Enter the ratio to be paid by %s:",s1[i].name);
            scanf("%f",&ratios[i]);
        }
        for (int i=0;i<n;i++)
        {
            split=(total*0.01*ratios[i]);
            s1[i].spent=split;
        }
    }
    for(i=0;i<n;i++)
    {
      printf("\nThe amount spent by %s is %f",s1[i].name,s1[i].spent);
    }
}

//balance function defintion

void balance(int n,char name[n][20],int *cash)
{
    int sum=0;
    float avg;

    //structure declaration

    typedef struct
    {
        char names[20];
        int spent;
        float debt;
        float get;
    }person;

    person people[n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<20||name[i][j]!='\0';j++)
        {
            people[i].names[j]=name[i][j];
        }
        people[i].spent=cash[i];
        sum+=cash[i];
    }
    avg=(float)sum/n;
    for(int i=0;i<n;i++)
    {
        if(people[i].spent>avg)
        {
            people[i].get=people[i].spent-avg;
        }
        else
        {
            people[i].get=0;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(people[i].spent<avg)
        {
            people[i].debt=avg-people[i].spent;
        }
        else
        {
            people[i].debt=0;
        }
    }
    printf("\n\n");

    //displaying the names of those who have to be paid and the amount

    printf("People who have to recieve money: \n");
    for(int i=0;i<n;i++)
    {
        if(people[i].get!=0)
        {
            printf("\t%s\t-  %.2f\n",people[i].names,people[i].get);
        }
    }

    //displaying the names of those who needs to pay and the amount needed to be paid

    printf("People who have to give money: \n");
    for(int i=0;i<n;i++)
    {
        if(people[i].debt!=0)
        {
            printf("\t%s\t-  %.2f\n",people[i].names,people[i].debt);
        }
    }
    

    //storing the details of the amount spent per person and the amount to be given to the group in a File

    FILE *f=fopen("record.csv","w");
    fprintf(f,"Name,Amount Spent,Amount to be ,Total Debt\n");
    for(int i=0;i<n;i++)
    {
        fprintf(f,"%s,%d,%.2f,%.2f\n",people[i].names,people[i].spent,people[i].get,people[i].debt);
    }

}

//reminder function defintion

void reminder()
{
    int n,i,j,k,temp,flag=0,flag1=1,t=0;
    
    printf("Enter the total number of people:");
    scanf("%d",&n);
 
    struct reminder r[n],*rn;
    for(i=0;i<n;i++)
    {
        rn=&r[i];
        printf("\nEnter the money owed by person %d:",i+1);
        scanf("%d",&rn->money_owed);
        

        //inputting the time limit

        printf("Enter the total number of days for payment of debt owed by person %d:",i+1);
        scanf("%d",&rn->timelimit);
        
        //inputting the days passed after borrowing

        printf("Enter the current day in the given number of days for person %d:",i+1);
        scanf("%d",&rn->day); 
        printf("\n");
    }
    
    printf("Enter a number from 1 to %d:",n);
    scanf("%d",&k);
    i=k-1;
    temp=n;
    
    while(i>=0&&i<temp)
    {
        rn=&r[i];
    	if(flag==k&&flag1==1)
    	{
    		printf("\nThe debt is already paid.");
    		printf("\nEnter a number between 1 to %d if you wish to continue or enter %d if you wish to stop:",temp,temp+1);
            scanf("%d",&k);
            if(k==3)
            break;
            if(t==k)
            continue;
            flag1=0;
    		continue;
		}
		flag=0;
        if(rn->money_owed==0)
        {
            rn->debt_paid='y';
            printf("Enter a number between 1 to %d if you wish to continue or enter %d if you wish to stop:",temp,temp+1);
            scanf("%d",&i);
        }
        
        else
        {
        for(j=rn->day;j<=rn->timelimit;j++)
        {
            printf("\nEnter 'y' if the debt is ready to be paid and 'n' if not, on day %d:",j);
            scanf("%s",&rn->debt_paid);
            
            if(rn->debt_paid=='y')
            {
            j=rn->timelimit;
            flag=1;
            }
        }
        
        if(rn->debt_paid=='y')
        {
        printf("\nThe money owed(%d) by person %d has been paid",rn->money_owed,i+1);
        flag=k;
        }
        else
        {
          rn->money_owed+=rn->money_owed*0.05;
        
          printf("\nEnter the extra number of days for payment of debt owed by person %d:",i+1);
          scanf("%d",&rn->timelimit);
          printf("\nEnter the current day in the given number of days for person %d:",i+1);
          scanf("%d",&rn->day);
        
          for(j=rn->day;j<=rn->timelimit;j++)
          {
              printf("\nEnter 'y' if the debt is ready to be paid and 'n' if not on day %d:",j);
              scanf("%s",&rn->debt_paid);
              if(rn->debt_paid=='y')
              j=rn->timelimit;
          }
          
          if(rn->debt_paid=='y')
          {
              printf("\nThe money owed(%d) by person %d has been paid",rn->money_owed,i+1);
              rn->money_owed=0;
              flag=k;	
          }
          else
          {

              //interest of 5% is added to the money to be paid, if the deadline in over

              rn->money_owed+=rn->money_owed*0.05;
              printf("\nThe money owed(%d) by person %d has been decuted with an extra penalty of 5 percent",rn->money_owed,i+1);
              rn->money_owed=0;
              rn->day=rn->timelimit+1;
              flag=k;
          }
        }
        t=k;
        printf("\nEnter a number between 1 to %d if you wish to continue or enter %d if you wish to stop:",temp,temp+1);
        scanf("%d",&k);
        i=k-1;
    }
    }
}
