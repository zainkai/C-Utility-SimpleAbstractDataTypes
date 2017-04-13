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

/**********************************
 ** NON CONTIGUOUS ARRAY LIBRARY **
***********************************/
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
} adt_arr;

adt_arr* adt_arrCreate(int init_capacity)
{
    int i;

    if(init_capacity == 0){
        return NULL;
    }

    adt_arr* obj = malloc(sizeof(adt_arr));
    obj->data = malloc(init_capacity * sizeof(TYPE));
    obj->capacity = init_capacity;
    obj->size = 0;

    //prevents dangling pointers.
    for(i = 0; i < init_capacity + 1;i++){
        obj->data[i] = NULL;
    }

    return obj;
}

void _adt_arrFreeData(adt_arr* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        SAFE_FREE(obj->data[i]);
    }
}

int adt_arrFree(adt_arr* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }

    _adt_arrFreeData(obj,0,obj->capacity); 

    free(obj->data);
    SAFE_FREE(obj);

    return EXIT_SUCCESS;
}

int adt_arrSize(adt_arr* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size;
}

TYPE adt_arrGet(adt_arr* obj, int idx)
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

TYPE adt_arrSet(adt_arr* obj,int idx, TYPE item)
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

int adt_arrClearItem(adt_arr* obj,int idx){
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

adt_arr* adt_arrResize(adt_arr* obj, int newcapacity)
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
        _adt_arrFreeData(obj,newcapacity,obj->capacity);
    }

    free(obj->data);
    obj->data = Newdata;
    obj->capacity = newcapacity;

    return obj;
}

int adt_arrInsert(adt_arr* obj, int idx, TYPE item)
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

    adt_arrSet(obj,idx,item);

    return EXIT_SUCCESS;
}

int adt_arrRemove(adt_arr* obj, int idx)
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

    adt_arr* arr = adt_arrCreate(100);
    printf("arrayCap:%d\n",arr->capacity);

    adt_arrSet(arr,88,&item1);
    adt_arrResize(arr,10);
    printf("arrayCap:%d\n",arr->capacity);

    
    adt_arrSet(arr,0,&item1);
    
    int temp = *(int*)adt_arrGet(arr,0);
    printf(":::%d\n",temp);

    adt_arrClearItem(arr,0);

    item1 = 69;
    adt_arrInsert(arr,3,&item1);
    adt_arrRemove(arr,3);

    // temp = *(int*)adt_arrGet(arr,3);
    // printf(":::%d\n",temp);

    adt_arrFree(arr);


    return 0;
}