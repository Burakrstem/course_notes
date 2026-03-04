# ⏰ Standard Functions Operating on Date and Time

There are some standard functions defined in the standard header file **`time.h`** to perform useful operations related to date and time information. The parameter variables or return values of some of these functions are address information of a structure type. These functions are explained below:

## The `time` Function

    time_t time (time_t *timer);

The return value of the function is the standard `typedef` type **`time_t`**. Most compilers declare this type as the `typedef` name for the `long` type. The parameter variable of the function is also an address of this type.

The function writes the number of seconds that have passed from a specific date (01.01.1970 in most systems) until the function call to the object whose address is sent. This value is referred to as **"calendar time"** in the standards. Some other functions that operate on date and time require this value to perform their tasks.

The function also conveys this value to the outside as a return value. If the calendar time information cannot be obtained, the function returns the value **(time_t)-1**.

If the **`NULL` address** is sent to the function, the function perceives this value as a special message, performs no writing to any object, and only conveys the seconds information to the outside with the return value.

A simple code snippet related to the use of the function is given below:

    #include <stdio.h>
    #include <time.h>
    int main()
    {
        time_t timer1, timer2, timer3;
        timer1 = time(&timer2); // Writes time to timer2, returns time to timer1
        printf("press a key to continue : ");
        getchar();
        timer3 = time(NULL); // Only returns time
        printf("timer1 = %ld\n", (long)timer1);
        printf("timer2= %ld\n", (long)timer2);
        printf("timer3= %ld\n", (long)timer3);
        return 0;
    }

## The `localtime` Function

The number of seconds passed since 01.01.1970, i.e., the calendar time, is not a time information that can be used directly. The `localtime` function takes this information and breaks it down into useful parts. The declaration of the function in the `time.h` header file is as follows:

    struct tm *localtime(const time_t *timer);

The return value of the function is an address of type **`struct tm *`**, a structure declared in `time.h`. This structure is declared as follows:

    struct tm {
        int tm_sec;   // Seconds (0 - 60)
        int tm_min;   // Minutes (0 - 59)
        int tm_hour;  // Hours (0 – 23)
        int tm_mday;  // Day of the month (1 – 31)
        int tm_mon;   // Month value (0 January, 1 February, 2 March…)
        int tm_year;  // Year value minus 1900
        int tm_wday;  // Day of the week (0 Sunday, 1 Monday, 2 Tuesday…)
        int tm_yday;  // Day of the year (0 for Jan 1st)
        int tm_isdst; // Daylight saving time flag
    };

All members of the structure starting with the prefix `tm_` are of type `int`. Each member holds useful data related to the date or time. Information about the structure members is given below:

* `tm_sec`: Seconds value (0 - 60)
* `tm_min`: Minutes value (0 - 59)
* `tm_hour`: Hours value (0 – 23)
* `tm_mday`: Day of the month (1 – 31)
* `tm_mon`: Month value (0 January, 1 February, 2 March…)
* `tm_year`: Year value minus 1900
* `tm_wday`: Day of the week (0 Sunday, 1 Monday, 2 Tuesday…)
* `tm_yday`: Day of the year (0 for Jan 1st)
* `tm_isdst`: Information regarding the daylight saving time mode. A positive value for this member indicates being in saving mode. If the value is 0, it is not saving mode. A negative value for this member means this information cannot be obtained.

The time information held with the `struct tm` structure is called **"broken-down time."**

The `localtime` function returns with the address of a **static duration** `struct tm` object. If the function is called again without the value of the structure object at the address that is the return value of the function being used or transferred to another object, the value produced related to the previous call is overwritten. The parameter variable of the function is a pointer pointing to a `time_t` type object. The function takes the calendar time information from this object whose address it receives.

