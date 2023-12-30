#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "node.c"
int main()
{
    char key[10];
    printf("请售货员输入密码:");
    scanf("%s", key);
    if (strcmp(key, "234567") != 0) {
        printf("密码错误\n");
        return 0;
    }
    Node shelves;
    initList(&shelves);
    add(&shelves, (Commodity){"绿豆", food, 100});
    Node cart;
    initList(&cart);
    int choose;
    do {
        showcommodity();
        printf("请输入选择的数字:");
        scanf("%d", &choose);
        switch (choose) 
        {
            case 1:
                create(&shelves);
                printf("创建完成\n");
                break;
            case 2:
            {
                refix(&shelves);
                printf("修改完成\n");
                break;
            }
            case 3:
            {
                refixquantity(&shelves);
                printf("修改数量完成\n");
                break;
            }
            case 4:
            {
                display(&shelves);
                printf("所有货架商品信息\n");
                break;
            }
            case 5:
            {
                char name[100];
                printf("请顾客输入查询商品的名称:");
                scanf("%s",name);
                ask(&shelves,name);
                break;
            }
            case 6:
            {
                char name[100];
                int quantity;
                printf("请顾客输入加入购物车商品的名称:");
                scanf("%s",name);
                printf("请输入顾客加入购物车商品的数量:");
                scanf("%d",&quantity);
                shopcart(&shelves,&cart,name,quantity);
                break; 
            }
            case 7:
            {
                check (&shelves,&cart);
                printf("结账完成\n");
                break;
            }
            case 8:
            {
                printf("退出系统\n");
                break;
            }
        }
    } 
    while (choose!=0);
    return 0;
}


