#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int productID;
    char productName[50];
    int quantity;
    float price;
    int categoryID;
} Product;

Product products[100];
int productCount = 0;

void loadProducts();
void saveProducts();
void displayMenu();
void displayProducts();
void addProduct();
void editProduct();
void deleteProduct();
void searchProduct();

int main() {
    loadProducts();
    int choice;
    do {
        displayMenu();
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                displayProducts();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                editProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                searchProduct();
                break;
            case 6:
                saveProducts();
                printf("Du lieu da duoc luu. Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 6);
    return 0;
}

void loadProducts() {
    FILE *file = fopen("products.dat", "rb");
    if (file==NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    fread(&productCount, sizeof(int), 1, file);
    fread(products, sizeof(Product), productCount, file);
    fclose(file);
}

void saveProducts() {
    FILE *file = fopen("products.dat", "wb");
    if (file==NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
}

void displayMenu() {
    printf("\n=== He Thong Quan Ly San Pham ===\n");
    printf("1. Hien thi danh sach san pham\n");
    printf("2. Them san pham\n");
    printf("3. Sua thong tin san pham\n");
    printf("4. Xoa san pham\n");
    printf("5. Tim kiem san pham theo ten\n");
    printf("6. Luu va thoat\n");
}

void displayProducts() {
    if (productCount == 0) {
        printf("Chua co san pham nao\n");
        return;
    }

    printf("\n+-----+--------------------+-----------+---------+\n");
    printf("|  ID |         Ten        |  So luong |   Gia   |\n");
    printf("+-----+--------------------+-----------+---------+\n");
    for (int i = 0; i < productCount; i++) {
        printf("| %-3d | %-18s | %-9d | %-7.0f |\n", products[i].productID, products[i].productName, products[i].quantity, products[i].price);
    }
    printf("+-----+--------------------+-----------+---------+\n");
}

void addProduct() {
    if (productCount >= 100) {
        printf("Khong the them \n");
        return;
    }

    Product newProduct;
    printf("Nhap ID san pham: ");
    scanf("%d", &newProduct.productID);
    getchar();

    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == newProduct.productID) {
            printf(" ID san pham da ton tai.\n");
            return;
        }
    }

    printf("Nhap ten san pham: ");
    fgets(newProduct.productName, 50, stdin);
    newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';

    printf("Nhap so luong san pham: ");
    scanf("%d", &newProduct.quantity);

    printf("Nhap gia san pham: ");
    scanf("%f", &newProduct.price);

    if (newProduct.productID <= 0 || strlen(newProduct.productName) == 0 || newProduct.quantity < 0 || newProduct.price < 0) {
        printf("Du lieu san pham khong hop le\n");
        return;
    }

    products[productCount++] = newProduct;
    printf("Them san pham thanh cong!\n");
}

void editProduct() {
    int id;
    printf("Nhap ID san pham can sua: ");
    scanf("%d", &id);
    getchar();

    int flag = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            flag = i;
            break;
        }
    }

    if (flag == -1) {
        printf("Khong tim thay ID nay.\n");
        return;
    }

    printf("Thong tin hien tai:\n");
    printf("+-----+--------------------+-----------+---------+\n");
    printf("|  ID |         Ten        |  So luong |   Gia   |\n");
    printf("+-----+--------------------+-----------+---------+\n");
    printf("| %-3d | %-18s | %-9d | %-7.0f |\n", products[flag].productID, products[flag].productName, products[flag].quantity, products[flag].price);
    printf("+-----+--------------------+-----------+---------+\n");

    Product newProduct = products[flag];

    printf("Nhap ten san pham moi: ");
    fgets(newProduct.productName, 50, stdin);
    if (newProduct.productName[0] != '\n') {
        newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';
    }

    printf("Nhap so luong moi: ");
    int newQuantity;
    scanf("%d", &newQuantity);
    if (newQuantity >= 0) {
        newProduct.quantity = newQuantity;
    }

    printf("Nhap gia moi: ");
    float newPrice;
    scanf("%f", &newPrice);
    if (newPrice >= 0) {
        newProduct.price = newPrice;
    }

    if (newProduct.productID <= 0 || strlen(newProduct.productName) == 0 || newProduct.quantity < 0 || newProduct.price < 0) {
        printf("Du lieu khong hop le.\n");
        return;
    }

    products[flag] = newProduct;
    printf("Sua thong tin san pham thanh cong!\n");
}

void deleteProduct() {
    int id;
    printf("Nhap ID san pham can xoa: ");
    scanf("%d", &id);
    getchar();

    int flag = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            flag = i;
            break;
        }
    }

    if (flag == -1) {
        printf("Khong tim thay ID nay.\n");
        return;
    }

    printf("Ban co chac chan muon xoa san pham ID=%d khong? (y/n): ", id);
    char confirm;
    scanf("%c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Huy xoa san pham.\n");
        return;
    }

    for (int i = flag; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    productCount--;
    printf("Xoa san pham thanh cong!\n");
}

void searchProduct() {
    char name[50];
    printf("Nhap ten san pham can tim: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("\nKet qua tim kiem:\n");
    printf("+-----+--------------------+-----------+---------+\n");
    printf("|  ID |         Ten        |  So luong |   Gia   |\n");
    printf("+-----+--------------------+-----------+---------+\n");

    int flag = -1;
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].productName, name) != NULL) {  
            printf("| %-3d | %-18s | %-9d | %-7.0f |\n", products[i].productID, products[i].productName, products[i].quantity, products[i].price);
            flag = 1;
        }
    }

    if (flag==-1) {
        printf("Khong tim thay"); 
    }
    printf("+-----+--------------------+-----------+---------+\n");
}

