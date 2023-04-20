#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ARRAY 300
#define MAX_CHARACTERS 1024

// Function to determine the min and max values of 4 numbers
double
min_max (double a, double b, double c, double d, double *min, double *max)
{
 /*Find minimum and maximum values */
 *min = a;
 *max = a;
 if (b < *min)
   {
     *min = b;
   }
 if (c < *min)
   {
     *min = c;
   }
 if (d < *min)
   {
     *min = d;
   }
 if (b > *max)
   {
     *max = b;
   }
 if (c > *max)
   {
     *max = c;
   }
 if (d > *max)
   {
     *max = d;
   }
 return *max;
}

// Function to determine the max and min of values from a 2d array
void
MinMax2dArray (double array[][4], int rows, double min[], double max[],
        int min_index[], int max_index[])
{
 for (int i = 0; i < rows; i++)
   {       // Runs through rows of array
     double minValue = array[i][0];
     double maxValue = array[i][0];
     int index_min = 0;
     int index_max = 0;

     for (int j = 1; j < 4; j++)
 {     //  Runs through columns of array
   if (array[i][j] < minValue)
     {     // Compares every number to determine min value
       minValue = array[i][j];
       index_min = j;

     }
   if (array[i][j] > maxValue)
     {     // Compares every number to determine max value
       maxValue = array[i][j];
       index_max = j;

     }
 }

     // Sets arrays to their respective values
     min[i] = minValue;
     max[i] = maxValue;
     max_index[i] = index_max;
     min_index[i] = index_min;
   }
}

