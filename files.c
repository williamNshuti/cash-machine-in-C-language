#include <stdio.h>
#include <string.h>
#define MAX 256


struct cash_machine
{
    char name[10];
    int age;
    int bal;
    int pin;
};


void cash_machine_services(int pin);
int main();


int update(int lno)
{
		FILE *fptr1, *fptr2;
        int linectr = 0;
        char str[MAX];
		char fname[MAX] = "cash_machine.txt";        
        char newln[MAX];
		char temp[] = "temp.txt";
        fptr1 = fopen(fname, "r");
        if (!fptr1) 
        {
                printf("Unable to open the input file!!\n");
                return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2) 
        {
                printf("Unable to open a temporary file to write!!\n");
                fclose(fptr1);
                return 0;
        }
        
        //lno++;
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            linectr++;
            if (linectr != lno) 
            {
                fprintf(fptr2, "%s", str);
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(fname);
        rename(temp, fname);
        printf(" Transaction performed successfully..!! \n");
}

void search()
{
    FILE *ptr;
    char input[10];
    int flag = 0;
    struct cash_machine a;
    printf("Enter the name to search \n");
    scanf("%s", input);
    ptr=fopen("cash_machine.txt","r");
    if(ptr == NULL)
    {
    	printf("No records found. ");
    	fclose(ptr);
    	return;
	}
    while(!feof(ptr))
    {
        fscanf(ptr,"%s\t%d\t%d\t%d\n",a.name,&a.age,&a.bal,&a.pin);
        if(strcmp(a.name,input) == 0)
        {
            fclose(ptr);
        	flag =1;
            printf("\n\tThe user %s exists with Age: %d and Amount: %d",a.name, a.age, a.bal);
            return;
        }
    }
    fclose(ptr);
    if(flag == 0)
    	printf("User not found.");
}

void register_user ()
{
    struct cash_machine e;
    FILE *p;
    p = fopen("cash_machine.txt", "a");
    printf("Enter Name:");
    scanf("%s", e.name);
    printf("Enter age:");
    scanf("%d", &e.age);
    printf("Enter deposit:");
    scanf("%d", &e.bal);
    printf("Enter pin:");
    scanf("%d", &e.pin);
    fprintf(p,"%s %d %d %d\n", e.name, e.age, e.bal,e.pin);
    fclose(p);
    printf("Account created successfully.");
}
void sort()
{
	FILE *p;
	struct cash_machine a[20],temp;
	int min;
	int i,j,imin,count = 0;
	p = fopen("cash_machine.txt","r");
	if(p == NULL)
    {
    	printf("No records found. ");
    	fclose(p);
    	return;
	}
	while(!feof(p))
	{
		fscanf(p,"%s\t%d\t%d\t%d\n",a[count].name,&a[count].age,&a[count].bal,&a[count].pin);
		count++;
	}
	for(i = 0;i<count;i++)
	{
//		strcpy(min,a[i].name);
		min = a[i].bal;
		imin = i;
		for(j=i+1;j<count;j++)
		{
			if(a[j].bal > min)
			{
				min = a[j].bal;
				imin=j;
			}

		}
		temp=a[i];
		a[i]=a[imin];
		a[imin]=temp;
	}
	printf("\nThe Sorted list by their account balance is:");
	printf("\n\n name\tage\tbalance\tpin\n==\t====\t===\t===\n");
	for (i = 0;i <count;i++)
	{
		printf("%s\t%d\t%d\t%d\n",a[i].name,a[i].age,a[i].bal,a[i].pin);
	}

}


void display()
{
    FILE *ptr;
    struct cash_machine a;
    ptr=fopen("cash_machine.txt","r");
    if(ptr==NULL)
    {
    	printf("No records found. ");
    	fclose(ptr);
    	return;
	}
    printf("\n\n name\t\tage\t\tbalance\t\tpin\n====\t\t====\t\t===\t\t===\n");
    while(!feof(ptr))
    {
	    fscanf(ptr,"%s\t\t%d\t\t%d\t\t%d\n",a.name,&a.age,&a.bal,&a.pin);
	    printf("%s\t\t%d\t\t%d\t\t%d\n",a.name,a.age,a.bal,a.pin);
    }
    fclose(ptr);
}

void deposit(int pin)
{   
    FILE *ptr;
    FILE *p;
    int key,line;
    struct cash_machine a;
    printf("Enter deposit amount\n");
    scanf("%d", &key);
    ptr=fopen("cash_machine.txt","r");
    p = fopen("cash_machine.txt","a");
    while(!feof(ptr))
    {
        ++line;
        fscanf(ptr,"%s\t%d\t%d\t%d\n",a.name,&a.age,&a.bal,&a.pin);
        if(a.pin==pin)
        {
            a.bal = a.bal + key;
            fprintf(p,"%s %d %d %d\n", a.name, a.age, a.bal,a.pin);
            fclose(p);
            fclose(ptr);
            update(line);
            break;
        }
    }
    cash_machine_services(pin);
	 	
}

void check_balance(int pin)
{
	FILE *ptr;
    int flag = 0;
    struct cash_machine a;
    ptr=fopen("cash_machine.txt","r");
    while(!feof(ptr))
    {
        fscanf(ptr,"%s\t%d\t%d\t%d\n",a.name,&a.age,&a.bal,&a.pin);
        if(a.pin == pin)
        {
            fclose(ptr);
            printf("\nCurrent account balance: %d", a.bal);
            break;
        }
    }
    cash_machine_services(pin);
}

void withdraw(int pin)
{
	FILE *ptr;
    FILE *p;
    int amount,line;
    struct cash_machine a;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);
    ptr=fopen("cash_machine.txt","r");
    p = fopen("cash_machine.txt","a");
    while(!feof(ptr))
    {
        ++line;
        fscanf(ptr,"%s\t%d\t%d\t%d\n",a.name,&a.age,&a.bal,&a.pin);
        if(a.pin==pin)
        {
        	//TODO: check if amount is > than acct balance
        	if(amount > a.bal)
        	{
        		printf("Insufficient funds.");
        		fclose(p);
        		fclose(ptr);
        		break;
			}
            a.bal = a.bal - amount;
            fprintf(p,"%s %d %d %d\n", a.name, a.age, a.bal,a.pin);
            fclose(p);
            fclose(ptr);
            //printf("line: %d",line); //current read line	
            update(line); //
            break;
        }
    }
    cash_machine_services(pin);
	
}


