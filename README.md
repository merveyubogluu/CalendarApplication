# CalendarApplication

## Introduction

A calendar application with a file database. Application have two different view: day view and month view. It can add events to the given dates, edit & delete an already added event and prints the events of the given date in the day view. It is working with main.txt file which will be created in the same directory with the C code. After that if you want to see the notes in a spesific date you write the date and it starts to read the main.txt file. If there is any note have the same day, month and year information with input, then it will be printed to the screen.
*Note: You can select create a new event, edit and delete operations at the main menu.
In the month view, application prints the days of a month with a proper order. If any day in the given month has an event then the applications prints a star next to the that day. 
If you set alarm for the event, then when the right date and time comes it will make a beep sound and prints it to the screen. If you run the application after the correct time it will still make a sound and print that event to the screen. For every event, when the alarm make a sound it will be set to 25:61 to not make a sound again and write it to the main.txt file.
All the things are inside the MainMenu() function which has a while loop. Every time you do a operation between those options, after it’s done, the application will re-run because of the while loop. If you press 6 which is for quitting, it will ask you are you sure and it will return if your answer is yes. 


## Building and Running

There are some information you should know when you’re running the code. 

*Note: You should press enter after doing some operation.

### addnote() 
addnote function takes a lot of arguments. At first enter a day, month and year in the proper order and use integers. For example write something like 5 12 2001( with spaces between the day, month and the year).  You have 30 characters for the name of the event and 255 characters for the description. After you write those info of the event the programme will want you to enter a time for the event. It is not for the alarm, it is for the event! You should enter the time using integers and it should be look like 10 30(with spaces between hour and the minute) for example. If you want to set an alarm for the event, you should write the time just like you write the event’s time. 

### findNote() 
findnote function wants a day, a month and a year from the user. You should enter the day, month and the year with a proper order, using integers and spaces between them. For example write something like 5 12 2001( with spaces between the day, month and the year).  

### MonthView() 
monthview function wants a month and a year from the user. You should enter month and the year with a proper order, using integers and spaces between them. For example write something like 12 2001( with spaces between the month and the year).  

### arrangeEvent() 
arrangeevent function prints all the events to the screen, you choose whichever you want to change. Enter the ID of the event you want to change.  Enter the number which thing you want to change. For example if you want to change the name of the event, you should enter 1. 

## Final Comments

I hope this project helps you to understand C programming better. 

Merve Eyüboğlu
