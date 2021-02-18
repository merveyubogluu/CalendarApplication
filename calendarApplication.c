#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MainMenu();
void MonthView();
void addnote();
void arrangeEvent();
void findNote();
void deleteEvent();
void TimeCheck();

typedef struct _note{ //structure for the events
  int ID, day, month, year;
  char name[30];
  char note[255];
  int alarm_hour,alarm_minute;
  int hour,minute;
} Note;

int main(){
    system("Color 3E"); //setting the cmd's color
    printf("Welcome! \n");
    MainMenu();
}

int MainMenu(){
        int choice, answer;
        while(1){//this loop always calls itself
            TimeCheck();//checks is there any alarm at that current moment
            printf("Enter your choice. \n1. Day View\n2. Month View\n3. New Event\n4. Edit An Event\n5. Delete An Event\n6. Quit\n");
            scanf("%d",&choice);
            switch (choice){
                case 1:
                    findNote();// this will print the events at the given date
                    break;
                case 2:
                    MonthView(); // this will print a proper month view for the given month and year
                    printf("\n\n");
                    break;
                case 3:
                    addnote(); // add a new event
                    break;
                case 4:
                    arrangeEvent(); // edit an existing event
                    break;
                case 5:
                    deleteEvent(); // delete an existing event
                    break;
                case 6:
                    printf("Are you sure? \n1. Yes\n2. No\n");
                    scanf("%d",&answer);
                    if (answer == 1){
                        return 0;
                    }
                }
        }
}

void addnote(){
    FILE *fp; //creating a file
    Note note; // creating a Note structure
    int ID,answer,minute,hour;

    fp= fopen("main.txt", "a+");
    if (fp == NULL) {
        fp = fopen("main.txt", "a+");
    }
    srand(time(NULL));
    ID = rand()%10000; // random number generator
    while(fread(&note, sizeof(Note), 1, fp)){ // this part checks the other events has the same ID or not
        while (ID == note.ID){
            ID = rand()%10000;
        }
    }
    note.ID = ID; // making the note's ID new ID
    printf("Enter the day, month and year: ");
    scanf("%d %d %d", &note.day, &note.month, &note.year);// taking a date from the user
    getchar();// after scanf it will create a new line so this function helps you to use fgets after scanf
    printf("Enter a name for the event: ");
    fgets(note.name,sizeof(note.name),stdin);// taking name from the user
    printf("Enter the note: ");
    fgets(note.note,sizeof(note.note),stdin);// taking description from the user
    printf("Enter the time for the event (hour minute): ");
    scanf("%d %d",&note.hour,&note.minute);
    printf("Do you want to set an alarm? \n1. Yes\n2. No\n");
    scanf("%d",&answer);
    if(answer ==1){
        printf("Enter the time for the alarm: ");
        scanf("%d %d",&hour,&minute);
        note.alarm_hour = hour;
        note.alarm_minute = minute;
    }
    else{ // if the user doesn't want to set an alarm, alarm will automatically set 25.61 which doesn't exist as a time
        note.alarm_hour=25;
        note.alarm_minute=61;
    }
    fwrite(&note, sizeof(Note), 1, fp); // writes the note inside the main.txt file
    printf("\nNote added successfully!\n\n");
    fclose(fp); //close the fp
}

void findNote(){
    FILE *fp;
    Note note;
    int d, m ,y;

    fp = fopen("main.txt", "r"); // open th main.txt file with reading mode
    if (fp == NULL) {
      fp = fopen("main.txt", "w");
    }

    printf("\n------Day View------\n\n");
    printf("Enter the day, month and year (dd mm yyyy): ");
    scanf("%d %d %d", &d, &m, &y); // takes a day, a month and a year from the user
    printf("\n%d/%d/%d\n", d,m,y);

    while(fread(&note, sizeof(Note), 1, fp)){ //reads the main.txt
        if((note.day == d) &&(note.month == m)&& (note.year == y)){//checks the notes for the ones which have the same day, month and year
            if(note.alarm_hour == 25 && note.alarm_minute == 61){
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: doesn't exist.\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute);
            }
            else{
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: %d:%d\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute,note.alarm_hour,note.alarm_minute);
            }
        }
    }
    fclose(fp);
}


