#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char id[10];
    char name[10];
} Category;

Category categories[50];
int categoryCount = 0;

void quanlidanhmuc();
void loadFile();
void saveFile();
void showMenu();
void showCategories();
void addCategory();
void editCategory();
void deleteCategory();
void searchCategoryByName();
void sortCategories();
int showSubMenu();

int main() {
	int pick;
	do{
		printf("\n===========MENU===========\n");
	printf("1. Quan Li Danh Muc\n");
	printf("2. Quan Li San Pham\n");
	printf("3. Thoat\n");
	printf("Lua chon cua ban la: ");
	scanf("%d", &pick);
	
		switch(pick){
			case 1:{
				quanlidanhmuc();
				break;
			}
			case 2:{
				printf("chua lam gi ca\n");
				break;
			}
			case 3:{
				printf("Thoat\n");
				break;
			}
			default:{
				printf("Lua chon khong hop le\n");
				break;
			}
		}
	
	}while(pick!=3);
    return 0;
}
void quanlidanhmuc(){
	loadFile();
    int choice;
    do {
        showMenu();
        printf("\nNhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                showCategories();
                break;
            case 2:
                addCategory();
                break;
            case 3:
                editCategory();
                break;
            case 4:
                deleteCategory();
                break;
            case 5:
                searchCategoryByName();
                break;
            case 6:
                sortCategories(); 
                break;
            case 7:
                saveFile();
                printf("\nLuu du lieu va thoat chuong trinh!\n");
                break;
            default:
                printf("\nLua chon khong hop le.\n");
        }
    } while (choice != 7);
    exit(0);
}
void loadFile() {
    FILE* file = fopen("categories.dat", "rb");
    if (file == NULL) {
        printf("\nKhong the mo file!\n");
        return;
    }
    fread(&categoryCount, sizeof(int), 1, file);
    fread(categories, sizeof(Category), categoryCount, file);
    fclose(file);
}

void saveFile() {
    FILE* file = fopen("categories.dat", "wb");
    if (file == NULL) {
        printf("\nKhong the mo file!\n");
        return;
    }
    fwrite(&categoryCount, sizeof(int), 1, file);
    fwrite(categories, sizeof(Category), categoryCount, file);
    fclose(file);
}

void showMenu() {
    printf("\n===== Quan Ly Danh Muc =====\n");
    printf("1. Hien thi danh sach danh muc\n");
    printf("2. Them danh muc\n");
    printf("3. Sua danh muc\n");
    printf("4. Xoa danh muc\n");
    printf("5. Tim kiem danh muc theo ten\n");
    printf("6. Sap xep danh sach danh muc\n");
    printf("7. Thoat\n");
}

void showCategories() {
    if (categoryCount == 0) {
        printf("\nKhong co danh muc nao!\n");
        return;
    }
    printf("\n*********DANH SACH DANH MUC**********\n\n");
    printf("+------------+----------------------+\n");
    printf("|     ID     |      Ten danh muc    |\n");
    printf("+------------+----------------------+\n");
    for (int i = 0; i < categoryCount; i++) {
        printf("| %-10s | %-20s |\n", categories[i].id, categories[i].name);
    }
    printf("+------------+----------------------+\n");
    showSubMenu();
}

void addCategory() {
	printf("\n**********THEM DANH MUC**********\n");
    if (categoryCount >= 50) {
        printf("\nKhong the them danh muc.\n");
        return;
    }
    Category newCategory;
    int flag = -1; 
    while (flag == -1) {
        printf("\nNhap ID danh muc: ");
        fgets(newCategory.id, 10, stdin);
        newCategory.id[strcspn(newCategory.id, "\n")] = 0; 
        flag = 1; 
        for (int i = 0; i < categoryCount; i++) {
            if (strcmp(categories[i].id, newCategory.id) == 0) {
                printf("ID \"%s\" da ton tai. Hay nhap ID khac!\n", newCategory.id);
                flag = -1; 
                break;
            }
        }
    }
    printf("Nhap ten danh muc: ");
    fgets(newCategory.name, 10, stdin);
    newCategory.name[strcspn(newCategory.name, "\n")] = 0;
    if (strlen(newCategory.name) == 0) {
        printf("\nDu lieu danh muc khong hop le!\n");
        return;
    }
    categories[categoryCount++] = newCategory;
    printf("\nThem danh muc thanh cong!\n");
    showSubMenu();
}