An example code using the `localtime` function is given below:

    #include <stdio.h>
    #include <time.h>
    // Changed month names to English
    char *months[12] = {"January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December"};
    // Changed day names to English
    char *days[7] = {"Sunday","Monday", "Tuesday", "Wednesday", "Thursday",
                     "Friday", "Saturday"};
    int main()
    {
        time_t timer;
        struct tm *tptr;
        time(&timer);
        tptr = localtime(&timer);
        
        printf("Date : %02d %s %04d %s\n",
               tptr->tm_mday, months[tptr->tm_mon], tptr->tm_year + 1900, days[tptr->tm_wday]);
        printf("Time:%02d:%02d:%02d\n", tptr->tm_hour, tptr->tm_min, tptr->tm_sec);
        printf("today is the %d. day of the year %d\n", tptr->tm_yday, tptr->tm_year + 1900);
        
        if (tptr->tm_isdst < 0)
            printf("daylight saving time information cannot be obtained!\n");
        else if (tptr->tm_isdst > 0)
            printf("we are in daylight saving time mode!\n");
        else
            printf("we are not in daylight saving time mode!\n");
            
        return 0;
    }

## The `ctime` Function

This function takes calendar time information as input and converts this information into a string. The declaration of the function is as follows:

    char *ctime(const time_t *time);

The parameter variable of the function is an address of type `time_t *`. The function reads the calendar time information from the object whose address it receives. The return value of the function is the starting address of a **26-character string**. This string is a specially formatted string containing broken-down time information:

    F r i   F e b   2 3   1 2 : 2 5 : 5 4   2 0 0 4 \n \0
    (Fri Feb 23 12:25:12 2004\n\0)

The function returns with the address of a **static duration** array. If the function is called again without the string at the address that is the return value of the function being used or transferred to another array, the string produced related to the previous call is overwritten.

An example code snippet related to the use of the function is located below:

    #include <stdio.h>
    #include <time.h>
    int main()
    {
        char *ptr;
        time_t timer;
        timer = time(NULL);
        ptr = ctime(&timer);
        printf("%s", ptr);
        return 0;
    }

## The `asctime` Function

It performs the exact same task as the `ctime` function. However, it takes broken-down time information as input, not calendar time:

    char *asctime (const struct tm *tblock);

The parameter variable of the function is an address of type `struct tm *`. The function reads the broken-down time information from the object whose address it receives. It converts this information into a string and writes it into a 26-character static duration array in a special format. The function returns the starting address of the relevant string. If the function is called again without the string at the address that is the return value of the function being used or transferred to another array, the string produced related to the previous call is overwritten.

An example code snippet related to the use of the function is located below:

    #include <stdio.h>
    #include <time.h>
    int main()
    {
        time_t timer;
        timer = time(NULL);
        printf("%s", asctime(localtime(&timer)));
        return 0;
    }

In the code snippet above, the address of type `struct tm *`, which is the return value of the `localtime` function, is sent directly as an argument to the `asctime` function. The address that is the return value of the `asctime` function is also passed to the `printf` function.

## The `clock` Function

The return value of the function is the standard `typedef` type **`clock_t`**, declared in the `time.h` header file. This type is declared as the `typedef` name for the `long` type in almost all compilers:

    clock_t clock(void);

The function returns the time elapsed from the start of the program's execution until the function call. However, the unit related to the function's return value is the tick count of the processor's time circuit, not seconds. To convert the function's return value to seconds, the return value must be divided by the number of ticks per second of the processor. The number of ticks per second of the time circuit is defined as a symbolic constant named **`CLOCKS_PER_SEC`** in `time.h`.

    #define CLOCKS_PER_SEC 1000

This symbolic constant should be used for code portability. Most compilers define another symbolic constant named `CLK_TCK` to enable the use of a shorter symbolic constant:

    #define CLK_TCK CLOCKS_PER_SEC

However, the `CLOCKS_PER_SEC` symbolic constant should be used for portability.

