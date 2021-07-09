#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

void insert_record();
void display_record();
void search_record();
void del_record();
void update_record();

int count = 0;


struct info
{

    char donor_name[50];
    char blood_group[10];
    int number;
    int bag_quantity;
};

struct info s;

void main()
{
    int ch;
    
    while(ch!=0)
    {
        
    
    printf("\n\t***********************************************\n");
    printf("\t    WELCOME TO PLASMA DONATION CAMP\n");
    printf("\t***********************************************\n\n\n");


        printf("\t\t 1: Add new donor\n");
        printf("\t\t 2: Display donor record\n");
        printf("\t\t 3: Search donor record\n");
        printf("\t\t 4: Edit donor record\n");
        printf("\t\t 5: Delete donor record\n");
        printf("\t\t 0: Exit\n");
        printf("\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                insert_record();
                break;
            case 2:
                display_record();
                break;

            case 3:
                search_record();
                break;

            case 5:
                del_record();
                 break;
            case 4:
                update_record();
                break;
            case 0:exit(1);
            default:
                printf("\n\t\tWrong choice Entered");
        }
        printf("\n\t\tPress any key to continue ");
        getch();
       }
}

void insert_record()
{
    FILE *fp;

    fp=fopen("plasma.txt","ab+");

    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
   

    printf("\n\n\t**** ENTER NEW DONOR DEATAILS ****\n\n");
    printf("\n\t\tEnter Donor Name: ");
    scanf("%s",s.donor_name);
    printf("\n\t\tEnter Donor Blood Group: ");
    scanf("%s",s.blood_group);
    // printf("\n\t\tEnter Donor Blood Group: ");
    // gets(s.blood_group);
    // printf("\n\t\tEnter Donor Name: ");
    // gets(s.donor_name);
    printf("\n\t\tEnter Donor Number: ");
    scanf("\t%d",&s.number);
    printf("\n\t\tEnter number of  Bag (in mL) donated: ");
    scanf("\t%d",&s.bag_quantity);
    fwrite(&s,sizeof(s),1,fp);

    printf("\n\n\t !!! Donor Record Inserted Sucessfully\n");
    count++;
    fclose(fp);

}


void display_record()
{
    FILE *fp;
    fp=fopen("plasma.txt","rb");

    if(fp==NULL)
    {
        printf("\n\t\tError : Cannot open the File !!!");
        return;
    } 

    printf("\n\n\t **** Donor Details Are As Follows ****\n");
    printf("\nName of Donor\t\tBlood Group\t\tNumber\t\tBag Qty(in mL)\n\n");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("%s\t\t\t%s\t\t\t%d\t\t\t%d\n",s.donor_name,s.blood_group,s.number,s.bag_quantity);
    }
    fclose(fp);
}


void search_record()
{
    int ph_no,flag=0;
    FILE *fp;
    fp=fopen("plasma.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\n\n\tEnter Donor Phone Number Which You Want To Search: ");
    scanf("%d",&ph_no);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.number==ph_no)
        {
        flag=1;
        printf("\n\n\tSearch Sucessfull And Donor Records are as Follows: \n\n");
        printf("\nName of Donor\t\tBlood Group\t\tNumber\t\tBag Qty(in ml)\n\n");
        printf("%s\t\t%s\t\t%d\t\t%d\n",s.donor_name,s.blood_group,s.number,s.bag_quantity);
        }
    }
    if(flag==0)
    {
    printf("\n\n\t\tNo Such Record Found !!!!!\n");
    }
fclose(fp);
}


void del_record()
{
    char s_id[15];
    int isFound = 0; 
    printf("\n\tEnter Donor Name to Delete: ");
	fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("plasma.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&s, sizeof(s),1,fp) == 1)
	{
        if(strcmp(s_id, s.donor_name) != 0)
		{
            fwrite(&s,sizeof(s),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("plasma.txt");
    rename("temp.txt","plasma.txt");
    printf("\n\tThe record is sucessfully deleted");
   
    return;
}


void update_record()
{
    FILE *fp;
    char ch, name[5];
    int rec, id, c;
    fp = fopen("plasma.txt", "rb+");
    printf("Enter the number to update:\n");
    scanf("%d", &id);
    fseek(fp, 0, 0);
    int flag=0;
    rec = count;
    while (!feof(fp) && flag==0)
    {
        fread(&s, sizeof(s), 1, fp);
        printf(" number :  %d \n", s.number);
        
        if (id == s.number)
        {
            // display_record();
            // curr=ftell(fp);
            printf("Enter the name to be updated : ");
            scanf(" %[^\n]s", s.donor_name);
            printf("Enter the blood group to be updated : ");
            scanf(" %[^\n]s", s.blood_group);
            // c = fwrite(name, 50, 1, fp);
            printf("Enter the number of bags(in ml) : ");
            scanf("%d", &s.bag_quantity);
            printf("Enter the number to be updated : ");
            scanf("%d", &s.number);
            fseek(fp,-(sizeof(s)),1);
            // strcpy(s.donor_name,name);
            fwrite(&s,sizeof(s),1,fp);
            // fwrite()
            flag = 1;
            break;
            
            
        }
        // fread(s.donor_name, 50, 1, fp);
        // printf("%d",rec);
       
    }
    if (flag == 1)
        printf("Record updated\n");
    else
        printf("Update not successful\n");
    fclose(fp);
    // free(temp);
    // free(temp->donor_name);

} 