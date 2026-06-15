#include <stdio.h>
#include <string.h>

void addDonation();
void viewHistory();
void awardCertificate(char name[], char subType[], float amount);
void menu();
void monetaryPackages();
void viewSortedHistory();
void viewTotalDonations();
int checkName(char name[]);
int checkPhone(char phone[]);
int checkDate(char date[]);
int readOrganisations(char org[][100]);
int chooseOrganisation(char org[][100], int count);


const int MAX_DONATIONS = 100;
const int LINE_SIZE = 200;


int main() {
    menu();
    return 0;
}

void menu() {
    int choice;

    do {
        printf("\n=======DONATION MANAGEMENT SYSTEM======= \n");
        printf("1. Make a Donation\n");
        printf("2. View Donation History (search by name)\n");
        printf("3. View Sorted History by Date\n");
        printf("4. View Total Donations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
		switch(choice){
			case 1:
            	addDonation(); 
            	break;
            case 2:
            	viewHistory(); 
            	break;
            case 3:
            	viewSortedHistory(); 
            	break;
        	case 4:
	            viewTotalDonations(); 
	            break;
	        case 5:
	            printf("Exiting...\n"); 
	            break; 
	        default:
            	printf("Invalid choice.\n");
		}
    }while (choice!=5);
}

int checkName(char name[]) {
    if(strlen(name) == 0) {
    	return 0;
	}
	int i;
    for( i = 0; name[i] != '\0'; i++) {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' ')){
            return 0;
        }
    }
    return 1;
}

int checkPhone(char phone[]){
	int i;
	int len=strlen(phone);
	if (len<11 || len>11){
		return 0;
	}
	for (i=0;i<len;i++){
		if (phone[i]<'0' || phone[i]>'9'){
			return 0;
		}
	}
	int allSame = 1;
    for (i = 1; i < len; i++) {
        if (phone[i] != phone[0]) {
            allSame = 0;
            break;
        }
    }
    if (allSame) {
        return 0;
    }
	return 1;
}
int checkDate(char date[]){
	int d, m, y;
	if(sscanf(date, "%d-%d-%d", &d, &m, &y) != 3){    //sscanf extracts date month year from string
        return 0;    
	}
    if(y < 1900 || y > 2025){
    	 return 0;
	} 
    if(m < 1 || m > 12){
		return 0;
	}
    if(d < 1 || d > 31) {
	return 0;
	}
	return 1;
}
int readOrganisations(char org[][100]) {           //orgs is the array to store names from file
    FILE *fp = fopen("organisations.txt", "r");
    if (!fp) {
        printf("Error! Could not open organisations.txt\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_DONATIONS && fgets(org[count], 100, fp)) {       // fgets(line, 100, file);
        org[count][strcspn(org[count], "\n")] = '\0'; // strcspn Remove newline
        count++;
    }
    fclose(fp);
    return count; // number of organisations in file
}

int chooseOrganisation(char org[][100], int count) {
    printf("\nAvailable Organisations:\n");
    int i;
    for ( i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, org[i]);
    }
    int choice;
    do {
        printf("Enter organisation number: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > count){
            printf("Invalid selection. Try again.\n");
        	}
    } while (choice < 1 || choice > count);

    return choice - 1;  // returns the index 
}
// list of monetary packages
void monetaryPackages() {
    printf("\nMonetary Packages:\n");
    printf("1. Platinum (50,000)\n2. Gold (20,000)\n3. Silver (10,000)\n4. Custom Amount\n");
}
 // awarding certificates
