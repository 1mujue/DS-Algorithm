//树的相关内容，如下先将进行定义和性质的说明。
/*
树的相关定义：
1.结点的度：拥有的子树数量（可以理解为有几个分叉）
2.树的度：max(节点的度)
3.叶子结点：度为0的节点（相当于在此终结了）
4.分支结点：度不为0
5.结点的层次：从根结点开始，根节点为第1层，其孩子节点都在第2层
6.树的深度：max(层次)
7.有序树：结点子树相对次序不能随意变换。
8.森林：m（m>=0)棵不相交的树的集合称之为森林或者树林。可见每个分支结点的子树的集合就是森林。
树的相关性质：
1.非空树的结点总数=所有结点的度+1
2.度为k的非空树的第i层最多有k^i-1个结点
3.深度为h的k叉树最多有(k^h-1)/(k-1)个结点
4.具有n个结点的k叉树的最小深度为[logk(n(k-1)+1)]
证明:根据性质3可知(k^h-1-1)/(k-1)<n<=(k^h-1)/(k-1)，所以k^h-1<n(k-1)+1<=k^h
所以可知h-1<logk(n(k-1)+1)<=h，即可得到结论.
注意:k叉树的意义是每一个结点都具有k个分支，而且严格区分第1，2......k分支的有序树。
三重链表来表示树：一个指针指向第一个（最左边）的孩子结点（没有则为NULL），第二个指针指向父母结点，第三个指向相邻在右边的兄弟结点（没有则为NULL)

二叉树的相关定义和性质
二叉树的相关定义：
1.满二叉树：叶子结点全在最后一层的二叉树就是满二叉树。换言之，一颗深度为h，且有2^h-1个结点的二叉树就是满二叉树
2.完全二叉树：只有最下面两层的度可以不为2，并且最后一层的结点（可知一定是叶结点）全在左侧，则为完全二叉树。
3.理想二叉树：除了最下面一层全是满的。
4.平衡二叉树：每个结点的子树深度相差不超过1，可知这样的树便于搜索查找。(AVL)
二叉树的相关性质：
1.具有n个结点的非空二叉树有且仅有n-1个分支。事实上这是很显然的，只要一个结点（除根节点）有且仅有
一个双亲结点就都满足这个性质。
2.在任意非空二叉树中，如果叶结点的数目为n0,度为2的结点数量为n2，则有：n0=n2+1。
证明：叶结点的数目等价于度为0的结点的数目。假设有n个结点，n1个度为1的结点，则：
n=n0+n1+n2，而n-1=0*n0+1*n1+2*n2，所以n0=n2+1。事实上只要知道了各个度所对应的节点数n0,n1,n2......nk,
则有n0=n2+2n3+3n4+......+(k-1)nk。
3.具有n个结点的完全二叉树的深度为[log2n]+1
4.对具有n个结点的完全二叉树进行编号（从上到下，从左到右），则编号为i的结点有以下性质。
1)i>1，则编号为i的双亲结点的编号为[i/2]
2)2i<=n，则编号为i的结点的左孩子结点的编号为2i，如果2i>n,则其无左孩子结点，也即为叶结点。
3)2i+1<=n，则编号为i的结点的右孩子结点编号为2i+1，如果2i+1>n，则其无右孩子结点。

树与二叉树的转换：
一般树转换成二叉树：
1在所有兄弟节点之间连线；
2对每个结点，只保留与左孩子的连线；
3顺时针旋转45度（这一步只是在图形上让人觉得更像一颗二叉树）
森林转换成二叉树：
1.先把每棵树转换成二叉树。
2.从最后一颗被转换的二叉树开始，将这颗二叉树的根节点作为上一颗树的右孩子，以此类推即可。
二叉树转换成一般树：
1.如果一个结点是其父母结点的左孩子，那么就只沿着这个父母结点的右孩子以及其右孩子的方向延续下去，然后将被
经过的右孩子均与最开始的这个父母结点连线。
2.删除原有二叉树的父母结点与其右孩子的连线。

二叉树的存储方式。
1.顺序存储。采用这种存储方式的核心思想是将一颗二叉树补充为完全二叉树（补充的都是空结点）
然后从上到下从左到右把每个结点放到数组中就可以。不难发现这样会造成很多空间浪费！（如果二叉树原本不是完全二叉树）
2.链式存储。实质上就是链表多了几个指针而已，需要注意的时，如果想要检索地更快，则建议用三个指针，分别指向左右孩子和
父母结点。

注意到树的定义是具有递归性质的，所以在编写程序的时候一定要善于利用这一点，对于一棵树的操作实际上就是先对
某个结点进行操作，然后再递归对其孩子结点进行操作，一直这样进行下去便可。

二叉树的遍历（重中之重）！！！
注意利用好二叉树的递归定义就可以很好地对一颗二叉树进行遍历。
有三种遍历方式，分别为
前序遍历，中序遍历和后续遍历。
含义就是访问父母结点的次序是什么，前序遍历就是先访问父母结点，再以前序遍历的方式访问该父母节点的左子树和右子树。
中序遍历就是先中序遍历父母结点的左子树，再访问父母节点，再中序遍历父母节点的右子树。
后序遍历就是先后序遍历父母结点的左子树，再后序遍历右子树，再访问父母节点。
程序实现。
void PRE(btree T)
{
    if(T != NULL)
    {
        visit(T);
        PRE(T->lchild);
        Pre(T->rchild);
    }
}
void IN(btree T)
{
    if(T != NULL)
    {
        IN(T->lchild);
        visit(T);
        IN(T->rchild);
    }
}
void POST(btree T)
{
    if(T != NULL)
    {
        POST(T->lchild);
        POST(T->rchild);
        visit(T);
    }
}

中序遍历还可以采用非递归的方法，也就是运用栈。
#define M 50
void in(btree T)
{
    btree stack[M],p = T;//采用stack[M]来存放指针
    int top = -1;
    if(T != NULL)
    {
        do
        {
            while(p != NULL)
            {
                stack[++top] = p;
                p = p->l;
            }//一直向左子树的方向走
            p = stack[top--];//上述循环推出说明已经到尽头，要开始访问父母结点了
            visit(p);
            p = p->r;//访问完父母结点就开始访问右子树了
        }while(p != NULL || top != -1);
    }
}

同样的，后序遍历也可以用堆栈的方法来进行，现在先分析以下思路。
可知对于后序遍历，要先遍历完左子树，然后再遍历完右子树，才能够访问父母结点，因此在遍历的时候需要将每一个
父母结点先压入栈，然后在采用某个指标看一看是否需要出栈。
#define M 50
void post(btree T)
{
    btree stack1[M],p = T;
    int stack2[M],flag,top = -1;//flag即使指标，也即用于判断该结点的左右子树是否已经遍历完
    if(T != NULL)
    {
        do
        {
            while(p != NULL)
            {
                stack1[++top] = p;
                stack2[top] = 0;
                p = p->l;
            }
            p = stack1[top];
            flag = stack2[top--];
            if(flag == 0)//尚未访问右子树
            {
                stack1[++top] = p;//说明这个结点还不需要出栈，所以又把它塞回去。
                stack2[top] = 1;
                p = p->r;
            }
            else if(flag == 1)
            {
                visit(p);
                p = NULL;
            }
        }while(p != NULL || top != -1)
    }
}

当然，我们还可以按照层次进行遍历。我们可以这样操作：
先将一行的结点全部压入队列，先把他们都访问一次，然后让它们出队，但是要把其左右子树压如队列，如此这样下去便可。
#define M 50
void layer_order(btree T)
{
    btree stack[M],p;
    int front = -1,rear = -1;
    if(T ! = NULL)
    {
        stack[++rear] = T;
        while(front < rear)
        {
            p = stack[++front];
            visit(p);
            if(p->l != NULL)
                stack[++rear] = p->l;
            if(p->r != NULL)
                stack[++rear] = p->r;
        }
    }
}

事实上我们可以根据前序遍历和中序遍历或者后序遍历和中序遍历来确认一颗树的原样
其具体思路是，前序遍历的第一个肯定是根节点，而中序遍历肯定会以根节点左右分为左子树和右子树，
然后再读取前序遍历的下一个结点，这又是一个父母节点。在中序遍历中再次左右分为左子树和右子树，
所以只需要这样一直进行下去，就可以还原出整个树的面貌，后序遍历和中序遍历还原的原理和这个类似。

树的相似和等价。
树的相似是指两棵树具有相同的拓扑结构，但是数据域不一定相同，而树的等价就是指两棵树的拓扑结构和数据域均相同。
判断相似的方法。
int is_similar(btree T1,btree T2)
{
    if(T1 == NULL & T2 == NULL)
        return 1;
    else if(T1 != NULL && T2 !=NULL && is_similar(T1->l,T2->l) && is_similar(T1->r,T2->r))
        return 1;
    return 0;
}

二叉表的建立
void build(dbtree T)//注意是二重指针
{
    int n;
    get(n);//获取一个数据点
    if(condition)//当满足一定条件的时候才建立二叉树
    {
        (*T)->data = n;
        build(&((*T)->l));
        build(&((*T)->r));
    }
    else
    {
        *T = NULL;
    }
}

二叉树的销毁
void destroy(btree T)
{
    if(T != NULL)
    {
        destroy(T->l);
        destroy(T->r);
        free(T);//类似于后序遍历！
        T = NULL;
    }
}

二叉树的复制（实际上就是二叉树的遍历问题）
btree copy(btree T1)
{
    btree T2;
    if(T1 == NULL)
        return NULL;
    else
    {
        T2 = (btree)malloc(sizeof(tree));
        T2->data = T1->data;
        T2->l = copy(T1->l);
        T2->r = copy(T1->r);//类似于前序遍历！
    }
    return T2;
}

测试二叉树是否等价
实质上与测试二叉树是否相似很像，只不过多了一个判定数据域是否相同的条件而已。

获得二叉树的深度
int depth(btree T)
{
    btree stack1[M].p = T;
    int stack2[M];
    int current_depth,max_depth = 0,top = -1;
    if(T != NULL)
    {
        current_depth = 1;
        do
        {
            while(p != NULL)
            {
                stack1[++top] = p;
                stack2[top] = current_depth;
                p = p->l;
                current_depth++;
            }
            p = stack1[top];
            current_depth = stack2[top--];
            if(p->l == NULL && p->r == NULL)
                if(current_depth > max_depth)
                    max_depth = current_depth;
            p = p->r;
            current_depth++;
        }while（p != NULL || top != -1)
    }
    return (max_depth);
}
递归算法
int depth(btree T)
{
    if(T == NULL)
        return 0;
    else
        return max(depth(T->l),depth(T->r));
}

求结点所在层次
#define M 50
int layer(btree T,datatype item)//采用的是后序遍历法，因为这样就可以先获取层次，访问结点时更易获取其所在层次
{
    btree stack1[M],p = T;
    int stack2[M],flag,top = -1;
    do
    {
        while(p != NULL)
        {
            stack1[++top] = p;
            stack2[top] = 0;
            p = p->l;
        }
        p = stack1[top];
        flag = stack2[top--];
        if(flag == 0)
        {
            stack1[++top] = p;
            stack2[top] = 1;
            p = p->r;
        }
        else
        {
            if(p->data == item)
                return (top + 2);
            p = NULL;
        }
    }while(p != NULL || top != -1)
}

交换所有结点的左右结点
#define M 50
void exchange(btree T)//层次遍历法
{
    btree queue[M],temp,p = T;
    int front,rear;
    if(T != NULL)
    {
        queue[0] = T;
        front = -1;
        rear = 0;
    }
    while(front < rear)
    {
        p = queue[++front];
        temp = p->l;
        p->l = p->r;
        p->r = temp;
        if(p->l != NULL)
            queue[rear++] = p->l;
        if(p->r != NULL)
            queue[rear++] = p->r;
    }
}

线索二叉树
我们知道，在有n个结点的二叉树中，一共有2*n个指针域，但是只有n-1个指针域被使用，另外的n+1个指针
并没有得到很好的利用，所以为了更加充分地利用空间，我们可以在遇到原本是NULL的指针让其指向前驱（左孩子指针为空时）
或者后驱（右孩子指针为空时）,但是这样也会牵涉到一个问题：我的指针到底是指的是前驱后驱还是左孩子右孩子树？因此
我们还需要构建一个标记来确认。
typedef struct node
{
    int data;
    int lbit;//如果取值为1，那么说明p->l指向左孩子树，如果取值为0，那么说明p->l指向直接前驱
    int rbit;//同上
    struct node *l,*r;
}
需要注意的是，前驱和后驱的判定不是一概不变的，主要和遍历方法有关系。
但是不难发现，无论是哪种遍历方式还是有可能有空指针，因此我们可以再建立一个头节点（注意不是根节点），
其head->l = root,head->r = head，(lbit = 1,rbit = 1)，那些还是空的指针就都指向这个head。

线索二叉树的运用
在中序线索二叉树中确定地址为X结点的直接前驱结点
1)如果x->lbit == 0，显然x->l就指向x的前驱结点
2)如果x->lbit == 1，根据中序遍历法，可知x的前驱结点一定是x的左孩子树中最右边的那个结点，
也即顺着左孩子树的右指针一直往下找，直到找到s->rbit == 0时，s就是x的直接前驱。
tbtree pre(tbtree x)
{
    tbtree s;
    s = x->l;
    if(x->lbit == 1)
        while(s->rbit == 1)
            s = s->r;
    return(s);
}

在中序二叉树中确定地址为x结点的直接后驱结点
1)如果x->rbit == 0，显然x->r就指向x的后驱结点
2)如果x->rbit == 1,从中序遍历法，可知右子树最左边的结点一定是x的后驱结点，因此只需要沿着
右孩子树的左结点一直往下找，直到找到s->lbit == 0时，s就是x的直接后驱。
tbtree post(tbtree x)
{
    tbtree s;
    s = x->r;
    if(x->rbit == 1)
        while(s->lbit == 1)
            s = s->l;
    return(s);
}
事实上前序遍历和后序遍历也可以通过类似的方法在线索二叉树中寻找前驱与后驱。
但是我们不难发现这两种遍历方法往往需要判定x结点是否具有兄弟结点以及获知其父母结点的信息，
因此在前序线索二叉树中找直接前驱或者后序线索二叉树中找直接后驱往往可以用三叉链表（储存父母结点地址）

线索二叉树的遍历
可知我们只需要一直访问直接后驱，直到某一个结点的后驱是head的时候就说明以及全部遍历
void Tin_Order(tbtree HEAD)
{
    tbtree p = HEAD;
    while(1)
    {
        p = post(p);
        if(p == HEAD)
            break;
        visit(p);
    }
}

从二叉树到线索二叉树
tbtree prior = head;
//prior指向前一次访问的结点，如果当前访问的结点的左指针
域为空，则它指向prior的结点，如果prior所指结点的右指针域为空，
那么它指向当前访问结点。
void interead(tbtree p)
{
    if(p != NULL)
    {
        interead(p->l);//使左子树线索化
        if(p->l == NULL)//没有左孩子
        {
            p->lbit = 0;//前驱线索
            p->lchild = prior;//左孩子指针指向直接前驱
        }
        else
            p->lbit = 1;
        if(prior->r == NULL)
        {
            prior->rbit = 0;//后继线索
            prior->r = p;//后孩子指针指向直接后继
        }
        else
            prior->rbit = 1;
        prior = p;
        interead(p->r);//使右子树线索化
    }
}
TBTNodeptr  piror;
TBTNodeptr  threading(TBTNodeptr  t)
{
     TBTNodeptr  head;
     head = (TBTNodeptr)malloc(sizeof(TBTNode));
     head->lchild = t; head->rchild = head; head->lbit = head->rbit=1;
     piror = head;
     inThreading(t);
     piror->rchild = head; piror->rbit = 0;
     return head;
}//主程序入口，t指的实际上是这棵树的根节点

线索二叉树的更新
这里只考虑一种很简单的情况，也即在中序线索二叉树中插入一个结点p，使之成为结点s的右孩子。
1)s的右子树为空，可知此时s->r指向的是s的后驱，所以可以将p->r = s->r，然后s->r = p,s->l = s
2)如果s的右子树非空，则将s的右子树变成p的右子树，然后s就成为p的直接前驱(注意，我们插入的是结点，
这说明p并没有左子树，所以其直接前驱是s)，s原来的直接后驱应该变成p的直接后驱。
void insert_right(tbtree s,tbtree p)
{
    tbtree w.
    p->r = s->r;
    p->rbit = s->rbit;//这一步十分巧妙，如国原来s没有右子树，s的直接后驱变成p的直接后驱，如果
    //原来s有右子树，那么s的右子树变成p的右子树，可以看到p->rbit和s->rbit是同步的！
    p->l = s;
    p->lbit = 0;
    s->r = p;
    s->rbit = 1;
    if(p->bit == 1)
    {
        w = post(p);//这里相当于是把原本s的右子树的直接前驱换成p
        w->l = p;
    }
}
二叉排序树
首先先获得一个数据，把它作为根结点的数据域，然后按照以下原则进行二叉树的创建或者插入：
如果data比当前访问结点x的数据域小，就访问x->l,否则访问x->r,直到访问的是空结点，那么
创造一个结点，链接上就可以。比如说一组数据5 10 2 7 20 31 1 2
   5
  2 10
1 2 7 20
        31
循环算法十分简单，只是看上去繁琐而已，接下来写递归算法。
void insert_BST(btree T,datatype item)
{
    if(T == NULL)
    {
        T = (btree)malloc(sizeof(tree));
        T->data = item;
        T->l = NULL;
        T->r = NULL;
    }
    else if(item < T->data)
        insert_BST(T->l,item);
    else
        insert_BST(T->r,item);
}

删除二叉查找树的一个结点
注意到这里的删除只是删除一个结点，并不是删除一个以该结点为根结点的树。而且，删除了之后还是要保持这是一棵二叉查找树
我们可以分为三类情况来讨论。
1)被删除的结点是叶子结点，这种情况下直接删除就可以，然后给父母结点指向该结点的指针域置为NULL
2)被删除的结点只有左子树/右子树，则可以用其左/右子树的根来替代这个结点。
3)被删除的结点有左右子树，那么这个时候我们就要选取其右子树的数据域最小的结点来取代这个结点，原因：
根据二叉查找树的定义，一个结点的左子树中的结点的数据域都会小于该结点的数据域，而右子树的结点的数据域都会大于等于该结点的
数据域，而选取右子树数据域最小的结点来替代被删除的结点就仍然可以满足这个性质。
void delete_BST(dbtree T,btree p,btree q)//删除由p指向的结点,T是根结点地址的地址,q是双亲变量地址
{
    btree R,s;
    int flag = 0;//flag的含义主要是看被删除结点是否由父母结点，如果有的话就需要进一步操作（改指针域）
    if(p->l == NULL)
        if(p == *T)
            *T = p->r;
        else
        {
            R = p->r;
            flag = 1;
        }
    else if(p->r == NULL)
    {
        if(p == *T)
            *T = p->l;
        else
        {
            R = p->l;
            flag = 1;
        }
    }
    else
    {
        s = p;
        R = s->r;
        while(R->l != NULL)
        {
            s = R;
            R = R->l;
        }
        R->l = p->l;//叶子结点作为根结点
        if(s != p)
        {
            s->l = R->r;
            R->r = p->r;
        }
        if(p == *T)
            *T = R;
        else 
            flag = 1;
    }
    if(flag == 1)//注意，在这里面是一个递归的思路，可以验证三种情况经过这个处理都是合适的
        if(p == q->l)
            q->l = R;
        else
            q->r = R:
    free(p);
}

二叉排序树的查找算法
同理可知循环算法十分简单，只是看起来复杂，现在给出递归算法。
btree search_BST(btree T,datatype item)
{
    if(T == NULL)
        return NULL;
    else
    {
        if(T->data == item)
            return T;
        else if(item < T->data)
            return search_BST(T->l,item);
        else if(item > T->data)
            return search_BST(T->r,item);
    }
}

查找长度
对于查找算法的优劣性，我们一般采用平均查找长度的概念来衡量。
不难看出如果数据给入的顺序不一样那么生成的二叉排序树也是不一样的
平均查找长度：确定一个元素在树中的位置所需进行比较次数的期望值
内路径长度(IPL)：从二叉树根结点到某结点所经过的分支数目定义为该结点的路径长度。二叉树里面所有的结点的
路径长度就定义为该二叉树的内路径长度。
外路径长度(EPL)：在二叉树出现空子树的时候增添新的空叶子结点来代表这些子树，从而得到一颗扩充后得到的二叉树
这些新增的结点就称为外部结点，树中本来有的结点就成为内部结点。外路径长度是所有外部结点的路径长度之和。
可以用归纳法证明EPL = IPL + 2n
现在分析二叉排序树的平均查找长度。在n个结点的二叉树中，假如对每个节点的查找概率相等，那么对每个结点
查找成功所需的比较次数就是该结点所在层次数，即等于该结点路径长度+1。则查找成功的平均查找长度是ASL = (IPL + n)/n
如果查找失败，也就是每一次都要查到空指针，可知比较次数为外路径长度，所以ASL = ESL/2n = (IPL + n)/2n
所以ASL = (IPL + n + EPL)/n + 1 + n(考虑到有可能查找成功有可能失败)=(2IPL + 3n)/(2n + 1)，不难证明，最佳
二叉排序树的平均查找长度为O(log2n)，如果二叉排序树退化成单支树，则平均查找长度为O(n)

不难看出如果一颗二叉排序树不平衡，也就是退化程度很大，那么会给查找带来很多的不便，因此我们可以将之转化成平衡二叉树（AVL)
平衡因子：每个结点的左子树深度和右子树深度之差定义为该结点的平衡因子，可以平衡因子只可能取{-1,0,1}(在平衡二叉树中)
插入结点带来的影响(以插入某结点后左子树深度加1为例)
1)插入前一部分结点的左子树深度(hL)与右子树深度(hR)相等，那么插入后平衡因子为1，不需要修改；
2)插入前一部分结点hL < hR，则插入后平衡因子变为0，平衡性更好，不需要完善
3)插入前一部分结点hL > hR，则插入后平衡因子变为2，需要调整！
(插入某结点导致右子树深度加1也类似)

最小不平衡二叉树：离插入结点最近，并且平衡因子绝对值大于1的结点为根的子树。后面我们可以证明，如果最小不平衡
二叉树被调整为平衡二叉树之后，整个二叉排序树就由平衡了。
接下来，我们用A来代替最小不平衡二叉树，总共有四种可能的调整情况（k代表插入的结点)
1)LL型调整
      A
    B   x
  y   z    
  k
如上面这颗树，造成不平衡的原因是在A的左孩子(B)的左子树上插入结点，那么就进行如下调整：
      B
    y   A
    k  z  x
可以验证这还是一颗排序二叉树。
具体的指针更改:
temp = B->r;
B->r = A;
A->l = temp;
注意：A不一定为整棵树的根结点，因此最后修改完成后还要将A的父母结点原本指向A的指针改成指向B。

2)RR型调整
      A
    x   B
      y   z
          k
如上面这一棵树，可以更改为：
      B
    A   z
  x  y  k
具体的指针更改：
temp = B->l;
B->l = A;
A->r = temp;

3)LR型调整
相当于在A的左子树(B)的右子树(C)中拆入了一个新结点
      A
    B   x
  y   C
    z   m
    k / k
在插入之前,hy = hx = h，hz = hm = h - 1，注意如果h = 0,则x,y,z,m都是空树，并且C结点不存在，也即说C就是将
被插入的新结点。否则，插入的结点就为C结点的左子树或右子树，更改方法：
      C
    B   A
  y  z m  x
     k
如果是在m下插入k，那么就是
      C
    B   A
  y  z m  x
       k
具体的指针更改：
temp1 = C->l;
temp2 = C->r;
C->l = B;
c->r = A;
B->r = temp1;
A->l = temp2;

4)RL型调整
      A
    y   B
      C   x
    z   m
    k / k
经过调整之后如下：
      C
    A   B
  y  z m  x
     k
或者
      C
    A   B
  y  z m  x
       k
具体的指针更改：
temp1 = C->l;
temp2 = C->r;
C->l = A;
c->r = B;
A->r = temp1;
B->l = temp2;

获得一一个结点的所有祖先结点
void parents(btree T,int stack[],int s,int key)//stack作为储存目前路径上的结点的关键值，
//当然，最根本的方法自然是开一个指针数组，储存目前路径上的结点，这样在形式上就可以统一。
{
    while(T != NULL)
    {
        if(T->key == key)
        {
            for(int i1 = 0;i1 <= s;i1++)
                printf("%d ",stack[i1]);
            return ;
        }
        else
        {
            stack[s++] = T->n;
            parents(T->l,stack,s,key);
            parents(T->r,stack,s,key);
            s--;//由于是递归，因此刚开始入栈后需要出栈
        }
    }
}

堆(heap)
一个堆是一个完全二叉树，且大顶堆或者小顶堆应当满足
对于每一个结点，其孩子结点的关键值大小均小于或者大于该结点的关键值
根据完全二叉树的概念，不难得出parent->key > parent->l->key,
parent->key > parent->r->key(小顶堆类似)
一般而言，为了形式上的简便，我们在创造一个堆的时候采用数组，并且首个
结点(根节点)的位置是stack[1],原因就是，对于完全二叉树的第i个结点，有：
[i/2]是其父母结点，2i是其左孩子结点，2i+1是其右孩子结点（如果存在的话）
但是如果用数组存储而且从0开始存储，那么上式就相应变为：
[(i-1)/2],2i+1,2i+2，很容易出现错误！

大顶堆的插入算法：
思路很简单，先把元素插在队尾，然后不断地调整位置就可以了（如果该元素
比起父母节点大，那么就交换二者位置，依次下去就行）
int heap[1000];
int Hnum;
void HeapInsert(int key,int heap[])
{
    int i;
    heap[Hnum++] = key;
    for(i = Hnum - 1;i != 0 && (key > heap[i/2]);i /= 2)
        heap[i] = heap[i/2];
    heap[i] = key;//找到合适的位置！
}
堆的删除（实质上就是从堆顶取走最大元素，将堆未的元素放在堆顶后
再慢慢进行调整）
int heapDelete(int heap[])
{
    int i = 1;j;
    int cur,last;
    cur = heap[1];
    last = heap[--Hnum];
    while(i * 2 < Hnum)
    {
        j = i * 2;
        if(j != Hnum - 1 && heap[j] < heap[j + 1])
            j++;//保证j指向的是i的左右孩子中的最大的一个
        if(last < heap[j])
            heap[i] = heap[j];
        else
            break;
        i = j;
    }
    heap[i] = last;
    return cur;
}
*/

