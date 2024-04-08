#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

void login();
void registration();
void shoap();
void choose();
void admin();
void user();
int searchUserName(char username[]);
int findUser(char username[],char password[]);
void add_product();
void remove_product();
void update_product();
void show_transactions(char user[]);
struct sub_product{
	char subP_id[8];
	char product_name[25];
	int price;
	int quantity;
};
struct product{
	char product_id[8];
	char product_name[25];
	struct sub_product products[8];
};
int read_product(struct product p[]);
int read_subProduct(struct sub_product p[],char name[]);
void write_product(struct product p[],int size);
int search_product(struct product p[],char id[],int size);

// the starting function of the app
void start(){
	int option;
printf("'1'.  Admin\n'2'.  User\n'3'. Exit App\n\n");
scanf("%d",&option);
 if(option==1){
 	admin();
 }
 else if(option==2){
 	user();
 } 
 else if(option==3){ 
  return; 
 }
 else{
 	printf("You choosed wrong option..\n");
 	start();
 }
 start();
}


//for user 
void user(){
	choose();
} 



// write products on text file
void write_product(struct product p[],int size){
 FILE *temp, *write;
//to clear file 
   temp = fopen("products.txt", "w");
   
   fclose(temp);
     if(write = fopen("products.txt", "a")){ 
     int i;
     for(i=0;i<size;i++){
     	if(i==size-1)
     	fprintf(write,"%s %s",p[i].product_id,p[i].product_name);
     	else{
     		fprintf(write,"%s %s\n",p[i].product_id,p[i].product_name);
		 }
	 }
	  fclose(write);
}
 else{ 
 	 printf("\nFile cannot open, try again."); 
 	
 }
}

//write product items on a text file 
void write_sub_product(struct sub_product p[],int size,char name[25]){
FILE *write,*temp ; 
//to clear file 
  char nm[25];
  strcpy(nm,name);
  strcat(nm,".txt");
   temp = fopen(nm, "w");
   fclose(temp);
     if(write = fopen(nm, "a")){ 
     int i;
     for(i=0;i<size;i++){ 
     	if(i==size-1)
     	fprintf(write,"%s %s %d %d",p[i].subP_id,p[i].product_name,p[i].price,p[i].quantity);
     	else{
     		fprintf(write,"%s %s %d %d\n",p[i].subP_id,p[i].product_name,p[i].price,p[i].quantity);
		 } 
	 }
	  fclose(write);
}
 else{ 
 	 printf("\nFile cannot open, try again."); 
 	
 }
}


// tracking transactions of users , write on text file
void write_transactions(char user_name[40],char product_name[40],int bill){
FILE *write,*temp ; 
  
     if(write = fopen("transactions.txt", "a")){ 
     		fprintf(write,"%s  Product:  %s  Bill:  %dRS\n",user_name,product_name,bill);
		
	 
	  fclose(write);
}
 else{ 
 	 printf("\nFile cannot open, try again."); 
 	
 }
}

//read items from a file 
int read_subProduct(struct sub_product p[],char name[]){
	char file[20];
	strcpy(file,name);
	strcat(file,".txt");
	FILE* log = fopen(file, "r"); 
	if(!log){ 
printf("\n Unable to open : %s ");
return -1;
} 
else{ 

int found=0;
int i=0;
while (!feof(log)) { 
	
   fscanf(log,"%s",&p[i].subP_id);
      fscanf(log,"%s",&p[i].product_name);
	   fscanf(log,"%d",&p[i].price);
	    fscanf(log,"%d",&p[i].quantity);
      i++;
}

fclose(log);
return i;
}
}


// add product to the existing list of products and save on a file
void add_product(){
	struct product p[12];
	int i=read_product(p);
	system("CLS");
	printf("\tAvailable products\n");
	int j;
   for(j=0;j<i;j++)
  printf("%s \t%s \n",p[j].product_id,p[j].product_name);
  
  printf("\tAdd a product\n");
  printf("Enter product_id");
  scanf("%s",p[i].product_id);
  if(search_product(p,p[i].product_id,i)!=-1){
 	printf("Product ID Already exists!\n");
 	return;
 }
  printf("Enter product name");
  scanf("%s",p[i].product_name);
  
 
  write_product(p,i+1);
  printf("Product Added successfully!\n");
}


