/*************************************************************************************
** Copyright (c) 2017 Kevin Turkington                                              **
**                                                                                  **
** Permission is hereby granted, free of charge, to any person obtaining a copy     **
** of this software and associated documentation files (the "Software"), to deal    **
** in the Software without restriction, including without limitation the rights     **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        **
** copies of the Software, and to permit persons to whom the Software is            **
** furnished to do so, subject to the following conditions:                         **
**                                                                                  **
** The above copyright notice and this permission notice shall be included in all   **
** copies or substantial portions of the Software.                                  **
**                                                                                  **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    **
** SOFTWARE.                                                                        **
**************************************************************************************/

//NON CONTIGUOUS ARRAY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_FREE(x) do { if ((x) != NULL) {free(x); x=NULL;} } while(0)

typedef void* TYPE;

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    TYPE* data;
} ADTArray;

ADTArray* ADTArrayCreate(int init_capacity)
{
    int i;

    if(init_capacity == 0){
        return NULL;
    }

    ADTArray* obj = malloc(sizeof(ADTArray));
    obj->data = malloc(init_capacity * sizeof(TYPE));
    obj->capacity = init_capacity;
    obj->size = 0;

    //prevents dangling pointers.
    for(i = 0; i < init_capacity + 1;i++){
        obj->data[i] = NULL;
    }

    return obj;
}

void _ADTArrayFreeData(ADTArray* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        SAFE_FREE(obj->data[i]);
    }
}

int ADTArrayFree(ADTArray* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }

    _ADTArrayFreeData(obj,0,obj->capacity); 

    free(obj->data);
    SAFE_FREE(obj);

    return EXIT_SUCCESS;
}

int ADTArraySize(ADTArray* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size;
}

TYPE ADTArrayGet(ADTArray* obj, int idx)
{
    if(obj == NULL){
        return NULL;
    } else if(obj->capacity <= idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    return obj->data[idx];
}

TYPE ADTArraySet(ADTArray* obj,int idx, TYPE item)
{
    if(obj == NULL || idx < 0 || item == NULL){
        return NULL;
    } else if(obj->capacity <= idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    TYPE temp_item = malloc(sizeof(item));
    memcpy(temp_item,item,sizeof(TYPE));
    obj->size++;

    return obj->data[idx] = temp_item;
}

int ADTArrayClearItem(ADTArray* obj,int idx){
    if(obj == NULL || idx < 0){
        return EXIT_FAILURE;
    } else if(obj->capacity >= idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    SAFE_FREE(obj->data[idx]);
    obj->size--;

    return EXIT_SUCCESS;
}

ADTArray* ADTArrayResize(ADTArray* obj, int newcapacity)
{
    if(obj == NULL || newcapacity <= 0){
        return NULL;
    }

    int i;
    TYPE* Newdata = malloc(newcapacity * sizeof(TYPE));
    
    for(i = 0; i < newcapacity;i++){
        //swapping pointers to items.
        Newdata[i] = obj->data[i];
    }

    if((newcapacity - obj->capacity) > 0){
        if(obj->size > newcapacity){
            obj->size -= newcapacity; 
        }
        _ADTArrayFreeData(obj,newcapacity,obj->capacity);
    }

    free(obj->data);
    obj->data = Newdata;
    obj->capacity = newcapacity;

    return obj;
}

int ADTArrayInsert(ADTArray* obj, int idx, TYPE item)
{
    int i;

    if(obj == NULL || idx < 0 || item == NULL){
        return EXIT_FAILURE;
    } else if(obj->capacity <= idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    for(i = idx; i < obj->capacity - 1;i++){
        obj->data[i + 1] = obj->data[i]; 
    }

    ADTArraySet(obj,idx,item);

    return EXIT_SUCCESS;
}

int ADTArrayRemove(ADTArray* obj, int idx)
{
    int i;

    if(obj == NULL || idx < 0){
        return EXIT_FAILURE;
    } else if(obj->capacity <= idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    SAFE_FREE(obj->data[idx]);

    for(i = idx; i < obj->size - 1; i++){
        obj->data[i] = obj->data[i+1];
    }

    obj->size--;

    return EXIT_SUCCESS;
}


int main()
{
    int item1 = 39;

    ADTArray* arr = ADTArrayCreate(100);
    printf("arrayCap:%d\n",arr->capacity);

    ADTArraySet(arr,88,&item1);
    ADTArrayResize(arr,10);
    printf("arrayCap:%d\n",arr->capacity);

    
    ADTArraySet(arr,0,&item1);
    
    int temp = *(int*)ADTArrayGet(arr,0);
    printf(":::%d\n",temp);

    ADTArrayClearItem(arr,0);

    item1 = 69;
    ADTArrayInsert(arr,3,&item1);
    ADTArrayRemove(arr,3);

    // temp = *(int*)ADTArrayGet(arr,3);
    // printf(":::%d\n",temp);

    ADTArrayFree(arr);


    return 0;
}