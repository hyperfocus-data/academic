#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
extern "C"
{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHA 26 // num letras do alfabeto
#define TRUE 1
#define FALSE 0

    struct data
    {
        int codCourse;
        char *nameCourse;
        int year;
        int period;
        int nLinked;
        int nRegistred;
        int nEntered;
        int nGraduated;
        int nDropped;
        struct data *next;
    };
    typedef struct data Data;

    struct collection
    {
        struct data *v[ALPHA];
    };

    typedef struct collection Collection;
}

// Funcoes e prototipos (C)
extern "C"
{
    Collection *createRegister(void)
    {
        Collection *c = (Collection *)malloc(sizeof(Collection));
        if (c != NULL)
        {
            for (int i = 0; i < ALPHA; i++)
                c->v[i] = NULL;
            return c;
        }
        return NULL;
    }

    int insert(Collection *c, int cod, char *name, int year, int period,
               int nlinked, int nregistred, int nentered, int ngraduated, int ndropped)
    {
        int index = 0;
        Data *newData = (Data *)malloc(sizeof(Data));
        if (newData != NULL)
        {
            newData->codCourse = cod;
            newData->nameCourse = (char *)malloc((strlen(name) + 1) * sizeof(char));
            if (newData->nameCourse == NULL)
            {
                free(newData->nameCourse);
                return FALSE;
            }
            strcpy(newData->nameCourse, name);
            newData->year = year;
            newData->period = period;
            newData->nLinked = nlinked;
            newData->nRegistred = nregistred;
            newData->nEntered = nentered;
            newData->nGraduated = ngraduated;
            newData->nDropped = ndropped;
            // Calcula o indice utilizando a tabela ASCII. Se o index for A == 65 -> 65 - 65 = 0
            index = toupper(name[0] - 'A');
            newData->next = c->v[index];
            c->v[index] = newData;
            return TRUE;
        }
        return FALSE;
    }

    void printalldata(Collection *c)
    {
        for (int i = 0; i < ALPHA; i++)
        {
            Data *p = c->v[i];
            printf("%c:\n", (char)i + 'A');
            while (p != NULL)
            {
                printf("===================================\n");
                printf("\t* CodCurso: %d\n", p->codCourse);
                printf("\t* Nome do Curso: %s\n", p->nameCourse);
                printf("\t* Ano: %d\n", p->year);
                printf("\t* Periodo: %d\n", p->period);
                printf("\t* N de vinculados: %d\n", p->nLinked);
                printf("\t* N de matriculados: %d\n", p->nRegistred);
                printf("\t* N de Ingressantes: %d\n", p->nEntered);
                printf("\t* N de Diplomados: %d\n", p->nGraduated);
                printf("\t* N de Evadidos: %d\n", p->nDropped);
                printf("===================================\n");
                p = p->next;
            }
        }
    }

    void printnames(Collection *c)
    {
        for (int i = 0; i < ALPHA; i++)
        {
            Data *p = c->v[i];
            printf("%c:\n", (char)i + 'A');
            while (p != NULL)
            {
                printf("\t===================================\n");
                printf("\t* Nome do Curso: %s\n", p->nameCourse);
                printf("\t===================================\n");
                p = p->next;
            }
        }
    }

    int containsstr(char* str, char* substr)
    {
        if (strstr(str, substr))
            return TRUE;
        else
            return FALSE;
    }

    void showCourseDataByName(Collection *c, char *query)
    {
        for (int i = 0; i < ALPHA; i++)
        {
            Data *p = c->v[i];
            printf("%c:\n", (char)i + 'A');
            while (p != NULL)
            {
                if (containsstr(p->nameCourse, query) == TRUE)
                {
                    //printf("\t* CodCurso: %d\n", p->codCourse);
                    printf("\t* Nome do Curso: %s\n", p->nameCourse);
                    printf("\t* Ano: %d | Periodo: %d\n", p->year, p->period);
                    printf("\t* N de Evadidos: %d\n", p->nDropped);
                    //printf("\t* N de Ingressantes: %d\n", p->nEntered);
                    printf("===================================\n");
                }
                p = p->next;
            }
        }
    }
}

using namespace std;

void readninsert(const char *filename, string &buffer, Collection *c) // string& passo a referencia
{
    ifstream fp(filename);
    string line;

    if (!fp.is_open())
    {
        cerr << "Error opening the file." << endl;
        return;
    }

    /* A primeira linha do arquivo csv eh o cabeçalho, logo iremos ler ela antes do loop
    para pula-la */
    getline(fp, line);

    while (getline(fp, line))
    {
        stringstream ss(line);
        vector<string> values;

        while (getline(ss, buffer, ';'))
        {
            values.push_back(buffer); // armazena os valores no vetor
            //cout << buffer << endl;
        }

        try
        {
            int cod = stoi(values[0]);
            string namestr = values[1];
            int year = stoi(values[2]);
            int period = stoi(values[3]);
            int nlinked = stoi(values[4]);
            int nregistred = stoi(values[5]);
            int nentered = stoi(values[6]);
            int ngraduated = stoi(values[7]);
            int ndropped = stoi(values[8]);

            //cout << "Cod: " << cod << ", Name: " << name << endl;
            char *name = (char *)malloc((namestr.length() + 1) * sizeof(char));
            if (name != NULL)
            {
                strcpy(name, namestr.c_str());
                insert(c, cod, name, year, period, nlinked, nregistred, nentered, ngraduated, ndropped);
            }
        }
        catch (const invalid_argument &e)
        {
            cerr << "Error converting values: " << e.what() << endl;
            cerr << "Line: " << line << endl;
        }
    }
    fp.close();
}

int main(int argc, char* argv[])
{
    Collection *c = createRegister();

    if (c != NULL)
    {
        string buffer;
        readninsert("raw/dadosabertos_graduacao_quantitativo-de-alunos.csv", buffer, c);
        //printalldata(c);
        //printnames(c);
        char query[] = "COMPUTAÇÃO E ROBÓTICA EDUCATIVA";
        showCourseDataByName(c, query);
    } 

    return 0;
}