Examine the following example program related to the `clock` function:

    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    int main()
    {
        clock_t clock1, clock2;
        long k;
        clock1 = clock(); // Start time
        for (k = 1; k < 10000000; ++k)
            sqrt(sqrt(k) + sqrt(k + 1)); // Workload
        clock2 = clock(); // End time
        printf("loop took %lf seconds!\n", (double)(clock2 - clock1) / CLOCKS_PER_SEC); // Use CLOCKS_PER_SEC for portability
        return 0;
    }

A delay function benefiting from the `clock` function is written below:

    #include <math.h>
    #include <time.h>
    #define SENSITIVITY 0.1
    void delay(double sec)
    {
        double total = 0.;
        clock_t tstart = clock();
        clock_t tend;
        double duration;
        for (;;) {
            tend = clock();
            duration = (double)(tend - tstart) / CLOCKS_PER_SEC;
            if (fabs(duration - sec) < SENSITIVITY) // Check if duration is close enough to 'sec'
                return;
        }
    }

## The `difftime` Function

The standard `difftime` function can be used to find the difference in seconds between two time information given in calendar time. The function declaration is as follows:

    double difftime(time_t timer2, time_t timer1);

The return value of the function is the number of seconds that have passed between the value `timer1` and the value `timer2`.

    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    int main()
    {
        time_t start,finish;
        long i;
        double result, elapsed_time;
        printf("taking square root 20000000 times.\n");
        time(&start); // Get start time
        for (i = 1; i <= 20000000; i++)
            result = sqrt(i); // Workload
        time(&finish); // Get end time
        elapsed_time = difftime(finish, start);
        printf("\nTotal time = %lf seconds.\n", elapsed_time);
        return 0;
    }

## The `mktime` Function

This standard function converts broken-down time information to calendar time. The declaration of the function is as follows:

    time_t mktime(struct tm *tptr);

The parameter of the function is the address of the structure object of type `struct tm` that holds the broken-down time information. Note that the address used in the function's parameter is **not `const`**. From this, you can deduce that the function will write to this address. The return value of the function is the calendar time value. If the calendar time value cannot be obtained in the relevant system, the function returns the value -1.

The function also has a side effect. If the members of the structure object at the address it receives as a parameter exceed their required values, the `mktime` function adds the excess part of the values to the next member. For this purpose, the `tm_sec` member is checked first. The excesses here are transferred to the `tm_min` member. If an excess occurs here as well, the `tm_hour`, `tm_mday`, `tm_mon`, and `tm_year` members of the structure object are modified sequentially. After the value of these members is obtained, the `tm_wday` and `tm_yday` members of the structure object are brought to the values they should have.

The following code uses this feature of the function to find the day of the week for a date:

    #include <stdio.h>
    #include <time.h>
    int main()
    {
        struct tm t;
        const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday","Saturday", "unknown"};
        t.tm_mday = 11;
        t.tm_mon = 2; // March (0-based)
        t.tm_year = 2005 - 1900;
        t.tm_sec = 1;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_isdst = -1;
        
        // mktime modifies tptr, calculating tm_wday and tm_yday
        if (mktime(&t) == (time_t)-1) // Check for failure
            t.tm_wday = 7; // Set to 'unknown' index on failure
            
        printf("day = %s\n", days[t.tm_wday]);
        return 0;
    }

## Applications Related to Structures

In the following program, a structure named `Date` is declared to hold a date information. Functions that provide service using this structure type are defined.

/********** date.h **************************/

    typedef struct {
        int m_d;
        int m_m;
        int m_y;
    }Date;
    #define YEAR_BASE 1000
    #define false 0
    #define true 1
    typedef int bool;
    
    void set_date(Date *ptr, int d, int m, int y);
    void set_today(Date *ptr);
    void set_random(Date *ptr);
    void display_date(const Date *ptr);
    void inc_date(Date *p);
    void dec_date(Date *p);
    Date ndays(const Date *p, int n);
    int date_cmp(const Date *p1, const Date *p2);
    int get_day(const Date *p);
    int get_month(const Date *p);
    int get_year(const Date *p);
    int get_yearday(const Date *ptr);
    int get_weekday(const Date *ptr);
    bool isweekend(const Date *ptr);
    bool isleap(int y);