// search for a product in the list  in files 
int search_product(struct product p[],char id[],int size){
int j;
	for(j=0;j<size;j++)
  {
  	if(strcmp(p[j].product_id,id)==0){
  		return j;
	  }
  }
  return -1;
}


//search items of a product 
int search_subProduct(struct sub_product p[],char id[],int size){
int j;
	for(j=0;j<size;j++)
  {
  	if(strcmp(p[j].subP_id,id)==0){
  		return j;
	  }
  }
  return -1;
}


//remove one of the item from existing list 
void remove_product(){
	struct product p[12];
	int i=read_product(p);
	system("CLS");
	printf("\tAvailable products\n");
	int j;
   for(j=0;j<i;j++)
  printf("%s \t%s \n",p[j].product_id,p[j].product_name);
  
  printf("\tremove a product\n");
  char p_id[20];
  printf("Enter product_id");
  scanf("%s",p_id);
  int index=search_product(p,p_id,i);
  if(index!=-1){
  	for(j=index;j<i;j++){
     p[j]=p[j+1];
     
 }
 write_product(p,i-1);
    printf("Product removed successfully\n"); 
  }
  else{
  	printf("Product id not found\n");
  } 
  
  
  
}


//update one of a product and update it on text file
void update(){
	
	struct product p[12];
	int i=read_product(p);
	int back;
	 int choice;
	 system("CLS");
	 do{
	printf(" Proucts available\n");
int j;
for(j=0;j<i;j++)
printf("%d.  %s %s \n",j+1,p[j].product_id,p[j].product_name);
printf("%d.  go to Main MENU\n",j+1);
 back=j+1;
  printf("Wich product you wan to update?");
  scanf("%d",&choice);
struct sub_product subP[15];
 if(choice<=j+1){ 
	if(choice<j+1)
       { 
      	int n=read_subProduct(subP,p[choice-1].product_name);
       	printf(" Proucts available\n");

for(j=0;j<n;j++)
printf("%s \t %s  \t%dRs \t %d\n",subP[j].subP_id,subP[j].product_name,subP[j].price,subP[j].quantity);
int op;
do{
printf("1.  add new item\n");
printf("2.  delete an item\n");
printf("3.  update item\n");
printf("4.  go back\n");

printf("Choose an option:");
scanf("%d",&op);


	   switch(op){
	   	case 1:
	   		printf("Enter item id:");
	   		scanf("%s",subP[n].subP_id);
	   			if(search_subProduct(subP,subP[n].subP_id,n)!=-1){
	   		printf("Item ID already exists\n");
	   		return;
	   	}
	   		printf("Enter item name:");
	   		scanf("%s",subP[n].product_name);
	   		printf("Enter item Price:");
	   		scanf("%d",&subP[n].price);
	   		printf("Enter item quantity:");
	   		scanf("%d",&subP[n].quantity);
	   	write_sub_product(subP,n+1,p[choice-1].product_name);
	   printf("Item Added successfully\n");
	   		
	   		break;
	   		
	   	case 2:
	  
  printf("Enter product_id");
  char p_id[20];
  scanf("%s",p_id);
  int index=search_subProduct(subP,p_id,n);
  if(index!=-1){
  	for(j=index;j<n-1;j++){
     subP[j]=subP[j+1];    
 }
 write_sub_product(subP,n-1,p[choice-1].product_name);
  }
  else{
  	printf("Id not found\n");
  }
	   break;
	   
	case 3:
  printf("Enter product_id");
  scanf("%s",p_id);
  index=search_subProduct(subP,p_id,n);
  if(index!=-1){
  	        printf("You are going to update %s\n",subP[index].product_name);
  	        printf("Enter item Price:");
	   		scanf("%d",&subP[index].price);
	   		printf("Enter item quantity:");
	   		scanf("%d",&subP[index].quantity);
	   		 write_sub_product(subP,n,p[choice-1].product_name);
	   		printf("\n  updated\n");
}
else{
	printf("Id not found\n");
}
break;
 case 4:
 	break;
 	default:
 		printf("wrong choosed\n");
}
}while(op!=4);
}
}
else{
	printf("Wrong\n");
}

}while(choice!=back);

}


