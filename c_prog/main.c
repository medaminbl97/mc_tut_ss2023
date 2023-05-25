


int str_length(char * str);
void upper_case(char * str);
/*{
    int c = 0;
    for (char * i = str; *i != 0 ; i++)
    {
        c++;
    }
    return c;
    
}*/

int main(){
    char * name=  "naceur";
    int l = str_length(name);
    upper_case(name);

    return 0; 
}