void awardCertificate(char name[], char subType[], float amount) {
    char line[LINE_SIZE];
    int donationCount = 0;

    FILE *fp = fopen("donations.txt", "r"); 
    if(!fp){
		return;
	}
    while(fgets(line, sizeof(line), fp)) {
        if(strstr(line, name)){               // strstr searches a substring inside the string
		 	donationCount++;
    	}
    }
    fclose(fp);
    printf("\nThank you for your donation! \n"); 
    if(donationCount >= 5){
        printf("Certificate Awarded: Loyal Donor (5+ donations)!\n");
	}else{
		if (amount==0){
			if(strcmp(subType, "Organ Donation") == 0){
	        	printf("Certificate Awarded: Organ Donor!\n");
	    	}else if (strcmp(subType, "Blood Donation") == 0){
	    		printf("Certificate Awarded: Blood Donor!\n");	
	    	}
		}else if (amount>0){
	    	if(amount >= 50000){
	        	printf("Certificate Awarded: Platinum Donor!\n");
	    	}else if(amount >= 20000){
	        	printf(" Certificate Awarded: Gold Donor!\n");
			}else if(amount >= 10000){
	        	printf(" Certificate Awarded: Silver Donor!\n");
	        }
	    }else{
	        printf("We appreciate your support! Donate more to earn a Certificate.\n");
		}
}
}


