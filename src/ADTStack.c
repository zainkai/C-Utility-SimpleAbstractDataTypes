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
    size_t size;
    size_t capacity;
    void** data;
} ADTStack;

ADTStack* ADTStackCreate(int capacity)
{
    if(capacity == 0){
        return NULL;
    }

    ADTStack* obj = malloc(sizeof(ADTStack));

    obj->data = malloc(capacity * sizeof(void*));
    obj->capacity = capacity;
    obj->size = 0;

    return obj;
}

int ADTStackFree(ADTStack* obj)
{
    if(obj == NULL){
        return EXIT_FAILURE;
    }  

    free(obj->data);
    free(obj);

    return EXIT_SUCCESS;
}

int ADTStackSize(ADTStack* obj){
    if(obj == NULL){
        return -1;
    }
    
    return obj->size;
}

void* ADTStackTop(ADTStack* obj)
{
    if(obj == NULL){
        return NULL;
    }

    return obj->data[obj->size -1];
}

void* ADTStackPush(ADTStack* obj, void* item)
{
    if(obj == NULL){
        return NULL;
    }
    else if(obj->size == obj->capacity){
        return NULL;
    }

    void* TempItem = malloc(sizeof(void*));
    memcpy(TempItem,item,sizeof(void*));
    obj->size++;

    return obj->data[obj->size -1] = TempItem;
}

int ADTStackPop(ADTStack* obj){
    if(obj == NULL){
        return EXIT_FAILURE;
    } else if(obj->size <= 0) {
        return EXIT_FAILURE;
    }
    
    free(obj->data[obj->size -1]);
    obj->data[obj->size -1] = NULL;
    obj->size--;

    return EXIT_FAILURE;
}

ADTStack* ADTStackResize(ADTStack* obj, int Newcapacity)
{
    if(obj == NULL || Newcapacity < 0){
        return NULL;
    }

    int i;
    void** Newdata = malloc(Newcapacity * sizeof(void*));
    
    for(i = 0; i < Newcapacity;i++){
        //swapping pointers to items.
        Newdata[i] = obj->data[i];
    }

    free(obj->data);
    obj->data = Newdata;
    obj->capacity = Newcapacity;

    return obj;
}

int main()
{
    ADTStack* arr = ADTStackCreate(100);
    ADTStackResize(arr,50);

    int item1 = 1;
    ADTStackPush(arr,&item1);
    
    int temp = *(int*)ADTStackTop(arr);
    

    ADTStackPop(arr);
    printf(":::%d\n",temp);
    ADTStackPop(arr);

    ADTStackFree(arr);

    return 0;
}