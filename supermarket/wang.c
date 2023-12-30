#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum //定义了一个名为 `Category` 的枚举类型，用于显示商品的种类。 
{
    dailyuse,
    fresh,
    food
} Category;
typedef struct //定义了一个名为"Commodity"的结构体，表示商品的信息。
{
    char name[100];
    Category category;
    int quantity;
} Commodity;
typedef struct Node //创建链表
{
    Commodity commodity;
    struct Node *next;//表示指向下一个Node节点指针的链表结构体
} Node;
void initList(Node *list)// 新增链表初始化函数，链表指针list所指向的节点初始化，使其成为一个空链表。如果链表没有初始化，那么就没有有效的数据节点，无法进行对链表的正常操作，
{
    list->next = NULL;//表示该节点后面没有其它节点，从而形成一个空链表。
}
//这两个函数配合使用，可以创建一个链表节点，并将节点添加到链表中，然后通过printList函数打印链表中每个节点的商品信息。
Node *createNode(Commodity commodity)//这个函数创建节点，因为插入节点前要先有节点（函数createNode，其作用是创建一个新的Node节点，并将传入的Commodity类型数据存储到新节点中。）
{
    Node *newNode = (Node *)malloc(sizeof(Node));//这是动态内存申请，使指针变为变量
    newNode->commodity = commodity;//将传入的commodity数据赋值给新节点的commodity成员变量。
    newNode->next = NULL;//将新节点的next指针设置为NULL，表示该节点是链表中的最后一个节点
    return newNode;//返回新节点的地址。
}
void printList(Node *headNode) //作用是打印链表中每个节点的信息
{
    Node *pmove = headNode->next;//使用一个临时的指针变量pmove指向链表的头节点的下一个节点（即链表的第一个有效节点）。
    while (pmove) //当pmove指针不为NULL时，继续执行循环。
    {
        printf("%s\t%d\t%d\n", pmove->commodity.name, pmove->commodity.category, pmove->commodity.quantity);//通过访问pmove->commodity成员变量来打印节点中存储的商品的名称、分类和数量信息。
        pmove = pmove->next;//将pmove指针指向下一个节点，继续下一次循环直至遍历完整个链表
    }
}
void insert(Node *headNode, Commodity commodity) //函数用于在链表尾部插入新的节点。
{
    Node *newNode = createNode(commodity);//先创建一个新节点newnode
    Node *currentNode = headNode;
    while (currentNode->next != NULL) //便利链表找到最后一个节点currentnode
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;//将新节点插到链表尾部
}
void add(Node *headNode, Commodity commodity) //用于向链表中添加节点
{
    insert(headNode, commodity);
}
Node *find(Node *headNode, char *name)//用于在链表中查找指定名称节点
{
    Node *p = headNode->next;//从链表第一个节点开始，比较节点名称于指定名称是否相同
    while (p != NULL) 
    {
        if (strcmp(p->commodity.name, name) == 0) 
        {
            return p;//返回该节点指针
        }
        p = p->next;
    }
    return NULL;
}
void fix(Node *list, char *name, Commodity commodity) {
    Node *p = find(list, name);
    if (p != NULL) {
        p->commodity = commodity;
    }
}
void show(Commodity commodity) {
    printf("商品名称：%s 种类：%d", commodity.name,commodity.category);
    switch (commodity.category) 
    {
        case dailyuse:
            printf("日用品");
            break;
        case fresh:
            printf("生鲜");
            break;
        case food:
            printf("食品");
            break;
    }
    printf("数量：%d\n", commodity.quantity);
}

// 修改 display 函数
void display(Node *list) 
{
    Node *p = list->next; // 使用 list->next 而不是 list->headNode
    while (p != NULL) 
    {
        show(p->commodity);
        p = p->next;
    }
}
void ask(Node *list, char *name) //顾客查询商品信息，这段代码用于在商品链表中查找并显示特定商品的信息。这是函数的声明，它接受一个指向链表的指针(`List *list`)和一个指向字符数组的指针(`char *name`)作为参数，返回类型为`void`，表示不返回任何值。
{
    Node *p = find(list, name);//调用find函数，查找链表里是否有此商品。返回一个指向节点(`Node`)的指针，该节点包含有关查询商品的信息。这个指针被赋给变量`p`。
    if (p != NULL) //检查指针`p`是否为`NULL
    {
        show(p->commodity);//调用show函数，显示商品信息。
    } 
    else 
    {
        printf("货架无上商品：%s\n", name);
    }
}
void shopcart(Node *cart, Node *shelves, char *name, int quantity) 
{
    Node *p = find(shelves, name);
    if (p != NULL) 
    {
        if (p->commodity.quantity >= quantity)
        {
            Commodity commodity = p->commodity;
            commodity.quantity = quantity;
            add(cart, commodity);
            p->commodity.quantity -= quantity;
        }
        else 
        {
            printf("商品：%s 数量不足\n", name);
        }
    } 
    else
    {
        printf("货架无此商品：%s\n", name);
    }
}
void check(Node *cart, Node *shelves) 
{
    Node *p = cart->next; 
    while (p != NULL) {
        Node *q = find(shelves, p->commodity.name);
        if (q != NULL) {
            q->commodity.quantity -= p->commodity.quantity;
        }
        Node *temp = p;
        p = p->next;
        free(temp); // 释放购物车中的节点
    }
    initList(cart); // 重新初始化购物车
}
void create(Node *list)
 {
    Commodity commodity;
    printf("创建商品的名称：");
    scanf("%s", commodity.name);
    printf("创建的商品种类 1:日用品 2 生鲜 3 食品：");
    scanf("%d", &commodity.category);
    printf("创建商品的数量：");
    scanf("%d", &commodity.quantity);
    add(list, commodity);
}
void refix(Node *list)
{
    char name[20];
    printf("请输入要修改的商品名称：");
    scanf("%s", name);
    Node *p = find(list, name);
    if (p != NULL) 
    {
        Commodity commodity;
        printf("新创建的商品名称：");
        scanf("%s", commodity.name);
        printf("新创建商品的种类 1 日用品 2 生鲜 3 食品：");
        scanf("%d", &commodity.category);
        printf("新创建商品的数量：");
        scanf("%d", &commodity.quantity);
        fix(list, name, commodity);
    } 
    else 
    {
        printf("货架无此商品：%s\n", name);
    }
}
void refixquantity(Node *list)
{
    char name[20];
    printf("要修改的商品名称：");
    scanf("%s", name);
    Node *p = find(list, name);
    if (p != NULL) 
    {
        int quantity;
        printf("新的商品数量：");
        scanf("%d", &quantity);
        p->commodity.quantity = quantity;
    } else {
        printf("货架无此商品：%s\n", name);
    }
}
void showcommodity() 
{
    printf("超市的商品管理系统\n");
    printf("1.售货员创建商品\n");
    printf("2.售货员修改商品\n");
    printf("3.售货员修改商品数量\n");
    printf("4.显示货架商品信息\n");
    printf("5.顾客查询商品信息\n");
    printf("6.顾客加入购物车\n");
    printf("7.顾客结账\n");
    printf("8.退出系统\n");
}
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


