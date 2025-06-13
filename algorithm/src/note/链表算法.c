#include <stdio.h>
typedef struct node//单向链表
{
    int data;
    struct node * link;//每一个链表上的单元储存一个数据，并且蕴含指向下一个单元的指针。
}Lnode,*LinkList;

LinkList p;//p指向某一个链表中的单元。
void *q;
p=p->link;//现在将p的地址赋值为p原先指向的单元指向的下一个单元的地址，可见如此循环下去就可以遍历整个列表。
q=p->link;//将p指向的单元所指向的下一个单元的地址赋值给q.

typedef struct node2//双向链表
{
    int data;
    struct node *llink,*rlink;//左右指针，分别指向上一个地址和下一个地址。
}Dnode,*DLinkList;

LinkList CreatList(int n)//创建一个链表,n为链表长度,返回的是头指针
{
    LinkList r,p,head=NULL;//r作为每次创建的空间，p作为遍历使用
    int a;
    for(int i1 = 0 ;i1 < n;i1++)
    {
        r=(LinkList)malloc(sizeof(Lnode));
        scanf("%d",&a);
        r->data = a;
        r->link = NULL;
        if(head==NULL)
        {
            head = r;
        }
        else
        {
            p->link = r;
        }
        p = r;
    }
    for(LinkList s = head;s!=NULL;s=s->link)
    {
        printf("%d ",s->data);
    }
    return(head);
}

void reverse(LinkList e1)//逆转一个链表(相当精妙的算法)
{
    LinkList p,q,r;//r作为储存的地址，p作为先驱，q作为后驱。
    p = e1;
    q = NULL;
    while(p!=NULL)
    {
        r = q;//进行存储，存储之前的后驱
        q = p;//之前的先驱变为现在的后驱
        p = p->link;//现在的先驱需要之前的先驱向下一位
        q->link = r;//注意到q已经变成了上一次的先驱，所以要指向上一次的后驱，也即r
    }//初始化是十分重要的！！！
    e1 = q;
}

LinkList COPY(LinkList lista)//复制一个链表并且返回复制后的链表的头指针
{
    LinkList listb;
    if(lista==NULL)
        return NULL;
    else
    {
        listb = (LinkList)malloc(sizeof(Lnode));
        listb -> data = lista ->data;
        listb -> link = COPY(lista->link);//精巧的递归思想
    }
    return listb;
}

void DELETELIST(LinkList list)//删除一个链表
{
    LinkList p = list;
    while(p != NULL)
    {
        list = p->link;
        free(p);//这个给我们了一个提示，如果想要删除一个节点，就需要用一个储存用的地址来保留相应的位置信息
        p = list;//如果释放了空间，则下一个节点的位置信息会丢失，因此需要做一个保存
    }
}

void INSERTLINK5(LinkList list,int item)//在按值有序链接的线性链表中插入一个数据信息为item的链结点
{
    LinkList p,q,r;
    p = (LinkList)malloc(sizeof(Lnode));//生成一个新的链接点
    p->data = item;//录入数据
    if(list == NULL || item < list->data)//如果链表是空表或者item小于第一个节点的数据
    {
        p->link = list;
        list = p;
        return;
    }//很经典的新建链表操作
    else
    {
        q = list;
        while(q != NULL&&item >= q->data)//不断寻找插入位置
        {
            r = q;//以此来做个标记
            q = q -> link;
        }
        p->link = q;
        r->link = p;
        return;
    }
}
//这些算法给了一个提示：有些时候可以多使用记录指针来记录当前位置。由于链表的首尾链接点与其他链接点
//有不同之处，所以采用这样的方式往往会更加方便操作。
//这也给我们了一个问题：是否可以用某种方式来消除这样的差异，以做到同一性，便于操作？
void JOSEPHUS(int n,int m,int k)//采用循环链表解决约瑟夫问题，也即：有n个人围在一起，编号为1，2，3...，
//从第k编号开始报数，数到m的那个人出列，然后从下一个人开始同样的操作，一直到所有人的出列，此时求出列顺序
{
    LinkList p,r,list = NULL;
    int i;
    for(i = 1;i <= n;i++)
    {
        p = (LinkList)malloc(sizeof(Lnode));
        p->data = i;
        if(list == NULL)
            list = p;
        else
            r->link = p;
        r = p;
    }
    p->link = list;//循环链表的建立
    p = list;
    for(i = 1;i < k;i++)
    {
        r = p;//这一步相当重要,如果没有这一步，在k!=1但m==1的时候删除操作将无法完成
        p = p->link;
    }
    while(p->link != p)//这个时候说明只有一个人了，该结束了，把这个人踢出去就可以
    {
        for(i = 1;i < m;i++)//这里就体现如果没有之前的r = p在m==1的时候删除操作就无法进行的原因。
        {
            r = p;
            p = p->link;
        }
        r->link = p->link;
        free(p);
        p = r->link;//这一步删除如此繁琐就是因为需要保留被删除节点的位置信息
    }
}
//但同时也要注意到循环链表尚有不足：还是没有解决由一个节点反向索引到上一个节点的问题，因此往往需要
//另外一个指针r来储存上一个节点的位置，以此来进行操作，因此我们提出了双向链表的概念。
DLinkList p2;
p2->llink->rlink = p2;
p2->rlink->llink = p2;
int INSERTD(DLinkList list,int x,int item)//在带有头节点的双向链表循环中第一个数据域内容为X的节点
//右边插入一个数据信息为item的新结点
{
    DLinkList p,q;
    q = list->rlink;
    while(q != list&&q->data != x)
        q = q->rlink;
    if(q == list)//一般这种情况就说明双向链表是循环的，而且如果q==list就说明已经遍历了整个链表都找不到
    {
        ERRORMESSAGE("链表中无满足条件的结点！");
        return -1;
    }
    p = (DLinkList)malloc(sizeof(Dnode));
    p->data = item;
    p->llink = q;
    p->rlink = q->rlink;
    q->rlink->llink = p;
    q->rlink = p;
    return 1;
}