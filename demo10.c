#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int STT = 0;
typedef struct{
    char name[50];
    int age;
    char MSV[20];
    char address[50];
}data;
struct sinhvien{
    data data;
    struct sinhvien *link;
};
typedef struct sinhvien Node;
typedef struct{
    Node *phead;
    Node *ptail;
}list;
void inlist(list *l){
    l->phead = l->ptail = NULL;
}
Node *create_node(char *name,int age,char *MSV,char *address){
    Node *new = (Node *)malloc(sizeof(Node));
    if(new == NULL){
        printf("Cap phat loi:");
        return 0;
    }
    strcpy(new->data.name,name);
    new->data.age = age;
    strcpy(new->data.MSV,MSV);
    strcpy(new->data.address,address);
    new->link = NULL;

    return new;
}
//
void create_list(list *l){
    int n;printf("Nhap 1 de bat dau: ");
    while(scanf("%d",&n) && n==1){
        getchar();

        char name[50];
        int age;
        char MSV[20];
        char address[50];
        
        printf("Nhap ten: ");
        gets(name);
        printf("Nhap tuoi: ");
        scanf("%d",&age);
        getchar();
        printf("Nhap MSV: ");
        gets(MSV);
        printf("Nhap dia chi: ");
        gets(address);

        Node *newNode = create_node(name,age,MSV,address);
        
        if(l->phead == NULL){
            l->phead = l->ptail = newNode;
        }
        else{
            l->ptail->link = newNode;
            l->ptail = newNode;
        }
        l->ptail->link = NULL;
        printf("\nNhap 1 de tiep tuc: ");
    }
}

//lay vi tri ten
int tach_ten(char s[]){
    int len = strlen(s);
    int idx = 0;
    for(int i = len-1;i>=0;i--){
        if(s[i]==' '){
            idx = i+1;
            break;
        }
    }
    return idx;
}
void xx(list *l){
    Node *i,*j;
    for(i=l->phead;i->link!=NULL;i = i->link){
        for(j = i->link;j!=NULL;j = j->link){
            int idx1 = tach_ten(i->data.name);
            int idx2 = tach_ten(j->data.name);
            if(i->data.name[idx1] > j->data.name[idx2]){
                data tmp = i->data;
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
}

//viet chuan hoa
void upper(char s[]){
    strlwr(s);
    int len = strlen(s);
    for(int i=0;i<len;i++){
        if(s[i]!=' '){
            s[i] = toupper(s[i]);
        }
        while(s[i]!=' '){
            i++;
        }
    }
}
//ghi vao file text
void ghi_vao_file(list l)
{
    FILE *ptr = fopen("QLSV.txt", "wt");
    if (ptr == NULL){
        printf("Loi khong mo duoc file nay\n");
        return;
    }
    Node *temp = l.phead;

    fprintf(ptr, "\t\t      ========== Danh sach quan ly sinh vien ========\n");
    fprintf(ptr,"\t\tSTT    HO TEN \t\t    MSV            TUOI        DIA CHI\n");
    while (temp != NULL){
        upper(temp->data.name);
        strupr(temp->data.MSV);
        upper(temp->data.address);
        STT++;
        fprintf(ptr, "\t\t%d     %-15s      %-10s      %-5d     %-15s\n", STT, temp->data.name, temp->data.MSV, temp->data.age, temp->data.address);
        fprintf(ptr, "\t\t----------------------------------------------------------------\n");
        temp = temp->link;
    }
    fclose(ptr);
}
//in
void in(list l){
    Node *temp = l.phead;
    int stt = 0;
    while(temp!=NULL){
        upper(temp->data.name);
        strupr(temp->data.MSV);
        upper(temp->data.address);
        stt++;
        printf("%d     %-15s      %-10s      %-5d     %-15s",stt,temp->data.name,temp->data.MSV,temp->data.age,temp->data.address);
        printf("\n----------------------------------------------------------------\n");
        temp = temp->link;
    }
}
//chen vao sau mot sinh vein
void insert(list *l){
    printf("Muon chen sau sinh vien co MSV: ");
    char msv[20];
    gets(msv);

    //tao mot sinh vien moi
    char name[50];
    int age;
    char MSV[20];
    char address[50];

    printf("Nhap ten: ");
    gets(name);
    printf("Nhap tuoi: ");
    scanf("%d", &age);
    getchar();
    printf("Nhap MSV: ");
    gets(MSV);
    printf("Nhap dia chi: ");
    gets(address);

    Node *svnew = create_node(name,age,MSV,address);

    Node *temp = l->phead;
    Node *p = NULL;
    if(temp!=NULL && stricmp(temp->data.MSV,msv)==0){
        p = temp->link;
        temp->link = svnew;
        svnew->link = p;
        return;
    }
    while (temp != NULL && stricmp(temp->data.MSV, msv) != 0){
        temp = temp->link;
        p = temp->link;
    }
    if(temp==NULL){
        printf("Khong tim thay vi tri can chen: ");
        free(svnew);
        return;
    }
    temp->link = svnew;
    svnew->link = p;
}

//xoa mot sinh vien dua vao msv
void xoa(list *l){
    char msv[20];
    printf("Nhap msv can xoa: ");
    gets(msv);

    Node *temp = l->phead;
    if(temp!=NULL && stricmp(temp->data.MSV,msv)==0){
        l->phead = temp->link;
        free(temp);
        return;
    }
    Node *p = NULL;
    while(temp!=NULL && stricmp(temp->data.MSV,msv)!=0){
        p = temp;
        temp = temp->link;
    }
    if(temp==NULL){
        printf("Khong tim thay msv can xoa:\n");
        return;
    }
    p->link = temp->link;
    free(temp);
}
int main(){
    list l;
    inlist(&l);
    int i;
    printf("1 :Tao list\n");
    printf("2 :Xoa mot sv\n");
    printf("3 :Chen them mot sv\n");
    printf("4 :Xap xep ten theo bcc\n");
    printf("5 :In ra console\n");
    printf("6 :Ghi vao file text\n");
    printf("0 :Ket thuc chuong trinh\n");
    printf("Nhap lua chon: ");
    while(scanf("%d",&i) && (i==1||i==2||i==3||i==4||i==5||i==6)){
        getchar();
        if(i==1){
            create_list(&l);
            printf("Tao thanh cong danh sach\n");
        }
        if(i==2){
            xoa(&l);
            printf("Xoa thanh cong mot sinh vien\n");
        }
        if(i==3){
            insert(&l);
            printf("Chen thanh cong them mot sinh vien\n");
        }
        if(i==4){
            xx(&l);
            printf("Da xap xep xong\n");
        }
        if(i==5){
            printf("STT    HO TEN \t\t    MSV           TUOI       DIA CHI\n");
            in(l);
        }
        if(i==6){
            ghi_vao_file(l);
            printf("Ghi thanh cong danh sach vao file\n");
        }
        if(i==0){
            break;
        }
        printf("Nhap lua chon: ");
    }
    printf("============== Ket thuc chuong trinh ============");
    return 0;
}