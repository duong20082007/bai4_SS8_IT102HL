#include <stdio.h>
#include <string.h>

struct Subscription {
    int user_id;
    char account_name[30];
    int plan_type;      
    int active_devices; 
    int max_devices;    
    int days_overdue;   
    int account_status; 
};

int main() {
    struct Subscription users[50];
    int n, i;
    int downgraded_count = 0;
    int violation_count = 0;

    printf("Nhap so luong tai khoan (1-50): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan %d ---\n", i + 1);
        printf("ID: "); scanf("%d", &users[i].user_id);
        printf("Ten TK (viet lien khong dau): "); scanf("%s", users[i].account_name);
        printf("Loai goi (1=Free, 2=Individual, 3=Family): "); scanf("%d", &users[i].plan_type);
        printf("So thiet bi dang ket noi: "); scanf("%d", &users[i].active_devices);
        printf("So ngay no cuoc: "); scanf("%d", &users[i].days_overdue);
    }

    for (i = 0; i < n; i++) {
        users[i].account_status = 1; 

        if (users[i].plan_type == 1 || users[i].plan_type == 2) {
            users[i].max_devices = 1;
        } else if (users[i].plan_type == 3) {
            users[i].max_devices = 5;
        }

        if (users[i].days_overdue > 3) {
            users[i].plan_type = 1;      
            users[i].max_devices = 1;     
            users[i].account_status = 0;  
            downgraded_count++;
        }

        if (users[i].active_devices > users[i].max_devices) {
            violation_count++;
        }
    }

    printf("\n=================================== DANH SACH TAI KHOAN ===================================\n");
    printf("%-5s %-15s %-12s %-15s %-10s %-15s\n", "ID", "Ten TK", "Goi", "Thiet Bi(Co/Da)", "Ngay No", "Trang Thai");
    printf("-------------------------------------------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        char plan_name[15];
        if (users[i].plan_type == 1) strcpy(plan_name, "Free");
        else if (users[i].plan_type == 2) strcpy(plan_name, "Individual");
        else strcpy(plan_name, "Family");

        char status_name[15];
        if (users[i].account_status == 1) strcpy(status_name, "Active");
        else strcpy(status_name, "Downgraded");

        printf("%-5d %-15s %-12s %d/%-13d %-10d %-15s\n",
            users[i].user_id,
            users[i].account_name,
            plan_name,
            users[i].active_devices, users[i].max_devices, 
            users[i].days_overdue,
            status_name);
    }
    printf("-------------------------------------------------------------------------------------------\n");

    printf("\n>>> BAO CAO THONG KE VAN HANH <<<\n");
    printf("- Tong so tai khoan rà soat : %d\n", n);
    printf("- So tai khoan bi ha cap    : %d\n", downgraded_count);
    printf("- So tai khoan vi pham      : %d\n", violation_count);

    return 0;
}