void editCategory() {
    printf("\n********** SUA DANH MUC **********\n");
    char id[10];
    printf("Nhap ID danh muc can sua: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = 0;
    int flag = -1;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, id) == 0) {
            flag = i;
            break;
        }
    }
    if (flag == -1) {
        printf("Danh muc voi ID \"%s\" khong ton tai.\n", id);
        return;
    }
    printf("\nThong tin hien tai:\n");
    printf("+------------+---------------------+\n");
    printf("|   ID       |   Ten               |\n");
    printf("+------------+---------------------+\n");
    printf("| %-10s | %-19s |\n", categories[flag].id, categories[flag].name);
    printf("+------------+---------------------+\n");
    printf("Nhap ten moi: ");
    fgets(categories[flag].name, 10, stdin);
    categories[flag].name[strcspn(categories[flag].name, "\n")] = 0;

    printf("Danh muc da duoc cap nhat thanh cong!\n");
    showSubMenu();
}


void deleteCategory() {
	printf("\n**********XOA DANH MUC**********\n");
    char id[10];
    printf("Nhap ID danh muc can xoa: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = 0;
    int flag = -1;
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].id, id) == 0) {
            flag = i;
            break;
        }
    }
    if (flag == -1) {
        printf("Danh muc voi ID \"%s\" khong ton tai.\n", id);
        return;
    }
    printf("Ban co chac chan muon xoa danh muc voi ID \"%s\"? (y/n): ", id);
    char confirm;
    scanf(" %c", &confirm);
    getchar();
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = flag; i < categoryCount - 1; i++) {
            categories[i] = categories[i + 1];
        }
        categoryCount--;
        printf("Danh muc da duoc xoa thanh cong!\n");
    } else {
        printf("Huy xoa danh muc.\n");
    }
    showSubMenu();
}

void searchCategoryByName() {
    printf("\n**********TIM KIEM DANH MUC THEO TEN**********\n");
    char name[50];
    printf("Nhap ten danh muc can tim: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("\nKet qua tim kiem:\n");
    printf("+------------+----------------------+\n");
    printf("|     ID     |      Ten danh muc    |\n");
    printf("+------------+----------------------+\n");

    int flag = 0;
    for (int i = 0; i < categoryCount; i++) {
        if (strstr(categories[i].name, name) != NULL) { 
            printf("| %-10s | %-20s |\n", categories[i].id, categories[i].name);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("Khong tim thay"); 
    }
    printf("+------------+----------------------+\n");
}


void sortCategories() {
	printf("\n**********SAP XEP DANH MUC**********\n");
    int choice;
    printf("\nChon thu tu sap xep:\n");
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    getchar();
    for (int i = 0; i < categoryCount - 1; i++) {
        for (int j = i + 1; j < categoryCount; j++) {
            int compare = strcmp(categories[i].name, categories[j].name);
            if ((choice == 1 && compare > 0) || (choice == 2 && compare < 0)) {
                Category temp = categories[i];
                categories[i] = categories[j];
                categories[j] = temp;
            }
        }
    }
    printf("\nDanh sach danh muc sau khi sap xep:\n");
    showCategories();
}

int showSubMenu() {
    int choose;
    do {
        printf("\n1.Quay lai menu\n");
        printf("2.Thoat chuong trinh\n");
        printf("Lua chon cua ban la: ");
        scanf("%d", &choose);
        getchar();
        switch (choose) {
            case 1:
                return 1;
            case 2:
            	exit(0);
            default:
                printf("\nLua chon khong hop le\n");
        }
    } while (choose != 1||choose != 2);

    return 1;
}

