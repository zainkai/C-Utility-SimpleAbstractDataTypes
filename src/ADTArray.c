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
 **   CONTIGUOUS ARRAY LIBRARY   **
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
} adtArr;

adtArr* adtArr_Create(int init_capacity)
{
    int i;

    if(init_capacity == 0){
        return NULL;
    }

    adtArr* obj = malloc(sizeof(adtArr));
    obj->data = malloc(init_capacity * sizeof(TYPE));
    obj->capacity = init_capacity;
    obj->size = 0;

    //prevents dangling pointers.
    for(i = 0; i < init_capacity + 1;i++){
        obj->data[i] = NULL;
    }

    return obj;
}

void _adtArr_FreeData(adtArr* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        SAFE_FREE(obj->data[i]);
    }
}

int adtArr_Free(adtArr* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }

    _adtArr_FreeData(obj,0,obj->capacity); 

    free(obj->data);
    SAFE_FREE(obj);

    return EXIT_SUCCESS;
}

int adtArr_Size(adtArr* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size;
}

int adtArr_Index(adtArr* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size -1;
}

int adtArr_ChkNull(adtArr* obj, int idx)
{
    if(obj == NULL || idx < -1){
        return EXIT_FAILURE;
    } else if(idx >= obj->capacity || obj->size < idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    return obj->data[idx] == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
}

TYPE adtArr_Get(adtArr* obj, int idx)
{
    if(obj == NULL || idx < -1){
        return NULL;
    } else if(idx >= obj->capacity || obj->size < idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    return obj->data[idx];
}

TYPE _adtArr_Save(adtArr* obj,int idx, TYPE item)
{
    TYPE temp_item = malloc(sizeof(item));
    memcpy(temp_item,item,sizeof(TYPE));
    obj->size++;

    return obj->data[idx] = temp_item;
}

TYPE adtArr_Set(adtArr* obj,int idx, TYPE item)
{
    if(obj == NULL || item == NULL || idx < -1){
        return NULL;
    } else if(idx >= obj->capacity || obj->size < idx) {
        return NULL;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    return _adtArr_Save(obj,idx,item);
}

//UNSAFE can cause array to be non contiguous.
int _adtArr_ClearItem(adtArr* obj,int idx){
    if(obj == NULL || idx < -1){
        return EXIT_FAILURE;
    } else if(idx >= obj->capacity || obj->size < idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size -1;
    }

    SAFE_FREE(obj->data[idx]);
    obj->size--;

    return EXIT_SUCCESS;
}

adtArr* adtArr_Resize(adtArr* obj, int newcapacity)
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
        _adtArr_FreeData(obj,newcapacity,obj->capacity);
    }

    free(obj->data);
    obj->data = Newdata;
    obj->capacity = newcapacity;

    return obj;
}

int adtArr_Insert(adtArr* obj, int idx, TYPE item)
{
    int i;

    if(obj == NULL || item == NULL || idx < -1){
        return EXIT_FAILURE;
    } else if(idx >= obj->capacity || obj->size < idx) {
        return EXIT_FAILURE;
    } else if(idx == -1) {
        idx = obj->size;
    }

    for(i = idx; i < obj->capacity - 1;i++){
        obj->data[i + 1] = obj->data[i]; 
    }

    _adtArr_Save(obj,idx,item);

    return EXIT_SUCCESS;
}

int adtArr_addItem(adtArr* obj, TYPE item)
{
    if(obj == NULL || item == NULL){
        return EXIT_FAILURE;
    } else if(obj->capacity <= obj->size) {
        return EXIT_FAILURE;
    }

    _adtArr_Save(obj,obj->size-1,item);
    return EXIT_SUCCESS;
}

int adtArr_Remove(adtArr* obj, int idx)
{
    int i;

    if(obj == NULL || idx < -1){
        return EXIT_FAILURE;
    } else if(idx >= obj->capacity || obj->size < idx) {
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

    adtArr* arr = adtArr_Create(100);
    printf("arrayCap:%d\n",arr->capacity);

    adtArr_Set(arr,88,&item1);
    adtArr_Resize(arr,10);
    printf("arrayCap:%d\n",arr->capacity);

    
    adtArr_Set(arr,0,&item1);
    
    int temp = *(int*)adtArr_Get(arr,0);
    printf(":::%d\n",temp);

    // adtArrClearItem(arr,0);

    item1 = 69;
    adtArr_Insert(arr,3,&item1);
    adtArr_Remove(arr,3);

    // temp = *(int*)adtArr_Get(arr,3);
    // printf(":::%d\n",temp);

    adtArr_Free(arr);


    return 0;
}