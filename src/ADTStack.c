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
} ADTStack;

ADTStack* ADTStackCreate(int capacity)
{
    if(capacity == 0){
        return NULL;
    }

    ADTStack* obj = malloc(sizeof(ADTStack));

    obj->data = malloc(capacity * sizeof(TYPE));
    obj->capacity = capacity;
    obj->size = 0;

    return obj;
}

void _ADTStackFreeData(ADTStack* obj, unsigned int minidx,unsigned int maxidx){
    int i;

    for(i = minidx; i < maxidx +1; i++){
        SAFE_FREE(obj->data[i]);
    }
}

int ADTStackFree(ADTStack* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }  

    _ADTStackFreeData(obj,0,obj->capacity);

    free(obj->data);
    SAFE_FREE(obj);

    return EXIT_SUCCESS;
}

int ADTStackSize(ADTStack* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    }
    
    return obj->size;
}

TYPE ADTStackTop(ADTStack* obj)
{
    if(obj == NULL){
        return NULL;
    } else if(obj->size == 0) {
        return NULL;
    }

    return obj->data[obj->size -1];
}

TYPE ADTStackPush(ADTStack* obj, TYPE item)
{
    if(obj == NULL || item == NULL){
        return NULL;
    } else if(obj->size == obj->capacity) {
        return NULL;
    }

    TYPE temp_item = malloc(sizeof(item));
    memcpy(temp_item,item,sizeof(TYPE));
    obj->size++;

    return obj->data[obj->size -1] = temp_item;
}

int ADTStackPop(ADTStack* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    } else if(obj->size == 0) {
        return EXIT_FAILURE;
    }
    
    SAFE_FREE(obj->data[obj->size -1]);
    obj->size--;

    return EXIT_FAILURE;
}

ADTStack* ADTStackResize(ADTStack* obj, int newcapacity)
{
    if(obj == NULL || newcapacity < 0){
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
        _ADTStackFreeData(obj,newcapacity,obj->capacity);
    }

    free(obj->data);
    obj->data = newdata;
    obj->capacity = newcapacity;

    return obj;
}

int main()
{
    int i;

    ADTStack* arr = ADTStackCreate(100);
    

    for(i =0;i< 100;i++){
        ADTStackPush(arr,&i);
    }

    ADTStackResize(arr,10);
    
    //int 
    int temp = *(int*)arr->data[9]; 
    //temp = *(int*)ADTStackTop(arr); 

    printf("SIZE:::%d\n",ADTStackSize(arr));  

    ADTStackPop(arr);
    printf(":::%d\n",temp);
    ADTStackPop(arr);

    ADTStackFree(arr);

    return 0;
}