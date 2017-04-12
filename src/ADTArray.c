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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    void** data;
} ADTArray;

ADTArray* ADTArrayCreate(int init_capacity)
{
    int i;

    if(init_capacity == 0){
        return NULL;
    }

    ADTArray* obj = malloc(sizeof(ADTArray));
    obj->data = malloc(init_capacity * sizeof(void*));
    obj->capacity = init_capacity;
    obj->size = 0;

    for(i = 0; i < init_capacity + 1;i++){
        obj->data[i] = NULL;
    }

    return obj;
}

void _ADTArrayFreeData(ADTArray* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        if(obj->data[i] != NULL){
            free(obj->data[i]);
        }
    }
}

int ADTArrayFree(ADTArray* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }

    _ADTArrayFreeData(obj,0,obj->capacity); 

    free(obj->data);
    free(obj);

    return EXIT_SUCCESS;
}

int ADTArraySize(ADTArray* obj){
    if(obj == NULL){
        return -1;
    }
    
    return obj->size;
}

void* ADTArrayGet(ADTArray* obj, int idx)
{
    if(obj == NULL){
        return NULL;
    } else if(obj->capacity <= idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->Current -1;
    }

    return obj->data[idx];
}

void* ADTArraySet(ADTArray* obj,int idx, void* item)
{
    if(obj == NULL || idx < 0){
        return NULL;
    } else if(obj->capacity <= idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->Current -1;
    }

    void* temp_item = malloc(sizeof(void*));
    memcpy(temp_item,item,sizeof(void*));
    obj->size++;

    return obj->data[idx] = temp_item;
}

int ADTArrayClearItem(ADTArray* obj,int idx){
    if(obj == NULL || idx < 0){
        return EXIT_FAILURE;
    } else if(obj->capacity >= idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->Current -1;
    }

    free(obj->data[idx]);
    obj->data[idx] = NULL;
    obj->size--;

    return EXIT_SUCCESS;
}

ADTArray* ADTArrayResize(ADTArray* obj, int newcapacity)
{
    if(obj == NULL || newcapacity <= 0){
        return NULL;
    }

    int i;
    void** Newdata = malloc(newcapacity * sizeof(void*));
    
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

int ADTArrayInsert(ADTArray* obj, int idx, void* item)
{
    int i;

    if(obj == NULL || idx < 0){
        return EXIT_FAILURE;
    } else if(obj->capacity <= idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->Current -1;
    }

    for(i = idx; i < obj->capacity - 1;i++){
        obj->data[i + 1] = obj->data[i]; 
    }

    void* temp_item = malloc(sizeof(void*));
    memcpy(temp_item,item,sizeof(void*));

    obj->size++;
    obj->data[idx] = temp_item;

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
        idx = obj->Current -1;
    }

    free(obj->data[idx]);

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
    //ADTArrayRemove(arr,3);

    temp = *(int*)ADTArrayGet(arr,3);
    printf(":::%d\n",temp);

    ADTArrayFree(arr);


    return 0;
}