/// A way to redirect stdout to cout.
#include <iostream>
#include <stdexcept>
#include <stdarg.h>
#include <string.h>
using namespace std;

#define mprintf(x,args...) _basic_glue_namespace::show_start(x,##args)
#define printf mprintf
namespace _basic_glue_namespace
{
char _show_buffer[1024];
int show_start(const char* FormatString,...) throw (runtime_error)
{
    va_list ap;
    va_start (ap,FormatString);
    int L=strlen(FormatString);
    int begin_i=0;
    for(int end_i=0; end_i<L; end_i++)
    {
        if(FormatString[end_i]=='%')
        {
            if(begin_i!=end_i)
            {
                memset(_show_buffer,0,1024);
                strncpy(_show_buffer,FormatString+begin_i,end_i-begin_i);
                cout<<_show_buffer;
            }
            switch(FormatString[end_i+1])
            {
            case '%':
            {
                cout<<"%";
                break;
            }
            case 'u':
            {
                unsigned int _temp=va_arg(ap,unsigned int);
                cout<<_temp;
                break;
            }
            case 'd':
            {
                int _temp=va_arg(ap,int);
                cout<<_temp;
                break;
            }
            case 's':
            {
                const char* _temp=va_arg(ap,const char*);
                cout<<_temp;
                break;
            }
            case 'p':
            {
                const void* _temp=va_arg(ap,const void*);
                cout<<_temp;
                break;
            }
            case 'f':
            {
                double _temp=va_arg(ap,double);
                cout<<_temp;
                break;
            }
            case 'l':
            {
                end_i++;
                if(FormatString[end_i+1]=='d')
                {
                    long _temp=va_arg(ap,long);
                    cout<<_temp;
                }
                else if(FormatString[end_i+1]=='u')
                {
                    unsigned long _temp=va_arg(ap,unsigned long);
                    cout<<_temp;
                }
                else if(FormatString[end_i+1]=='f')
                {
                    double _temp=va_arg(ap,double);
                    cout<<_temp;
                }
                else if(FormatString[end_i+1]=='l')
                {
                    if(FormatString[end_i+1]=='d')
                    {
                        long long _temp=va_arg(ap,long long);
                        cout<<_temp;
                    }
                    else if(FormatString[end_i+1]=='u')
                    {
                        unsigned long long _temp=va_arg(ap,unsigned long long);
                        cout<<_temp;
                    }
                    else
                    {
                        throw runtime_error("Cannot cast ll?");
                    }
                }
                else
                {
                    throw runtime_error("Cannot cast l?");
                }
                break;
            }
            default:
                throw runtime_error("Cannot cast ?");
            }
            end_i++;
            begin_i=end_i+1;
        }
    }
    if(begin_i<L)
    {
        cout<<FormatString+begin_i;
    }
    return 0;
}

}

int main()
{
    printf("Hello world This is a test %d and %f%% is now watching %s\n",3,2.5,"Holy Shit");
    return 0;
}
