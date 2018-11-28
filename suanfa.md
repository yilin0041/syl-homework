
在计算器科学与数学中，一个排序算法（英语：Sorting algorithm）是一种能将一串数据依照特定排序方式进行排列的一种算法。最常用到的排序方式是数值顺序以及字典顺序。有效的排序算法在一些算法（例如搜索算法与合并算法）中是重要的，如此这些算法才能得到正确解答。排序算法也用在处理文字数据以及产生人类可读的输出结果。

基本上，排序算法的输出必须遵守下列两个原则： 

1. 输出结果为递增序列（递增是针对所需的排序顺序而言）
2. 输出结果是原输入的一种排列、或是重组

虽然排序算法是一个简单的问题，但是从计算器科学发展以来，在此问题上已经有大量的研究。举例而言，冒泡排序在1956年就已经被研究。虽然大部分人认为这是一个已经被解决的问题，有用的新算法仍在不断的被发明。------引用wiki

下面介绍三种基本的排序

## 冒泡排序

先来看一个动图，形象的诠释了冒泡排序

![](images/冒泡排序.gif)

下面给出c语言代码


```
#include <stdio.h>
void bubble_sort(int arr[], int len) {
	int i, j, temp;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}
int main() {
	int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	bubble_sort(arr, len);
	int i;
	for (i = 0; i < len; i++)
		printf("%d ", arr[i]);
	return 0;
}
```
![](images/冒泡排序.png)

## 插入排序

我们还是以gif的形式来诠释这个排序过程

![](images/插入排序.gif)
![](images/插入排序1.gif)


下面给出c语言代码

void insertion_sort(int arr[], int len){
 
        int i,j,key;
  
        for (i=1;i<len;i++){

                key = arr[i];

                j=i-1;
 
                while((j>=0) && (arr[j]>key)) {
 
                        arr[j+1] = arr[j];
 
                        j--;

                }

                arr[j+1] = key;

        }

    }
## 鸡尾酒排序

这是一个相当有意思的名字，让我们来看看是怎么回事吧~

鸡尾酒排序等于是冒泡排序的轻微变形。不同的地方在于从低到高然后从高到低，而冒泡排序则仅从低到高去比较序列里的每个元素。他可以得到比冒泡排序稍微好一点的性能，原因是冒泡排序只从一个方向进行比对（由低到高），每次循环只移动一个项目。

以序列(2,3,4,5,1)为例，鸡尾酒排序只需要访问一次序列就可以完成排序，但如果使用冒泡排序则需要四次。但是在随机数序列的状态下，鸡尾酒排序与冒泡排序的效率都很差劲。 

![](images/鸡尾酒排序.gif)

下面是c语言代码

    void cocktail_sort(int arr[], int len) {
 
	int i, left = 0, right = len - 1;
 
	int temp;
 
	while (left < right) {
 
		for (i = left; i < right; i++)

			if (arr[i] > arr[i + 1]) {
 
			temp = arr[i];

				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
 
		right--;
		for (i = right; i > left; i--)

			if (arr[i - 1] > arr[i]) {
 
				temp = arr[i];

				arr[i] = arr[i - 1];

				arr[i - 1] = temp;

			}

		left++;
 
	}
 
    }
## 小结

排序的算法有许多，随着学习的深入，我们会学到更多更便捷的排序方法，他们的效率会更高更强。我们要多了解，多积累排序的算法，为写出更高效，更便捷的程序奋斗！