/********** date.c **************************/

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <assert.h>
    
    // Using simple macros for PUBLIC/PRIVATE
    #define PUBLIC
    #define PRIVATE static
    #define FACTOR 2
    
    PRIVATE int daytabs[2][13] = { // Days in month table (row 0: non-leap, row 1: leap)
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };
    
    PRIVATE bool check_date(int d, int m, int y);
    PRIVATE int totaldays(const Date *p);
    PRIVATE Date revdate(int totaldays);
    
    PRIVATE bool check_date(int d, int m, int y)
    {
        if (y < YEAR_BASE)
            return false;
        if (m < 1 || m > 12)
            return false;
        if (d < 1 || d > daytabs[isleap(y)][m])
            return false;
        return true;
    }
    
    /*************************************************************************/
    PRIVATE int totaldays(const Date *ptr)
    {
        int sum = 0;
        int k;
        // Sum of days from YEAR_BASE to (ptr->m_y - 1)
        for (k = YEAR_BASE; k < ptr->m_y; ++k)
            sum += 365 + isleap(k); 
        // Add days within current year
        return sum + get_yearday(ptr); 
    }
    
    /*************************************************************************/
    PRIVATE Date revdate(int totaldays)
    {
        Date ret_val;
        int val;
        int index;
        
        ret_val.m_y = YEAR_BASE;
        // Determine the year
        while (totaldays > (val = isleap(ret_val.m_y) + 365)) {
            totaldays -= val;
            ret_val.m_y++;
        }
        
        ret_val.m_m = 1;
        index = isleap(ret_val.m_y);
        // Determine the month and day
        while (totaldays > daytabs[index][ret_val.m_m])
            totaldays -= daytabs[index][ret_val.m_m++];
            
        ret_val.m_d = totaldays;
        return ret_val;
    }
    
    /*************************************************************************/
    PUBLIC int get_yearday(const Date *ptr)
    {
        int sum = ptr->m_d;
        int k;
        int index = isleap(ptr->m_y);
        // Sum days from months before current month
        for (k = 1; k < ptr->m_m; ++k) 
            sum += daytabs[index][k];
        return sum;
    }
    
    /*************************************************************************/
    PUBLIC int dayofweek(const Date *ptr)
    {
        return totaldays(ptr) % 7;
    }
    
    /*************************************************************************/
    PUBLIC bool isleap(int y)
    {
        return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
    }
    
    /*************************************************************************/
    PUBLIC void set_date(Date *ptr, int d, int m, int y)
    {
        assert(check_date(d, m, y));
        ptr->m_d = d;
        ptr->m_m = m;
        ptr->m_y = y;
    }
    
    /*************************************************************************/
    PUBLIC void set_today(Date *ptr)
    {
        time_t timer = time(NULL);
        struct tm *tptr = localtime(&timer);
        ptr->m_d = tptr->tm_mday;
        ptr->m_m = tptr->tm_mon + 1; // tm_mon is 0-based
        ptr->m_y = tptr->tm_year + 1900;
    }
    
    /*************************************************************************/
    PUBLIC void set_random(Date *ptr)
    {
        ptr->m_y = rand() % 50 + 1960; // Random year between 1960 and 2009
        ptr->m_m = rand() % 12 + 1;
        // Random day within the month
        ptr->m_d = rand() % daytabs[isleap(ptr->m_y)][ptr->m_m] + 1; 
    }
    
    /*************************************************************************/
    PUBLIC void display_date(const Date *ptr)
    {
        static const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                     "Thursday", "Friday", "Saturday"};
        static const char *mons[] = {"", "January", "February", "March", "April",
                                      "May", "June", "July", "August", "September",
                                      "October", "November", "December"}; // Using English for consistency
        printf("%02d %s %4d %s\n", ptr->m_d, mons[ptr->m_m], ptr->m_y,
               days[get_weekday(ptr)]);
    }
    
    /*************************************************************************/
    PUBLIC int date_cmp(const Date *p1, const Date *p2)
    {
        if (p1->m_y != p2->m_y)
            return p1->m_y - p2->m_y;
        if (p1->m_m != p2->m_m)
            return p1->m_m - p2->m_m;
        return p1->m_d - p2->m_d;
    }
    
    /*************************************************************************/
    PUBLIC void inc_date(Date *p)
    {
        *p = revdate(totaldays(p) + 1);
    }
    
    /*************************************************************************/
    PUBLIC void dec_date(Date *p)
    {
        *p = revdate(totaldays(p) - 1);
    }
    
    /*************************************************************************/
    PUBLIC Date ndays(const Date *p, int n)
    {
        return revdate(totaldays(p) + n);
    }
    
    /*************************************************************************/
    PUBLIC int get_weekday(const Date *ptr)
    {
        return (totaldays(ptr) + FACTOR) % 7; // FACTOR aligns start date of the week to an arbitrary reference date
    }
    
    /*************************************************************************/
    PUBLIC bool isweekend(const Date *ptr)
    {
        int day = get_weekday(ptr);
        return day == 6 || day == 0; // Saturday (6) or Sunday (0)
    }
    
    /*************************************************************************/
    int main()
    {
        Date today;
        Date ndaysafter;
        
        set_today(&today);
        ndaysafter = ndays(&today, 10); // Date 10 days after today
        
        // Loop until today >= ndaysafter (date_cmp returns 0 if equal, -1 if today < ndaysafter)
        while (date_cmp(&today, &ndaysafter)) { 
            display_date(&today);
            inc_date(&today);
        }
        return 0;
    }

