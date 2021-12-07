#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUMBER_OF_FILES 42


const char* fileNames[] = {
"content_103390154372.txt",
"content_241371942532.txt",
"content_275965120132.txt",
"content_457408286340.txt",
"content_548894379652.txt",
"content_561845407364.txt",
"content_563053694596.txt",
"content_564021726852.txt",
"content_581716971140.txt",
"content_585649196676.txt",
"content_589720620676.txt",
"content_600347020932.txt",
"content_602481462916.txt",
"content_608679923332.txt",
"content_609140248196.txt",
"content_611464941188.txt",
"content_613006216836.txt",
"content_613535616644.txt",
"content_614351081092.txt",
"content_617442086532.txt",
"content_625611869828.txt",
"content_625611869828.txt",
"content_635974160004.txt",
"content_637213838980.txt",
"content_637910290052.txt",
"content_639149772420.txt",
"content_640072322692.txt",
"content_640226922116.txt",
"content_640440831620.txt",
"content_640756977284.txt",
"content_640796167812.txt",
"content_641103728260.txt",
"content_642105708164.txt",
"content_642921434756.txt",
"content_643025047172.txt",
"content_643155463812.txt",
"content_643205664388.txt",
"content_643773337220.txt",
"content_644115500676.txt",
"content_645567712900.txt",
"content_646179491460.txt",
"content_646599577220.txt"
} ;

char* takeUserInput(char* keyword);
void readAllFiles(char* keyword);
int calculateSimilarityScoreForFile(FILE *filePtr, char* keyword);




struct documentNode{

FILE *filePtr;
int documentNumber;
int similarityScore;

int flag;

int degree;

struct documentNode *parent;
struct documentNode *sibling;
struct documentNode *child;

};

typedef struct documentNode document;

document *relevantDocuments[NUMBER_OF_FILES];
int inserter = 0;

document* createNewDocument(int documentNumber, int similarityScore, FILE *filePtr);

int getArraySize(document *array[]);
void printRelevantDocuments(document *array[]);


document* MAKE_bin_HEAP();
int bin_LINK(document* node, document* node2);
document* bin_HEAP_UNION(document* node, document* node2);
document* bin_HEAP_INSERT(document* node, document* node2);
document* bin_HEAP_MERGE(document* node, document* node2);
document* H = NULL;
document* findMaximumNode(document* head);
void printTheContent(document* node);
int numberInserter = 0;
document* printResults[5];





int main(){

    int sizeOfArr;
    int i;
    int m;
         int r;
    char keyword[100];
    document* root = NULL;
    document* rootOfSubTree = NULL;
    /* taking input from the user */
    takeUserInput(keyword);
    /* now we have the keyword. */
    printf("\n");

    printf("List of all documents with the keyword \"%s\":\n\n", keyword);

    readAllFiles(keyword); /* Now all files are read into our "Documents" Array. We will use heapify operation to create a max-heap from this array. */

    sizeOfArr = getArraySize(relevantDocuments);

    printRelevantDocuments(relevantDocuments);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n");


    for(i=0; i<sizeOfArr; i++) {

        H = bin_HEAP_INSERT(H, relevantDocuments[i]);

    }


    printf("The relevance order is: ");
    for(m=0; m<5; m++) {
    document* maxNode = findMaximumNode(H);
    if(maxNode != NULL) {
    if(m==4){
            printf("Doc%d(%d).\n\n", maxNode->documentNumber, maxNode->similarityScore);
    } else {
        printf("Doc%d(%d), ", maxNode->documentNumber, maxNode->similarityScore);}


    printResults[m] = maxNode;
    numberInserter++;

    H = NULL;
    maxNode->flag = -1;


    for(i=0; i<sizeOfArr; i++) {

        if(relevantDocuments[i]->flag != -1) {
        H = bin_HEAP_INSERT(H, relevantDocuments[i]);
        } else {
        continue;}

    }} else {
    break;}
     }

     for(r=0; r<5; r++){

            if(printResults[r] != NULL) {
     char ch;
     printf("\n\n");
     printf("Doc%d(%d): ", printResults[r]->documentNumber, printResults[r]->similarityScore);
    while((ch = fgetc(printResults[r]->filePtr)) != EOF){
      printf("%c", ch);
      }

      printf("\n\n");
      } else {
      break;}
     }









return 0;
}


