//
// Created by 24887 on 2023/7/13.
//


#include "Sequence.h"
#include "SingleList.h"
#include "CircleSingleList.h"
#include "DoubleLinkedList.h"
#include "StackAndQueue.h"
#include "Binarytreetraversal.h"
#include "Cluebinarytree.h"
#include "Huffman.h"
#include "AdjacencyMartixGraph.h"
#include "AdjacencyListGraph.h"
#include "Adjacencymultiplicity.h"
#include "OrthogonallistGraph.h"
#include "sort.h"

#include <iostream>
#include <stack>
using namespace std ;


/*
 * 第一章 数据结构的定义
 * 第二章 线性表
 *       顺序表 单链表 循环单链表 双向链表
 * 第三章 栈和队列
 *       栈 队列 括号匹配问题 表达式求值
 * 第四章 串
 *
 * 第五章 树
 *       二叉树的创立与三种遍历
 *       线索二叉树
 *       哈夫曼树
 *
 * 第六章 图
 *
 *
 * */
//顺序表
void OpSeq(){
    Sequence sequence(10) ; // 创建一个size为10顺序表的实例
    sequence.InitTable() ;       //实例中初始化链表各种数据
    sequence.ShowTable() ;       // 遍历
    cout << "-------------" << endl ;
    sequence.InsertTable(6, 99) ;
    sequence.InsertTable(1, 90) ;
    sequence.InsertTable(4 , 88) ;
    sequence.InsertTable(3 , 520) ;
    sequence.ShowTable() ;       // 遍历
    cout << "-------------" << endl ;

    sequence.addLength() ;
    cout << sequence.seq.size << endl ;
    cout << "-------------" << endl ;

    int data ;
    sequence.DeleteTable(2 , data) ;
    cout << "Delete the data :" << data << endl ;
    sequence.ShowTable() ;       // 遍历
    cout << "-------------" << endl ;
    if (sequence.DestroyTable()){
        cout << "Delete Success" << endl ;
    }
}


//单链表
void OpSlL(){
    SingleList singleList ;
    singleList.InitList_L() ;
    singleList.CreateList_R(6) ;
    singleList.ListPrint() ;
    if(singleList.DestroyList()){
        cout << "Having Deleting !!!" << endl ;
    }
    cout << "-----------" << endl ;
    SingleList singleList1 ;
    singleList1.InitList_L() ;
    singleList1.CreateList_H(6) ;
    singleList1.ListPrint() ;
    cout << "-----------" << endl ;
    singleList1.ListInsert_L(2,56);
    singleList1.ListPrint() ;
    singleList1.ListInsert_L(6, 90) ;
    singleList1.ListPrint() ;
    singleList1.ListInsert_L(1,67) ;
    singleList1.ListPrint() ;
    cout << "-----------" << endl ;
    if(singleList1.DestroyList()){
        cout << "Having Deleting !!!" << endl ;
    }
}


//双链表
void OpDll(){
    DoubleLinkedList doubleLinkedList ;
    if(doubleLinkedList.InitTDoubleList()){
        cout << "Create a doublelinkedlist successfully" << endl ;
    }

    doubleLinkedList.CreateList_H(10) ;
    doubleLinkedList.DisplayLink() ;

    DoubleLinkedList doubleLinkedList1 ;
    if(doubleLinkedList1.InitTDoubleList()){
        cout <<"Create an another doubleLinkedList successfully" << endl ;
    }
    doubleLinkedList1.CreateList_T(10) ;
    doubleLinkedList1.DisplayLink() ;
}


//括号匹配问题
bool Check(char str[] , int len){
    StackAndQueue stackAndQueue ;
    stackAndQueue.InitStack(stackAndQueue.stack) ;
    for (int i = 0 ; i < len ; i ++){
        if(str[i] == '(' || str[i] == '[' || str[i] == '{'){
            stackAndQueue.PushStack(stackAndQueue.stack , str[i]) ;
        }else {
            if(stackAndQueue.EmptyStack(stackAndQueue.stack)){
                return false ;
            }
            char top ;
            stackAndQueue.PopStack(stackAndQueue.stack , top) ;
            if((str[i] == ')' && top != '(') ||
                (str[i] == ']' && top != '[') ||
               ( str[i] == '}' && top != '{')){
                return false ;
            }
        }
    }

    return stackAndQueue.EmptyStack(stackAndQueue.stack) ;

}


//中缀表达式转换为后缀表达式
int getpriority(char c){
    if ( c == '+' || c == '-'){
        return -1 ;
    }else {
        return 1 ;
    }
}


