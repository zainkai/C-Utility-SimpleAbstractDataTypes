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
    int Current;
    int Capacity;
    void** Data;
} ADTArray;

ADTArray* ADTArrayCreate(int Capacity)
{
    if(Capacity == 0){
        return NULL;
    }

    int i;

    ADTArray* obj = malloc(sizeof(ADTArray));
    obj->Data = malloc(Capacity * sizeof(void*));

    for(i = 0;i < Capacity; i++){
        obj->Data[i] = NULL;
    }

    obj->Capacity = Capacity;
    obj->Current = 0;

    return obj;
}

void _ADTArrayFreeData(void** Data, int MinIdx,int MaxIdx){
    int i;

    for(i = MinIdx; i < MaxIdx +1; i++){
        if(Data[i] != NULL){
            free(Data[i]);
        }
    }
}

void ADTArrayFree(ADTArray* obj)
{
    if(obj == NULL){
        return;
    }  

    _ADTArrayFreeData(obj->Data,0,obj->Capacity); 

    free(obj->Data);
    free(obj);
}

int ADTArraySize(ADTArray* obj){
    if(obj == NULL){
        return -1;
    }
    
    return obj->Current;
}

void* ADTArrayGet(ADTArray* obj, int idx)
{
    if(obj == NULL){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->Current -1;
    }

    return obj->Data[idx];
}

void* ADTArraySet(ADTArray* obj,int idx, void* item)
{
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->Capacity < idx){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->Current -1;
    }

    void* TempItem = malloc(sizeof(void*));
    memcpy(TempItem,item,sizeof(void*));
    obj->Current++;

    return obj->Data[idx] = TempItem;
}

ADTArray* ADTArrayClearItem(ADTArray* obj,int idx){
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->Capacity < idx || (obj->Data[idx] == NULL)){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->Current -1;
    }

    free(obj->Data[idx]);
    obj->Data[idx] = NULL;
    obj->Current--;

    return obj;
}

ADTArray* ADTArrayResize(ADTArray* obj, int NewCapacity)
{
    if(obj == NULL || NewCapacity < 0){
        return NULL;
    }

    int i;
    void** NewData = malloc(NewCapacity * sizeof(void*));
    
    for(i = 0; i < NewCapacity;i++){
        //swapping pointers to items.
        NewData[i] = obj->Data[i];
    }

    //check if offset is negative
    if((obj->Capacity - NewCapacity) < 0){
        if(obj->Current > NewCapacity){
            obj->Current -= NewCapacity; 
        }
        _ADTArrayFreeData(obj->Data,NewCapacity,obj->Capacity);
    }

    free(obj->Data);
    obj->Data = NewData;
    obj->Capacity = NewCapacity;

    return obj;
}

void* ADTArrayInsert(ADTArray* obj, int idx, void* item)
{
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->Current == obj->Capacity){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->Current -1;
    }

    int i;

    for(i = obj->Current; i > idx;i--){
        obj->Data[i] = obj->Data[i -1]; 
    }

    obj->Current++;

    return obj->Data[idx] = item;
}

void ADTArrayRemove(ADTArray* obj, int idx)
{
    if(obj == NULL || idx < -1){
        return;
    }
    else if(idx == -1){
        idx = obj->Current -1;
    }

    int i;

    free(obj->Data[idx]);

    for(i = idx; i < obj->Current - 1; i++){
        obj->Data[i] = obj->Data[i+1];
    }

    obj->Current--;
}


// int main()
// {
//     ADTArray* arr = ADTArrayCreate(100);
//     ADTArrayResize(arr,50);

//     int item1 = 1;
//     ADTArraySet(arr,0,&item1);
    
//     int temp = *(int*)ADTArrayGet(arr,0);
//     printf(":::%d\n",temp);

//     ADTArrayClearItem(arr,0);

//     ADTArrayFree(arr);
//     return 0;
// }