void addDonation() { 
    char date[15], name[50], phone[20], org[50][100], category[20], subType[30],myorg[100];
    float amount = 0;
    int catChoice, subChoice, orgChoice,orgCount;

    FILE *fp = fopen("donations.txt", "a"); 
    if(!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Donor Name: ");
    scanf(" %[^\n]", name); // [^\n] instead of %s to count spaces
    while (checkName(name)!=1){
    	printf("\nInvalid Input! Re-Enter Donor Name: ");
    	scanf(" %[^\n]", name);
	}

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", phone);
    while (checkPhone(phone)!=1){
    	printf("\nInvalid Input! Re-Enter Phone Number : ");
    	scanf(" %[^\n]", phone);
	}
    

    printf("Enter date (DD-MM-YYYY): ");
    scanf(" %[^\n]", date);
    while(checkDate(date)!=1){
    	printf("Invalid date! Re-Enter a valid date (DD-MM-YYYY) in this format: ");
    	scanf(" %[^\n]", date);
	}
	orgCount= readOrganisations(org);
	orgChoice= chooseOrganisation(org,orgCount);
	strcpy(myorg,org[orgChoice]);
	
	    printf("\nDonation Categories:\n");
	    printf("1. Health\n2. Monetary\n3. Miscellaneous\n");
	    printf("Choose category: ");
	    scanf("%d", &catChoice);
	switch(catChoice){
		case 1:
			strcpy(category, "Health");
	        printf("1. Blood\n2. Organ\nChoose: ");//add validation
	        scanf("%d", &subChoice);
	        if(subChoice == 1) {
				strcpy(subType, "Blood Donation");
	        }else{
			 	strcpy(subType, "Organ Donation");
			}
	        amount = 0;
	        break;	
	    case 2:
	    	strcpy(category, "Monetary");
	        monetaryPackages(); 
	        printf("Choose package: ");
	        scanf("%d", &subChoice);
	        if(subChoice == 1) {
				 strcpy(subType, "Platinum"); 
				 amount = 50000; 
			}else if(subChoice == 2) { 
				strcpy(subType, "Gold"); 
				amount = 20000; 
	        }else if(subChoice == 3) { 
				strcpy(subType, "Silver"); 
				amount = 10000; 
			}else if(subChoice == 4){
				 strcpy(subType, "Custom"); 
				 printf("Enter amount: "); 
				 scanf("%f", &amount);
	        }else{
	        	printf("Invalid Choice!");
			}
			break;
		case 3:
			strcpy(category, "Miscellaneous");
	        printf("1. Clothes\n2. Food\n3. Appliances\n4. Books\n5. Services\n6. Others\nChoose: "); // can add more things
	        scanf("%d", &subChoice);
	        switch(subChoice){
	        	case 1:
	        		strcpy(subType, "Clothes");
	        		break;
	        	case 2:
	        		strcpy(subType, "Food Items");
	        		break;
	        	case 3:
	        		strcpy(subType, "Appliances");
	        		break;
	        	case 4:
	        		strcpy(subType, "Books");
	        		break;
	        	case 5:
	        		strcpy(subType, "Services");
	        		break;
	        	case 6:
	        		strcpy(subType, "Other Misc");
	        		break;
	        	default:
	        		printf("Invalid Input!");		
			}
	        amount = 0;
	        break;
	    default:
	    	printf("Invalid choice.");
	    	
	}

    fprintf(fp, "%s,%s,%s,%s,%s,%s,%.2f\n", date, name, phone, myorg, category, subType, amount);// storing data in file
    fclose(fp); 

    printf("\nDonation entry recorded successfully!\n");
    awardCertificate(name, subType, amount);
}


//history
void viewHistory() {
    char searchName[50], line[LINE_SIZE];
    int found = 0;

    printf("\nEnter donor name to search: ");
    scanf(" %[^\n]", searchName);

    FILE *fp = fopen("donations.txt", "r"); //open file for read
    if(!fp) { 
		printf("No donation records found.\n"); 
		return;
	}
    printf("\n<---Donation History--->\n");
    while(fgets(line, sizeof(line), fp)) {
        if(strstr(line, searchName)) {
            printf("%s", line);
            found = 1;
        }
    }
    fclose(fp);

    if(!found){
    	 printf("No history found for this donor.\n");
    }
}
//sorting history by date
void viewSortedHistory() {
    char dates[MAX_DONATIONS][15], names[MAX_DONATIONS][50], phones[MAX_DONATIONS][20];
    char orgs[MAX_DONATIONS][50], categories[MAX_DONATIONS][20], subTypes[MAX_DONATIONS][30];
    float amounts[MAX_DONATIONS];
    int count = 0;
    char line[LINE_SIZE];

    // Open file
    FILE *fp = fopen("donations.txt", "r");
    if (!fp) { 
        printf("No donation records found.\n"); 
        return;
    }

    // Read all data from the file
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f",
            dates[count], names[count], phones[count], orgs[count],
            categories[count], subTypes[count], &amounts[count]);
        count++;
    }
    fclose(fp);


    // Convert date "DD-MM-YYYY" to an integer YYYYMMDD
    int convertDate(char d[]) {
        int day, month, year;
        sscanf(d, "%d-%d-%d", &day, &month, &year);
        return year*10000 + month*100 + day;
    }

    // Bubble sort by converted date value
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (convertDate(dates[j]) > convertDate(dates[j+1])) {

                char temp[100];
                float tempAmt;

                // Swap dates
                strcpy(temp, dates[j]); 
                strcpy(dates[j], dates[j+1]); 
                strcpy(dates[j+1], temp);

                // Swap names
                strcpy(temp, names[j]); 
                strcpy(names[j], names[j+1]); 
                strcpy(names[j+1], temp);

                // Swap phones
                strcpy(temp, phones[j]); 
                strcpy(phones[j], phones[j+1]); 
                strcpy(phones[j+1], temp);

                // Swap orgs
                strcpy(temp, orgs[j]); 
                strcpy(orgs[j], orgs[j+1]); 
                strcpy(orgs[j+1], temp);

                // Swap categories
                strcpy(temp, categories[j]); 
                strcpy(categories[j], categories[j+1]); 
                strcpy(categories[j+1], temp);

                // Swap subtypes
                strcpy(temp, subTypes[j]); 
                strcpy(subTypes[j], subTypes[j+1]); 
                strcpy(subTypes[j+1], temp);

                // Swap amounts
                tempAmt = amounts[j];
                amounts[j] = amounts[j+1];
                amounts[j+1] = tempAmt;
            }
        }
    }

    // Display sorted data
    printf("\n Donations Sorted by Date \n");
    for (i = 0; i < count; i++) {
        printf("%s,%s,%s,%s,%s,%s,%.2f\n",
            dates[i], names[i], phones[i], orgs[i], categories[i], subTypes[i], amounts[i]);
    }
}

//total donations done on software and total amount in money
void viewTotalDonations(){
    char line[LINE_SIZE];
    float total = 0;
    int count = 0;
    float amount;

    FILE *fp = fopen("donations.txt", "r");//open file read
    if(!fp) { 
		printf("No donation records found.\n"); 
		return;
	}

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%f", &amount);

        total += amount;
        count++;//total donations
    }
    fclose(fp);

    printf("\nTotal Donations \n");
    printf("Number of donations: %d\n", count);
    printf("Total monetary amount: %.2f\n", total);
}