int
main ()
{
 // Variable Declaration
 char row[MAX_ARRAY];
 char ref_dateH[MAX_ARRAY][MAX_CHARACTERS];
 char geo[MAX_ARRAY][MAX_CHARACTERS];
 char age_group[MAX_ARRAY][MAX_CHARACTERS];
 char sex[MAX_ARRAY][MAX_CHARACTERS];
 char value[MAX_ARRAY][MAX_CHARACTERS];
 int index = 0;

 // Open and reading the csv file
 FILE *input_file = fopen ("statscan_diabetes.csv", "r");
 if (input_file == NULL)
   {       // If file does not exist
     printf ("Error opening input file.");
     return 1;
   }

 // Runs through entire csv file until no more input/data
 while ( fgets (row, MAX_CHARACTERS, input_file)); // Get each row of the csv file and stores it in "row"

   {
   char *token = strtok (row, ",\"");  // Cleans the string of "row" by removing commas and quotation marks
     int columns = 0;    // Counter variable to count through the amount of columns
     while (token != NULL && columns < 15) //We only need data from columns 1 - 14
 {
   switch (columns)
     {
     case 0:   // Column 1, REF_DATE
       strcpy (ref_date[index], token);
       break;
     case 1:   // Column 2, GEO
       strcpy (geo[index], token);
       break;
     case 2:   // Column 2, GEO for Canada as it is short one row, DGUID for other values (Not needed)
       if (strcmp (geo[index], "Canada (excluding territories)") == 0)
   {
     strcpy (age_group[index], token);
     break;
   }
       break;
     case 3:   // Column 3, SEX for Canada as it is short one row. AGE_GROUP for other values
       if (strcmp (geo[index], "Canada (excluding territories)") == 0)
   {
     strcpy (sex[index], token);
     break;
   }
       strcpy (age_group[index], token);
       break;
     case 4:   // Column 5, SEX for other values
       if (strcmp (geo[index], "Canada (excluding territories)") == 0)
   {
     break;
   }
       strcpy (sex[index], token);
       break;
     case 12:    // Column 14, VALUE for Canada, nothing for other
       if (strcmp (geo[index], "Canada (excluding territories)") == 0)
   {
     strcpy (value[index], token);
   }
       break;
     case 13:    // Column 14, Value for everything else
       if (strcmp (geo[index], "Canada (excluding territories)") == 0)
   {
     break;
   }
       strcpy (value[index], token);
       break;
     default:
       break;
     }
   token = strtok (NULL, ",\""); // Cleans the string by removing , and "
   columns++;
 }
     index++;
   }
 fclose (input_file);
 // Question 1.A ----------------------------------------------------
 // counter for each provinces
 // Variable declaration
 double ontario_count = 0.0;
 double ontario_sum = 0.0;
 double ontario_ave;

 double quebec_count = 0.0;
 double quebec_sum = 0.0;
 double quebec_ave;

 double bc_count = 0.0;
 double bc_sum = 0.0;
 double bc_ave;

 double alberta_count = 0.0;
 double alberta_sum = 0.0;
 double alberta_ave;

// Loop through all rows of data
 for (int i = 0; i <= index; i++)
   {
     // Check if the row corresponds to a specific province and accumulate the sum and count for that province
     if (strcmp (geo[i], "Ontario") == 0)
 {
   if (atof (value[i]) != 0.0)
     {
       ontario_count++;
     }
   ontario_sum += atof (value[i]);
   ontario_ave = ontario_sum / ontario_count;
 }
     else if (strcmp (geo[i], "Quebec") == 0)
 {
   if (atof (value[i]) != 0.0)
     {
       quebec_count++;
     }
   quebec_sum += atof (value[i]);
   quebec_ave = quebec_sum / quebec_count;
 }
     else if (strcmp (geo[i], "British Columbia") == 0)
 {
   if (atof (value[i]) != 0.0)
     {
       bc_count++;
     }
   bc_sum += atof (value[i]);
   bc_ave = bc_sum / bc_count;
 }
     else if (strcmp (geo[i], "Alberta") == 0)
 {
   if (atof (value[i]) != 0.0)
     {
       alberta_count++;
     }
   alberta_sum += atof (value[i]);
   alberta_ave = alberta_sum / alberta_count;
 }
   }

// Print out the results
 printf ("\nQuestion 1.A --- Provincial Averages ---\n");
 printf ("Provincial diabetes average of Ontario: %0.2f%%\n", ontario_ave);
 printf ("Provincial diabetes average of Quebec: %0.2f%%\n", quebec_ave);
 printf ("Provincial diabetes average of British Columbia: %0.2f%%\n",
   bc_ave);
 printf ("Provincial diabetes average of Alberta: %0.2f%%\n\n", alberta_ave);

 // Question 1.B ---------------------------------------------------
 printf ("\nQuestion 1.B --- National Average ---\n");
 double canada_count = 0.0;
 double canada_sum = 0.0;
 double canada_ave;

 for (int i = 0; i <= index; i++)
   {
     if (strcmp (geo[i], "Canada (excluding territories)") == 0)
 {
   if (atof (value[i]) != 0.0)
     {
       canada_count++;
     }
   canada_sum += atof (value[i]);
   canada_ave = canada_sum / canada_count;
 }
   }
 printf ("Canadian diabetes average: %0.2f%%\n\n", canada_ave);

 // Question 1.C ---------------------------------------------------
 printf ("\nQuestion 1.C --- Yearly Averages ---\n");
  // Creates file for later use in Question 5
 FILE* Q5_File = fopen("plot_Q5.txt", "w");
 fprintf(Q5_File, "#Year\tCan\tOn\tQub\tBC\tAlb\n"); // Prints Header for file
  // Loop through years 2015-2021
 for (int year = 2015; year < 2022; year++)
   {
     // Initialize counters and sums for each region
     double canadaCounter = 0.0;
     double canadaSum = 0.0;
     double ontarioCounter = 0.0;
     double ontarioSum = 0.0;
     double quebecCounter = 0.0;
     double quebecSum = 0.0;
     double bcCounter = 0.0;
     double bcSum = 0.0;
     double albertaCounter = 0.0;
     double albertaSum = 0.0;

     // Loop through all data points
     for (int i = 0; i < index; i++)
 {
   // Check if data point matches current year
   if (atof (ref_date[i]) == year)
     {
       // Check which region data point is for and update counters and sums accordingly
       if (strcmp (geo[i], "Canada (excluding territories)") == 0)
   {
     if (atof (value[i]) != 0)
       {
         canadaCounter++;
       }
     canadaSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "Ontario") == 0)
   {
     if (atof (value[i]) != 0)
       {
         ontarioCounter++;
       }
     ontarioSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "Quebec") == 0)
   {
     if (atof (value[i]) != 0)
       {
         quebecCounter++;
       }
     quebecSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "British Columbia") == 0)
   {
     if (atof (value[i]) != 0)
       {
         bcCounter++;
       }
     bcSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "Alberta") == 0)
   {
     if (atof (value[i]) != 0)
       {
         albertaCounter++;
       }
     albertaSum += atof (value[i]);
   }
     }
 }
   // Print averages into file for question 5 GNUPLOT
   fprintf(Q5_File, "%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", year, (canadaSum / canadaCounter), (ontarioSum / ontarioCounter), (quebecSum / quebecCounter), (bcSum / bcCounter), (albertaSum / albertaCounter));
 
     // Print the average values for each region for the current year
     printf ("The averages for the year %d\n", year);
     printf ("Canada: %.2f%%\n", (canadaSum / canadaCounter));
     printf ("Ontario: %.2f%%\n", (ontarioSum / ontarioCounter));
     printf ("Quebec: %.2f%%\n", (quebecSum / quebecCounter));
     printf ("British Columbia: %.2f%%\n", (bcSum / bcCounter));
     printf ("Alberta: %.2f%%\n\n", (albertaSum / albertaCounter));
   }
   fclose(Q5_File);

   // Question 1.D ---------------------------------------------------
   printf("\nQuestion 1.D --- Age Group Averages ---\n");
   FILE* Q6_File = fopen("plot_Q6.txt", "w");
 fprintf(Q6_File, "#AgeGroup\tAverage(%%)\n");
   for (int age = 35.0; age <= 65.0; age += 15.0){
       double CaCounter = 0.0;
       double CaSum = 0.0;
       double OnCounter = 0.0;
       double OnSum = 0.0;
       double QbCounter = 0.0;
       double QbSum = 0.0;
       double BcCounter = 0.0;
       double BcSum = 0.0;
       double AbCounter = 0.0;
       double AbSum = 0.0;
      
   for (int i=0; i<=index; i++){
     if (atoi(age_group[i]) == age){
        if (strcmp(geo[i], "Canada (excluding territories)") == 0){
                   if (atof(value[i]) != 0.0){
                       CaCounter++;
                   } CaSum += atof(value[i]);
       }else if (strcmp(geo[i], "Ontario") == 0){
                   if (atof(value[i]) != 0.0){
                       OnCounter++;
                   } OnSum += atof(value[i]);
               }else if (strcmp(geo[i], "Quebec") == 0){
                   if (atof(value[i]) != 0.0){
                       QbCounter++;
                   } QbSum += atof(value[i]);
               }else if (strcmp(geo[i], "British Columbia") == 0){
                   if (atof(value[i]) != 0.0){
                       BcCounter++;
                   } BcSum += atof(value[i]);
               }else if (strcmp(geo[i], "Alberta") == 0){
                   if (atof(value[i]) != 0.0){
                       AbCounter++;
                   } AbSum += atof(value[i]);
         }
   }
   }
   if (age == 65){
   printf("The averages for the age group 65-above\n");
   fprintf(Q6_File, "65-above\t");
 }else{
   printf("The averages for the age group %d-to-%d\n", age, age+14);
   fprintf(Q6_File, "%d-to-%d\t", age, age+14);
 }
 printf("Canada: %.2f%%\n", CaSum/CaCounter);
   printf("Ontario: %.2f%%\n", OnSum/OnCounter);
   printf("Quebec: %.2f%%\n", QbSum/QbCounter);
   printf("British Columbia: %.2f%%\n", BcSum/BcCounter);
   printf("Alberta: %.2f%%\n", AbSum/AbCounter);
  
   fprintf(Q6_File, "%.2f\n", (CaSum)/(CaCounter));
 }