document* findMaximumNode(document* head){

document* maximum = NULL;
document* temp = head;
int max = -1;

while(temp != NULL) {

    if(temp->similarityScore > max) {
       max = temp->similarityScore;
        maximum = temp;

    }
    temp = temp->sibling;
}

return maximum;


}


void printTheContent(document* node) {

char ch;

FILE* fp = node->filePtr;

fseek(fp, 0, SEEK_SET);

printf("Doc%d(%d):\n", node->documentNumber, node->similarityScore);


while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);

}



char* takeUserInput(char* keyword) {

    printf("Please enter the keyword:\n");

    scanf("%s", keyword);

    return keyword;

}




void readAllFiles(char* keyword) {

    int i;
    int similarityScore;
    for(i=0; i<NUMBER_OF_FILES; i++) {
    FILE *filePtr = fopen(fileNames[i], "r");


        similarityScore = calculateSimilarityScoreForFile(filePtr, keyword);

        if(similarityScore > 0) {

        relevantDocuments[inserter] = createNewDocument(i+1, similarityScore, filePtr);
        inserter++;

       }
        }

}




void printRelevantDocuments(document *array[]) {
int found = 0;
int arraySize = getArraySize(array);
int i;

for(i = 0; i <arraySize; i++){
    printf("File number #%d. Similarity score is %d.\n", array[i]->documentNumber, array[i]->similarityScore);
    found = 1;
}

if(found==0) {
    printf("No documents could be found!\n");
    printf("Terminating the programme...\n\n");

    exit(0);
;}

}



int getArraySize(document *array[]) {

int k = 0;
while(relevantDocuments[k] != NULL){
    k++;
    }


    return k;



}


int calculateSimilarityScoreForFile(FILE *filePtr, char* keyword) {

int count = 0;
int i = 0;
char word[100];
char ch;
strcpy(word, keyword);


 while ((ch = fgetc(filePtr)) != EOF)
        {

            if(ch == word[i] && i == strlen(word)-1) {
                count++;
                i=0;
            }  else if(ch == word[i]){
                i++;
                continue;
            } else {
                i=0;
            }



        }

    return count;

}


document* createNewDocument(int documentNumber, int similarityScore, FILE *filePtr){



document *createdDocument = (document*) malloc(sizeof(document));

createdDocument->documentNumber = documentNumber;
createdDocument->similarityScore = similarityScore;
createdDocument->filePtr = filePtr;

fseek(createdDocument->filePtr, 0, SEEK_SET);

return createdDocument;


}

document* MAKE_bin_HEAP() {
    document* nullPointer;
    nullPointer = NULL;
    return nullPointer;
}

int bin_LINK(document* y, document* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}



document* bin_HEAP_UNION(document* H1, document* H2) {
    document* prev_x;
    document* next_x;
    document* x;
    document* H = MAKE_bin_HEAP();
    H = bin_HEAP_MERGE(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
                && (next_x->sibling)->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->similarityScore > next_x->similarityScore) {
                x->sibling = next_x->sibling;
                bin_LINK(next_x, x);
            } else {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                bin_LINK(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}



document* bin_HEAP_INSERT(document* H, document* x) {
    document* H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    return H;
}

document* bin_HEAP_MERGE(document* H1, document* H2) {
    document* H = MAKE_bin_HEAP();
    document* y;
    document* z;
    document* a;
    document* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            /* need some modifications here;the first and the else conditions can be merged together!!!! */
            H = z;
        else
            H = y;
    } else
        H = z;
    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            y = y->sibling;
        } else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}




