#include <stdio.h>

// Recursive function to solve the Tower of Hanoi puzzle
void solveTowerOfHanoi(int disks, char source, char destination, char auxiliary)
{
    if (disks == 1)
    {
        printf("\n Move disk 1 from rod %c to rod %c", source, destination);
        return;
    }
    
    solveTowerOfHanoi(disks - 1, source, auxiliary, destination);//recursive call with shifting position of the disks
    printf("\n Move disk %d from rod %c to rod %c", disks, source, destination);
    solveTowerOfHanoi(disks - 1, auxiliary, destination, source);//recusive call with shifting position of the disks
}

int main()
{
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    
    solveTowerOfHanoi(n, 'X', 'Y', 'Z'); //Rods are x y and z

    return 0;
}