// Question 2 ---------------------------------------------------
 printf ("\nQuestion 2 --- Highest Average ---\n");
 // Declare variables for highest and lowest average
 double max, min;

// Call function to determine the highest and lowest average
 min_max (ontario_ave, quebec_ave, bc_ave, alberta_ave, &min, &max);

// Check which province has the highest average and print it
 if (max <= ontario_ave)
   {
     printf ("Ontario has the highest percentage %.2lf%%\n", max);
   }
 else if (max <= quebec_ave)
   {
     printf ("Quebec has the highest percentage %.2lf%%\n", max);
   }
 else if (max <= bc_ave)
   {
     printf ("British Columbia has the highest percentage %.2lf%%\n", max);
   }
 else if (max <= alberta_ave)
   {
     printf ("Alberta has the highest percentage %.2lf%%\n", max);
   }

// Check which province has the lowest average and print it
 if (min >= ontario_ave)
   {
     printf ("Ontario has the lowest percentage %.2lf%%\n", min);
   }
 else if (min >= quebec_ave)
   {
     printf ("Quebec has the lowest percentage %.2lf%%\n", min);
   }
 else if (min >= bc_ave)
   {
     printf ("British Columbia has the lowest percentage %.2lf%%\n", min);
   }
 else if (min >= alberta_ave)
   {
     printf ("Alberta has the lowest percentage %.2lf%%\n", min);
   }

