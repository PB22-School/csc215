#define MAXSIZE 15
#define END '\0'

struct big_int {
    int data[MAXSIZE];
};

struct big_int* toBigInt(num)
int num;
{

    struct big_int* newBigInt;
    
    int i;
    i = 0;

    int len;
    len = getDigits(num);

    if (len >= MAXSIZE) {
        len = MAXSIZE;
    }
    
    while (i < len) {
        newBigInt->data[i] = num % 10;
        num /= 10;
        i++;
    }
    
    newBigInt->data[i] = END;

}

int getBigIntDigits(bigInt)
struct big_int bigInt;
{
    int i;
    i = 0;

    while (bigInt.data[i] != END) {
        i++;
    }

    return i;
}

int getDigits(number)
int number; 
{

    int i;
    i = 0;

    while (number) {
        number /= 10;
        i++;
    }

    return i;
}

void printBigInt(bigInt)
struct big_int bigInt;
{
    int i;
    i = 0;

    while (bigInt.data[i] != END) {
        printf("%c\0", bigInt.data[i]);
        i++;
    }
}

void big_add(new_num)
struct big_int new_num; 
{

    /*if ()

    int newArr[getDigits(new)]*/
}

int main()
{
    struct big_int* bgint;
    bgint = toBigInt(1024);
    printBigInt(&bgint);
}