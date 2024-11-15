#include<stdio.h>
#include<string.h>
#define NAME_SIZE 100
#define CATEGORY_SIZE 20
#define USER_DB_SIZE 1000
#define FAMILY_DB_SIZE 100
#define EXPENSE_DB_SIZE 1000
#define FAMILY_SIZE 4
#define DAY_SIZE 10
#define MONTH_SIZE 12
struct date
{
    int day;
    int month;
};
struct User 
{
    int user_id;
    char user_name[NAME_SIZE];
    float user_income;
};
struct Family
{
    int family_id;
    char family_name[NAME_SIZE];
    int Users_id_family[4];
    float family_income;
    float monthly_expense;
};
struct Expense
{
    int expense_id;
    int user_id;
    char expense_category[CATEGORY_SIZE];
    float expense_amount;
    struct date expense_date;
};
struct Family family_database[FAMILY_DB_SIZE];
struct User user_database[USER_DB_SIZE];
struct Expense expense_database[EXPENSE_DB_SIZE];

int AddUser(struct User user_database[] , int size , int id , float income , char name[]);
int AddExpense(struct Expense expense_database[] , int size , int exp_id , int user_id , char category[] , float expense , int day , int month);
int CreateFamily(struct Family family_database[], int size , int family_id , int user_ids[] , char name[] , float income);
int update_delete_expense(struct Expense expense_database[] , int size , int exp_id);
float get_total_expense(struct Expense expense_database[] , int size , int family_id , int month);
float get_categorical_expense(struct Expense expense_database[] , int size , int family_id , char category[]);
int get_highest_expense_day(struct Expense expense_database[] , int size , int family_id);
float get_individual_expense(struct Expense expense_database[] , int size , int user_id);
void update_or_delete_individual_family_details(struct User user_database[] , struct Family family_database[] , int user_id , int family_id);
void sort_user_db(struct User user_database[] , int size)
{
    int i=0,found =0;
    for(i=0 ; i<size && !found; i++)
    {
        if(user_database[i].user_id == 0)
        {
            break;
        }
    }
    i=i-1;
    int flag = 0;
    for(int j=0 ; j<i-1 && !flag; j++)
    {
        flag = 1;
        for(int k=0 ; k<i-j-1 ; k++)
        {
            if(user_database[k].user_id > user_database[k+1].user_id)
            {
                int temp = user_database[k].user_id;
                user_database[k].user_id = user_database[k+1].user_id;
                user_database[k+1].user_id = temp;
                float tempo = user_database[k].user_income;
                user_database[k].user_income = user_database[k+1].user_income;
                user_database[k+1].user_income = tempo;
                char name[NAME_SIZE];
                strcpy(name,user_database[k].user_name);
                strcpy(user_database[k].user_name , user_database[k+1].user_name);
                strcpy(user_database[k+1].user_name , name);
                flag = 0;
            }
        }
    }
}
void sort_family_db(struct Family family_database[] , int size)
{
    int i=0,found=0;
    for(int z=0 ; z<size && !found; z++)
    {
        if(family_database[z].family_id == 0)
        {
            break;
        }
    }
    i = i-1;
    int flag = 0;
    for(int j=0 ; j<i-1 && !flag; j++)
    {
        for(int k=0 ; k<i-j-1 ; k++)
        {
            if(family_database[k].family_id > family_database[k+1].family_id)
            {
                int temp = family_database[k].family_id;
                family_database[k].family_id = family_database[k+1].family_id;
                family_database[k+1].family_id = temp;
                float tempo = family_database[k].family_income;
                family_database[k].family_income = family_database[k+1].family_income;
                family_database[k+1].family_income = tempo;
                float exp = family_database[k].monthly_expense;
                family_database[k].monthly_expense = family_database[k+1].monthly_expense;
                family_database[k+1].monthly_expense = exp;
                char name[NAME_SIZE];
                strcpy(name , family_database[k].family_name);
                strcpy(family_database[k].family_name , family_database[k+1].family_name);
                strcpy(family_database[k+1].family_name , name);
                for(int o=0 ; o<FAMILY_SIZE ; o++)
                {
                    int cp = family_database[k].Users_id_family[o];
                    family_database[k].Users_id_family[o] = family_database[k+1].Users_id_family[o];
                    family_database[k+1].Users_id_family[o] = cp;
                }
            }
        }
    }
}
void sort_expense_db(struct Expense expense_database[] , int size)
{
    int i=0,found =0;
    for(i=0 ; i<size && !found ; i++)
    {
        if(expense_database[i].user_id == 0)
        {
            break;
        }
    }
    i = i-1;
    int flag = 0;
    for(int j=0 ; j<i-1 && !flag; j++)
    {
        flag = 1;
        for(int k=0 ; k<i-j-1 ; k++)
        {
            if(expense_database[k].user_id > expense_database[k+1].user_id)
            {
                int temp = expense_database[k].user_id;
                expense_database[k].user_id = expense_database[k+1].user_id;
                expense_database[k+1].user_id = temp;
                int tempo = expense_database[k].expense_id;
                expense_database[k].expense_id = expense_database[k+1].expense_id;
                expense_database[k+1].expense_id = tempo;
                float cp = expense_database[k].expense_amount;
                expense_database[k].expense_amount = expense_database[k+1].expense_amount;
                expense_database[k+1].expense_amount = cp;
                int cpy = expense_database[k].expense_date.day;
                expense_database[k].expense_date.day = expense_database[k+1].expense_date.day;
                expense_database[k+1].expense_date.day = cpy;
                int copy = expense_database[k].expense_date.month;
                expense_database[k].expense_date.month = expense_database[k+1].expense_date.month;
                expense_database[k+1].expense_date.month = copy;
                char name[CATEGORY_SIZE];
                strcpy(name , expense_database[k].expense_category);
                strcpy(expense_database[k].expense_category , expense_database[k+1].expense_category);
                strcpy(expense_database[k+1].expense_category , name);
            }
        }
    }
}
int check_family_id(struct Family family_database[] , int size , int family_id)
{
    int ret_val = 0;
    int i=0;
    for(i = 0 ; (i<size) && (!ret_val); i++)
    {
        if(family_database[i].family_id == family_id)
        {
            ret_val = 1;
        }
    }
    return ret_val;
}
float income_individual(struct User user_database[], int size , int id)
{
    int i=0,flag=0;
    float ans=0;
    for(i=0 ; i<size &&(!flag) ; i++)
    {
        if(user_database[i].user_id == id){
            ans = user_database[i].user_income;
            flag = 1;
        }
    }
    return ans;
}
int check_user_id(struct User user_database[] , int size , int id)
{
    int i=0,ret_code=0;
    for(int i=0 ; (i<size) && (!ret_code) ; i++)
    {
        if(user_database[i].user_id == id)
        {
            ret_code = 1;
        }
    }
    return ret_code;
}
void initialise_user_database(struct User user_database[],int size)
{
    for(int i=0 ; i<size ; i++)
    {
        user_database[i].user_id = 0;
        user_database[i].user_name[0] = '\0';
        user_database[i].user_income = 0;
    }
}
void initialise_family_database(struct Family family_database[] , int size)
{
    for(int i=0 ; i<size ; i++)
    {
        family_database[i].family_id = 0;
        family_database[i].family_name[0] = '\0'; 
        family_database[i].family_income = 0;
        family_database[i].monthly_expense = 0;
        for(int j=0 ; j<FAMILY_SIZE ; j++){
            family_database[i].Users_id_family[j] = 0;
        }
    }
}
void initialise_expense_database(struct Expense expense_database[] , int size)
{
    for(int i=0 ; i<size ; i++)
    {
        expense_database[i].expense_id = 0;
        expense_database[i].expense_category[0] = '\0';
        expense_database[i].expense_amount = 0;
        expense_database[i].user_id = 0;
        expense_database[i].expense_date.day = 0;
        expense_database[i].expense_date.month = 0;
    }
}
int AddUser(struct User user_database[] , int size , int id , float income , char name[])
{   
    int i=0,ret_code=0,flag=0;
    while((user_database[i].user_id < id) && (i < size) && (user_database[i].user_id != 0) && (user_database[i].user_id != id)) // checking for space in sorted array of structures
    {
        i++;
    }
    if(i == size) //if i will be size then no space is present
    {
        printf("There is no space present\n");
        ret_code = 0;
    }
    else{
        int j=i,found=0;
        while(j<size && !found) // For checking the last filled available in the user database array
        {
            if(user_database[j].user_id == 0){
                found = 1;
            }
            else{
                j++;
            }
        }
        for(int k=j ; k>=i ; k--) //Shifting all elements by 1 to make space for new user in database
        {
            user_database[k+1].user_id = user_database[k].user_id;
            strcpy(user_database[k+1].user_name , user_database[k].user_name);
            user_database[k+1].user_income = user_database[k].user_income;
        }
        user_database[i].user_id = id; //Copying the user's data in space made
        strcpy(user_database[i].user_name , name);
        user_database[i].user_income = income;
        printf("user successfully Added\n");
        ret_code = 1;
        int family;
        printf("Do you want to add this user in existing family press 1 or to create a new family press 0\n");
        scanf("%d",&family);
        if(family)
        {
            printf("Enter the family id\n");
            int family_id;
            scanf("%d",&family_id);
            update_or_delete_individual_family_details(user_database,family_database,id,family_id);
        }
        else
        {
            printf("Enter the family id and family name\n");
            int family_id;
            char family_name[NAME_SIZE];
            scanf("%d",&family_id);
            scanf("%s",&family_name);
            int user_ids[4] = {id,0,0,0};
            CreateFamily(family_database,FAMILY_DB_SIZE,family_id,user_ids,family_name,income);
        }
    }
    
    return ret_code;

}
int AddExpense(struct Expense expense_database[] , int size , int exp_id , int user_id , char category[] , float expense , int day , int month)
{
    int ret_code;
    int i=0,found=0;
    while((i<size) && (!found)) //Checking the elements with the same user id as input user id
    {
        if(expense_database[i].user_id == user_id)
        {
            found = 1;
        }
        i++;
    }
    int j=0;
    while((j<size) && (expense_database[j].expense_id != 0)) // Checking the location upto which this array is filled
    {
        j++;
    }
    if(j == size) // If whole array is filled then j is equal to size
    {
        printf("No space is present for extra input\n");
        ret_code = 0;
    }
    else if(j<size && found == 0) // If j is less than size but the user id don't have any previous expense
    {
        expense_database[j].expense_amount = expense;
        expense_database[j].expense_id = exp_id;
        expense_database[j].user_id = user_id;
        strcpy(expense_database[j].expense_category , category);
        expense_database[j].expense_date.day = day;
        expense_database[j].expense_date.month = month;
        printf("Expense Id is successfully created\n");
        ret_code = 1;
    }
    else // Adding the expense id with user id's
    {
        int k = i-1,is_exist=0;
        while(k<size && expense_database[k].user_id == user_id && expense_database[k].expense_id < exp_id) /* Getting the location where it can fit in this array*/
        {
            if(expense_database[k].expense_id == exp_id)//Checking if the expense id does exist in the array or not
            {
                is_exist = 1;
            }
            k++;
        }
        if(is_exist)
        {
            printf("Expense Id already exists\n");
            update_delete_expense(expense_database , EXPENSE_DB_SIZE , exp_id); //Sharing this to update the existing expense
        }
        else // Continue if the expense array don't exist in the array
        {
            for(int z=j ; z>=k ; z--) // Moving all the elements by 1 position to get the space for input values
            {
                expense_database[z+1].expense_amount = expense_database[z].expense_amount;
                expense_database[z+1].expense_id = expense_database[z].expense_id;
                expense_database[z+1].user_id = expense_database[z].user_id;
                strcpy(expense_database[z+1].expense_category,expense_database[z].expense_category);
                expense_database[z+1].expense_date.day = expense_database[z].expense_date.day;
                expense_database[z+1].expense_date.month = expense_database[z].expense_date.month;
            }
            expense_database[k].expense_amount = expense;
            expense_database[k].expense_id = exp_id;
            expense_database[k].user_id = user_id;
            strcpy(expense_database[k].expense_category , category);
            expense_database[k].expense_date.day = day;
            expense_database[k].expense_date.month = month;
            printf("Expense Id is successfully created\n");
            ret_code = 1;
        }
    }
    return ret_code;
}
int CreateFamily(struct Family family_database[], int size , int family_id , int user_ids[] , char name[] , float income)
{
    int ret_code = 0;
    
    float expense=0;
    int i=0,j=0,found=0;
    i=0;
    while((i<size) && (family_database[i].family_id <= family_id) && (family_database[i].family_id != 0) && (!found))//Checking if the family id is smaller than some id(for doing insertion sort taking i)
    {
        if(family_database[i].family_id == family_id)
        {
            found = 1;
        }
        i++;
    }
    while((j<size) && (family_database[j].family_id != 0))//Checking up to where the array is filled and from where it is empty
    {
        j++;
    }
    if(j == size)//If the array is full then j will become equal to the size
    {
        printf("No space is available for creating family");
        ret_code = 0;
    }
    else
    {
        for(int k=j ; k>=i ; k--)//Moving all the elements by 1 to get the space for the input by user
        {
            family_database[k+1].family_id = family_database[k].family_id;
            family_database[k+1].family_income = family_database[k].family_income;
            family_database[k+1].monthly_expense = family_database[k].monthly_expense;
            strcpy(family_database[k+1].family_name , family_database[k].family_name);
            for(int z=0 ; z<FAMILY_SIZE ; z++)
            {
                family_database[k+1].Users_id_family[z] = family_database[k+1].Users_id_family[z];
            }
        }
        family_database[i].family_id = family_id; 
        family_database[i].family_income = income;
        strcpy(family_database[i].family_name , name);
        for(int k=0 ; k<4 ; k++)
        {
            family_database[i].Users_id_family[k] = user_ids[k];
        }
        
        for(int a=0 ; a<FAMILY_SIZE ; a++)
        {
            for(int b=0 ; b<EXPENSE_DB_SIZE ; b++)
            {
                if(family_database[i].Users_id_family[a] == expense_database[b].user_id)
                {
                    expense += expense_database[b].expense_amount;
                }
            }
        }
        family_database[i].monthly_expense = expense;
        printf("The Family has been Created\n");
        ret_code = 1;
    }
    
    return ret_code;
}
int update_delete_expense(struct Expense expense_database[] , int size , int exp_id)
{
    int ret_code;
    printf("For updating expense enter 1 else for deleting enter 0\n");
    int update;
    scanf("%d",&update);
    if(update)//For updating the expense
    {
        int found = 0,i=0;
        for(i=0 ; i<size && (!found) ; i++) //Checking for the expense id in the database
        {
            if(expense_database[i].expense_id == exp_id)
            {
                found = 1;
            }
        }
        i = i-1;
        if(found == 1)//If the expense id is present in the database
        {
            float expense;
            char category[CATEGORY_SIZE];
            int day,month;
            printf("Enter the updated expense amount\n");
            scanf("%f",&expense);
            printf("Enter the updated category of the expense\n");
            scanf("%s",&category);
            printf("Enter the updated day and month of expense\n");
            scanf("%d%d",&day,&month);
            expense_database[i].expense_amount = expense;//Updating the database by giving new values
            expense_database[i].expense_date.day = day;
            expense_database[i].expense_date.month = month;
            strcpy(expense_database[i].expense_category , category);
            printf("Expense successfully Updated\n");
            ret_code = 1;
        }
        else//If the expense id is not present
        {
            printf("Expense of expense id %d does not exist",exp_id);
            ret_code = 0;
        }
    }
    else
    {
        int found = 0,i=0;
        for(i=0 ; i<size && (!found) ; i++) //Checking for the expense id in the database
        {
            if(expense_database[i].expense_id == exp_id)
            {
                found = 1;
            }
        }
        if(found == 1)
        {
            int k=i;
            for(k=i ; k<size ; k++)//Shifting all the expenses by 1 place where the expense is deleted
            {
                expense_database[k-1].expense_amount = expense_database[k].expense_amount;
                expense_database[k-1].expense_id = expense_database[k].expense_id;
                expense_database[k-1].user_id = expense_database[k].user_id;
                expense_database[k-1].expense_date.day = expense_database[k].expense_date.month;
                expense_database[k-1].expense_date.month = expense_database[k].expense_date.month;
                strcpy(expense_database[k-1].expense_category , expense_database[k].expense_category);
            }
            printf("Expense deleted succesfully\n");
            ret_code = 1;
        }
        else
        {
            printf("Expense does not exist\n");
            ret_code = 0;
        }
        
    }
}
float get_total_expense(struct Expense expense_database[] , int size , int family_id , int month)
{
    int is_exist=0;
    float ret_value = 0;
    int i=0;
    for(i=0 ; (i<FAMILY_DB_SIZE) && (!is_exist) ; i++) //Checking if the family exist or not
    {
        if(family_id == family_database[i].family_id)
        {
            is_exist = 1;
        }
    }
    if(is_exist)
    {
        i = i-1;
        float total_expense = 0;
        float total_income = 0;
        for(int j=0 ; j<FAMILY_SIZE ; j++)
        {
            int user_id = family_database[i].Users_id_family[j];
            for(int k=0 ; k<EXPENSE_DB_SIZE ; k++)
            {
                if((expense_database[k].user_id == user_id) && (expense_database[k].expense_date.month == month)) //Checking for the given month and user id
                {
                    total_expense = total_expense + expense_database[k].expense_amount;
                }
            }
            total_income += income_individual(user_database,USER_DB_SIZE,user_id);
        }
        if(total_income < total_expense)
        {
            printf("Total expense surpasses the total income by %f\n",total_expense-total_income);
        }
        else
        {
            printf("Total expense is less than total income of the Family\n");
        }
        ret_value = total_expense;
    }
    else
    {
        printf("This Family do not exist\n");
    }
    return ret_value;
}
float get_categorical_expense(struct Expense expense_database[] , int size , int family_id , char category[])
{
    int is_exist = 0;
    float ret_val = 0;
    int i=0;
    for(i=0 ; (i<FAMILY_DB_SIZE) && (!is_exist) ; i++)//Checking if it exists
    {
        if(family_id == family_database[i].family_id)
        {
            is_exist = 1;
        }
    }
    if(is_exist)
    {
        i = i-1;
        float total_expense = 0;
        float expense_id[4] = {0};
        for(int k=0 ; k<4 ; k++)
        {
            int id = family_database[i].Users_id_family[k];
            for(int z=0 ; z<size ; z++) //Getting all the expenses of the category
            {
                if((expense_database[z].user_id == id) && !(strcmp(expense_database[z].expense_category , category)))
                {
                    expense_id[k] += expense_database[z].expense_amount;
                }
            }
            total_expense += expense_id[k];
        }
        printf("Total expense of category %s is %f\n",category,total_expense);
        for(int o=0 ; o<3 ; o++) 
        {
            int min = expense_id[o];
            int loc = o;
            for(int l = o+1 ; l<4 ; l++)
            {
                if(expense_id[l] < min)
                {
                    min = expense_id[l];
                    loc = l;
                }
            }
            expense_id[loc] = expense_id[o];
            expense_id[o] = min;
        }
        for(int b=0 ; b<4 ; b++)
        {
            printf("The user %d spends %f on %s category\n",b+1,expense_id[b],category);
        }

        ret_val = 1;
    }
    else
    {
        printf("This family do not exist\n");
        ret_val = 0;
    }
    return ret_val;
}
int get_highest_expense_day(struct Expense expense_database[] , int size , int family_id)
{
    int ret_val = 0;
    int user_ids[4] = {0};
    int is_exist = 0,i = 0;
    for(i=0 ; (i<FAMILY_DB_SIZE) && (!is_exist); i++)
    {
        if(family_database[i].family_id == family_id)
        {
            is_exist = 1;
        }
    }
    if(is_exist)
    {
        i = i-1;
        for(int j=0 ; j<FAMILY_SIZE ; j++)
        {
            user_ids[j] = family_database[i].Users_id_family[j];
        }
        int month = 1,day = 1;
        float maximum_expense = 0;
        struct date max_day;
        for(month = 1 ; month <= MONTH_SIZE ; month++)
        {
            float expense_day = 0;
            for(day = 1 ; day<=DAY_SIZE ; day++)
            {
                for(int z=0 ; z<FAMILY_SIZE ; z++)//For every user calculating for condition of day and month
                {
                    for(int k=0 ; k<EXPENSE_DB_SIZE ; k++)
                    {
                        if((expense_database[k].user_id == user_ids[z]) && (expense_database[k].expense_date.day == day) && (expense_database[k].expense_date.month == month)) //Checking this for a day in the year
                        {
                            expense_day += expense_database[k].expense_amount;
                        }
                    }
                }
                if(expense_day > maximum_expense)
                {
                    maximum_expense = expense_day;
                    max_day.day = day;
                    max_day.month = month;
                }
            }
        }
        printf("The maximum expense is done on the %d day %d month which was %f\n",max_day.day,max_day.month,maximum_expense);
        ret_val = 1; 
    }
    else
    {
        printf("The family of family id %d does not exist\n",family_id);
        ret_val = 0;
    }

    return ret_val;
}
float get_individual_expense(struct Expense expense_database[] , int size , int user_id)
{
    int i=0;
    float total_expense = 0;
    struct expense_user 
    {
        float expense;
        char category[CATEGORY_SIZE];
    };
    struct expense_user expenses[5];
    expenses[0].expense = 0; //Initially keeping it for each category eg Utility at 0 and rent at 1 and so on
    expenses[1].expense = 0;
    expenses[2].expense = 0;
    expenses[3].expense = 0;
    expenses[4].expense = 0;
    int cnt = 0;
    for(i=0 ; i<EXPENSE_DB_SIZE ; i++)
    {
        if(expense_database[i].user_id == user_id)
        {
            total_expense += expense_database[i].expense_amount;
            expenses[cnt].expense += expense_database[i].expense_amount;
            strcpy(expenses[cnt].category , expense_database[i].expense_category);
            cnt++;
        }
    }
    //Sort this expenses-> expense then print it out for all
    int flag =0 ;
    for(int j=0 ; j<FAMILY_SIZE && !flag; j++)
    {
        for(int k=0 ; k<FAMILY_SIZE-j ; k++)
        {
            if(expenses[k].expense > expenses[k+1].expense)
            {
                float temp = expenses[k].expense;
                expenses[k].expense = expenses[k+1].expense;
                expenses[k+1].expense = temp;
                char name[NAME_SIZE];
                strcpy(name , expenses[k].category);
                strcpy(expenses[k].category , expenses[k+1].category);
                strcpy(expenses[k+1].category , name);
            }
        }
    }
    int a;
    for(a=0 ; a<5 ; a++)
    {
        if(expenses[a].expense == 0)
        {
            break;
        }
    }
    for(int b = a-1 ; b>=0 ; b++)
    {
        printf("Expense for %s was %f\n",expenses[b].category,expenses[b].expense);
    }
    printf("Total expense of the user %d is %f\n",user_id,total_expense);
}
void update_or_delete_individual_family_details(struct User user_database[] , struct Family family_database[] , int user_id , int family_id)
{
    
    int update_delete;
    printf("Do you want to update or delete?\nFor update press 1 else 0\n");
    scanf("%d",&update_delete);
    
    int i=0,j=0;
    int found = 0;
    for(i=0 ; (i<USER_DB_SIZE) && (!found) ; i++)
    {
        if(user_database[i].user_id == user_id)
        {
            found = 1;
        }
    }
    i = i-1;
    found = 0;
    for(j=0 ; (j<FAMILY_DB_SIZE) && (!found) ; j++)
    {
        if(family_database[j].family_id == family_id)
        {
            found = 1;
        }
    }
    j = j - 1;
    found = 0;
    int k=0;
    for(k=0 ; k<FAMILY_SIZE && !found; k++)
    {
        if(family_database[j].Users_id_family[k] == user_id)
        {
            found = 1;
        }
    }
    if(!update_delete)
    {
        if(user_id!=0)
        {
            family_database[j].family_income = family_database[j].family_income - user_database[i].user_income;
            
            if(k==1)
            {
                for(int o=j ; (family_database[o].family_id != 0) && (o<FAMILY_DB_SIZE) ; o++)
                {
                    family_database[o].family_id = family_database[o+1].family_id;
                    family_database[o].family_income = family_database[o+1].family_income;
                    strcpy(family_database[o].family_name , family_database[o+1].family_name);
                    family_database[o].monthly_expense = family_database[o+1].monthly_expense;
                    for(int z=0 ; z<4 ; z++){
                        family_database[o].Users_id_family[z] = family_database[o+1].Users_id_family[z];
                    } 
                }
                
                printf("Family with family id %d deleted\n",family_id);
            }
            else
            {
                k = k-1;
                if(k==3)
                {
                    family_database[j].Users_id_family[3] = 0;
                }
                else
                {
                    for(int z=k ; z<3 ; z++)
                    {
                        family_database[j].Users_id_family[k] = family_database[j].Users_id_family[k+1];
                    }
                }
            }
            for(int z=i ; (z<USER_DB_SIZE) && (user_database[z].user_id != 0) ; z++)
            {
                user_database[z].user_id = user_database[z+1].user_id;
                user_database[z].user_income = user_database[z+1].user_id;
                strcpy(user_database[z].user_name , user_database[z+1].user_name);
            }
            printf("User with user id %d is deleted\n",user_id);
        }
        else
        {
            int user_ids[FAMILY_SIZE];
            for(int z=0 ; z<FAMILY_SIZE ; z++)
            {
                user_ids[z] = family_database[j].Users_id_family[z];
            }
            for(int z=j ; (z<FAMILY_DB_SIZE) && (family_database[z].family_id != 0) ; z++)
            {
                family_database[z].family_id = family_database[z+1].family_id;
                family_database[z].family_income = family_database[z+1].family_income;
                family_database[z].monthly_expense = family_database[z+1].monthly_expense;
                strcpy(family_database[z].family_name , family_database[z+1].family_name);
                for(int a=0 ; a<4 ; a++)
                {
                    family_database[z].Users_id_family[a] = family_database[z+1].Users_id_family[a];
                }
            }
            for(int z=0 ; z<FAMILY_SIZE ; z++)
            {
                int id,a,check=0;
                id = user_ids[z];
                for(a=0 ; (a<USER_DB_SIZE) && (!check) ; a++)
                {
                    if(id == user_database[a].user_id)
                    {
                        check = 1;
                    }
                }
                a = a-1;
                for(int b=a ; (b<USER_DB_SIZE) && (user_database[b].user_id != 0) ; b++)
                {
                    user_database[b].user_id = user_database[b+1].user_id;
                    user_database[b].user_income = user_database[b+1].user_income;
                    strcpy(user_database[b].user_name , user_database[b+1].user_name);
                }
            }
            printf("Family with family id %d delete\n",family_id);
        }
    }
    else
    {
        if(user_id!=0)
        {
            printf("Enter the updated information for name and income\n");
            float new_income;
            char new_name[NAME_SIZE];
            scanf("%s",&new_name);
            scanf("%f",&new_income);
            float change = new_income - user_database[i].user_income;
            strcpy(user_database[i].user_name , new_name);
            user_database[i].user_income = new_income;
            family_database[j].family_income += change;
            printf("User updated Successfully\n");
        }
        else
        {
            printf("Enter the user id,name and income which you want to add\n");
            int new_user,check = 0,a;
            float new_income;
            char new_name[NAME_SIZE];
            scanf("%d",&new_user);
            scanf("%s",new_name);
            scanf("%f",new_income);
            for(a=0 ; a<FAMILY_SIZE && !check ; a++)
            {
                if(family_database[j].Users_id_family[a] == 0)
                {
                    check = 1;
                }
            }
            if(check)
            {
                a = a-1;
                family_database[j].Users_id_family[a] = new_user;
                family_database[j].family_income += new_income;
                for(int b=0 ; b<EXPENSE_DB_SIZE ; b++)
                {
                    if(expense_database[b].user_id == new_user)
                    {
                        family_database[j].monthly_expense += expense_database[b].expense_amount;
                    }
                }
                printf("Family updated Successfully\n");
            }
            else
            {
                printf("There is no space available in family\n");
            }
        }
    }
}
int main()
{
    int i,exitLoop = 0;
    initialise_user_database(user_database,USER_DB_SIZE);
    initialise_family_database(family_database,FAMILY_DB_SIZE);
    initialise_expense_database(expense_database,EXPENSE_DB_SIZE);
    //Sort the initial databases on the basis of user_id
    sort_user_db(user_database,USER_DB_SIZE);
    sort_family_db(family_database,FAMILY_DB_SIZE);
    sort_expense_db(expense_database,EXPENSE_DB_SIZE);
    while(!exitLoop)
    {
        int menu_code;
        printf("\tExpense Tracking System\n");
        printf("Menu\n1.Add User\n2.Add Expense\n3.Create Family\n4.Update or delete individual family details\n5.Update or delete expense\n6.Get Total expense\n7.Get categorical expense\n8.Get highest expense day\n9.Get individual expense\n10.Exit\n");
        printf("Enter number between 1 to 10\n");
        scanf("%d",&menu_code);
        if(menu_code < 1 && menu_code > 10)
        {
            printf("Invalid input");
        }
        else
        {
            switch (menu_code)
            {
            case 1:
            {
                int id;
                float income;
                char name[NAME_SIZE];
                printf("Enter your user id\n"); // Taking input from user
                scanf("%d",&id);
                int check = check_user_id(user_database,USER_DB_SIZE,id);
                if(!check){
                    printf("Enter your name\n");
                    scanf("%s",&name);
                    printf("Enter your income\n");
                    scanf("%f",&income);
                    AddUser(user_database,USER_DB_SIZE,id,income,name);
                }
                else
                {
                    printf("Already exists\n");
                }
                break;
            }
            case 2:
            {
                int exp_id,user_id;
                char category[CATEGORY_SIZE];
                float expense;
                int day,month;
                printf("Enter Expense id\n"); // Taking input from the user
                scanf("%d",&exp_id);
                printf("Enter User id\n");
                scanf("%d",&user_id);
                printf("Enter the category\n");
                scanf("%s",&category);
                printf("Enter the expense amount\n");
                scanf("%f",&expense);
                printf("Enter the day and month of the expense");
                scanf("%d%d",&day,&month);
                AddExpense(expense_database,EXPENSE_DB_SIZE,exp_id,user_id,category,expense,day,month);
                break;
            }
            case 3:
            {
                int family_id; //Taking inputs from the user about the family
                int user_ids[4];
                char name[NAME_SIZE];
                float income=0;
                printf("Enter The family id\n");
                scanf("%d",&family_id);
                if(!check_family_id(family_database,FAMILY_DB_SIZE,family_id)){
                    printf("Enter the number of individuals in the family\n");
                    int n;
                    scanf("%d",&n);
                    if(n>4 || n<1) //If the user has given wrong number of individuals in the input
                    {
                        printf("Invalid input , Number of individuals in family can be between 1 to 4\n");
                    }
                    else
                    {
                        for(int i=0 ; i<n ; i++)//Taking the input of all the user ids 
                        {
                            printf("Enter the user id of %dth individual\n",i+1);
                            scanf("%d",&user_ids[i]);
                            if(!check_user_id(user_database,USER_DB_SIZE,user_ids[i]))//Checking that if the input user id already exists or not 
                            {
                                printf("User id is not registered, Register it first\n");
                                float income_new;
                                char name_new[NAME_SIZE];
                                printf("Enter the income of %d id\n",user_ids[i]);
                                scanf("%f",&income_new);
                                printf("Enter the name of the individual\n");
                                scanf("%s",&name_new);
                                AddUser(user_database,USER_DB_SIZE,user_ids[i],income_new,name_new);
                            }

                        }
                        printf("Enter the name of family\n");
                        scanf("%s",&name);
                        int i=0;
                        while(i<n)//Adding the input of the all individuals of the family
                        {
                            float temp;
                            temp = income_individual(user_database,USER_DB_SIZE,user_ids[i]);
                            income = income + temp;
                            i++;
                        }
                        CreateFamily(family_database,FAMILY_DB_SIZE,family_id,user_ids,name,income);
                    }
                }
                else
                {
                    printf("Family Id already exists\n");
                }
                break;
            }
            case 4:
            {
                printf("Do you want to do a function on a family or a individual,for family press 1 else 0\n");
                int check;
                scanf("%d",&check);
                if(check)
                {
                    int family_id;
                    printf("Enter family id\n");
                    scanf("%d",&family_id);
                    if(check_family_id(family_database,FAMILY_DB_SIZE,family_id) )
                    {
                        update_or_delete_individual_family_details(user_database,family_database,0,family_id);
                    }
                    else
                    {
                        printf("Family id does not exist\n");
                    }
                }
                else
                {
                    int family_id,user_id;
                    printf("Enter family id and user id\n");
                    scanf("%d%d",&family_id,&user_id);
                    if(check_family_id(family_database,FAMILY_DB_SIZE,family_id) && check_user_id(user_database,USER_DB_SIZE,user_id))
                    {
                        update_or_delete_individual_family_details(user_database,family_database,user_id,family_id);
                    }
                    else
                    {
                        printf("Family id or User id does not exist\n");
                    }
                }
                break;
            }
            case 5:
            {
                int exp_id;
                printf("Enter the expense id you want to update or delete\n");
                scanf("%d",&exp_id);
                update_delete_expense(expense_database , EXPENSE_DB_SIZE , exp_id);
                break;
            }
            case 6:
            {
                int family_id;
                float ans;
                printf("Enter the Family id for getting expense of family\n");
                scanf("%d",&family_id);
                printf("Enter the month of the year in numeric form (January = 1,feb =2...)\n");
                int month;
                scanf("%d",&month);
                ans = get_total_expense(expense_database , EXPENSE_DB_SIZE , family_id , month);
                if(ans != 0){
                    printf("Total expense of the Family is %f",ans);
                }
                break;
            }
            case 7:
            {
                int family_id;
                char category[CATEGORY_SIZE];
                printf("Enter the family id\n");
                scanf("%d",&family_id);
                printf("Enter the category\n");
                scanf("%s",&category);
                get_categorical_expense(expense_database , EXPENSE_DB_SIZE , family_id , category);
                break;
            }
            case 8:
            {
                int family_id;
                printf("Enter the family id of the family of getting maximum expense of a day\n");
                scanf("%d",&family_id);
                get_highest_expense_day(expense_database , EXPENSE_DB_SIZE , family_id);
                break;
            }
            case 9:
            {
                int id;
                printf("Enter the user id for getting expenses\n");
                scanf("%d",&id);
                int is_exist = 0;
                is_exist = check_user_id(user_database , USER_DB_SIZE , id);
                if(is_exist)
                {
                    get_individual_expense(expense_database , EXPENSE_DB_SIZE , id);
                }
                else
                {
                    printf("User does not exist\n");
                }
                break;
            }
            case 10:
                exitLoop = 1;
                break;
            default:
                break;
            }
        }
        printf("If you want to continue enter 1 else enter 0\n");
        int cnt;
        scanf("%d",&cnt);
        if(cnt == 1){
            exitLoop = 0;
        }
        else{
            exitLoop = 1;
        }
    }
   
}
