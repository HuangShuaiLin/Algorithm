#include <stdio.h>
void quicksort(int a[],int l,int h)
{    if(l>=h) return ;  
	int low=l,high=h;
	int pivot=a[low];
	while(low<high){
		while(low<high&&a[high]>=pivot){
			high--;
		}
	    if(low<high)	 a[low]=a[high];
		while(low<high&&a[low]<=pivot){
		    low++;
		}
		if(low<high)     a[high]=a[low];
		if(low==high) a[high]=pivot;
	}   
	quicksort(a,l,low-1);
	quicksort(a,low+1,h);
 } 
 
 
 int main(){
 	int a[]={1,3,5,6,4,8,2,9,7};
 	quicksort(a,0,8);
 	for(int i=0;i<9;i++){
 		printf("%d ",a[i]);
	 }
 	
 	return 0;
 }