void cash_machine_menu()
{
    printf("\n\n\t\t ****** Cash Machine Advanced Menu ******");
    printf("\n\t\t Press [1] to check balance cash  ");
    printf("\n\t\t Press [2] to deposit cash");
    printf("\n\t\t Press [3] to withdraw cash");
    printf("\n\t\t press [0] to quit ");
}

void main_menu()
{
    printf("\n\n\t\t ****** Cash Machine Main Menu ******\n\n");
    printf("\n\t\t Press [1] to register  ");
    printf("\n\t\t Press [2] to login  ");
    printf("\n\t\t Press [3] to Display  all Users");
    printf("\n\t\t Press [4] to search users by Name");
    printf("\n\t\t Press [5] to sort users");
    printf("\n\t\t press [0] to quit ");
}

void cash_machine_services(int pin)
{
    int choice;
    cash_machine_menu();
    printf("\n\n Enter your choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            check_balance(pin);
            break;
        case 2:
            deposit(pin);
            break;
        case 3:
            withdraw(pin);
            break;
        case 0:
            main();
            break;
        default:
            printf("Invalid option. Try again. ");
            break;
    }
}

void check_user()
{
    FILE *p;
    struct cash_machine a;
    int flag=0,pin;
    char name[10];
    printf("Enter USERNAME: ");
    scanf("%s",name);
    printf("Enter the PIN: ");
    scanf("%d",&pin);
    p=fopen("cash_machine.txt","r");
    if(p == NULL)
    {
    	printf("No records found. ");
    	fclose(p);
    	return;
	}
    while(!feof(p))
    {
        fscanf(p,"%s\t%d\t%d\t%d\n",a.name,&a.age,&a.bal,&a.pin);
        if((a.pin==pin) && (strcmp(name,a.name) == 0))
        {
            printf("\nUser Verified...");
        	flag=1;
            fclose(p);
            break;
        }
    }
    if(flag==0)
    {
    	printf("Invalid PIN or USERNAME...Please Try again.");
    	fclose(p);
	}
    else{
    	cash_machine_services(pin);
	}
        
}


int main() 
{
    int choice;
    do{
        main_menu();
        printf("\n\n Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            register_user();
            break;
        case 2:
        	check_user();
        	break;
        case 3:
            display();
            break;
        case 4:
            search();
            break;
        case 5:
            sort();
            break;
        case 0:
            printf("Thank you for using Cash Machine services. ");
            break;
        default:
            printf("Invalid option.");
            break;
        }
    }while(choice!=0);
    return 0;
}
  
  




