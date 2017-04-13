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

#define SAFE_FREE(x) do { if ((x) != NULL) {free(x); x=NULL;} } while(0)

typedef void* TYPE;

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    TYPE* data;
} adtStk;

adtStk* adtStk_Create(int init_capacity)
{
    int i;
    
    if(init_capacity == 0){
        return NULL;
    }

    adtStk* obj = malloc(sizeof(adtStk));

    obj->data = malloc(init_capacity * sizeof(TYPE));
    obj->capacity = init_capacity;
    obj->size = 0;

    //prevents dangling pointers.
    for(i = 0; i < init_capacity + 1;i++){
        obj->data[i] = NULL;
    }

    return obj;
}

void _adtStk_FreeData(adtStk* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        SAFE_FREE(obj->data[i]);
    }
}

int adtStk_Free(adtStk* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }  

    _adtStk_FreeData(obj,0,obj->capacity);

    free(obj->data);
    SAFE_FREE(obj);

    return EXIT_SUCCESS;
}

int adtStk_Size(adtStk* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size;
}

TYPE adtStk_Top(adtStk* obj)
{
    if(obj == NULL){
        return NULL;
    } else if(obj->size == 0) {
        return NULL;
    }

    return obj->data[obj->size -1];
}

int adtStk_Push(adtStk* obj, TYPE item)
{
    if(obj == NULL || item == NULL){
        return EXIT_FAILURE;
    } else if(obj->size == obj->capacity) {
        return EXIT_FAILURE;
    }

    TYPE temp_item = malloc(sizeof(item));
    memcpy(temp_item,item,sizeof(TYPE));
    obj->size++;
    obj->data[obj->size -1] = temp_item;

    return EXIT_SUCCESS;
}

int adtStk_Pop(adtStk* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    } else if(obj->size == 0) {
        return EXIT_FAILURE;
    }
    
    SAFE_FREE(obj->data[obj->size -1]);
    obj->size--;

    return EXIT_FAILURE;
}

adtStk* adtStk_Resize(adtStk* obj, int newcapacity)
{
    if(obj == NULL || newcapacity <= 0){
        return NULL;
    }

    int i;
    TYPE* newdata = malloc(newcapacity * sizeof(TYPE));
    
    for(i = 0; i < newcapacity;i++){
        //swapping pointers to items.
        newdata[i] = obj->data[i];
    }

    if((newcapacity - obj->capacity) > 0){
        if(obj->size > newcapacity){
            obj->size -= newcapacity; 
        }
        _adtStk_FreeData(obj,newcapacity,obj->capacity);
    }

    free(obj->data);
    obj->data = newdata;
    obj->capacity = newcapacity;

    return obj;
}

int main()
{
    int i;

    adtStk* arr = adtStk_Create(100);
    

    for(i =0;i< 100;i++){
        adtStk_Push(arr,&i);
    }

    adtStk_Resize(arr,10);
    
    //int 
    int temp = *(int*)arr->data[9]; 
    //temp = *(int*)adtStk_Top(arr); 

    printf("SIZE:::%d\n",adtStk_Size(arr));  

    adtStk_Pop(arr);
    printf(":::%d\n",temp);
    adtStk_Pop(arr);

    adtStk_Free(arr);

    return 0;
}