//s1操作数栈 s2是符号栈
void convert(string& express, stack<char>& s1, stack<char>& s2)
{
    int i = 0;
    while (express[i] != '\0')//扫描中缀表达式
    {
        if ('0' <= express[i] && express[i] >= '9')//如果扫描到了操作数，直接入s1
        {
            s1.push(express[i++]);
        }
        else if (express[i] == '(')//如果扫描到了左括号，直接入s2
        {
            s2.push(express[i++]);
        }
        else if (express[i] == '+' || express[i] == '-' || express[i] == '*' || express[i] == '/')//扫描到运算符进行优先级判断
        {
            if (s2.empty() || s2.top() == '(' || getpriority(express[i]) > getpriority(s2.top()))//如果此时S2为空或者栈顶元素为左括号，或者扫描到的运算符优先级大于栈顶运算符优先级，则入S2
            {
                s2.push(express[i++]);
            }
            else//反之优先级如果是小于等于的话，那么就要把运算符出栈然后入s1
            {
                char temp = s2.top();
                s2.pop();
                s1.push(temp);
            }
        }
        else if (express[i] == ')')//最后一种情况就是扫描到了右括号，那么就把S2从栈顶到左括号的元素依次出栈入栈
        {
            while (s2.top() != '(')
            {
                char temp = s2.top();
                s2.pop();
                s1.push(temp);
            }
            //注意最后停止循环的时候S2的栈顶元素是左括号，但是不要把左括号入栈，所以直接丢掉左括号
            s2.pop();
            i++;//不要忘记后移
        }
    }
    while (!(s2.empty()))//如果s2没有空，那么依次出s2，入s1
    {
        char temp = s2.top();
        s2.pop();
        s1.push(temp);
    }
}


//二叉树的遍历:Per
void BTT() {
    bst bstTree ;
    int n ;
    ElemTypeBTT s[100] = {0};
    cout << "Enter the PerOrder String ( '#' is on behalf of null ) :  ";
    cin >> s ;
    bstTree.root = bstTree.PerCreateTree(s) ;
    bstTree.PerOrder(bstTree.root) ;
    cout << endl ;
    bstTree.InOrder(bstTree.root) ;
    cout << endl ;
    bstTree.ReOrder(bstTree.root) ;
    cout << endl ;
    bstTree.PerFree(bstTree.root) ;
}


//线索二叉树
void ClueBT(){
    cluebinarytree cbt1 ; //创建一个二叉树的实例1
    cout << "Please input the PreOrder string " << endl ;
    cbt1.root = cbt1.create_ThreadTree() ;
    cbt1.PerOrder(cbt1.root) ;
    cout << endl ;


    cbt1.InThread(cbt1.root) ;
    cbt1.InOrder(cbt1.root) ;
    cbt1.RevInorder(cbt1.root) ;

    cbt1.PerFree(cbt1.root) ;
}

