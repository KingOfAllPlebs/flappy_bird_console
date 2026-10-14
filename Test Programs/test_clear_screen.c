#include <stdio.h>

int main()
{
    printf("\e[1;1H\e[2J");

    printf("fdlkjsafjldsjaf;jljasfd\n");
    printf("dlksajflkdjsaflkdjsalfjdljsa\n");
    printf("fdlkjsafjldsjaf;jljasfd\n");
    printf("dlksajflkdjsaflkdjsalfjdljsa\n");

    int nothing;

    scanf("%d", &nothing);

    printf("\e[1;1H\e[2J");

    scanf("%d", &nothing);

    return 0;
}