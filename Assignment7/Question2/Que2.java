import java.util.*;
import java.lang.*;
import java.io.*;

class Que2
{

    void finding(){
        
    }

    long findMin(long segArray[], long segStart, long segEnd, long start, long end, long index)
    {
        if (start <= segStart && end >= segEnd)
            return segArray[index];

        if (segEnd < start || segStart > end)
            return 1000000000;

        finding();
        long mid = segStart + (segEnd - segStart) / 2;

        long left = findMin(segArray, segStart, mid, start, end, 2*index + 1);
        finding();
        long right = findMin(segArray, mid + 1, segEnd, start, end, 2*index + 2);
        return (left <= right ? left : right);
    }

    long findSum(long segArray[], long segStart, long segEnd, long start, long end, long index){

        if(start <= segStart && end >= segEnd){
            return segArray[index];
        }

        if (segEnd < start || segStart > end)
            return 0;

        long mid = segStart + (segEnd - segStart) / 2;
        finding();

        return (findSum(segArray, segStart, mid, start, end, 2*index+1) + findSum(segArray, mid+1, segEnd, start, end, 2*index+2));

    }

    long findMax(long segArray[], long segStart, long segEnd, long start, long end, long index)
    {
        if (start <= segStart && end >= segEnd)
            return segArray[index];

        if (segEnd < start || segStart > end)
            return 0;

        long mid = segStart + (segEnd - segStart) / 2;
        finding();

        long left = findMax(segArray, segStart, mid, start, end, 2*index + 1);
        long right = findMax(segArray, mid + 1, segEnd, start, end, 2*index + 2);
        finding();
        return (left >= right ? left : right);
    }

    void updateValue(long segArray[], long segStart, long segEnd, long difference, long updateValueIndex, long index){

        if(updateValueIndex < segStart || updateValueIndex > segEnd){
            finding();
            return;
        }

        segArray[index] += difference;

        if(segStart != segEnd){
            long mid = segStart + (segEnd - segStart) / 2;
            updateValue(segArray, segStart, mid, difference, updateValueIndex, 2*index+1);
            finding();
            updateValue(segArray, mid+1, segEnd, difference, updateValueIndex, 2*index+2);
        }

    }

    void updateRange(long segArray[], long segStart, long segEnd, long value, long start, long end, long index){

        for(long i=start; i<=end; i++){
            long difference = value;
            updateValue(segArray, segStart, segEnd, difference, i, 0);
            finding();
        }

    }

    void updateValueForMax(long arr[], long st[], long segStart, long segEnd,  
                    long updateValueIndex, long value, long index) 
    { 
        if (updateValueIndex < segStart || updateValueIndex > segEnd)  
        { 
            System.out.println("Invalid Input");
            return; 
        } 
        
        if (segStart == segEnd)  
        {    
            arr[updateValueIndex] += value; 
            finding();
            st[index] += value; 
        } 
        else { 
                long mid = segStart + (segEnd - segStart)/2; 
                
                if (updateValueIndex >= segStart && updateValueIndex <= mid) 
                    updateValueForMax(arr, st, segStart, mid, updateValueIndex,  
                                value, 2 * index + 1); 
                else
                    updateValueForMax(arr, st, mid + 1, segEnd,  
                                updateValueIndex, value, 2 * index + 2); 
                                
                
                st[index] = Math.max(st[2 * index + 1],  
                        st[2 * index + 2]); 
            finding();

        } 
        return; 
    }

    void updateRangeForMax(long arr[], long segArray[], long segStart, long segEnd, long value, long start, long end, long index){

        for(long i=start; i<=end; i++){
            long difference = value;
            updateValueForMax(arr, segArray, segStart, segEnd, i, difference, 0);
            finding();

        }

    }

    void updateValueForMin(long arr[], long st[], long segStart, long segEnd,  
                    long updateValueIndex, long value, long index) 
    { 
        if (updateValueIndex < segStart || updateValueIndex > segEnd)  
        { 
            System.out.println("Invalid Input");
            finding();

            return; 
        } 
        
        if (segStart == segEnd)  
        {    
            arr[updateValueIndex] += value; 
            st[index] += value; 
        } 
        else { 
                long mid = segStart + (segEnd - segStart)/2; 
                
                if (updateValueIndex >= segStart && updateValueIndex <= mid) 
                    updateValueForMin(arr, st, segStart, mid, updateValueIndex,  
                                value, 2 * index + 1); 
                else
                    updateValueForMin(arr, st, mid + 1, segEnd,  
                                updateValueIndex, value, 2 * index + 2); 
                
                st[index] = Math.min(st[2 * index + 1],  
                        st[2 * index + 2]); 
            finding();

        } 
        return; 
    }