The following program creates a singly linked list.

/********** datelist.h **************************/

    #include "date.h"
    typedef struct tagNode {
        Date date;
        struct tagNode *pnext;
    }Node;
    
    typedef struct {
        Node *pstart;
        Node *pend;
        size_t size;
    }*ListHandle; // ListHandle is a pointer to the list control structure
    
    ListHandle openlist(void);
    void closelist(ListHandle);
    void push_front(ListHandle handle);
    void push_back(ListHandle handle);
    void display_list(ListHandle handle);
    void pop_front(ListHandle handle);
    void pop_back(ListHandle handle);
    void remove_date(const Date *); // Assuming implementation for this is defined elsewhere
    void clear_list(ListHandle handle);
    size_t get_size(ListHandle handle);

/********** datelist.c **************************/

    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    
    #define PUBLIC
    #define PRIVATE static
    
    PRIVATE Node *create_node(void);
    PRIVATE void free_nodes(Node *p);
    
    /*************************************************************************/
    PRIVATE void free_nodes(Node *p)
    {
        Node *temp;
        while (p) {
            temp = p;
            p = p->pnext;
            free(temp);
        }
    }
    
    /*************************************************************************/
    PRIVATE Node *create_node(void)
    {
        Node *pd = (Node *)malloc(sizeof(Node));
        if (!pd) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        return pd;
    }
    
    /*************************************************************************/
    PUBLIC ListHandle openlist(void)
    {
        ListHandle pd = (ListHandle)malloc(sizeof(*pd)); // Allocate ListHandle structure
        if (!pd) {
            printf("cannot allocate memory!\n");
            exit(EXIT_FAILURE);
        }
        pd->pstart = pd->pend = NULL;
        pd->size = 0;
        return pd;
    }
    
    /*************************************************************************/
    PUBLIC void closelist(ListHandle handle)
    {
        clear_list(handle);
        free(handle);
    }
    
    /*************************************************************************/
    PUBLIC void push_front(ListHandle handle)
    {
        Node *pnew = create_node();
        set_random(&pnew->date); // Set date member
        handle->size++;
        
        if (handle->pstart == NULL) {
            handle->pstart = handle->pend = pnew;
            pnew->pnext = NULL;
            return;
        }
        
        pnew->pnext = handle->pstart;
        handle->pstart = pnew;
    }
    
    /*************************************************************************/
    PUBLIC void push_back(ListHandle handle)
    {
        Node *pnew = create_node();
        set_random(&pnew->date);
        pnew->pnext = NULL;
        handle->size++;
        
        if (handle->pstart == NULL) {
            handle->pstart = handle->pend = pnew;
            return;
        }
        
        handle->pend->pnext = pnew;
        handle->pend = pnew;
    }
    
    /*************************************************************************/
    PUBLIC void display_list(ListHandle handle)
    {
        Node *cur = handle->pstart;
        if (!handle->size) {
            printf("empty list!\n");
            return;
        }
        while (cur) {
            display_date(&cur->date);
            cur = cur->pnext;
        }
    }
    
    /*************************************************************************/
    PUBLIC void clear_list(ListHandle handle)
    {
        free_nodes(handle->pstart);
        handle->pstart = handle->pend = NULL;
        handle->size = 0; // Reset size
    }
    
    /*************************************************************************/
    PUBLIC size_t get_size(ListHandle handle)
    {
        return handle->size;
    }
    
    /*************************************************************************/
    PUBLIC void pop_front(ListHandle handle)
    {
        Node *temp;
        if (!handle->size) {
            printf("list empty!\n");
            return;
        }
        
        handle->size--;
        if (handle->pstart == handle->pend) { // Only one element
            free(handle->pstart);
            handle->pstart = handle->pend = NULL;
            return;
        }
        
        temp = handle->pstart;
        handle->pstart = handle->pstart->pnext;
        free(temp);
    }
    
    /*************************************************************************/
    PUBLIC void pop_back(ListHandle handle)
    {
        Node *temp, *cur;
        if (!handle->size) {
            printf("list empty!\n");
            return;
        }
        
        handle->size--;
        if (handle->pstart == handle->pend) { // Only one element
            free(handle->pstart);
            handle->pstart = handle->pend = NULL;
            return;
        }
        
        temp = handle->pend; // Node to be freed
        // Find the node before the end node
        for (cur = handle->pstart; cur->pnext != handle->pend; cur = cur->pnext)
            ;
        
        cur->pnext = NULL; // New end node's next is NULL
        handle->pend = cur; // Update pend pointer
        free(temp);
    }
    
    /*************************************************************************/
    void display_menu()
    {
        printf("[1] PUSH FRONT\n");
        printf("[2] PUSH BACK\n");
        printf("[3] DISPLAY LIST\n");
        printf("[4] POP FRONT\n");
        printf("[5] POP BACK\n");
        printf("[6] CLEAR LIST\n");
        printf("[7] EXIT\n");
        printf("your choice : ");
    }
    
    /*************************************************************************/
    int get_option()
    {
        int option;
        display_menu();
        scanf("%d", &option);
        if (option < 1 || option > 7)
            option = 0;
        return option;
    }
    
    /*************************************************************************/
    int main()
    {
        int option;
        ListHandle handle = openlist();
        for (;;) {
            option = get_option();
            switch (option) {
                case 1: push_front(handle); break;
                case 2: push_back(handle); break;
                case 3: display_list(handle);break;
                case 4: pop_front(handle);break;
                case 5: pop_back(handle);break;
                case 6: clear_list(handle); break;
                case 7: goto END;
                case 8: printf("invalid entry!\n"); // Case 8 is outside the menu
            }
        }
    END:
        closelist(handle);
        printf("end of program!\n");
        return 0;
    }