//fucntion for admin works
void admin(){ 
int opt;

//admin username:mujtaba4509
//password: skxm5380
char u_name[25];
char password[25];
printf("Enter your username: ");
scanf("%s",u_name);
printf("Enter your password: ");
scanf("%s",password);
if(strcmp(u_name,"mujtaba4509")!=0 || strcmp(password,"skxm5380")!=0){
	printf("Incorrect inputs\n");
}
else{
	system("CLS");
do{
	
	printf(" \tAdmin Menu\n");
	printf("1.  add Product\n");
	printf("2.  remove product\n");
	printf("3.  update products\n");
	printf("4.  check a user transactions\n");
	printf("5.  show all transactions\n");
	printf("6.  log Out\n");
	printf("Enter choice..");
	
	scanf("%d",&opt);
	system("CLS");
 switch(opt){
 	case 1:
 	
 		add_product();
 		break;
 	case 2:
 	
	    remove_product();
		break;
	case 3:
	    update();
		break;
		case 4:
			printf("Enter username of the user :  ");
			scanf("%s",u_name);
	    show_transactions(u_name);
		break;
		case 5:
	    show_transactions("emty");
		break;
	case 6:	
	    
	    
	   break;
	  default:
	      printf("Wrong choosed,try again\n");
 }
}while(opt!=6);
 
}
}

 
 
 // options for a user to choose
void choose()
{ 
int option;
printf("'1'.  Register\n'2'.  Login\n'3'.  go Back\n\n");
scanf("%d",&option);
getchar();           
if(option == 1)
{
system("CLS");
registration();
}
else if(option==2)
{
	login();
}
else if(option==3)
{
return;
}
else{
	printf("Wrong optiion..\n");
	choose();
}
}


//registration of a new user and save on file
void registration()
{ 
char firstname[15]; 
char lastname[15]; 
char username[20]; 
char password[30]; 
int logged=0;
printf("\nEnter First Name:\n");
scanf("%s",firstname);
printf("\nEnter Last Name:\n");
scanf("%s",lastname);
printf("Thank you.\nNow please choose a username and password as credentials for system login.\nEnsure the username is no more than 30 characters long.\nEnsure your password is at least 8 characters long long and contains lowercase, uppercase, numerical and special character values.\n"); 
again:
printf("\nEnter Username:\n");
scanf("%s",username);
if(searchUserName(username)==1){
	printf("Username already exists,\n"); 
	goto again;
}  
printf("\nEnter Password:\n");
scanf("%s",password);
FILE *log,*write ;  
     if(log = fopen("log in.txt", "a")){ 
     
	  fprintf(log,"%s %s\n",username,password);
	  write=fopen("users.txt", "a");
	  fprintf(write,"%s %s %s\n",username,firstname,lastname);
	  fclose(write);
	   fclose(log); 
	   logged=1;
} 
 else{ 
 	 printf("\nFile cannot open, try again."); 
 	
 } 
printf("\nRegistration Successful!\n");

if(logged==1)
shoap(username);

} 


// utility function for searching username in the file
int searchUserName(char username[]){
	FILE* log = fopen("log in.txt", "r"); 
	if(!log){
printf("\n Unable to open : %s ");
return -1;
} 
else{ 
char uname[40]; 
char pswd[40]; 
int found=0;
while (!feof(log)) { 
	
   fscanf(log,"%s",&uname);
      fscanf(log,"%s",&pswd); 
     
     if(strcmp(uname,username)==0){
     	found=1;
     	break;
	 }
}

fclose(log);
return found;
}
}


//find user form file 
int findUser(char username[],char password[]){
	FILE* log = fopen("log in.txt", "r"); 
	if(!log){
printf("\n Unable to open : %s ");
return -1;
} 
else{ 
char uname[40]; 
char pswd[40]; 
int found=0;
while (!feof(log)) { 
   fscanf(log,"%s",&uname);
      fscanf(log,"%s",&pswd); 
     
     if(strcmp(uname,username)==0 && strcmp(password,pswd)==0){
     	found=1;
     	break;
	 }
}

fclose(log);
return found;
}
}


// display transacions , all transactions, transactions of a user
void show_transactions(char user[]){
	   // Admin type 
        	FILE* log = fopen("transactions.txt", "r"); 
	if(!log){
printf("\n Unable to open : %s ");
} 
else{
	 printf("\n ======> Transactions <======\n");
	char transaction[120];
if(strcmp(user,"emty")==0) { 
  
while (fgets(transaction, 120, log) != NULL) { 
    
           printf(" -->  %s", transaction);
     
} 

}

else{
	int f=0;
	while (fgets(transaction, 120, log) != NULL) { 
    if (strstr(transaction,user) != NULL) { 
    f=1;
            printf(" -->  %s", transaction);
        }
     
}
if(f==0)
printf("    No Transactions\n");
}

fclose(log);
}




}