void MonthView(){
    int d=1, m, y;
    printf("\n------Month View------\n\n");
    printf("Enter the month and year (mm yyyy): ");
    scanf("%d %d", &m, &y); // takes a month and a year from the user
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ( ((y % 4 == 0) && (y % 4000!= 0)) ){ // this part calculates whether the year is a leap year or not
        months[1] = 29; //ýf it is a leap year it will add one to the february
    }

    FILE *fp;
    Note* notes, note;
    int len =0, j=0;

    fp = fopen("main.txt", "r"); // opens the main.txt file with r mode
    if (fp == NULL) {
      fp = fopen("main.txt", "w+");
    }

    while(fread(&note, sizeof(Note), 1, fp)) {
      if (note.year == y && note.month == m ) {
        len++;
      } //reads the notes inside the main and if there is any note which has same month and year with the input len increase 1
    }
    rewind(fp); // taking the cursor at the beginning of the file
    notes = (Note*) malloc (sizeof(Note) * len); // memory allocation for notes pointer

    while(fread(&note, sizeof(Note), 1, fp)) {
      if (note.year == y && note.month == m ) {
        notes[j] = note; // the notes which has same month and year with input is written inside the notes j'th element
        j++;
      }
    }
    fclose(fp);

    printf("\nMo |Tu |We |Th |Fr |Sa |Su |\n");
    printf("----------------------------\n");

    int days[7]={1,2,3,4,5,6,7};

    if ( m < 3 ){// calculating the first day of a given date
        d = d + y;
        y--;
    }
    else{
        d = d + y - 2;
    }
    int weekday = (23 * m/9) + d + 4 + y/4 - y/100 + y/400;
    weekday = weekday %7;
    if(weekday==0){weekday=7;}//weekday is the first day of an exact month

    for (int i=0;i<weekday-1;i++){
            printf("   |");
    }//print space until the first day of that month

    int day=1, hasNote;
    for(int i=weekday-1;i<months[m-1]+weekday-1;i++,day++){
        hasNote =0;
        for (int a = 0; a < len; a++) {// this part checks the notes which have an event will be print with a star, other will be print alone
            if (notes[a].day == day){
                if(day>9){printf("%d*|",day);}
                else{printf("%d* |",day);}
                hasNote = 1;
                break;
            }
        }
        if(hasNote == 0){
                    if(day>9){printf("%d |",day);}
                    else {printf("%d  |",day);}
        }
        if(i % 7 == 6){
                printf("\n----------------------------\n");}

        if (day>=months[m-1]){
            break;
        }
    }
}

void arrangeEvent(){
    FILE *fp,*update;
    Note note;
    int ID,choice =0;

    fp = fopen("main.txt", "r+"); //opens the main.txt file with r+ mode
    if (fp == NULL) {
      fp = fopen("main.txt", "w+");
    }

    while(fread(&note, sizeof(Note), 1, fp)){ // prints all the events to the screen
        if(note.alarm_hour == 25 && note.alarm_minute == 61){
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nDate: %d/%d/%d\nAlarm Time: doesn't exist.\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute,note.day,note.month,note.year);
            }
            else{
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nDate: %d/%d/%d\nAlarm Time: %d:%d\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute,note.day,note.month,note.year,note.alarm_hour,note.alarm_minute);
            }
    }

    (void)fseek(fp, 0L, SEEK_SET); // taking the cursor at the beginning of the file
    printf("Please enter the event's ID that you want to arrange: ");
    scanf("%d",&ID); // takes the users input for the event that they want to change

    update = fopen("update.txt", "r+"); // opens the update.txt file with r+ mode
    if (update == NULL) {
        update = fopen("update.txt", "w+");
    }

    while(fread(&note, sizeof(Note), 1, fp)){
        if(ID == note.ID){// checks if the input is equal to the notes inside the main.txt file
            printf("\nID: %d\nName: %sNote: %s\n",note.ID,note.name,note.note);
            printf("What do you want to change? \n1. Name\n2. Note\n3. Time\n4. Alarm \n5. Back to Main Menu\n\n");
            scanf("%d",&choice);
            getchar();
            switch(choice){// this part is for choosing the thing that the user want to change
                case 1:
                    printf("Enter the new name: ");
                    fgets(note.name,sizeof(note.name),stdin);
                    break;
                case 2:
                    printf("Enter the new note: ");
                    fgets(note.note,sizeof(note.note),stdin);
                    break;
                case 3:
                    printf("Enter the new hour and minute for the event: ");
                    scanf("%d %d",&note.hour,&note.minute);
                    break;
                case 4:
                    printf("Enter the new hour and minute for the event's alarm: ");
                    scanf("%d %d",&note.alarm_hour,&note.alarm_minute);
                    break;
            }
            printf("\nNote changed!\n\n");
        }
        fwrite(&note, sizeof(Note), 1, update); // writes the updated notes to the update.txt file
    }

    fclose(fp);// close the main.txt file
    fp = fopen("main.txt","w+"); // open the main.txt file with w+ mode
    (void)fseek(update, 0L, SEEK_SET); // taking cursor at the beginning of the update.txt file
    while(fread(&note, sizeof(Note), 1, update)){ // reads the update file and writes all the events to the main.txt file
        fwrite(&note, sizeof(Note), 1, fp);
    }
    fclose(fp);
    fclose(update);// closes the files
}

