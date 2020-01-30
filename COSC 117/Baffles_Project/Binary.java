
public class Binary {
	
	
	public static int linearSearch(int arr[], int value) {
		
		int i;
		
		int arrLength = arr.length;
		
		for(i = 0; i < arrLength; i++) {
			
			if(arr[i] == value) {
				
				return i;
				
			}
			
		}
		
		return -1;
		
	}
	
	public static int binarySearch(int arr[], int value) {
		
		int begin = 0;
		int end = arr.length - 1;
		int mid;
		
		while(begin <= mid) {
			
			mid = (begin + end)/2;
			
			if(arr[mid] == value) {
				
				return mid;
				
			} else if(arr[mid] < value) {
				
				begin = mid + 1;
				
			} else {
				
				end = mid - 1;
				
			}
			
		}
		
		return -1;
		
	}
	
	public static void main(String[] args) {
		
		int[] arr1 = new int[10];
		
		int[] arr2 = new int[10];
		
		int i;
		
		for(i = 0; i < 10; i++) {
			
			arr1[i] = (int)(Math.random() * 10);
			
		}
		
		for(i = 0; i < 10; i++) {
			
			arr2[i] = i;
			
		}
		
	}

}
