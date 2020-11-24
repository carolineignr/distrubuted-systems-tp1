#include <stdio.h>
#include <string.h>
#include <pthread.h>

// ------ define struct
struct arg_struct
{
    char filename[100];
    char *message;
};

int showMenu()
{
    printf("Digite para 1 salvar sua mensagem \n");
    printf("1 - Salvar mensagem \n");
    printf("Digite qualquer outra tecla para sair \n");

    int option;
    scanf("%d", &option);

    return option;
}

FILE *readFile(char *filename)
{
    FILE *fp;

    fp = fopen(filename, "ab");

    return fp;
}

void *writeFile(void *args)
{
    FILE *fp;
    struct arg_struct *arguments = (struct arg_struct *)args;

    fp = readFile(arguments->filename);
    fprintf(fp, "%s \n", arguments->message);
    fclose(fp);
    printf("Writed message: \"%s\" on %s file \n", arguments->message, arguments->filename);
}

int main(int argc, char *argv[])
{
    int option = showMenu();
    if (option == 1)
    {

        printf("Digite sua mensagem \n");
        char message[100];
        scanf(" %[^\n]", message);

        struct arg_struct arguments = {"backup1.txt", message};
        struct arg_struct arguments1 = {"backup2.txt", message};
        struct arg_struct arguments2 = {"backup3.txt", message};

        pthread_t t1, t2, t3;

        pthread_create(&t1, NULL, writeFile, &arguments);
        pthread_create(&t2, NULL, writeFile, &arguments1);
        pthread_create(&t3, NULL, writeFile, &arguments2);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
    }
    return 0;
}
