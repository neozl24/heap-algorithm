//
//  Heap.h
//  Heap
//
//  Created by 钟立 on 2016/11/19.
//  Copyright © 2016年 钟立. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

template <typename Item>
class MaxHeap {
private:
    Item *data;  //初始化时并不知道数组有多少元素
    int count;
    int capacity;
    
    void shiftUp(int k) {
        //将k这个索引的元素尝试着向上移动，来维持堆的定义
        while (k > 1 && data[k/2] < data[k]) {
            std::swap(data[k/2], data[k]);
            k = k/2;
        }
    }
    
    void shiftDown(int k) {
        while (2 * k <= count) {
            int i = 2 * k;
            if (i + 1 <= count && data[i + 1] > data[i]) {
                i += 1;
            }
            if (data[i] > data[k]) {
                std::swap(data[k], data[i]);
                k = i;
            } else {
                break;
            }
        }
    }
    
public:
    MaxHeap(int capacity) {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }
    
    MaxHeap(Item arr[], int n) {
        data = new Item[n+1];
        capacity = n;
        count = n;
        
        for (int i = 0; i < n; i ++) {
            data[i+1] = arr[i];
        }
        for (int i = count/2; i >= 1; i --) {
            shiftDown(i);
        }
    }
    
    ~MaxHeap() {
        delete [] data;
    }
    
    int size() {
        return count;
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    void insert(Item item) {
        assert(count + 1 <= capacity);
        data[count+1] = item;
        count ++;
        shiftUp(count);
    }
    
    void getMax() {
        assert(count > 0);
        return data[1];
    }
    
    Item extractMax() {
        assert(count > 0);
        Item ret = data[1];
        
        std::swap(data[1], data[count]);
        count --;
        shiftDown(1);
        
        return ret;
    }
    
private:
    void putNumberInLine( int num, std::string &line, int index_cur_level, int cur_tree_width, bool isLeft){
        
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }
    
    void putBranchInLine(std::string &line, int index_cur_level, int cur_tree_width){
        
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );
        
        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
    
public:
    void testPrint(){
        
        if( size() >= 100 ){
            std::cout<<"Fancy print can only work for less than 100 int";
            return;
        }
        
        if( typeid(Item) != typeid(int) ){
            std::cout <<"Fancy print can only work for int item";
            return;
        }
        
        std::cout<<"The Heap size is: "<<size()<<std::endl;
        std::cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            std::cout<<data[i]<<" ";
        std::cout<<std::endl;
        std::cout<<std::endl;
        
        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }
        
        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            std::string line1 = std::string(max_level_number*3-1, ' ');
            
            int cur_level_number = std::min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            std::cout<<line1<<std::endl;
            
            if( level == max_level - 1 )
                break;
            
            std::string line2 = std::string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            std::cout<<line2<<std::endl;
            
            cur_tree_max_level_number /= 2;
        }
    }
    
};


#endif /* Heap_h */