    void updateRangeForMin(long arr[], long segArray[], long segStart, long segEnd, long value, long start, long end, long index){

        for(long i=start; i<=end; i++){
            long difference = value;
            updateValueForMin(arr, segArray, segStart, segEnd, i, difference, 0);
        }

    }

    long treeMin(long array[], long start, long end, long segArray[], long index)
    {
        if (start == end)
        {
            segArray[index] = array[start];
            return array[start];
        }

        long mid = start + (end - start) / 2;
        long left = treeMin(array, start, mid, segArray, index*2 + 1);
        long right = treeMin(array, mid + 1, end, segArray, index*2 + 2);
        finding();


        segArray[index] = (left <= right ? left : right);

        return segArray[index];
    }

    long buildSegmentTreeForSum(long array[], long start, long end, long segArray[], long index)
    {
        if (start == end)
        {
            segArray[index] = array[start];
            return array[start];
        }

        long mid = start + (end - start) / 2;
        long left = buildSegmentTreeForSum(array, start, mid, segArray, index*2 + 1);
        long right = buildSegmentTreeForSum(array, mid + 1, end, segArray, index*2 + 2);
        finding();


        segArray[index] = left + right;

        return segArray[index];
    }

    long treeMax(long array[], long start, long end, long segArray[], long index)
    {
        if (start == end)
        {
            segArray[index] = array[start];
            return array[start];
        }

        long mid = start + (end - start) / 2;
        long left = treeMax(array, start, mid, segArray, index*2 + 1);
        long right = treeMax(array, mid + 1, end, segArray, index*2 + 2);
        finding();


        segArray[index] = (left >= right)?left:right;

        return segArray[index];
    }


	public static void main (String[] args) throws java.lang.Exception
	{
        
        Scanner sc = new Scanner(System.in);

        long array[] = {2,5,1,4,9,3};
        long size = 6;

        long height  = (int)Math.ceil((Math.log(size) / Math.log(2)));
        
        long segtree_size = 2*((int)Math.pow(2, height) - 1);

        System.out.println(height);

        long[]  segArrayForMin = new int[segtree_size];
        long[]  segArrayForMax = new int[segtree_size];
        long[]  segArrayForSum = new int[segtree_size];

        Que2 obj = new Que2();
        obj.treeMin(array, 0, size-1, segArrayForMin, 0);
        obj.treeMax(array, 0, size-1, segArrayForMax, 0);
        obj.buildSegmentTreeForSum(array, 0, size-1, segArrayForSum, 0);
        long start, end, valueToBeAdded;

        while(true){
            System.out.println("1. minimum value ");
            System.out.println("2. maximum value ");
            System.out.println("3. sum ");
            System.out.println("4. Update(value k from l to r i.e. k l r) ");
            System.out.println("5. Exit");
            long option = sc.nextInt();

            switch(option){
                case 1:
                    start = sc.nextInt();
                    end = sc.nextInt();
                    System.out.print("Minimum value in index range "+start+" to "+end+" is ");
                    System.out.println(obj.findMin(segArrayForMin, 0, size - 1, start, end, 0));
                    break;

                case 2:
                    start = sc.nextInt();
                    end = sc.nextInt();
                    System.out.print("Maximum value in index range "+start+" to "+end+" is ");
                    System.out.println(obj.findMax(segArrayForMax, 0, size - 1, start, end, 0));
                    break;

                case 3:
                    start = sc.nextInt();
                    end = sc.nextInt();
                    System.out.print("Sum in index range "+start+" to "+end+" is ");
                    System.out.println(obj.findSum(segArrayForSum, 0, size - 1, start, end, 0));
                    break;

                case 4:
                    valueToBeAdded = sc.nextInt();
                    start = sc.nextInt();
                    end = sc.nextInt();
                    obj.updateRange(segArrayForSum, 0, size-1, valueToBeAdded, start, end, 0);
                    obj.updateRangeForMax(array, segArrayForMax, 0, size-1, valueToBeAdded, start, end, 0);
                    obj.updateRangeForMin(array, segArrayForMin, 0, size-1, valueToBeAdded, start, end, 0);
                    break;

                case 5:
                    System.exit(0);

                default:
                    System.out.println("Enter valid option!!!");
                
            }
        }

	}
}