//void
int main()
{

    cout << "The Function is created to show relevant basic operation in these chapters from Table to sorting !!!" <<endl ;
    int Chapter = -1 ;
    cout << "Please input the number for the Chapter(1:data 2:table 3:stack&queue 4:string 5:tree 6:graph 7:search 8:sorting):" ;
    cin >> Chapter ;

    while (Chapter != -1){
        switch (Chapter) {
            case 1:{
                break;
            }
            case 2: {

                cout << "1~6 分别代表动态顺序链表，单链表，双向链表，循环单链表，循环双链表，静态链表" << endl ;
                int num = -1 ;
                cout << "Please input the number :" ;
                cin >> num ;
                switch (num) {
                    case 1 :{
                        OpSeq() ;
                        break ;
                    }
                    case 2:{
                        OpSlL() ;
                        break;
                    }
                    case 3:{
                        OpDll() ;
                        break ;
                    }
                    case 4:{
                        break;
                    }
                }

                break;

            }
            case 3:{
                //栈与队列
                cout << "括号匹配问题" << endl ;
                char str[10] = {0} ;
                cin >> str ;
                if(Check(str , 6)){
                    cout << "括号匹配" << endl ;
                }else {
                    cout << "匹配失败" << endl ;
                }

                //表达式的转换
                stack<char> s1;//结果栈，入操作数
                stack<char> s2;//辅助栈，入运算符和括号

                stack<char> result;//输出用

                string expression("(a+b)*c+d-(e+g)*h");
                cout << "转换前为中缀式" << expression << endl;
                convert(expression, s1, s2);
                cout << "转换为后缀式";

                while (!(s1.empty()))
                {
                    char temp = s1.top();
                    s1.pop();
                    result.push(temp);
                }
                while (!(result.empty()))
                {
                    cout << result.top();
                    result.pop();
                }
                cout << endl ;
                break ;
            }
            case 4:{
                //串
                break ;
            }
            case 5:{
                //二叉树的遍历
//                cout << "二叉树的遍历" << endl ;
//                BTT() ;
//                cout << "线索二叉树" << endl ;
//                // 中序线索二叉树
//                ClueBT() ;
                //哈夫曼树
                cout << "Please input the number " << endl ;
                int nums[10] = {0};
                for (int i = 0 ; i < 10 ; i ++){
                    cin >> nums[i] ;
                }

                Huffman huffman ;
                huffman.CreateHuffmanTree(huffman.HT , 10 , nums) ;

                break;
            }
            case 6:{

                //邻接矩阵
//                Graph2 graph2 ;
//                graph2.InitAMGraph(graph2.amGraph) ;
//                graph2.CreateAMGrpah(graph2.amGraph) ;
//                graph2.DisplayAMGraph(graph2.amGraph) ;
                //邻接表
//                Graph3 graph3 ;
//                graph3.InitALGraph(graph3.alGraph) ;
//                graph3.CreateALGrapg(graph3.alGraph) ;
//                graph3.DisplayALGraph(graph3.alGraph) ;
                //邻接多重表
//                Graph graph ;
//                graph.InitAMLGraph(graph.G) ;
//                graph.CreateAMLGraph(graph.G) ;
//                graph.DisplayAMLGraph(graph.G) ;
                //十字链表
                Graph4 graph4 ;
                graph4.InitOLGrpah(graph4.olGraph) ;
                graph4.CreateOLGraph(graph4.olGraph) ;
                graph4.DisplayOLGraph(graph4.olGraph) ;
                break ;
            }
            case 7:{

                break;
            }
            case 8:{
//                cout << "Insertion Sort" << endl ;
////                cout << "Please ensure the length of the arr :" ;
////                int num = -1 ;
////                cin >> num ;
////                ElemType arr[num] ;
////                for (int i = 0 ; i < num ; ++ i){
////                    cin >> arr[i] ;
////                }
////                DirectInsertSort(arr , num) ;
                cout << "HalfInsertSort" << endl ;
                int arr[] = {578,432,1325,384,5432,651,3817,564,387,5} ;
                int size = sizeof (arr) / sizeof(arr[0]) ;
                cout << "Before Sorting : " << endl ;
                PrintArr(arr , size) ;
                HalfInsertSort(arr ,size) ;
                cout << endl << "After Sorting :" << endl ;
                PrintArr(arr , size) ;

                cout << "BubbleSort:" << endl ;
                int arr1[] = {5, 243, 42, 123, 55, 56, 32, 23, 78, 324};
                int size1 = sizeof (arr1) / sizeof(arr1[0]) ;
                BubbleSort(arr1 , size1) ;

                cout << "QuickSort:" << endl ;
                int arr2[] = {5, 243, 42, 123, 55, 56, 32, 23, 78, 324};
                int size2 = sizeof (arr2) / sizeof(arr2[0]) ;
                QuickSort(arr2, 0 , size2-1) ;
                PrintArr(arr2 , size2) ;


                cout << "HeapSort:" << endl ;
                int arr3[] = {8, 4, 3, 1, 6, 9, 5, 7, 2, 0};
                int size3 = sizeof (arr3) / sizeof(arr2[3]) ;
                DisplayHeapSort(arr3, size3) ;
                CreateHeap(arr3, size3)  ;
                DisplayHeapSort(arr3 ,size3) ;

                cout <<"MergeSort:" << endl ;
                int a[4] = {0,2,4,6} ;
                int b[6] = {1,3,5,7,8,9};
                int *c = new int[4+6] ;
                MergeSort(a, b, c, 4, 6) ;

                cout << "RadixSort" << endl ;
                int arr4[9] = { 52, 200, 4, 1034, 17, 3319, 8324, 33112, 603 };
                RadixSort(arr4, 9) ;
                break;
            }
            default:{
                break;
            }

        }
        cout << "Please again input the number for the Chapter:" ;
        cin >> Chapter ;
    }

    cout << "The All process has stopped!" << endl ;
    cout << "Thanks for using !" << endl ;
    return 0 ;
}