//user will login in this function
void login()
{ 

char username[25];
char password[25];
int logged=0;
printf("\nPlease Enter your login credentials below\n\n");
printf("Username:  ");
scanf("%s",username); 
printf("\nPassword: "); 
printf("\n"); 
scanf("%s",password);
if(findUser(username,password)==1){
	logged=1;
}
else if(findUser(username,password)==0){
	printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
}

 if(logged==1){
 	shoap(username);
 }
return;
}


//all products here, read from file and show to the user
int Products(char prod_name[], char userName[]){
	int u;
	int totalbill=0,quantity,price;
	int total=0;
    char pr[20];
    strcpy(pr,prod_name);
  strcat(prod_name,".txt");
	FILE* log = fopen(prod_name, "r"); 
	if(!log){
printf("\n Unable to open : %s ");
} 
else{ 
int found=0;
int i=0;
struct sub_product p[6];
while (!feof(log)) { 
	
   fscanf(log,"%s",&p[i].subP_id);
      fscanf(log,"%s",&p[i].product_name); 
      fscanf(log,"%d",&p[i].price);
      fscanf(log,"%d",&p[i].quantity);
      i++;
}

fclose(log);
int back=0;
char p_name_temp[30];
int temp_total=0;
do{
printf("%s Proucts available\n",pr);

int j;
for(j=0;j<i;j++)
printf("%d. %s  \t%dRs\n",j+1,p[j].product_name,p[j].price);
printf("%d.Go to Back MENU\n",j+1);
back=j+1;
printf("Enter  a choice..");
scanf("%d",&u);
if(u<=j+1){
	if(u<j+1){
printf("how many %s u want? ",p[u-1].product_name);
scanf("%d",&quantity);
if(quantity<p[u-1].quantity){
totalbill=p[u-1].price*quantity;
total+=totalbill;
printf("%s bill is: %d\n",p[u-1].product_name,totalbill);
}
}


}
else{
	printf("You entered much quantity\n");
}

if(total>0 && strcmp(p_name_temp,p[u-1].product_name)!=0 && temp_total!=total ){
 	write_transactions(userName,p[u-1].product_name,total);
 } 
  strcpy(p_name_temp,p[u-1].product_name);
  temp_total=total;
}while(u!=back);
 
return total;
}
} 


//a utility funtion to read products from the file
int read_product(struct product p[]){
	FILE* log = fopen("products.txt", "r"); 
	if(!log){
printf("\n Unable to open : %s ");
return -1;
} 
else{ 

int found=0;
int i=0;
while (!feof(log)) { 
	
   fscanf(log,"%s",&p[i].product_id);
      fscanf(log,"%s",&p[i].product_name); 
      i++;
}

fclose(log);
return i;
}
}

// our main shoap , which has menus and other products
void shoap(char userName[]){
	int choice;
	int back;
	int bought=0;
		system("CLS");
printf("\n                          MS SHOPPING MART                       \n");
printf("Welcome To MS Shopping MART\n");
long total=0;
do{

printf("\nSelect from following\n");
printf("What do want to buy\n");
struct product p[12];
 int i=read_product(p);
int j;
for(j=0;j<i;j++)
printf("%d. %s  \n",j+1,p[j].product_name);
printf("%d.Check your previous transactions\n",j+1);
printf("%d.Log Out\n",j+2);
back=j+2;
printf("Enter  a choice..");
scanf("%d",&choice);
if(choice<=i+2){
	system("CLS");
	if(choice<i+1){
   total+=Products(p[choice-1].product_name,userName);
    bought=1; 
}
else if(choice==j+1){
	show_transactions(userName);
}
  else{
  	if(bought>0){
  	 printf("Your Bill is: %d\n",total);
  	 bought++;
  }
  if(bought<=2){
  	char phone[20];
  	char addr[50];
  	printf("Please Enter Phone Number: ");
  	scanf("%s",phone);
  	printf("Please Enter the address(NO SPACES) where you wanna recieve: ");
  	scanf("%s",addr);
  	printf("  Will be delievered , thanks,\n");
  }
  }
}
else{
	printf("Wrong choice,Press any key\n");
	getche();
} 

}while(choice!=back); 

}


// main driver function 
int main ()
{
start();
 
}