// Print a new line for formatting purposes
 printf ("\n");


// Question 3 ---------------------------------------------------
 // Base string for print statement for provinces below and above national average
 printf ("\nQuestion 3 --- Provinces Below and Above National Average ---\n");
 char avebelow[MAX_ARRAY] = "Provinces below national average: \n";
 char aveabove[MAX_ARRAY] = "Provinces above national average: \n";

// Compares which one is below and above and appends to base string
 if (canada_ave >= ontario_ave)
   {
     strcat (avebelow, "Ontario\n");
   }
 else
   {
     strcat (aveabove, "Ontario\n");
   }
 if (canada_ave >= quebec_ave)
   {
     strcat (avebelow, "Quebec\n");
   }
 else
   {
     strcat (aveabove, "Quebec\n");
   }
 if (canada_ave >= bc_ave)
   {
     strcat (avebelow, "British Columbia\n");
   }
 else
   {
     strcat (aveabove, "British Columbia\n");
   }
 if (canada_ave >= alberta_ave)
   {
     strcat (avebelow, "Alberta\n");
   }
 else
   {
     strcat (aveabove, "Alberta\n");
   }

// Prints strings
 puts (avebelow);
 puts (aveabove);

// Question 4 ---------------------------------------------------
 printf ("\nQuestion 4 --- Yearly Averages Min Max ---\n");

 double diabetes_rates[7][4];
 // Loop through the data array to extract diabetes rates for the current year and province
 for (int year = 2015; year < 2022; year++)
   {
     int row = year - 2015;
     double ontarioCounter = 0.0;
     double ontarioSum = 0.0;
     double quebecCounter = 0.0;
     double quebecSum = 0.0;
     double bcCounter = 0.0;
     double bcSum = 0.0;
     double albertaCounter = 0.0;
     double albertaSum = 0.0;

     for (int i = 0; i < index; i++)
 {
   if (atof (ref_date[i]) == year)
     {     // Check if the current record is for the current year
       if (strcmp (geo[i], "Ontario") == 0)
   {
     if (atof (value[i]) != 0)
       {
         ontarioCounter++;
       }
     ontarioSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "Quebec") == 0)
   {
     if (atof (value[i]) != 0)
       {
         quebecCounter++;
       }
     quebecSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "British Columbia") == 0)
   {
     if (atof (value[i]) != 0)
       {
         bcCounter++;
       }
     bcSum += atof (value[i]);
   }
       else if (strcmp (geo[i], "Alberta") == 0)
   {
     if (atof (value[i]) != 0)
       {
         albertaCounter++;
       }
     albertaSum += atof (value[i]);
   }
     }
 }
     // Calculate the average diabetes rate for each province and store in the 2D array
     diabetes_rates[row][0] = ontarioSum / ontarioCounter;
     diabetes_rates[row][1] = quebecSum / quebecCounter;
     diabetes_rates[row][2] = bcSum / bcCounter;
     diabetes_rates[row][3] = albertaSum / albertaCounter;
   }
// Declare arrays to store the minimum and maximum diabetes rates for each year and their corresponding provinces
 double min_each_year[7];
 double max_each_year[7];
 int index_max_each_year[7];
 int index_min_each_year[7];
// Declare an array to store province names for printing the results
 char province_name[][30] =
   { "Ontario", "Quebec", "British Columbia", "Alberta" };

 // Calls function to determine the max and min value and appends to array
 MinMax2dArray (diabetes_rates, 7, min_each_year, max_each_year,
    index_min_each_year, index_max_each_year);

 // Print the results
 for (int i = 0; i < 7; i++)
   {
     printf("Year %d\nLowest Percentage: %s at %.2f%%\nHighest Percentage: %s at %.2f%%\n\n",
  2015 + i, province_name[index_min_each_year[i]], min_each_year[i],
  province_name[index_max_each_year[i]], max_each_year[i]);
   }
}