void deleteEvent(){ // deleting the events
    FILE *fp,*del;
    Note note;
    int ID;

    fp = fopen("main.txt", "r+"); //opens the main.txt file
    if (fp == NULL) {
      fp = fopen("main.txt", "w+");
    }
    while(fread(&note, sizeof(Note), 1, fp)){// prints all the notes to the screen
        if(note.alarm_hour == 25 && note.alarm_minute == 61){
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nDate: %d/%d/%d\nAlarm Time: doesn't exist.\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute,note.day,note.month,note.year);
            }
            else{
                printf("\nID: %d\nName: %sNote: %sTime: %d:%d\nDate: %d/%d/%d\nAlarm Time: %d:%d\n\n",
                       note.ID,note.name,note.note,note.hour,note.minute,note.day,note.month,note.year,note.alarm_hour,note.alarm_minute);
            }
    }

    (void)fseek(fp, 0L, SEEK_SET); //taking the cursor at the beginning of the main.txt file
    del = fopen("update.txt", "w+"); // open the update.txt file with w+ mode
    if (del == NULL) {
        del = fopen("update.txt", "w+");
    }

    printf("Please enter the event's ID that you want to delete: ");
    scanf("%d",&ID); // taking ID from the user for the one that they want to delete
    while(fread(&note, sizeof(Note), 1, fp)){ // this part reads the main.txt file if any event has the same ID with input then skip that and writes all the other events to the update.txt file
        if(ID != note.ID){
            fwrite(&note, sizeof(Note), 1, del);
        }
    }

    fclose(fp);
    fp = fopen("main.txt","w+"); //opening the main.txt with w+ mode
    (void)fseek(del, 0L, SEEK_SET);
    while(fread(&note, sizeof(Note), 1, del)){// writes everything inside the update.txt file to the main.txt file
        fwrite(&note, sizeof(Note), 1, fp);
    }
    fclose(fp);
    fclose(del);// close the files
}

void TimeCheck(){ // checking the alarms
    FILE *fp ,*del;
    Note note;
    int ID,choice;

    fp = fopen("main.txt", "r+");
    if (fp == NULL) {
      fp = fopen("main.txt", "w+");
    }

    time_t rawtime; // this part is to find the current local time
    struct tm *info;
    time(&rawtime);
    info = localtime( &rawtime );
    del = fopen("update.txt", "w+"); // opens the update.txt file with w+ mode
    if (del == NULL) {
        del = fopen("update.txt", "w+");
    }

    while(fread(&note, sizeof(Note), 1, fp)){// this if statement checks whether the note is proper for the making a beep sound
        if(((note.year == info->tm_year+1900)&& (note.month == info->tm_mon+1)&&(note.day == info->tm_mday)&&
           (note.alarm_hour == info->tm_hour)&& (note.alarm_minute == info->tm_min))||(
           (note.year < info->tm_year+1900)&&(note.alarm_hour != 25)&& (note.alarm_minute != 61))){
                printf("\n\aID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: %d:%d\n\n",
                note.ID,note.name,note.note,note.hour,note.minute,note.alarm_hour,note.alarm_minute);
                note.alarm_hour=25; // this for the alarm making a beep sound just once
                note.alarm_minute=61;
        }
        else if((note.year == info->tm_year+1900)&&(note.alarm_hour != 25)&& (note.alarm_minute != 61)){// if the year is equals to the current year
            if((note.month == info->tm_mon+1)){// checks is the month equals to the current month
                if((note.day == info->tm_mday)&&
                   ((note.alarm_hour < info->tm_hour)||((note.alarm_hour == info->tm_hour)&&(note.alarm_minute < info->tm_min)))){
                       //checks note's day is equals to the current day and the alarm's hour is equals to the current hour and
                       //minute of the alarm is smaller than current minute
                        printf("\n\aID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: %d:%d\n\n",
                        note.ID,note.name,note.note,note.hour,note.minute,note.alarm_hour,note.alarm_minute);
                        note.alarm_hour=25; // this for the alarm making a beep sound just once
                        note.alarm_minute=61;
                }
                else if((note.day < info->tm_mday)){ //checks note's day is smaller than the current or not
                    printf("\n\aID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: %d:%d\n\n",
                    note.ID,note.name,note.note,note.hour,note.minute,note.alarm_hour,note.alarm_minute);
                    note.alarm_hour=25;// this for the alarm making a beep sound just once
                    note.alarm_minute=61;
                }
            }
            else if((note.month < info->tm_mon+1)){// checks the month of the note is smaller than the current month
                printf("\n\aID: %d\nName: %sNote: %sTime: %d:%d\nAlarm Time: %d:%d\n\n",
                note.ID,note.name,note.note,note.hour,note.minute,note.alarm_hour,note.alarm_minute);
                note.alarm_hour=25;// this for the alarm making a beep sound just once
                note.alarm_minute=61;
            }
        }
        fwrite(&note, sizeof(Note), 1, del); // writes all the updated notes to the update.txt file

    }

    fclose(fp);
    fp = fopen("main.txt","w+");// opens the main.txt file with w+ mode
    (void)fseek(del, 0L, SEEK_SET);
    while(fread(&note, sizeof(Note), 1, del)){ // writes everything inside the update.txt file to the main.txt file
        fwrite(&note, sizeof(Note), 1, fp);
    }
    fclose(fp);
    fclose(del); // closing all the files
}
