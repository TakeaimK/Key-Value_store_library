#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval tv1,tv2;
static inline void set_start_time(){ gettimeofday(&tv1, NULL); }
static inline void set_end_time()  { gettimeofday(&tv2, NULL); }
static inline double get_interval(){ return ((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)); }

const char *opers[] = {"GET", "PUT", "DEL", "OPEN", "CLOSE", NULL};

#define GET             0x0
#define PUT             0x1
#define DEL             0x2
#define OPEN            0x3
#define CLOSE           0x4

char oper[10];
char key[4097];
char value[1100001];
char buf[1100001];


int main(int argc, char **argv)
{
 	int i;
    for(i=1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp==NULL)
        {
        	printf("%s open fail\n", argv[i]);
        	break;
        }
        printf("%s running..\n", argv[i]);

        int incorrect = 0;
        int cnt = 0;
        int err = 0;

        double spent_time = 0.;
        
        while(!feof(fp))
        {
            if(fscanf(fp, "%s", oper) != 1)
                break;
            cnt++;

            int op = 0;
            while(opers[op] && strcmp(opers[op], oper))
                op++;

            int old = incorrect;

            int ret;

            switch(op)
            {
            case GET:
                fscanf(fp, "%s%s", key, value);
                set_start_time();
                ret = kvget(key, buf);
                set_end_time();
                spent_time += get_interval();
                if(strcmp(value, "없음") == 0)
                    incorrect += ret == 0;
                else
                    incorrect += !!strncmp(buf, value, strlen(value));
                break;
            case PUT:
                fscanf(fp, "%s%s", key, value);
                set_start_time();
                ret = kvput(key, value);
                set_end_time();
                spent_time += get_interval();
                break;
            case DEL:
                fscanf(fp, "%s%s", key, value);
                set_start_time();
                ret = kvdel(key);
                set_end_time();
                spent_time += get_interval();
                //if(strcmp(value, "없음") == 0)
                //    incorrect += ret == 0;
                //else
                //    incorrect += ret != 0;
                break;
            case OPEN:
                set_start_time();
                ret = kvopen();
                set_end_time();
                spent_time += get_interval();
                break;
            case CLOSE:
                set_start_time();
                ret = kvclose();
                set_end_time();
                spent_time += get_interval();
                break;
            }

            err += !!ret;
        }



        
        fclose(fp);
    
        
        printf("operations: %d, incorrect : %d, accurate: %.2f, time : %f\n", 
			cnt, incorrect, (cnt - incorrect) * 100. / cnt, spent_time);

    }


    return 0;
}
